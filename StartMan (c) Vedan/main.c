#include "c:\arm\inc\swilib.h"
#include "c:/ARM/inc/cfg_items.h"
#include "C:\ARM\inc\xtask_ipc.h"
#include "conf_loader.h"
//#include "enterpass.h"
//#include "errors.h"
//#include "params.h"
//#include "inits.h"
#include "main.h"
#include "voids.h"
#include "turnoff.h"
#include "pandemon.h"
#include "strings.h"
GBSTMR tmr;
extern const unsigned int fcolor;
extern const char *successed_config_filename;
extern const int bright;
GBSTMR tmr_displacement;
  char name[256];
char old_light;
int x;
int WHAT_DO=0;  
const int minus11=-11;
const char fname[64];
char Quit_Required = 0;
extern void kill_data(void *p, void (*func_p)(void *));

extern const char DIR_RUN_S1[128];
extern const char DIR_RUN_S2[128];
extern const char DIR_RUN_S3[128];

extern const char DIR_RUN_DE1[128];
extern const char DIR_RUN_DE2[128];
extern const char DIR_RUN_DE3[128];

extern const char NAME_S1[128];
extern const char NAME_S2[128];
extern const char NAME_S3[128];

extern const char ICONS_SD[128];
extern const char ICONS_RB[128];
extern const char ICONS_SR[128];
extern const char ICONS_E[128];
extern const char PIC_SET3[128]; 
extern const char PIC_SET2[128]; 
extern const char PIC_SET1[128];  
extern const char PIC_CUR[128];  
extern const char PIC_FON[128];
extern const char PIC_OFF[128];

extern const char PASSWORD_SET1[9];
extern const char PASSWORD_SET2[9];
extern const char PASSWORD_SET3[9];
extern const int UZERS;
extern const int ILL_NUM;
extern const int ENA_PASS;

const char nullpass[9]="";
const char per_s[]="%s";
const char per_t[]="%t";
const char per_d[]="%d";

int y=176;
int mode;

void UpDateSet()
{
  InitConfig();
  mode=0;
  if (UZERS==1)y=75; else
  if (UZERS==2)y=59; else
  if (UZERS==3)y=43;
  //DIC(y);
}

int ERMSG=0;
int TURNOFF=0;
int mode1;



unsigned short maincsm_name_body[140];
//unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

long int  res=0, resprew=0, c = 0;
volatile int Ter= 0; 

int DISET3(int y){DrawImg(15,80+y,(int)PIC_SET3);return(0);}
int DISET2(int y){DrawImg(15,80+y,(int)PIC_SET2);return(0);}
int DISET1(int y){DrawImg(15,80+y,(int)PIC_SET1);return(0);}
int DIC(int y){DrawImg(10,y,(int)PIC_CUR);return(0);}

//Ошибка////////////////////////////////////////////////////////////////////////
int xt=1;

//int DIE(int py){DrawImg(30,py,(int)"4:\\Zbin\\StartMan\\img\\error.png");return(0);};
void ErrorMSG()
{
  int px, py;
    WSHDR *wws = AllocWS(512);
    px= ScreenW()/2 - GetImgWidth((int)ICONS_E)/2;
    py = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_E)/2;
    
    DrawImg(px, py, (int)ICONS_E);
    if(mode>0)
    {
                 // DIE(py+95);
    wsprintf(wws,per_t,"ОШИБКА !\nНеверный\n пароль!");
    }else
    {
    wsprintf(wws,per_t,"ОШИБКА !\nПароль\nне введен!"); 
    }
    DrawString(wws,px+30,py+7,px+30+150,py+7+170,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    //};
    GBS_StartTimerProc(&tmr_displacement,100, ErrorMSG);
    xt++;
    if (xt>7)
    {
    GBS_DelTimer(&tmr_displacement);
    xt=1;
    REDRAW();
  
   }
   FreeWS(wws);
   
}///////////////////////////////////////////////////////////////////////////////







//-----------------------------------------------------------------------------

