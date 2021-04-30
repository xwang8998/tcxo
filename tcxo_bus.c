#include<stdio.h>
#include"stdint.h"

#define AK2179 1
#ifdef AK2157
#define cmd_write_eeprom 0x04
#define cmd_read_eeprom  0x05
#define cmd_write_ram    0x03
#endif

#ifdef AK2179
#define cmd_write_eeprom 0x1a
#define cmd_read_eeprom  0x1d
#define cmd_write_ram    0x12
#endif

#define DELAY_NUM 50
#define INPUT 1
#define OUTPUT 0
uint8_t bus_VAFC,bus_CS,bus_CSOUT;
void xdelay(int a)
	{
		int i;
		for(i=0;i<a;i++)
			{
				;
			}
	}
void clk_sel2(void)
	{
		bus_VAFC = 0;
		xdelay(DELAY_NUM);
		bus_VAFC =1;
		xdelay(DELAY_NUM);
		bus_VAFC = 0;
		xdelay(DELAY_NUM);
		bus_VAFC =1;
	}
void bus_CSOUT_inout(uint8_t data)
	{
		if(data==1)
		;
		else
		;
	}
uint8_t bus_send_data(uint32_t data)
	{
		uint8_t i;
		uint8_t r_data;
		bus_CS = 1;
		clk_sel2();
		printf("\r\n");
		for(i=0;i<24;i++)
			{
				
				bus_VAFC = 1;
				xdelay(DELAY_NUM);
				bus_VAFC = 0;
				if(i>=16)
				{
				r_data = r_data <<1;	
				bus_CSOUT =1;
				bus_CSOUT_inout(INPUT);//
				r_data = bus_CSOUT;
				printf("\r\n%d-",i);
				
				}
				else
				{	
				bus_CSOUT_inout(OUTPUT);//
				if((data & 0x80000000) !=0)
				bus_CSOUT = 1;
				else
				bus_CSOUT = 0;
				printf("\r\n%d-%d",i,bus_CSOUT);
				}
				xdelay(DELAY_NUM);
				data = data<<1;		
			}
	return r_data;	
	}
uint8_t bus(uint8_t cmd,uint8_t addr,uint8_t data)
	{	
		uint32_t data32;
		uint8_t read_data;
		data32 = (cmd&0x001f)<<27;
		data32 |= (addr&0x000f) <<23;
		data32 |= (data&0x007f) <<16;
		printf("\r\n data32 = %04x",data32);
		read_data =bus_send_data(data32);
		return read_data;
	}

void main(void)
	{
		int i=1;
		while(i--)
			{
				bus(cmd_write_eeprom,0x01,0x05);
			}
	}
