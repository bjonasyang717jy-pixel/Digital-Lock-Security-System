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

/* I2C pin */
sbit scl = LCD_SCL;
sbit sda = LCD_SDA;

/* keypad rows (5 rows) */
sbit R1 = P2^0;
sbit R2 = P2^1;
sbit R3 = P2^2;
sbit R4 = P2^3;
sbit R5 = P2^4;

/* keypad columns (4 columns) */
sbit C1 = P2^5;
sbit C2 = P2^6;
sbit C3 = P2^7;
sbit C4 = P3^0;

unsigned char slave_add;

/* keypad layout */
char keypad[5][4] =
{
{'A','B','#','*'},
{'1','2','3','C'},
{'4','5','6','D'},
{'7','8','9','E'},
{'F','0','G','H'}
};

/* I2C START */
void i2c_start()
{
    sda = 1; _nop_();
    scl = 1; _nop_();
    sda = 0; _nop_();
}

/* I2C STOP */
void i2c_stop()
{
    scl = 0;
    sda = 0;
    scl = 1;
    sda = 1;
}

/* Slave address */
void lcd_slave(unsigned char slave)
{
    slave_add = slave;
}

/* ACK */
void i2c_ACK()
{
    scl = 0;
    sda = 1;
    scl = 1;
    _nop_(); _nop_();
    scl = 0;
}

/* Write byte */
void i2c_write(unsigned char dat)
{
    unsigned char i;

    for(i=0;i<8;i++)
    {
        scl = 0;
        sda = (dat & (0x80>>i)) ? 1:0;
        _nop_();_nop_();
        scl = 1;
        _nop_();_nop_();
    }

    scl = 0;
}

/* Delay */
void delay_ms(unsigned int n)
{
    unsigned int m;

    while(n--)
        for(m=121;m>0;m--)
            _nop_();
}

/* Send LCD command */
void lcd_send_cmd(unsigned char cmd)
{
    unsigned char cmd_l,cmd_u;

    cmd_l=(cmd<<4)&0xF0;
    cmd_u=cmd&0xF0;

    i2c_start();
    i2c_write(slave_add);
    i2c_ACK();

    i2c_write(cmd_u|0x0C); i2c_ACK(); delay_ms(1);
    i2c_write(cmd_u|0x08); i2c_ACK(); delay_ms(2);

    i2c_write(cmd_l|0x0C); i2c_ACK(); delay_ms(1);
    i2c_write(cmd_l|0x08); i2c_ACK(); delay_ms(2);

    i2c_stop();
}

/* Send LCD data */
void lcd_send_data(unsigned char data)
{
    unsigned char data_l,data_u;

    data_l=(data<<4)&0xF0;
    data_u=data&0xF0;

    i2c_start();
    i2c_write(slave_add);
    i2c_ACK();

    i2c_write(data_u|0x0D); i2c_ACK(); delay_ms(1);
    i2c_write(data_u|0x09); i2c_ACK(); delay_ms(2);

    i2c_write(data_l|0x0D); i2c_ACK(); delay_ms(1);
    i2c_write(data_l|0x09); i2c_ACK(); delay_ms(2);

    i2c_stop();
}

/* Send string */
void lcd_send_str(unsigned char *p)
{
    while(*p)
        lcd_send_data(*p++);
}

/* LCD init */
void lcd_init()
{
    delay_ms(15);

    lcd_send_cmd(0x02);
    delay_ms(2);

    lcd_send_cmd(0x28);
    delay_ms(2);

    lcd_send_cmd(0x0C);
    delay_ms(2);

    lcd_send_cmd(0x06);
    delay_ms(2);

    lcd_send_cmd(0x01);
    delay_ms(5);
}

/* write line */
void lcd_write_line(unsigned char *str,unsigned char line)
{
    unsigned char len=0;

    if(line==1)
        lcd_send_cmd(0x80);
    else if(line==2)
        lcd_send_cmd(0xC0);
    else
        return;

    lcd_send_str(str);

    while(str[len]!='\0') len++;

    for(;len<16;len++)
        lcd_send_data(' ');
}

/* keypad scan */
char keypad_scan()
{
    char row;

    R1=R2=R3=R4=R5=1;

    for(row=0;row<5;row++)
    {
        R1=R2=R3=R4=R5=1;

        if(row==0) R1=0;
        if(row==1) R2=0;
        if(row==2) R3=0;
        if(row==3) R4=0;
        if(row==4) R5=0;

        if(C1==0){delay_ms(20);while(C1==0);return keypad[row][0];}
        if(C2==0){delay_ms(20);while(C2==0);return keypad[row][1];}
        if(C3==0){delay_ms(20);while(C3==0);return keypad[row][2];}
        if(C4==0){delay_ms(20);while(C4==0);return keypad[row][3];}
    }

    return 0;
}

/* main program */
void main()
{
    char key;

    lcd_slave(LCD_ADDR);

    lcd_init();

    lcd_write_line("PRESS KEY:",1);

    while(1)
    {
        key = keypad_scan();

        if(key!=0)
        {
            lcd_send_cmd(0xC0);
            lcd_send_data(key);
        }
    }
}