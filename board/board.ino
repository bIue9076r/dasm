#include <SPI.h>
#include <SD.h>
#include <Tiny4kOLED.h>
#include <dasm_type.h>
#include <dasm_cpu.h>
#include <dasm_alu.h>
#include <dasm_inst_set.h>
#include <dasm_inst_switch.h>

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
	StackMem.seek(SK++);
	byte r = StackMem.read();
	StackMem.close();
	return r;
}

void StkPut(uint8_t b){
	StackMem = SD.open(Stk_F,O_RDWR);
	StackMem.seek(SK--);
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
	SetRom(0x1, 0x01);
	SetRom(0x2, I_INC);
	SetRom(0x3, I_JUMP);
	SetRom(0x4, 0x00);
	SetRom(0x5, 0x00);
}

void display_handler(){
	// Do things when display is called
}

void interupt_handler(uint8_t in){
	// Do things with A and values on stack
	// Serial.println("Interupted");
	// Serial.println(A);
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
	delay(1000);
}

void loop(){
	while(!(FL & FLAG_HALT)){
		uint8_t inst = RomFetch();
		SwitchInst(inst);
		
		if((FL & FLAG_DIS) > 0){
			display_handler();
		}

		if((FL & FLAG_INT) > 0){
			interupt_handler(inst);
		}
	}
	// delay(50);
}
