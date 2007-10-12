#include "../inc/swilib.h"
#include "main.h"
#include "mainmenu.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

/*
 Тут делаю главное меню...
 Все работает норм! И графика пашет. Так что здесь пока можно ничего не трогать,
 пока новые пункты не добавлять...
*/
// Ну да ладно! это не помешает!
//==============================================================================
// ELKA Compatibility
#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//==============================================================================
char exename[]=DEFAULT_DISK":\\ZBin\\SPlayer\\SPlayer cfg editor.elf";

#define N_ITEMS 4

int MainMenu_ID;

void Coordinates()
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,exename,strlen(exename)+1);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void Settings()   //Настройки  AAA
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
};

void AboutDlg()
{
  ShowMSG(0,(int)"SPlayer v0.7.2\n(c) Anderstand, Blind007, DemonGloom");
};

void Exit_SPlayer()
{
  QuitCallbackProc(0);
}

HEADER_DESC menuhdr={0,0,131,21,NULL,(int)"Меню",LGP_NULL};

int mmenusoftkeys[]={0,1,2};

int icon_array[2];

MENUITEM_DESC menuitems[N_ITEMS]=
{
  {0,(int)"Позиционирование",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Настройки",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Об эльфе...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Выход",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

void *menuprocs[N_ITEMS]={
                          (void *)Coordinates,
                          (void *)Settings,
                          (void *)AboutDlg,
                          (void *)Exit_SPlayer
                         };

SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

// Выкинем пока это...
/*
void menuitemhandler(void *data, int curitem, int *unk)
{
  switch(curitem)
  {
  case 4:
//    SetMenuItemIcon(data,curitem,Is_Vibra_Enabled?0:1);
    break;

  case 5:
//    SetMenuItemIcon(data,curitem,Is_Sounds_Enabled?0:1);
    break;
  }
}
*/

// swilib.h от 17.08.07. Проблема со структурой MENU_DESC
MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  1,
  NULL,             // Написал NULL, не знаю что будет...
  menuitems,
  (MENUPROCS_DESC*)menuprocs, // Дописал (MENUPROCS_DESC*)
  N_ITEMS
};

extern const char PIC_DIR[128];
int S_ICONS[N_ITEMS];
char coordinatespic[128];
char settingspic[128];
char aboutpic[128];
char exitpic[128];

void MM_Show()
{
#ifdef USE_PNG_EXT
  // Картинка Настройки
  strcpy(coordinatespic,PIC_DIR);
  strcat(coordinatespic,"coordinates.png");
  S_ICONS[0] = (int)coordinatespic;
  menuitems[0].icon = S_ICONS;
  // Картинка Настройки
  strcpy(settingspic,PIC_DIR);
  strcat(settingspic,"settings.png");
  S_ICONS[1] = (int)settingspic;
  menuitems[1].icon = S_ICONS+1;
  // Картинка Об эльфе...
  strcpy(aboutpic,PIC_DIR);
  strcat(aboutpic,"about.png");
  S_ICONS[2] = (int)aboutpic;
  menuitems[2].icon = S_ICONS+2;
  // Картинка Выход
  strcpy(exitpic,PIC_DIR);
  strcat(exitpic,"exit.png");
  S_ICONS[3] = (int)exitpic;
  menuitems[3].icon = S_ICONS+3;
#endif  
  
  patch_header(&menuhdr);
  MainMenu_ID = CreateMenu(0,0,&tmenu,&menuhdr,0,N_ITEMS,0,0);
}
