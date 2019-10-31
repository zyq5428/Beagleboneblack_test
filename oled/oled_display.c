#include "oled.h"

// #include "bmp.h"

/*******************************Main*******************************/
void oled_display_memu(void)
{
	unsigned char Humidity_Unit[5] = "%RH";
	unsigned char Light_Unit[5] = "Lx";
    OLED_Init();
    delay_ms(10);

    OLED_ShowCHinese(14,0,0);//濠电偞鎼幏锟�
    OLED_ShowCHinese(42,0,1);//濠电姭鍋撻柨鐕傛嫹
    OLED_ShowCHinese(72,0,2);//闁硅壈鎻幏锟�
    OLED_ShowCHinese(100,0,3);//闁荤姳绶ら幏锟�

    OLED_ShowCHinese(2,2,0);//濠电偞鎼幏锟�
    OLED_ShowCHinese(22,2,2);//闁硅壈鎻幏锟�
//	OLED_ShowString(56,2,":");
//	OLED_ShowString(48,2,"26.50");
    OLED_ShowCHinese(100,2,4);//闂佹枼鏅幏锟�

    OLED_ShowCHinese(2,4,1);//濠电姭鍋撻柨鐕傛嫹
    OLED_ShowCHinese(22,4,2);//闁硅壈鎻幏锟�
//	OLED_ShowString(56,4,":");
//	OLED_ShowString(48,4,"78.23");
    OLED_ShowString(98,4,Humidity_Unit);

    OLED_ShowCHinese(2,6,5);//濠电姭鍋撻柨鐕傛嫹
    OLED_ShowCHinese(22,6,6);//闁硅壈鎻幏锟�
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
//    OLED_ShowChar(48,6,t);//闂佽法鍠愰弸濠氬箯妞嬪簺浠汚SCII闂佽法鍠曢、婊堝礄閵堝棗顏�
//    t++;
//    if(t>'~')t=' ';
//    OLED_ShowNum(103,6,t,3,16);//闂佽法鍠愰弸濠氬箯妞嬪簺浠汚SCII闂佽法鍠曢、婊堝礄閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊宕愰敓锟�
//
//
//    delay_ms(50);
//    OLED_Clear();
//    delay_ms(50);
////        OLED_DrawBMP(0,0,128,8,BMP1);  //闁搞儱澧芥晶鏍煥閻斿憡鐏柟鐑筋棑閵囷拷(闁搞儱澧芥晶鏍煥閻斿憡鐏柟鐑筋棑閵囨岸鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾绘儗椤愵剛绉堕柟椋庡厴閺佹捇寮妶鍡楊伓闂佽法鍠撻崡宕囧枈婢跺顏堕梺璺ㄥ枙椤㈡粓骞夌€ｎ偄顏舵繛鍙夘殙閻庝即顢栭弽顓熸櫢缂佸鎽滈妴瀣箯瀹勬壆宕梻鍛懇閺佹挾绮旈幖浣癸紵闁挎稑鐡桳ASH闂佽法鍠撶瑧缁绢參鏀辩€氾拷8K闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏�)
//    delay_ms(50);
//    OLED_DrawBMP(0,0,128,8,gImage_128x64);
//    delay_ms(50);
}

int oled_init(void)
{
    oled_i2c_init();
    oled_display_memu();
}

int sht3x_display(int32_t temperature, int32_t humidity)
{
    int32_t Tem = temperature / 10;
    int32_t hum = humidity / 10;
    unsigned char tem_unit[5], hum_unit[5];

    int tmp;

    tmp = Tem;
    tem_unit[4] = tmp / 1 % 10 + '0';
    tem_unit[3] = tmp / 10 % 10 + '0';
    tem_unit[2] = '.';
    tem_unit[1] = tmp / 100 % 10 + '0';
    tem_unit[0] = tmp / 1000 % 10 + '0';

    tmp = hum;
    hum_unit[4] = tmp / 1 % 10 + '0';
    hum_unit[3] = tmp / 10 % 10 + '0';
    hum_unit[2] = '.';
    hum_unit[1] = tmp / 100 % 10 + '0';
    hum_unit[0] = tmp / 1000 % 10 + '0';

    OLED_Display_On();
    
    OLED_ShowString_N(50,2, tem_unit, sizeof(tem_unit));

    OLED_ShowString_N(50,4, hum_unit, sizeof(hum_unit));

    sleep(2);
    OLED_Display_Off();
    sleep(5);

    return 0;
}
