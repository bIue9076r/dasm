#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dasm_type.h>
#include <dasm_cpu.h>
#include <dasm_alu.h>
#include <dasm_inst_set.h>
#include <dasm_inst_switch.h>

static File f;

Adafruit_SSD1306 display;

void setup() {
	Serial.begin(9600);
	SD.begin();

	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		for(;;);
	}

	// Read File or default rom
	f = SD.open("main.rom",FILE_READ);
	if()
}

void display_handler(){
	// Do things when display is called
}

void interupt_handler(){
	// Do things with A and values on stack
}

void loop(){
	while(!(FL & FLAG_HALT)){
		byte inst = ROM[ADDR++];
		SwitchInst(inst);
		
		if(FL & FLAG_DIS > 0){
			display_handler();
		}

		if(FL & FLAG_INT > 0){
			interupt_handler();
		}
	}
}
