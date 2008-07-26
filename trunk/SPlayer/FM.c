#include "../inc/swilib.h"
#include "main.h"
#include "FM.h"
#include "lang.h"
#include "playlist.h"


typedef struct
{
  GUI gui;
}SHOW_FM_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}SHOW_FM_CSM;
extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
//////////////////////////Переменные//////////////////////////////
WSHDR* Files[256];   // Массив путей к файлам/папкам   AAA
extern const char PIC_DIR[];
extern const char MUSIC[];
//extern char COLOR_BG[4];
extern const int SHOW_NAMES;
int MarkLines[256];  // Массив-маркер для выделения файлов   AAA
int CurFile=1;       // Текущий элемент   AAA
unsigned int TCFM=0; // Количество элементов   AAA
char nowpath[128];
extern unsigned short ShowNamesNoConst;
extern unsigned short FM_o;
extern const char p_3s[];
extern char COLOR[ncolor][4];
//////////////////////////Переменные//////////////////////////////

void PastFile(WSHDR *p, unsigned short i)
{
  Files[TCFM+1]=AllocWS(256);
  wstrcpy(Files[TCFM+1],p);
  TCFM++;
  if(i) {CurFile=TCFM;}
}

void DeleteFiles()
{
  DisableScroll();
  while(TCFM>0)
  {
    CurFile=1;
    FreeWS(Files[TCFM]);
    Files[TCFM]=NULL;
    TCFM--;
  }
}
/*
void Sortir(WSHDR** mass)
{
  WSHDR* buf=AllocWS(256);
  char* a=malloc(256);
  char* b=malloc(256);
  for(unsigned int j=0;j<TCFM;j++)
  {
    for(unsigned int i=0;i<TCFM;i++)
    {
      
        unsigned int j=0;
        for(unsigned int k=0;k<j+1;k++)
        {
          ws_2str(mass[i],a,256);
          ws_2str(mass[i+1],b,256);
          if(a[j]>b[j])
          {
            wstrcpy(buf,mass[i]);
            wstrcpy(mass[i],mass[i+1]);
            wstrcpy(mass[i+1],buf);
          }else{
            if(a[j]==b[j]) {j++;}
          }
        }
      
    }
  }
  FreeWS(buf);
  mfree(a);
  mfree(b);
}*/
/*
void Sortir(WSHDR** mass)
{
  WSHDR* buf=AllocWS(256);
  for(unsigned int j=0;j<TCFM;j++)
  {
    for(unsigned int i=0;i<TCFM;i++)
    {
      
        unsigned int j=0;
        for(unsigned int k=0;k<j+1;k++)
        {
          if(mass[i][j]>mass[i+1][j])
          {
            wstrcpy(buf,mass[i]);
            wstrcpy(mass[i],mass[i+1]);
            wstrcpy(mass[i+1],buf);
          }else{
            if(mass[i]==mass[i+1]) {j++;}
          }
        }
      
    }
  }
  FreeWS(buf);
}
*/
//LoadDaemonList(" 4:\\Doc\\");
void LoadDaemonList(const char* path, unsigned short re, unsigned short toPL) // Теперь пашет частично   AAA
{
 // ShowMSG(0,(int)path);
  
  if(toPL==0) {strcpy(nowpath, path);}
  DIR_ENTRY de;
  unsigned int err;
  char name[256];
  strcpy(name,path);
  strcat(name,"*");
  if(FindFirstFile(&de,name,&err))
  {
    do
    {
      char* p1=malloc(256);
      WSHDR* p=AllocWS(256);
      strcpy(name,path);
      strcat(name,de.file_name);
      
      if (!isdir(name, &err))//(de.file_attr&FA_DIRECTORY)
      {
        int a=de.file_name[strlen(de.file_name)-3];
        int b=de.file_name[strlen(de.file_name)-2];
        int c=de.file_name[strlen(de.file_name)-1];
        if(((a=='m'||a=='M')&&(b=='p'||b=='P')&&c=='3')||
           ((a=='w'||a=='W')&&(b=='a'||b=='A')&&(c=='v'||c=='V'))||
            ((a=='a'||a=='A')&&(b=='a'||b=='A')&&(c=='c'||c=='C'))||
             ((a=='m'||a=='M')&&(b=='i'||b=='I')&&(c=='d'||c=='D'))||
              ((a=='s'||a=='S')&&(b=='p'||b=='P')&&(c=='l'||c=='L'))||
               ((a=='m'||a=='M')&&b=='3'&&(c=='u'||c=='U')))   // Перерываем форматы   AAA
        {
          
          strcpy(p1,name);
          fix(p1);
          utf8_2ws(p,p1,256);
          if(toPL==0) {PastFile(p, 0);}
          else {
            if(((a=='s'||a=='S')&&(b=='p'||b=='P')&&(c=='l'||c=='L'))||
               ((a=='m'||a=='M')&&b=='3'&&(c=='u'||c=='U'))){   // Перерываем форматы   AAA
                 LoadPlaylist(name);
               }else{
                 PastLine(p, 0);
               }
          }
        }
      }
      else
      {
        if(re==1) {strcat(name,"\\"); LoadDaemonList(name, re, toPL);}
        else{
          strcpy(p1,name);
          strcat(p1,"\\");
          fix(p1);
          utf8_2ws(p,p1,256);
          PastFile(p, 0);
        }
      }
      FreeWS(p);
      mfree(p1);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
 // Sortir(Files);
}

void LoadingDaemonList(const char* path, unsigned int re, unsigned int toPL)
{
  DeleteFiles();  // Перед загрузкой все стираем   AAA
  LoadDaemonList(path, re, toPL);
}

void NULLmass(int* mass, unsigned int end) {for(unsigned int i=0; i<end+1; i++) {mass[i]=0;}}   // Обнуляем массив-маркер   AAA

void CopyFName(WSHDR** mlines, int* mark, unsigned int imax)   // Копируем пути к файлам в пл   AAA
{
  unsigned int err;
  char path[256];
  for(unsigned int i=1; i<imax+1; i++)
  {
    if(mark[i])
    {
      ws_2str(mlines[i],path,256);
      if(isdir(path,&err))
      {
        LoadDaemonList(path, 1, 1);
      }else{
        int a=path[strlen(path)-3];
        int b=path[strlen(path)-2];
        int c=path[strlen(path)-1];
        if(((a=='s'||a=='S')&&(b=='p'||b=='P')&&(c=='l'||c=='L'))||
           ((a=='m'||a=='M')&&b=='3'&&(c=='u'||c=='U'))){   // Перерываем форматы   AAA
             LoadPlaylist(path);
           }else{
             PastLine(mlines[i], 0);
           }
      }
    }
  }
  NULLmass(mark, imax);
}

void GO()
{
  char pn[128];
  WSHDR* ws=AllocWS(256);
  NULLmass(MarkLines, TCFM);
if(strlen(nowpath)>3)
{
  nowpath[strlen(nowpath)-1]=0;
  const char *p=strrchr(nowpath,'\\')+1;
  strncpy(pn,nowpath,p-nowpath);
  pn[p-nowpath]='\0';
  LoadingDaemonList(pn, 0, 0);
}else{
  NULLchar(nowpath, 128);
  DeleteFiles();
  for(unsigned short i=0; i<5; i++)
  {
    if(i!=3){
      wsprintf(ws, "%d:\\", i);
      PastFile(ws, 0);
    }}}
FreeWS(ws);
}

static void OnRedraw(SHOW_FM_GUI *data)
{
  if (data->gui.state==2)//это нужно для того, чтобы действия происходили только в этом гуе
  {
    #ifdef ELKA
    unsigned short top = 24;
    #else
    unsigned short top = 0;
    #endif
    DrawRoundedFrame(0,top,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(1),COLOR[2]);
    #ifndef NO_PNG
    char sfname1[256];
    sprintf(sfname1,p_3s,PIC_DIR,items1[0],PNGEXT);
    DrawImg(0,top,(int)sfname1);  // Рисуем фон
    #else
    #endif
    if(strlen(nowpath)) {ShowNamesNoConst=3;}
    else {ShowNamesNoConst=1;}
    PL_Redraw(Files ,&CurFile, 0, MarkLines, &TCFM, 0, 0);  // MarkLines тут не совсем подходит... Надо будет подкорректировать...   AAA
    
  }
}

void FreeMemFM();

static int OnKeyFM(SHOW_FM_GUI *data, GUI_MSG *msg)//горячо любимый онкей
{
  unsigned int err;
  char* p=malloc(256);
 int sh=msg->gbsmsg->msg;
  switch(sh)
  {
   case KEY_DOWN:
    switch(msg->gbsmsg->submess)
    {
    case LEFT_SOFT:
      FreeMemFM();
      return (1);
    case RIGHT_SOFT:
      if(strlen(nowpath))
      {
        GO();
        OpenAnim();
        }else{
      FreeMemFM();
      return (1);
      }
      break;
    case GREEN_BUTTON:
      CTtoFirst();
      CopyFName(Files, MarkLines, TCFM);
      break;
    case ENTER_BUTTON:
      if(TCFM>0){
        ws_2str(Files[CurFile], p, 256);
        if(strlen(nowpath)){
          if (isdir(p, &err)) // Проверка папка или нет AAA
          {
            NULLmass(MarkLines, TCFM);
            LoadingDaemonList(p, 0, 0);
            OpenAnim();
          }else{
            int a=p[strlen(p)-3];
            int b=p[strlen(p)-2];
            int c=p[strlen(p)-1];
            if(!((a=='s'||a=='S')&&(b=='p'||b=='P')&&(c=='l'||c=='L'))&&
               !((a=='m'||a=='M')&&b=='3'&&(c=='u'||c=='U'))){
                 StopAllPlayback();
                 PlayMP3File(Files[CurFile]);
               }
          }
        }else{
          NULLmass(MarkLines, TCFM);
          LoadingDaemonList(p, 0, 0);
          OpenAnim();
        }
      }
      break;
    case UP_BUTTON:
      if(CurFile>1) {CurFile--;}
      else {CurFile=TCFM;}
      break;
    case DOWN_BUTTON:
      if(CurFile<TCFM) {CurFile++;}
      else {CurFile=1;}
      break;
    case RIGHT_BUTTON:
      
      break;
    case '1':
      NULLchar(nowpath, 128);
      GO();
      break;
    case '2':
      if(CurFile-6>0) {CurFile-=6;}
      else {CurFile=1;}
      break;
    case '8':
      if(CurFile+6<TCFM+1) {CurFile+=6;}
      else {CurFile=TCFM;}
      break;
    case '0':
      MarkLines[CurFile]=!MarkLines[CurFile];
      if(CurFile<TCFM) {CurFile++;}
      break;
    case '*':
      for(unsigned int i=1; i<TCFM+1; i++) {MarkLines[i]=!MarkLines[i];}
      break;
    }
    break;
  }
  mfree(p);
DirectRedrawGUI();//это тоже нужно
return 0;
}

void FreeMemFM()
{
  DeleteFiles();
  CurFile=1;
  FM_o=0;
  NULLmass(MarkLines, TCFM);
  ShowNamesNoConst=SHOW_NAMES;
}

static void OnCreate(SHOW_FM_GUI *data,void *(*malloc_adr)(int))
{
       data->gui.state=1;
}
static void OnClose(SHOW_FM_GUI *data,void (*mfree_adr)(void *))
{
    data->gui.state=0;
}

static void OnFocus(SHOW_FM_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  // #ifdef ELKA
  //  DisableIconBar(1);//эт убить иконбар,можно и убрать
  //  #endif
    DisableIDLETMR();
    data->gui.state=2;
}

//Unfocus
static void OnUnfocus(SHOW_FM_GUI *data,void (*mfree_adr)(void *))
{
  //  #ifdef ELKA
  //  DisableIconBar(0);
  //  #endif
        if (data->gui.state!=2) return;
        data->gui.state=1;
}

static int met0(void){return(0);}
static const void * const SHOW_FM_gui_methods[11]={
  (void *)OnRedraw,
  (void *)OnCreate,
  (void *)OnClose,
  (void *)OnFocus,
  (void *)OnUnfocus,
  (void *)OnKeyFM,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)met0,
  (void *)met0,
  0
};

void ShowFM()
{
static const RECT Canvas={0,0,0,0};
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  SHOW_FM_GUI *main_gui=malloc(sizeof(SHOW_FM_GUI));
  zeromem(main_gui,sizeof(SHOW_FM_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)SHOW_FM_gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  
  CreateGUI(main_gui);
  
  FM_o=1;
  NULLchar(nowpath, 128);
  NULLmass(MarkLines, TCFM);
  if(strlen(MUSIC)) {LoadingDaemonList(MUSIC, 0, 0);}
  else {GO();}
}
