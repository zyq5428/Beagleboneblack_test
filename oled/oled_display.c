#include "oled.h"

// #include "bmp.h"

/*******************************Main*******************************/
void oled_display_memu(void)
{
	unsigned char Humidity_Unit[5] = "%RH";
	unsigned char Light_Unit[5] = "Lx";
    OLED_Init();
    delay_ms(10);

    OLED_ShowCHinese(14,0,0);//婵犵數鍋為幖顐﹀箯閿燂拷
    OLED_ShowCHinese(42,0,1);//婵犵數濮崑鎾绘煥閻曞倹瀚�
    OLED_ShowCHinese(72,0,2);//闂佺澹堥幓顏堝箯閿燂拷
    OLED_ShowCHinese(100,0,3);//闂佽崵濮崇欢銈夊箯閿燂拷

    OLED_ShowCHinese(2,2,0);//婵犵數鍋為幖顐﹀箯閿燂拷
    OLED_ShowCHinese(22,2,2);//闂佺澹堥幓顏堝箯閿燂拷
//	OLED_ShowString(56,2,":");
//	OLED_ShowString(48,2,"26.50");
    OLED_ShowCHinese(100,2,4);//闂備焦鏋奸弲顏堝箯閿燂拷

    OLED_ShowCHinese(2,4,1);//婵犵數濮崑鎾绘煥閻曞倹瀚�
    OLED_ShowCHinese(22,4,2);//闂佺澹堥幓顏堝箯閿燂拷
//	OLED_ShowString(56,4,":");
//	OLED_ShowString(48,4,"78.23");
    OLED_ShowString(98,4,Humidity_Unit);

    OLED_ShowCHinese(2,6,5);//婵犵數濮崑鎾绘煥閻曞倹瀚�
    OLED_ShowCHinese(22,6,6);//闂佺澹堥幓顏堝箯閿燂拷
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
//    OLED_ShowChar(48,6,t);//闂備浇娉曢崰鎰板几婵犳艾绠瀣昂娴犳睔SCII闂備浇娉曢崰鏇€€佸⿰鍫濈闁靛牆妫楅锟�
//    t++;
//    if(t>'~')t=' ';
//    OLED_ShowNum(103,6,t,3,16);//闂備浇娉曢崰鎰板几婵犳艾绠瀣昂娴犳睔SCII闂備浇娉曢崰鏇€€佸⿰鍫濈闁靛牆妫楅鍫曟⒑鐠恒劌鏋戦柡瀣煼楠炲繘鎮滈懞銉︽闂佸搫鍊堕崐鏍偓姘秺瀹曟劙鏁撻敓锟�
//
//
//    delay_ms(50);
//    OLED_Clear();
//    delay_ms(50);
////        OLED_DrawBMP(0,0,128,8,BMP1);  //闂佹悶鍎辨晶鑺ユ櫠閺嶎厽鐓ラ柣鏂挎啞閻忣噣鏌熼悜绛嬫闁靛浄鎷�(闂佹悶鍎辨晶鑺ユ櫠閺嶎厽鐓ラ柣鏂挎啞閻忣噣鏌熼悜绛嬫闁靛洦宀搁弻銊╂偄閸涘﹦浼勯梺褰掝棑閸忔﹢寮幘缁樺剹妞ゆ劦鍓涚粔鍫曟煙妞嬪骸鍘撮柡浣规崌瀵剟濡堕崱妤婁紦闂備浇娉曢崰鎾诲础瀹曞洤鏋堝璺侯儏椤忓爼姊虹捄銊ユ灆妞ゃ垺绮撻獮澶屸偓锝庡亜椤忚埖绻涢崣澶樻畽闁诲簼鍗抽、鏍冀椤撶喐娅㈢紓浣割槸閹芥粓濡寸€ｎ喖绠€瑰嫭澹嗗畷顖炴⒒閸涱喚鎳囬柡浣规尵缁棃骞栨担鐧哥吹闂佹寧绋戦悺妗矨SH闂備浇娉曢崰鎾剁懅缂佺虎鍙冮弨杈┾偓姘炬嫹8K闂備浇娉曢崰鎰板几婵犳艾绠柣鎴ｅГ閺呮悂鏌￠崒妯衡偓鏍偓姘秺閺屻劑鎮㈤崨濠勪紕闂佸綊顥撻崗姗€寮幘璇叉闁靛牆妫楅锟�)
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

    // OLED_Display_On();
    
    OLED_ShowString_N(50,2, tem_unit, sizeof(tem_unit));

    OLED_ShowString_N(50,4, hum_unit, sizeof(hum_unit));

    // sleep(2);
    // OLED_Display_Off();
    // sleep(5);

    return 0;
}
