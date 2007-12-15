#include "../inc/swilib.h"
#include "main.h"
#include "mainmenu.h"
#include "lang.h"
#include "playlist.h"

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

// Mr. Anderstand:
// Переделал все...

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
extern unsigned short EditPL;
//extern const char COORD[];

#define N_ITEMS 6

int MainMenu_ID;

void SetNextPlayedOn()
{
  SetNextPlayed();
  GeneralFuncF1(1);
}

void Coordinates()
{
  WSHDR *ws=AllocWS(256);
  extern const char PIC_DIR[];
  char sfname[256];
  str_2ws(ws,exename,strlen(exename)+1);
  sprintf(sfname,"%s%s",PIC_DIR,"skin.cfg");
  ExecuteFile(ws,0,(char*)sfname);
  FreeWS(ws);
}

void SetEditPL()
{
  EditPL=!(EditPL);
  RefreshGUI();
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
  ShowMSG(0,(int)"SPlayer v0.7.5.6\n(c) Anderstand, Blind007, DemonGloom");
};

void Exit_SPlayer()
{
  QuitCallbackProc(0);
}

HEADER_DESC menuhdr={0,0,131,21,NULL,(int)"Меню",LGP_NULL};

int mmenusoftkeys[]={0,1,2};

int icon_array[2];

static const char * const menutexts[N_ITEMS]=
{
  LG_SetNextPlayed,
  LG_Coordinates,
  LG_SetEditPL,
  LG_Settings,
  LG_AboutDlg,
  LG_Exit_SPlayer
};
/*
MENUITEM_DESC menuitems[N_ITEMS]=
{
  {0,(int)"Позиционирование",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Редактирование",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Настройки",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Об эльфе...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Выход",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};*/

void *menuprocs[N_ITEMS]={
                          (void *)SetNextPlayedOn,
                          (void *)Coordinates,
                          (void *)SetEditPL,
                          (void *)Settings,
                          (void *)AboutDlg,
                          (void *)Exit_SPlayer
                         };
/*
static const MENUPROCS_DESC menuprocs[N_ITEMS]={
                          Coordinates,
                          SetEditPL,
                          Settings,
                          AboutDlg,
                          Exit_SPlayer
                         };*/

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

/*
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
};*/
int S_ICONS[N_ITEMS];

void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,"%t",menutexts[curitem]);
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,S_ICONS+0);
    break;
  case 1:
    SetMenuItemIconArray(data,item,S_ICONS+1);
    break;
  case 2:
    SetMenuItemIconArray(data,item,icon_array+(EditPL?0:1));
    break;
  case 3:
    SetMenuItemIconArray(data,item,S_ICONS+3);
    break;
  case 4:
    SetMenuItemIconArray(data,item,S_ICONS+4);
    break;
  case 5:
    SetMenuItemIconArray(data,item,S_ICONS+5);
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int mmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC tmenu=
{
  8,mmenu_keyhook,mmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,
  menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  N_ITEMS
};

extern const char PIC_DIR[128];
int S_ICONS[N_ITEMS];
char setnexttrackpic[128];
char coordinatespic[128];
char editplpic[128];
char settingspic[128];
char aboutpic[128];
char exitpic[128];

void MM_Show()
{
#ifndef NO_PNG
  // Картинка В очередь
  strcpy(setnexttrackpic,PIC_DIR);
  strcat(setnexttrackpic,"setnexttrack.png");
  S_ICONS[0] = (int)setnexttrackpic;
 // menuitems[0].icon = S_ICONS;
  // Картинка Настройки
  strcpy(coordinatespic,PIC_DIR);
  strcat(coordinatespic,"coordinates.png");
  S_ICONS[1] = (int)coordinatespic;
 // menuitems[0].icon = S_ICONS;
  // Картинка Редактирорвание пл
  // S_ICONS[2]
  // Картинка Настройки
  strcpy(settingspic,PIC_DIR);
  strcat(settingspic,"settings.png");
  S_ICONS[3] = (int)settingspic;
 // menuitems[2].icon = S_ICONS+2;
  // Картинка Об эльфе...
  strcpy(aboutpic,PIC_DIR);
  strcat(aboutpic,"about.png");
  S_ICONS[4] = (int)aboutpic;
 // menuitems[3].icon = S_ICONS+3;
  // Картинка Выход
  strcpy(exitpic,PIC_DIR);
  strcat(exitpic,"exit.png");
  S_ICONS[5] = (int)exitpic;
 // menuitems[4].icon = S_ICONS+4;
#else
  S_ICONS[0] = 0;
  menuitems[0].icon = S_ICONS;
  S_ICONS[1] = 0;
  menuitems[1].icon = S_ICONS+1;
 // S_ICONS[2] = 0;
 // menuitems[2].icon = S_ICONS+2;
  S_ICONS[3] = 0;
  menuitems[3].icon = S_ICONS+2;
  S_ICONS[4] = 0;
  menuitems[4].icon = S_ICONS+4;
  S_ICONS[5] = 0;
  menuitems[5].icon = S_ICONS+5;
#endif  
  
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  
  patch_header(&menuhdr);
  MainMenu_ID = CreateMenu(0,0,&tmenu,&menuhdr,0,N_ITEMS,0,0);
}
