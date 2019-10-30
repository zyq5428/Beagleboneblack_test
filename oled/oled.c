#include "oled.h"
#include "picture.h"
#include "oledfont.h"

#include "sensirion_i2c.h"

//OLED闁汇劌瀚Ο澶屸偓娑虫嫹
//閻庢稒蓱閺備線寮介悡搴ｇ濠碘€冲€风粭锟�.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

/*
 * SSD1106闁哄嫸鎷�132x64闁挎稑鐭侀埀顒€顒玈D1306闁哄嫸鎷�128x64闁挎冻鎷�1.3閻庣數顎桳ED闁哄嫸鎷�128*64闁稿秴绻掔粈宀勬晬鐏炶棄绠靛ù婊冩閼垫垿姊婚敓锟�128濞达絽绋勭槐婵嬪箥閳ь剚绂掗妷銊﹀闯濠殿喖顑呭妤呭冀閸ワ箒绀�0x2
 */

/*
 * STM32F4闁汇劌鍤�2C閹煎瓨鎸诲﹢渚€姊婚鈧。浠嬫晬鐎涳拷2C闁革附婢樺鍐╃▔瀹ュ嫮绐楅柤濂変簻婵晛菐鐠囨彃顫ｉ悹鍥嚙閸熸挻鎷呴敓锟�
 */
#define oled_addr 0x3C
//#define oled_addr 0x78

#define OLED_I2C_DEVICE_PATH "/dev/i2c-2"
static int oled_device = 0;

unsigned char oled_cmd[2] = {0x00, 0x00};
unsigned char oled_data[2] = {0x40, 0x00};

void oled_i2c_init(void) {
    /* open i2c adapter */
    oled_device = linux_i2c_init(OLED_I2C_DEVICE_PATH);
}

void oled_i2c_release(void)
{
    linux_i2c_release(oled_device);
}

int8_t oled_i2c_write(uint8_t address, const uint8_t *data, uint16_t count)
{
    return(linux_i2c_write(oled_device, address, data, count));
}

void delay_ms(unsigned int ms)
{
    sensirion_sleep_usec(1000 * ms);
}

/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
    oled_cmd[1] = IIC_Command;

/*     if(HAL_I2C_Master_Transmit(&hi2c2, oled_addr, oled_cmd, 2, 1000) != HAL_OK) {
    	HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_SET);
    } */
   if(oled_i2c_write(oled_addr, oled_cmd, 2) != STATUS_OK) {
       ;
   }
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
    oled_data[1] = IIC_Data;

/*     if(HAL_I2C_Master_Transmit(&hi2c2, oled_addr, oled_data, 2, 1000) != HAL_OK) {
    	HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_SET);
    } */
   if(oled_i2c_write(oled_addr, oled_data, 2) != STATUS_OK) {
       ;
   }
}

//闁告碍鍙€SD1306闁告劖鐟ラ崣鍡樼▔閳ь剚绋夐鍕憻闁煎搫鍊堕埀顒婃嫹
//dat:閻熸洑绀侀崯鎾诲礂閵壯勭暠闁轰胶澧楀畵锟�/闁告稒鍨濋幎锟�
//cmd:闁轰胶澧楀畵锟�/闁告稒鍨濋幎銈夊冀閸パ呯 0,閻炴稏鍔庨妵姘跺川閹存帗濮�;1,閻炴稏鍔庨妵姘跺极閻楀牆绁�;
void OLED_WR_Byte(unsigned char data,unsigned char cmd)
{
    if (cmd) {
        Write_IIC_Data(data);
    } else {
        Write_IIC_Command(data);
    }
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);
}

//鐎殿喒鍋撻柛姘辨灳LED闁哄嫬澧介妵锟�
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC闁跨喐鏋婚幏鐑芥晸閺傘倖瀚�
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//闁稿繑濞婂Λ纰燣ED闁哄嫬澧介妵锟�
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC闁跨喐鏋婚幏鐑芥晸閺傘倖瀚�
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//婵炴挸鎳庨惈鍡涘礄閼恒儲娈�,婵炴挸鎳庨悾顒備沪閿燂拷,闁轰胶绻濋柌婊呬沪韫囨挾顔庨柡鍕靛灦缁箓鎳濋懠顒佺暠!闁告粌鏈惀鍛存倷闁稑鐦ㄥ☉鎾亾闁哄稄鎷�!!!
void OLED_Clear(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //閻犱礁澧介悿鍡樸亜闂堟稒鍕鹃柛褉鍋撻柨娑虫嫹0~7闁挎冻鎷�
        OLED_WR_Byte (0x00,OLED_CMD);      //閻犱礁澧介悿鍡涘及閸撗佷粵濞达絽绉堕悿鍡涘灳閺傚灝鐏欏ù锝呴濠€鎾锤閳э拷
        OLED_WR_Byte (0x10,OLED_CMD);      //閻犱礁澧介悿鍡涘及閸撗佷粵濞达絽绉堕悿鍡涘灳閺傚灝鐏欏Δ鍌浢﹢鎾锤閳э拷
        for(n=0;n<130;n++)
            OLED_WR_Byte(0,OLED_DATA);
    } //闁哄洤鐡ㄩ弻濠囧及閸撗佷粵
}

