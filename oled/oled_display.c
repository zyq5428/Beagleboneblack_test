#include "oled.h"

// #include "bmp.h"

/*******************************Main*******************************/
void oled_display_memu(void)
{
	unsigned char Humidity_Unit[5] = "%RH";
	unsigned char Light_Unit[5] = "Lx";
    OLED_Init();
    delay_ms(10);

    OLED_ShowCHinese(14,0,0);//婵炴搫鎷�
    OLED_ShowCHinese(42,0,1);//婵犫偓閿燂拷
    OLED_ShowCHinese(72,0,2);//閹艰揪鎷�
    OLED_ShowCHinese(100,0,3);//閻犱緤鎷�

    OLED_ShowCHinese(2,2,0);//婵炴搫鎷�
    OLED_ShowCHinese(22,2,2);//閹艰揪鎷�
//	OLED_ShowString(56,2,":");
//	OLED_ShowString(48,2,"26.50");
    OLED_ShowCHinese(100,2,4);//闁斥晪鎷�

    OLED_ShowCHinese(2,4,1);//婵犫偓閿燂拷
    OLED_ShowCHinese(22,4,2);//閹艰揪鎷�
//	OLED_ShowString(56,4,":");
//	OLED_ShowString(48,4,"78.23");
    OLED_ShowString(98,4,Humidity_Unit);

    OLED_ShowCHinese(2,6,5);//婵犫偓閿燂拷
    OLED_ShowCHinese(22,6,6);//閹艰揪鎷�
//	OLED_ShowString(56,5,":");
//	OLED_ShowString(48,5,"78.23");
    OLED_ShowString(98,6,Light_Unit);

//    delay_s(1);
//
//    OLED_ShowString(0,2,"0.96' OLED TEST");
//
//    OLED_ShowString(20,4,"2014/05/01");
//    OLED_ShowString(0,6,"ASCII:");
//    OLED_ShowString(63,6,"CODE:");
//    OLED_ShowChar(48,6,t);//闁跨喐鏋婚幏椋庛仛ASCII闁跨喕顢滈崙銈嗗
//    t++;
//    if(t>'~')t=' ';
//    OLED_ShowNum(103,6,t,3,16);//闁跨喐鏋婚幏椋庛仛ASCII闁跨喕顢滈崙銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归崐锟�
//
//
//    delay_ms(50);
//    OLED_Clear();
//    delay_ms(50);
////        OLED_DrawBMP(0,0,128,8,BMP1);  //閸ュ墽澧栭柨鐔告灮閹烽銇�(閸ュ墽澧栭柨鐔告灮閹烽銇氶柨鐔告灮閹风兘鏁撻惌顐秶閹风兘鏁撻弬銈嗗闁跨喓鍗崇喊澶嬪闁跨喕顢滈幉瀣濞叉鐎伴鏍晸缁夊摜銆嬮幏宄扮崯闂呮瑩鏁撶粔鎼佹？閿涘瓗LASH闁跨喓笑绾攱瀚�8K闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗)
//    delay_ms(50);
//    OLED_DrawBMP(0,0,128,8,gImage_128x64);
//    delay_ms(50);
}

int oled_init(void)
{
    oled_i2c_init();
    oled_display_memu();
}

