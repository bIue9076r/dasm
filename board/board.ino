#include <SPI.h>
#include <SD.h>
#include <Tiny4kOLED.h>
#include <dasm_type.h>
#include <dasm_cpu.h>
#include <dasm_alu.h>
#include <dasm_inst_set.h>
#include <dasm_inst_switch.h>

// #define DEBUG_INFO

static File f;
static File FlashMem;
static File StackMem;
static File RomFile;

static char* Fls_F = "flash.mem";
static char* Stk_F = "stack.mem";
static char* Rom_F = "main.rom";

void BlankSD(void){
	// Read File or default rom
	char block[0x100] = {0};
	SD.remove(Stk_F);
	StackMem = SD.open(Stk_F,FILE_WRITE);
	StackMem.write(block,0x100);
	StackMem.close();
	Serial.println("Stack done");

	SD.remove(Fls_F);
	FlashMem = SD.open(Fls_F,FILE_WRITE);
	for(int i = 0; i < 0x8; i++){
		Serial.print("Flash Block [");
		Serial.print(i + 1);
		Serial.println("] done");
		FlashMem.write(block,0x100);
	}
	FlashMem.close();
	Serial.println("Flash done");

	SD.remove(Rom_F);
	RomFile = SD.open(Rom_F,FILE_WRITE);
	for(int i = 0; i < 0x80; i++){
		Serial.print("Rom Block [");
		Serial.print(i + 1);
		Serial.println("] done");
		RomFile.write(block,0x100);
	}
	RomFile.close();
	Serial.println("Rom done");
}

uint8_t GetRom(uint16_t addr){
	RomFile = SD.open(Rom_F,O_RDWR);
	RomFile.seek(addr);
	byte r = RomFile.read();
	RomFile.close();
	return r;
}

void SetRom(uint16_t addr, uint8_t b){
	RomFile = SD.open(Rom_F,O_RDWR);
	RomFile.seek(addr);
	RomFile.write(b);
	RomFile.close();
}

uint8_t GetMem(uint16_t addr){
	FlashMem = SD.open(Fls_F,O_RDWR);
	FlashMem.seek(addr);
	byte r = FlashMem.read();
	FlashMem.close();
	return r;
}

void SetMem(uint16_t addr, uint8_t b){
	FlashMem = SD.open(Fls_F,O_RDWR);
	FlashMem.seek(addr);
	FlashMem.write(b);
	FlashMem.close();
}

uint8_t StkPop(){
	StackMem = SD.open(Stk_F,O_RDWR);
	StackMem.seek(++SK);
	byte r = StackMem.read();
	StackMem.close();
	return r;
}

void StkPut(uint8_t b){
	StackMem = SD.open(Stk_F,O_RDWR);
	StackMem.seek(--SK);
	StackMem.write(b);
	StackMem.close();
}

void setup() {
	SD.begin();
	Serial.begin(9600);
	
	oled.begin();
	oled.setFont(FONT6X8);
	oled.clear();
	oled.on();
	oled.switchRenderFrame();

	SetRom(0x0, I_SEND);
	SetRom(0x1, 0xF9);
	SetRom(0x2, I_INC);
	SetRom(0x3, I_JEQU);
	SetRom(0x4, 0x10);
	SetRom(0x5, 0x00);
	SetRom(0x6, 0x2D);
	SetRom(0x7, I_LDBI);
	SetRom(0x8, 0x2);
	SetRom(0x9, I_PUB);
	SetRom(0xA, I_POC);
	SetRom(0xB, 0x00);
	SetRom(0xC, 0x00);
	SetRom(0xD, 0x00);
	SetRom(0x2A, I_JUMP);
	SetRom(0x2B, 0x00);
	SetRom(0x2C, 0x00);
	SetRom(0x2D, I_SEND);
	SetRom(0x2E, 0x0F);
	SetRom(0x2F, 0xFF);
}

void display_handler(){
	// Do things when display is called
}

void display_info(uint8_t in){
	oled.clear();
	oled.setCursor(0, 0);
	oled.print("A: ");
	oled.print(A);
	oled.setCursor(0, 1);
	oled.print("B: ");
	oled.print(B);
	oled.setCursor(0, 2);
	oled.print("C: ");
	oled.print(C);
	oled.setCursor(0, 3);
	oled.print("AD: ");
	oled.print(ADDR);
	oled.setCursor(64, 0);
	oled.print("SK: ");
	oled.print(SK);
	oled.setCursor(64, 1);
	oled.print("FL: ");
	oled.print(FL);
	oled.setCursor(64, 3);
	oled.print("IS: ");
	oled.print(in);
	oled.switchFrame();
}

void interupt_handler(uint8_t in){
	// Do things with A and values on stack
	switch(in){
		case 0x0:
			// bogus
		break;

		case 0x01:
			// same as DIS
			display_handler();
		break;

		case 0xF9:
			// info
			display_info(I_SEND);
		break;

		case 0x0F:
			// Halt
			oled.clear();
			oled.setCursor(0, 0);
			oled.print("Halted!");
			oled.switchFrame();
		break;
	}

	FL = FL & (~FLAG_INT);
}

void loop(){
	while(!(FL & FLAG_HALT)){
		uint8_t inst = RomFetch();
		SwitchInst(inst);
		
		if((FL & FLAG_DIS) > 0){
			display_handler();
		}

		#ifdef DEBUG_INFO
		display_info(inst);
		#endif

		if((FL & FLAG_INT) > 0){
			byte itn = RomFetch();
			interupt_handler(itn);
		}
	}
	// delay(50);
}
