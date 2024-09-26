/*
 * i2c_lcd.c
 *
 *  Created on: Sep 24, 2024
 *      Author: asus
 */
#include "i2c_lcd.h"
#include "i2c.h"

void WriteByteandCtrl(uint8_t val){
		I2C_Start();
		I2C_SendSlavAdd(LCD_SLAVE_ADD_W);
		I2C_Data(val);
		I2C_Stop();


}
void WriteByte(uint8_t rs, uint8_t val){
	uint8_t high = val & 0xF0, low = (val << 4) & 0xF0;
		uint8_t bvrs = (rs == LCD_CMD) ? 0 : BV(LCD_RS);
		WriteByteandCtrl(high | bvrs| BV(LCD_EN) | BV(LCD_BL));
		DelayMs(1);
		WriteByteandCtrl(high | bvrs | BV(LCD_BL));

		WriteByteandCtrl(low | bvrs | BV(LCD_EN) | BV(LCD_BL));
		DelayMs(1);
		WriteByteandCtrl(low | bvrs | BV(LCD_BL));
}



int Lcd_InIt(void){
	DelayMs(20);
			I2CInIt();
			I2C_Start();
			int ret = I2CIsdeviceReady(LCD_SLAVE_ADD_W);
			I2C_Stop();
			if(!ret)
				return 0;



			WriteByteandCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
				__NOP();
				WriteByteandCtrl(LCD_FN_SET_8BIT);
				DelayMs(5);

				WriteByteandCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
				__NOP();
				WriteByteandCtrl(LCD_FN_SET_8BIT);
				DelayMs(1);

				WriteByteandCtrl(LCD_FN_SET_8BIT | BV(LCD_EN));
				__NOP();
				WriteByteandCtrl(LCD_FN_SET_8BIT);
				DelayMs(3);

				WriteByteandCtrl(LCD_FN_SET_4BIT | BV(LCD_EN));
				__NOP();

				WriteByteandCtrl(LCD_FN_SET_4BIT);
				DelayMs(3);
				WriteByteandCtrl(LCD_FN_SET_4BIT_1LINES);
					DelayMs(1);
					WriteByte(LCD_CMD, LCD_DISP_CTRL);
					DelayMs(1);
					WriteByte(LCD_CMD, LCD_CLEAR);
					DelayMs(1);
					WriteByte(LCD_CMD, LCD_ENTRY_MODE);
					DelayMs(1);
					WriteByte(LCD_CMD, LCD_DISP_ON);
					DelayMs(1);
					return ret;



}
void LCD_Puts(uint8_t line, char str[]){
	int i;
	WriteByte(LCD_CMD, line);
		DelayMs(1);
		for(i=0; str[i]!='\0'; i++)
			WriteByte(LCD_DATA, str[i]);
}


void LCD_scroll(void){
	WriteByte(LCD_CMD, LCD_DISPLAY_SHIFT);
}
