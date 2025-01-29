#include "menu.h"
#include "SHOW.h"

int aim=0;
int key=0;
int key_1_staut=1;
int key_2_staut=1;
int key_3_staut=1;
int key_4_staut=1;
int key_5_staut=1;
int key_6_staut=1;
int key_7_staut=1;
int key_8_staut=1;
int key_9_staut=1;
int key_10_staut=1;
int key_11_staut=1;
int key_12_staut=1;
int key_1_col_staut=1;
int key_2_col_staut=1;
int key_3_col_staut=1;
//当前按键状态

int key_1_staut0=0;
int key_2_staut0=0;
int key_3_staut0=0;
int key_4_staut0=0;
int key_5_staut0=0;
int key_6_staut0=0;
int key_7_staut0=0;
int key_8_staut0=0;
int key_9_staut0=0;
int key_10_staut0=0;
int key_11_staut0=0;
int key_12_staut0=0;
int key_1_col_staut0=0;
int key_2_col_staut0=0;
int key_3_col_staut0=0;

int key_value=0;
int key_value_col=0;
int show_value=0;
uint8 show_img=0;
int title_flag=1;
int point_flag=1;
int key_time=0;//按键时间
int Save[100];

extern uint32 b[256];

unsigned char ui_MotorPID[10][17] =
{
    " MotorP: ",
    "                ",
	  " MotorI:  ",
    "                ",
    " L_Speed:   ",
    "                ",
	  " R_Speed:   ",
    "                ",
    "                ",
    " MotorPID       "
};

extern int a;


int menu(void)
{
    ips200_show_chinese(25, 0, 16, show_camara, 4, RGB565_BLACK);
ips200_show_chinese(25, 20, 16, changedada, 4, RGB565_BLACK);
ips200_show_chinese(25, 40, 16, showdada, 4, RGB565_BLACK);
    while(1)
    {
        gpio_init(KEY_1,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_2,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_3,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_4,GPI,0,GPI_PULL_UP);

        key_1_staut0=key_1_staut;
        key_2_staut0=key_2_staut;
        key_3_staut0=key_3_staut;
        key_4_staut0=key_4_staut;
        key_1_staut=gpio_get_level(KEY_1);
        key_2_staut=gpio_get_level(KEY_2);
        key_3_staut=gpio_get_level(KEY_3);
        key_4_staut=gpio_get_level(KEY_4);
        if(key_1_staut==1 && key_1_staut0==0) key_value=1;
        if(key_2_staut==1 && key_2_staut0==0) key_value=2;
        if(key_3_staut==1 && key_3_staut0==0) key_value=3;
        if(key_4_staut==1 && key_4_staut0==0) key_value=4;
        system_delay_ms (50);


        switch(key_value)
        {
            case 1:
            {
                title_flag++;
                    if(title_flag>=4)
                    {
                        title_flag=1;
                    }
                key_value=0;
            }
                break;
            case 2:
            {
             ips200_clear();
             return title_flag;

            }
        }
        switch(title_flag)
        {
            case 1:
            {
            ips200_show_string(0, 0, "->");
            ips200_show_string(0, 20, "  ");
            ips200_show_string(0, 40, "  ");
            }
            break;
            case 2:
            {
            ips200_show_string(0, 0, "  ");
            ips200_show_string(0, 20, "->");
            ips200_show_string(0, 40, "  ");
            }
            break;
            case 3:
            {
            ips200_show_string(0, 0, "  ");
            ips200_show_string(0, 20, "  ");
            ips200_show_string(0, 40, "->");
            }
            break;
        }
        ips200_show_uint(120, 120, title_flag, 3);
        ips200_show_uint(120, 140, key_value, 3);

        
    }
}

int menu_2(void)
{
    
    while(1)
    {
        gpio_init(KEY_1,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_2,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_3,GPI,0,GPI_PULL_UP);
        gpio_init(KEY_4,GPI,0,GPI_PULL_UP);

        key_1_staut0=key_1_staut;
        key_2_staut0=key_2_staut;
        key_3_staut0=key_3_staut;
        key_4_staut0=key_4_staut;
        key_1_staut=gpio_get_level(KEY_1);
        key_2_staut=gpio_get_level(KEY_2);
        key_3_staut=gpio_get_level(KEY_3);
        key_4_staut=gpio_get_level(KEY_4);
        if(key_1_staut==1 && key_1_staut0==0) key_value=1;
        if(key_2_staut==1 && key_2_staut0==0) key_value=2;
        if(key_3_staut==1 && key_3_staut0==0) key_value=3;
        if(key_4_staut==1 && key_4_staut0==0) key_value=4;
        system_delay_ms (50);
        switch(key_value)
        {
            case 1:
            {
                title_flag++;
                    if(title_flag>10)
                    {
                        title_flag=1;
                    }
                key_value=0;
            }
                break;
        }
        if(key_value==4&&title_flag==3)
        {
            b[0]+=10;
            key_value=0;
            // flash_erase_sector(63, 3);


        }
        if(key_value==2&&title_flag==3)
        {

            flash_write_page(63, 3, b, 256);

        }
        
     switch(sec)
      {
            case 1:
            {
                if(mt9v03x_finish_flag)
                {
                  ips200_displayimage03x(mt9v03x_image[0], 188, 120);
                  mt9v03x_finish_flag=0;
                }
                break;
            }  
           case 2:
            {
                for(int i =0;i<10;i++)
                {
                    if(i==title_flag-1)
                    {
                        ui_MotorPID[i][0]='>';
                    }
                    else
                    {
                    ui_MotorPID[i][0]=' ';
                    }
                ips200_show_string(30, 20*i, ui_MotorPID[i]);                
                }
                ips200_show_int(130, 40, b[0], 3); 
                ips200_show_int(130, 300, title_flag, 3); 
                // ips200_show_string(0, 300, StrToDouble(b);
                // ips200_show_float(0, 300, StrToDouble(b), 2, 3); 
                //ips200_show_uint(0, 0, b[0], 3); 
                break;
            }  
            case 3:
            {
            for (int i = 0; i < 240; i++)
             {
              for (int j = 0; j < 240; j++)
              {
                  
              ips200_draw_point(j, i, jian_0[i * 240 +j]); 
              }
             }
                break;
            } 
      }
      if(key_value==3)
      {
        ips200_clear();
      return 0;
      }
    }
     
}
