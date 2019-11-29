/*
 * MENUS.c
 *
 *  Created on: 2019年11月23日
 *      Author: cal
 */

#include "MENUS.h"

extern Word_Module WordTable[];
extern uint8_t CharTable[][17];
extern uint8_t buttons_counter;

typedef struct GUI_menu{
	void(* menu_handler)();

}GUI_MENU;

GUI_MENU gui_menus[8];
uint8_t gui_menus_counter=0;

uint8_t menu01_button_flag=0;

uint16_t menu01_button_new_click=0;

uint8_t warehouseStatus[4]={0,0,0,0};
uint8_t carStatus=0;

uint8_t menu_flag=0;

uint8_t stm_flag=0;
uint8_t ldm_flag=0;
uint8_t warehouse_choice=0;

extern BUTTON_S buttons[];

void  menu01_buttons_handler(uint8_t val){
	menu01_button_flag=val;
	menu01_button_new_click=1;
}

uint8_t menu01_last_button_flag=0;	//只记录小于4的值， 也就是warehouse的按钮

void menu01_handler(){
	if(menu01_button_new_click){

		if((menu01_last_button_flag<255)){
			if((carStatus!=warehouseStatus[menu01_last_button_flag])){
				if(carStatus){
					if(menu01_button_flag==5){
						warehouse_choice=menu01_last_button_flag;
						stm_flag=1;
						menu_flag=2;
					}
				}else{
					if(menu01_button_flag==4){
						warehouse_choice=menu01_last_button_flag;
						ldm_flag=1;
						menu_flag=2;
					}
				}
			}
		}else{

		}

		if((menu01_button_flag==7)&&(menu01_last_button_flag<255)){
			warehouseStatus[menu01_last_button_flag]=!warehouseStatus[menu01_last_button_flag];

			if(warehouseStatus[menu01_last_button_flag]){
				buttons[menu01_last_button_flag].back_color=0xffff;
			}else{
				buttons[menu01_last_button_flag].back_color=0x0000;
			}
			buttons[7].back_color=buttons[menu01_last_button_flag].back_color;
			drawButton(buttons[menu01_last_button_flag].name, buttons[menu01_last_button_flag].start_x, buttons[menu01_last_button_flag].start_y, buttons[menu01_last_button_flag].end_x, buttons[menu01_last_button_flag].end_y, buttons[menu01_last_button_flag].font_color, buttons[menu01_last_button_flag].back_color, 0xf800);

			drawButton(buttons[7].name, buttons[7].start_x, buttons[7].start_y, buttons[7].end_x, buttons[7].end_y, buttons[7].font_color, buttons[7].back_color, buttons[7].border_color);

		}

		if(menu01_button_flag==6){
			carStatus=!carStatus;
			if(carStatus){
				buttons[6].back_color=0xffff;
			}else{
				buttons[6].back_color=0x0000;
			}
			drawButton(buttons[6].name, buttons[6].start_x, buttons[6].start_y, buttons[6].end_x, buttons[6].end_y, buttons[6].font_color, buttons[6].back_color, buttons[6].border_color);
		}

		if((menu01_button_flag!=menu01_last_button_flag)&&(menu01_button_flag<4)){

			buttons[7].back_color = buttons[menu01_button_flag].back_color;

			if(menu01_last_button_flag<255){
				drawButton(buttons[menu01_last_button_flag].name, buttons[menu01_last_button_flag].start_x, buttons[menu01_last_button_flag].start_y, buttons[menu01_last_button_flag].end_x, buttons[menu01_last_button_flag].end_y, buttons[menu01_last_button_flag].font_color, buttons[menu01_last_button_flag].back_color, buttons[menu01_last_button_flag].border_color);
			}
			menu01_last_button_flag = menu01_button_flag;

			drawButton(buttons[menu01_button_flag].name, buttons[menu01_button_flag].start_x, buttons[menu01_button_flag].start_y, buttons[menu01_button_flag].end_x, buttons[menu01_button_flag].end_y, buttons[menu01_button_flag].font_color, buttons[menu01_button_flag].back_color, 0xf800);
			drawButton(buttons[7].name, buttons[7].start_x, buttons[7].start_y, buttons[7].end_x, buttons[7].end_y, buttons[7].font_color, buttons[7].back_color, buttons[7].border_color);

			if(carStatus!=warehouseStatus[menu01_button_flag]){
				//	drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, buttons[5].font_color, buttons[5].back_color, buttons[5].border_color);
				if(carStatus){	//状态， 0为空， 1为满
					drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0x3800, 0x39e7, 0x01e0);
					drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0xf800, 0xffff, 0x07e0);
				}else{
					drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0xf800, 0xffff, 0x07e0);
					drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0x3800, 0x39e7, 0x01e0);
				}
			}else{
				drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0x3800, 0x39e7, 0x01e0);
				drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0x3800, 0x39e7, 0x01e0);
			}
		}

		if(((menu01_button_flag==6)||(menu01_button_flag==7))&&(menu01_last_button_flag<255)){
			if(carStatus!=warehouseStatus[menu01_last_button_flag]){
				//	drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, buttons[5].font_color, buttons[5].back_color, buttons[5].border_color);
				if(carStatus){	//状态， 0为空， 1为满
					drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0x3800, 0x39e7, 0x01e0);
					drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0xf800, 0xffff, 0x07e0);
				}else{
					drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0xf800, 0xffff, 0x07e0);
					drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0x3800, 0x39e7, 0x01e0);
				}
			}else{
				drawButton(buttons[4].name, buttons[4].start_x, buttons[4].start_y, buttons[4].end_x, buttons[4].end_y, 0x3800, 0x39e7, 0x01e0);
				drawButton(buttons[5].name, buttons[5].start_x, buttons[5].start_y, buttons[5].end_x, buttons[5].end_y, 0x3800, 0x39e7, 0x01e0);
			}
		}



		menu01_button_new_click=0;
	}
}