void GetpassINFO()
{
 
  char *mem;
  int hFile;
  unsigned int io_error = 0;
 // int i;
  if(mode>0)
  {
   if (UZERS==1)
   {
    
    
  //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
    hFile = fopen(DIR_RUN_S1,A_ReadOnly+A_BIN,P_READ, &io_error);
    if(hFile!=-1)
    {
     mem=malloc(100);
     int size=fread(hFile,mem,100,&io_error);
     *(mem+size)=0;
     if (strstr(PASSWORD_SET1,mem))
     {
     ShowMSG(1,(int)"Вход\nвыполнен !");
     RunElfs();
     CloseCSM(MAINCSM_ID);
     }else
     {
       ErrorMSG();
       fclose(hFile, &io_error);
     }
     mfree(mem);
     }
   }
   
  else
  if (UZERS==2)
  { 
    if(y==59)
     {
      //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
      hFile = fopen(DIR_RUN_S1,A_ReadOnly+A_BIN,P_READ, &io_error);
      if(hFile!=-1)
      {
      mem=malloc(100);
      int size=fread(hFile,mem, 100, &io_error);
      *(mem+size)=0;
      if (strstr(PASSWORD_SET1,mem))
      {
      ShowMSG(1,(int)"Вход\nвыполнен !");
      RunElfs();
      CloseCSM(MAINCSM_ID);
      }else
      {
      ErrorMSG();
      fclose(hFile, &io_error);
     }
     mfree(mem);
     }
     }else
  if(y==91)
    {
  //sprintf(name,DIR_RUN_S2,"\\password_2.ini");
    hFile = fopen(DIR_RUN_S2,A_ReadOnly+A_BIN,P_READ, &io_error);
    if(hFile!=-1)
     {
     mem=malloc(100);
     int size=fread(hFile,mem, 100, &io_error);
     *(mem+size)=0;
     if (strstr(PASSWORD_SET2,mem))
     {
     ShowMSG(1,(int)"Вход\nвыполнен !");
     RunElfs();
     CloseCSM(MAINCSM_ID);
     }else
     {
       ErrorMSG();
       fclose(hFile, &io_error);
     }
     mfree(mem);
     }
  }
  }
  else
  if (UZERS==3)
  { 
  if(y==43)
  {
  //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
  hFile = fopen(DIR_RUN_S1,A_ReadOnly+A_BIN,P_READ, &io_error);
  if(hFile!=-1)
   {
     mem=malloc(100);
     int size=fread(hFile,mem, 100, &io_error);
     *(mem+size)=0;
     if (strstr((char*)PASSWORD_SET1,mem))
     {
     ShowMSG(1,(int)"Вход\nвыполнен !");RunElfs();
     CloseCSM(MAINCSM_ID);
     }else
     {
       ErrorMSG();
       fclose(hFile, &io_error);
     }
     mfree(mem);
  }
  }else
  if(y==75)
  {
  //sprintf(name,DIR_RUN_S2,"\\password_2.ini");
    hFile = fopen(DIR_RUN_S2,A_ReadOnly+A_BIN,P_READ, &io_error);
    if(hFile!=-1)
    {
     mem=malloc(100);
     int size=fread(hFile,mem, 100, &io_error);
     *(mem+size)=0;
     if (strstr((char*)PASSWORD_SET2,mem))
     {
     ShowMSG(1,(int)"Вход\nвыполнен !");RunElfs();
     CloseCSM(MAINCSM_ID);
     }else
     {
       ErrorMSG();
       fclose(hFile, &io_error);
     }
     mfree(mem);
  }
  }
  if(y==107)
  {
  //sprintf(name,DIR_RUN_S3,"\\password_3.ini");
  hFile = fopen(DIR_RUN_S3,A_ReadOnly+A_BIN,P_READ, &io_error);
  if(hFile!=-1)
   {
     mem=malloc(100);
     int size=fread(hFile,mem, 100, &io_error);
     *(mem+size)=0;
     if (strstr((char*)PASSWORD_SET3,mem))
     {
     ShowMSG(1,(int)"Вход\nвыполнен !");RunElfs();
     CloseCSM(MAINCSM_ID);
     }else
     {
       ErrorMSG();
       fclose(hFile, &io_error);
     }
     mfree(mem);
  }
  }
  } 
  }
 
  else
  {
  ErrorMSG();
  }  
   //FreeWS(text);
}
  

//-----------------------------------------------------------------------------


    


/*void UpDateSet()
{
  InitConfig();
  if (UZERS==1)y=75; else
  if (UZERS==2)y=59; else
  if (UZERS==3)y=43;
  //DIC(y);
}*/

