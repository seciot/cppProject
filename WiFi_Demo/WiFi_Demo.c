/****************************************************************************
*
*�ļ�(File):         WiFi_Demo.c
*
*�޸�(Modify):       2011-03-24 14:18:45
*
*����(Author):       forsunzheng
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*1..ARM ��Ŀ�ļ�(ARM Project):WiFi_Demo.dsp 
*2..��Ŀ����������ļ�(project binary output  file):WiFi_Demo.bin
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-03-24 14:18:displayPosition5           forsunzheng 
----------------------------------------------------------------------------
****************************************************************************/

/*�ڴ����Ӵ���(TODO: add  code here)*/

#include "in_call.h"
#include "WiFi/WiFi.h"
#include "WiFi/NaNoWiFiConst.h"
#include "WiFi/WiFiPubFuncs.h"
#include <unistd.h>
//#include "usb.h"
//#include "updown.h"

int main(void)
{
	Disp_Init(DISP_INIT_ON);		//��ʼ�� LCD
	Disp_Clear();				
	
	KEY_Init(KEY_BEEP_KEY|KEY_AUTO_EL_ON);	//��ʼ�� Keyborad
	KEY_Beep_Mask_Set(0xffffffff);			
	KEY_EL_Mask_Set(0xffffffff);
	EL_Set_Timeout(20);			//��ʱ�رձ����
	Sys_Auto_Poweroff_Set(60*2);		//��ʱ����
	
	//Meanless for 0218/0318/0518
	Disp_Icon_Battery_Time_Set(1,ICON_AT_TAIL);
	Disp_Icon_Battery_Time_Refresh();
	Disp_Set_Color(SET_FONT_COLOR, 0x0000);		//��
	Disp_Set_Color(SET_BACK_COLOR, 0xFFFF);		//��
	Disp_Set_Color(SET_SELECT_COLOR, 0x07E0);	//��
	Disp_Set_Color(SET_CLEAR_COLOR, 0xFFFF);	//��

	adminPsd_init();	//һ���Գ�ʼ�������ݳ���
	db_check();	//���ݿ���
	//wifiInit_open();	//wifi��ʼ��
	main_task();
	return 0;
}
/*************************************/
void debugFun(char* debugStr)	//debug����
{
	DispStr_CE(0, 22, "MESSAGE", DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0, 24, debugStr, DISP_CENTER);
	DispStr_CE(0, 26, "�����������", DISP_CENTER);
	delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
}
void dblen(char* debugStr, int len)	//debug����
{
	unsigned char disp[20] = {0};
	memcpy(disp, debugStr, len);
	DispStr_CE(0, 22, "DEBUG", DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0, 24, disp, DISP_CENTER);
	DispStr_CE(0, 26, "�����������", DISP_CENTER);
	delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
}
void psdReset()	//��������
{
	eeprom_write("11111111", 8, EEPROM_OFFSET_ADM_PSD);
}