//闁稿繈鍔嶅Ο澶愬礄閼恒儲娈�,闁轰胶绻濋柌婊呬沪韫囨挾顔庨柡鍕靛灟鐎垫帡鎯冮敓锟�!
void OLED_On(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //閻犱礁澧介悿鍡樸亜闂堟稒鍕鹃柛褉鍋撻柨娑虫嫹0~7闁挎冻鎷�
        OLED_WR_Byte (0x00,OLED_CMD);      //閻犱礁澧介悿鍡涘及閸撗佷粵濞达絽绉堕悿鍡涘灳閺傚灝鐏欏ù锝呴濠€鎾锤閳э拷
        OLED_WR_Byte (0x10,OLED_CMD);      //閻犱礁澧介悿鍡涘及閸撗佷粵濞达絽绉堕悿鍡涘灳閺傚灝鐏欏Δ鍌浢﹢鎾锤閳э拷
        for(n=0;n<128;n++)
            OLED_WR_Byte(1,OLED_DATA);
    } //闁哄洤鐡ㄩ弻濠囧及閸撗佷粵
}

//闁革负鍔嶇€垫氨鈧鐭紞鍛磾椤旇姤鈻旂紒鈧潪鎵伇濞戞搩浜滈悺褏绮敓锟�,闁告牕鎳忕€氼參鏌堥妸銉ョ€婚悗娑欘殘椤戯拷
//x:0~127
//y:0~63
//mode:0,闁告瑥绉跺▍褔寮伴崜褋浠�;1,婵繐绲介悥鍫曞及閸撗佷粵
//size:闂侇偄顦扮€氥劎鈧稒銇炵紞锟� 16/12
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{
    unsigned char c=0,i=0;
        c=chr-' ';//鐎电増顨呴崺宀勫磻韫囨泤鈺呭触鎼达絾鐣遍柛濠忔嫹
        if(x>Max_Column-1){x=0;y=y+2;}
        if(SIZE ==16)
        {
            OLED_Set_Pos(x,y);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
            OLED_Set_Pos(x,y+1);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        } else {
            OLED_Set_Pos(x,y+1);
            for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
        }
}

//m^n闁告垼濮ら弳锟�
unsigned int oled_pow(unsigned char m,unsigned char n)
{
    unsigned int result=1;
    while(n--)
        result*=m;
    return result;
}

//闁哄嫬澧介妵锟�2濞戞搩浜濋弳鐔衡偓娑虫嫹
//x,y :閻犙囶棑閸嬶綁宕搁幇顓犲灱
//len :闁轰焦婢橀悺褔鎯冮崟顏嗙Т闁轰緤鎷�
//size:閻庢稒銇炵紞瀣緞瑜嶉惃锟�
//mode:婵☆垪鈧磭纭€   0,濠靛鍋勯崢鏍熼垾宕囩;1,闁告瑧濮存慨鐐参熼垾宕囩
//num:闁轰焦婢橀埀顒婃嫹(0~4294967295);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{
    unsigned char t,temp;
    unsigned char enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ');
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0');
    }
}

//闁哄嫬澧介妵姘▔閳ь剚绋夐鍕憻缂佹绠戣ぐ鎸庣▔閿燂拷
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {
        OLED_ShowChar(x,y,chr[j]);
        x+=8;

        if(x>120)
        {
            x=0;y+=2;
        }
            j++;
    }
}

//闁哄嫬澧介妵姘扁偓娑欘殘椤戜焦绋夌拠褏绀夐柟绋挎搐閻ｉ箖姊归崹顔碱唺闂侇剙鐏濋崢銈夊极閹殿喚鐭嬮悺鎺戯功閺咃拷
void OLED_ShowString_N(unsigned char x,unsigned char y,unsigned char *chr, int size)
{
    int j=0;
    while (j < size)
    {
        OLED_ShowChar(x,y,chr[j]);
        x+=8;

        if(x>120)
        {
            x=0;y+=2;
        }
            j++;
    }
}

//闁哄嫬澧介妵姘ф径濠勬憻
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{
    unsigned char t,adder=0;
    OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
        adder+=1;
    }
        OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
        adder+=1;
    }
}

/***********闁告梻鍠曢崗姗€骞撹箛姘墯闁挎稒纰嶅Ο澶岀矆閻戞ɑ鈻旂紒鈧弧濉嶱闁搞儱澧芥晶锟�128閼达拷64閻犙冨槻椤劙鎮欓悷鐗堢稄闁哄稄鎷�(x,y),x闁汇劌瀚€垫牠宕堕敓锟�0闁挎繐鎷�127闁挎稑鐦斿☉鎾存そ閵嗗鎯冮崟顔肩槺闁搞儻鎷�0闁挎繐鎷�7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0)
      y=y1/8;
  else
      y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

//void Initial_M096128x64_ssd1306(void)
void OLED_Init(void)
{
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xdf);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 

    OLED_Clear();
    OLED_Set_Pos(0x02,0);
}