void OnRedraw(MAIN_GUI *data)
{
  
  DrawRoundedFrame(0,0,131,175,0,0,0,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(0));
  
  WSHDR *ws = AllocWS(512);
  WSHDR *ascii2ws(char *s);
  /*char name[256];
  sprintf(name,folder_pic,"\\background.png");
  DrawImg(0,0,(int)name);*/
  //char *dann=ws2ascii(*ws);
  DrawImg(0,0,(int)PIC_FON);
  DrawImg(115,160,(int)PIC_OFF);
  if (UZERS==0)
  {}else
  {
  DIC(y);
  }
  if (UZERS==1){//x=10;
                //y=75;
                //DIC(75);
                DISET1(0);
                //DrawImg(10,y,(int)"4:\\Zbin\\StartMan\\img\\cursor.png");
                //ascii2ws(NAME_S1);
                wsprintf(ws,per_t,NAME_S1);
                DrawString(ws,35,80,35+150,70+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
                } else
    if (UZERS==2){//y=59;
                  //DIC(59);
                  //DrawImg(10,y,(int)"4:\\Zbin\\StartMan\\img\\cursor.png");
                  DISET1(-16);
                  wsprintf(ws,per_t,NAME_S1);
                  DrawString(ws,35,64,35+150,64+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
                  DISET2(16);
                  wsprintf(ws,per_t,NAME_S2);
                  DrawString(ws,35,96,35+150,96+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
                  } else
      if (UZERS==3){//y=43;
                   // DIC(43);
                    //DrawImg(10,y,(int)"4:\\Zbin\\StartMan\\img\\cursor.png");
                    DISET1(-32);
                    wsprintf(ws,per_t,NAME_S1);
                    DrawString(ws,35,48,35+150,48+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
                    DISET2(0);
                    wsprintf(ws,per_t,NAME_S2);
                    DrawString(ws,35,80,35+150,80+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
                    DISET3(32);
                    wsprintf(ws,per_t,NAME_S3);
                    DrawString(ws,35,112,35+150,112+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
      }
 // DrawImg(x,y,(int)"4:\\Zbin\\StartMan\\img\\cursor.png");
  //if (ERMSG==1) DrawImg(10,10,(int)"4:\\Zbin\\StartMan\\img\\cursor.png");
  if (TURNOFF==1)
   {
    int x, y;
   
   switch(mode1)
    {
    case 0:
    //if (mode==0);
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SR)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SR)/2;
        DrawImg(x, y, (int)ICONS_SR);
      }
      break;
      case 1:
  /// if (mode==1);  
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SD)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SD)/2;
        DrawImg(x, y, (int)ICONS_SD);
      }
      break;
      case 2:
    //if (mode==0);  
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_RB)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_RB)/2;
        DrawImg(x, y, (int)ICONS_RB);
      }
     break;
    }  
   }
  
 // wsprintf(ws,per_t,"Выключить");DrawString(ws,85бностью,165,115+150,165+120,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  //InitConfig();
}

/*void ErrorMSGs(GUI *data)
{
ErrorMSG();
}*/


//Ввод пароля///////////////////////////////////////////////////////////////////
//extern const char PASSWORD;

GUI *ggui=0;

#define wslen(ws) ws->wsbody[0]

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}



    

