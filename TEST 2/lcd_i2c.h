#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include <reg51.h>
#include <intrins.h>

#define LCD_SCL   P0^4
#define LCD_SDA   P0^5
#define LCD_ADDR  0x4E

void lcd_slave(unsigned char slave);
void lcd_init(void);
void lcd_send_cmd(unsigned char cmd);
void lcd_send_data(unsigned char dataw);
void lcd_send_str(unsigned char *p);
void lcd_write_line(unsigned char *str, unsigned char line);

void delay_ms(unsigned int n);

void i2c_start(void);
void i2c_stop(void);
void i2c_ACK(void);
void i2c_write(unsigned char dat);

#endif