void GUI_Menu01_Create(void(*menu_handler)(), uint8_t id){
	buttons_counter=0;
	gui_menus_counter=0;
	menu01_last_button_flag=255;
	clearScreen(0x0000);
	warehouse_choice=255;

	uint32_t tmpColor=0;
	if(warehouseStatus[0]){
		tmpColor=0xffff;
	}else{
		tmpColor=0x0000;
	}
	ButtonCreate("FIRST", buttons_counter, 5, 100, 55, 130, menu01_buttons_handler, 0xf800, tmpColor, 0x07e0);
	if(warehouseStatus[1]){
		tmpColor=0xffff;
	}else{
		tmpColor=0x0000;
	}
	ButtonCreate("SECOND", buttons_counter, 5+60, 100, 55+60, 130, menu01_buttons_handler, 0xf800, tmpColor, 0x07e0);
	if(warehouseStatus[2]){
		tmpColor=0xffff;
	}else{
		tmpColor=0x0000;
	}
	ButtonCreate("THIRD", buttons_counter, 5+60*2, 100, 55+60*2, 130, menu01_buttons_handler, 0xf800, tmpColor, 0x07e0);
	if(warehouseStatus[3]){
		tmpColor=0xffff;
	}else{
		tmpColor=0x0000;
	}
	ButtonCreate("FOURTH", buttons_counter, 5+60*3, 100, 55+60*3, 130, menu01_buttons_handler, 0xf800, tmpColor, 0x07e0);

	ButtonCreate("LDM", buttons_counter, 45, 100+60, 115, 130+70, menu01_buttons_handler, 0x3800, 0x39e7, 0x01e0);
	ButtonCreate("STM", buttons_counter, 125, 100+60, 195, 130+70, menu01_buttons_handler, 0x3800, 0x39e7, 0x01e0);

	if(carStatus){
		tmpColor=0xffff;
	}else{
		tmpColor=0x0000;
	}

	ButtonCreate("Car Status", buttons_counter, 25, 240, 95, 280, menu01_buttons_handler, 0xf800, tmpColor, 0x7e0);	//ID = 6
	ButtonCreate("War Status", buttons_counter, 145, 240, 215, 280, menu01_buttons_handler, 0xf800, tmpColor, 0x7e0);	//ID = 7


	gui_menus[id].menu_handler=menu_handler;
	gui_menus_counter++;

}

void GUI_Menu01_Scan(){
	ScreenScan();
	Button_dothings();
	gui_menus[0].menu_handler();
}


void Menu01_loop(){

	if(menu_flag==1){
		GUI_Menu01_Create(menu01_handler, 0);

		while(menu_flag==1){
			GUI_Menu01_Scan();
		}
	}
}

uint8_t car_location=0;

void Menu02_handler(){
	delay_ms(1000);
	if(stm_flag){
		stm_flag=0;
		warehouseStatus[warehouse_choice]=1;
		carStatus=0;
	}

	if(ldm_flag){
		ldm_flag=0;
		warehouseStatus[warehouse_choice]=0;
		carStatus=1;
	}

	menu_flag=1;

}

void GUI_Menu02_Scan(){
	ScreenScan();
	Button_dothings();
	gui_menus[0].menu_handler();
}

void GUI_Menu02_Create(void(*menu_handler)(), uint8_t id){

	clearScreen(0x0000);

	gui_menus_counter=0;
	buttons_counter=0;

	drawSquare(60, 40, 65, 280, 0x07e0);
	drawSquare(60, 40, 180, 45, 0x07e0);
	drawSquare(60, 40+60, 180, 45+60, 0x07e0);
	drawSquare(60, 40+60*2, 180, 45+60*2, 0x07e0);
	drawSquare(60, 40+60*3, 180, 45+60*3, 0x07e0);

	switch(car_location){
	case 0:
		drawSquare(60-10, 280, 60+10, 300, 0xf800);
		break;
	case 2:
		drawSquare(60-10, 280-60, 60+10, 300-60, 0xf800);
		break;
	case 4:
		drawSquare(60-10, 280-60*2, 60+10, 300-60*2, 0xf800);
		break;
	case 6:
		drawSquare(60-10, 280-60*3, 60+10, 300-60*3, 0xf800);
		break;
	case 8:
		drawSquare(60-10, 280-60*4, 60+10, 300-60*4, 0xf800);
		break;
	case 1:
		drawSquare(60+120, 280-60, 60+120+20, 300-60, 0xf800);
		break;
	case 3:
		drawSquare(60+120, 280-60*2, 60+120+20, 300-60*2, 0xf800);
		break;
	case 5:
		drawSquare(60+120, 280-60*3, 60+120+20, 300-60*3, 0xf800);
		break;
	case 7:
		drawSquare(60+120, 280-60*4, 60+120+20, 300-60*4, 0xf800);
		break;
	}

	gui_menus[id].menu_handler=menu_handler;

	gui_menus_counter++;
}

void Menu02_loop(){
	if(menu_flag==2){

		GUI_Menu02_Create(Menu02_handler, 0);

	while(menu_flag==2){

		car_location++;

		GUI_Menu02_Create(Menu02_handler, 0);

		GUI_Menu02_Scan();
	}

	}
}