void save_file(void)
{
  
  EDITCONTROL ec;
  ExtractEditControl(ggui, 2, &ec);     
  char *text=ws2ascii(ec.pWS);
  volatile int hFile;
  unsigned int io_error = 0;

  if (UZERS==1)
  {
  //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
  hFile = fopen(DIR_RUN_S1,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }
  else
  if (UZERS==2)
  { 
  if(y==59)
  {
  //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
  hFile = fopen(DIR_RUN_S1,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }else
  if(y==91)
  {
  //sprintf(name,DIR_RUN_S2,"\\password_2.ini");
  hFile = fopen(DIR_RUN_S2,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }
  }
  else
  if (UZERS==3)
  { 
  if(y==43)
  {
  //sprintf(name,DIR_RUN_S1,"\\password_1.ini");
  hFile = fopen(DIR_RUN_S1,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }else
  if(y==75)
  {
  //sprintf(name,DIR_RUN_S2,"\\password_2.ini");
  hFile = fopen(DIR_RUN_S2,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }
  if(y==107)
  {
  //sprintf(name,DIR_RUN_S3,"\\password_3.ini");
  hFile = fopen(DIR_RUN_S3,A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
  }
  }  
  if(hFile!=-1)
   {
     fwrite(hFile, text, strlen(text), &io_error);
     fclose(hFile, &io_error);
   }
  mfree(text);
  mode=1;
  //ShowMSG(1,(int)"Saved txt");
}

void RUC(){RunElfs();CloseCSM(MAINCSM_ID);}
//Загрузка демонов//////////////////////////////////////////////////////////////
//const char elfpath[]="4:\\Zbin\\altdaemons\\";
void RunElfs()
{
  WSHDR *ws;
  ws=AllocWS(150);
  DIR_ENTRY de; //директория
  unsigned int err;//ошибка
  char dname[256];//описание переменной
  if (UZERS==1) strcpy(dname,DIR_RUN_DE1);
  if (UZERS==2)
     { 
     if(y==59) strcpy(dname,DIR_RUN_DE1);else
     if(y==91) strcpy(dname,DIR_RUN_DE2);
     }
  if (UZERS==3)
     { 
     if(y==43) strcpy(dname,DIR_RUN_DE1);else
     if(y==75) strcpy(dname,DIR_RUN_DE2);else
     if(y==107)strcpy(dname,DIR_RUN_DE3);
     }
  strcat(dname,"*.elf");//создание строки с расширением еlf
  if (FindFirstFile(&de,dname,&err))//ecли поиск, в директории и имени
  {
    do
    {
      strcpy(dname,de.folder_name);
      strcat(dname,"\\");
      strcat(dname,de.file_name);
      str_2ws(ws,dname,128);
      ExecuteFile(ws,0,0);
    }
    while(FindNextFile(&de,&err));
  }
  FreeWS(ws);
  KbdUnlock();
}

////////////////////////////////////////////////////////////////////////////////


#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

int elinfo_onkey(GUI *gui, GUI_MSG *msg){if (msg->keys==0x18){return(-1);}return(0);}
void elinfo_ghook(GUI *gui, int cmd)
{
  if(cmd==0xA)
{
  //void SavePassword();
  DisableIDLETMR();
}
  if(cmd==0x03)
  {
    
    void SavePassword();
   //FreeWS(elws);
   // elws = NULL;
  }
}

void edchat_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC skk={0x0018, 0x0000,(int)"Ok"};
  if (cmd==7)
  SetSoftKey(data,&skk,SET_SOFT_KEY_N); 
}

int itemnum, wd_id;

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  
  void create_ed(void);
  
  switch (msg->gbsmsg->submess)
  {
    
#ifndef NEWSGOLD
  case RED_BUTTON:
    
    CloseCSM(MAINCSM_ID);
    break;
#endif  
    
  case GREEN_BUTTON:
      save_file();
    break;
  
  case LEFT_SOFT:
        save_file();
    break;
    }
  if (msg->keys==0x18)
  {
    void SavePassword();
   return(-1);
    //MMenu();
  }
  if (msg->keys==0x1)
  {
    void SavePassword();
   // CloseCSM(MAINCSM_ID);
  }
  return(0); 
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"Пароль:",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  elinfo_ghook,
  //edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

///ВВОД ПАРОЛЯ//////////////////////////////////////////////////////////////////
void EnterPassword()
{
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(50);
  if (UZERS==1)
  {
  utf8_2ws(ws,NAME_S1,20);
  }
  else
  if (UZERS==2)
  { 
  if(y==59)
  {
  utf8_2ws(ws,NAME_S1,20);
  }else
  if(y==91)
  {
  utf8_2ws(ws,NAME_S2,20);
  }
  }
  else
  if (UZERS==3)
  { 
  if(y==43)
  {
  utf8_2ws(ws,NAME_S1,20);
  }else
  if(y==75)
  {
  utf8_2ws(ws,NAME_S2,20);
  }
  if(y==107)
  {
  utf8_2ws(ws,NAME_S3,20);
  }
  }  
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  
  AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,10);
  AddEditControlToEditQend(eq,&ec,ma);  
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
}

// menu

void SavePassword()
{
  SUBPROC((void *)save_file);
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); //костыль!!
}
////////////////////////////////////////////////////////////////////////////////


void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
   if(Quit_Required)
  {
    GeneralFuncF1(1); 
  }

}

void Settings()
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}


int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
   
    if(Quit_Required)return 1; 
    REDRAW();
    if(msg->gbsmsg->msg==KEY_DOWN)
    {
    switch(msg->gbsmsg->submess)
    {
    /*  case RED_BUTTON:KbdLock();
      break;*/
    //case '*':RunElfs();break;  
      case ENTER_BUTTON://if (y==75)
      if (UZERS==0)
      {
        KbdUnlock();
        CloseCSM(MAINCSM_ID);
      }
      else
      {
   if (ENA_PASS==0)
    {     
     if (UZERS==1)RunElfs();CloseCSM(MAINCSM_ID);
     if (UZERS==2)
        { 
        if(y==59) RUC(); else
        if(y==91) RUC();
        }
     if (UZERS==3)
        { 
        if(y==43) RUC(); else
        if(y==75) RUC(); else
        if(y==107) RUC();
        }
    }
 }
 if (TURNOFF==1)
         {
          if(mode1==0)//Если Ждуший режим
          {
             if (WHAT_DO==1)
             {
              KbdLock();
              TURNOFF=0;
              }
              else ShowMSG(1,(int)"Ждущий режим!");// SetProfile(PROFILE-1);
          }
           else
          if(mode1==1)//Выключение
              {
                CloseCSM(MAINCSM_ID);
                GBS_DelTimer(&tmr);
                SwitchPhoneOff();
              }//ShowMSG(1,(int)"Выключить!");  
          else
            if(mode1==2) 
             {ShowMSG(1,(int)"Перезагрузка!"); 
             RebootPhone();
             }//
           }    
        else
       {
      //GetpassINFO();
      EnterPassword();
       }
      break;
      case GREEN_BUTTON:
      if (UZERS==0)
      {
      KbdUnlock();
      CloseCSM(MAINCSM_ID);
      }
      else 
      {  
      if (TURNOFF==1)
      {
      }
      else
      {
      GetpassINFO();
      //ErrorMSG();
      }
    }
      break;
    //case '1': SavePassword(); break;
    //case '7':ErrorMSG();break;
    //case '0': UpDateSet();TURNOFF=0;break;
    /*case LEFT_SOFT:  if (TURNOFF==1)
                                         {
                                          }else
                                         {
                                           Settings();
                                         }break;*/
    case RIGHT_SOFT: /*TURNOFF=1;*/if(TURNOFF==1)TURNOFF=0;else if(TURNOFF==0)TURNOFF=1;
    mode1=1;
      //OpenTurnOff();
      break;
    case LEFT_BUTTON:if(mode1==1)mode1=0;else if(mode1==2)mode1=1; else if(mode1==0)mode1=2;
         break;
    case RIGHT_BUTTON:if(mode1==1)mode1=2;else if(mode1==2)mode1=0; else if(mode1==0)mode1=1;
         break;    
      //return(1);
    case UP_BUTTON:        if (TURNOFF==1)
                                         {
                                          }else
                                          {      
                                           if (UZERS==1){
                                            y=75;
                                            }
                                            else  
                                if (UZERS==2){
                                             if (y==59)y=91;else y-=32;
                                             }
                                             else
                                  if (UZERS==3){
                                               if(y==43)y=107;else y-=32;
                                               }
                                          }
                                               break;
    case DOWN_BUTTON:  if (TURNOFF==1)
                                         {
                                          }else
                                          { 
                                        if (UZERS==1)
                                    {
                                    y=10;
                                    y=75;
                                    } else
                                    if (UZERS==2)
                                      {
                                        x=10; 
                                        if(y==91)y=59;else y+=32;
                                         }
                                       if (UZERS==3)
                                         {
                                         x=10; 
                                         if(y==107)y=43;else y+=32;
                                         }
                                          }
                                      break;
    }}
    if (msg->gbsmsg->msg==LONG_PRESS)
    {
    switch(msg->gbsmsg->submess)
    {
     /* case RED_BUTTON:KbdLock();
      break;*/
    //case '#':KbdUnlock();break;
   
    case RED_BUTTON: KbdLock();
    break;
    }
              
  }           
  return(0);
}



void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
  GBS_DelTimer(&tmr);
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
  GBS_DelTimer(&tmr);
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,	
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
    
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

void setparams()
{
  SetIllumination(0, 1,ILL_NUM,10); 
  GBS_StartTimerProc(&tmr,100,setparams);
}
  

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
  GBS_DelTimer(&tmr);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      UpDateSet();
      //ShowMSG(1,(int)"PicPusk config updated!");
    }
  }

  
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {//meerc.ifmo ip
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"StartMan");
}
int main(void)
{
  //old_light=GetIlluminationDataTable()[3];
  KbdLock();
  GBS_StartTimerProc(&tmr,100,setparams);
  UpDateSet();
  CSM_RAM main_csm;
  UpdateCSMname();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  return 0;
}

