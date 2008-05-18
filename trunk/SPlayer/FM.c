#include "../inc/swilib.h"
#include "main.h"
#include "FM.h"
#include "lang.h"
//#include "playlist.h"


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
extern char COLOR_BG[4];
int MarkLines[256];  // Массив-маркер для выделения файлов   AAA
int CurFile=1;       // Текущий элемент   AAA
unsigned int TCFM=0; // Количество элементов   AAA
//////////////////////////Переменные//////////////////////////////
void DisableScroll(void);
extern void fix(char* p);
extern void PastLine(WSHDR *p, unsigned short i);
extern void PL_Redraw(WSHDR** mass, int* CurLine, int* MarkLine, unsigned int* AllLines, int CurList, int MarkList);

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
//Ищем файлы в папке   AAA
void FindMusic(const char *dir)
{
  DIR_ENTRY de;
  unsigned int err;
  char path[256];
  strcpy(path,dir);
  char *ptr=path+strlen(path)+1;
  strcat(path,"\\*.mp3");
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      strcpy(ptr,de.file_name);
      if(isdir(path,&err))
      {
       // FindMusic(path,i);
      }
      else
      {
        
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}*/
//LoadDaemonList(" 4:\\Doc\\");
int LoadDaemonList(const char* path) // Теперь пашет частично   AAA
{
 // ShowMSG(0,(int)path);
  DIR_ENTRY de;
  unsigned int err;
  char name[256];
  strcpy(name,path);
  strcat(name,"*.mp3");
  int count1=0;
  if(FindFirstFile(&de,name,&err))
  {
    do
    {
      char* p1=malloc(256);
      WSHDR* p=AllocWS(256);
      
      
      
      if (de.file_attr&FA_DIRECTORY) //если ето директория вызываем рекурсивно ето ф.
      {
      /*  strcpy(name,path);           // Рекурсия. чего то не пашет, но пока и не нужно   AAA
        strcat(name,de.file_name);
        strcat(name,"\\");
        count1=count1+LoadDaemonList(name);*/
        
        strcpy(p1,path);
        strcat(p1,de.file_name);
        strcat(p1,"\\");
        fix(p1);
        ShowMSG(0,(int)path);
        utf8_2ws(p,p1,256);
        PastFile(p, 0);
      }
      else
      {
        strcpy(p1,path);
        strcat(p1,de.file_name);
        fix(p1);
        utf8_2ws(p,p1,256);
        PastFile(p, 0);
        count1++;
      }
      FreeWS(p);
      mfree(p1);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return count1;
};

void LoadingDaemonList(const char* path)
{
  /*  if(TC[CurrentPL]>0)
    {
      MsgBoxYesNo(1,(int)"Заменить?",Change);
      if(change)
      {
        CTtoFirst();
        PTtoFirst();
        while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
      }
    }else{
      CTtoFirst();
    }*/
  DeleteFiles();  // Перед загрузкой все стираем   AAA
  LoadDaemonList(path);
}

void NULLmass(int* mass, unsigned int end) {for(unsigned int i=0; i<end; i++) {mass[i]=0;}}   // Обнуляем массив-маркер   AAA

void CopyFName(WSHDR** mlines, int* mark, unsigned int imax)   // Копируем пути к файлам в пл   AAA
{
  for(unsigned int i=0; i<imax; i++)
  {
    if(mark[i]) {PastLine(mlines[i], 0);}
  }
  NULLmass(mark, imax);
}







static void OnRedraw(SHOW_FM_GUI *data)
{
  if (data->gui.state==2)//это нужно для того, чтобы действия происходили только в этом гуе
  {
    DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(1),color(COLOR_BG));
    #ifndef NO_PNG
    char sfname1[256];
    sprintf(sfname1,"%s%s",PIC_DIR,"background.png");
    DrawImg(0,0,(int)sfname1);  // Рисуем фон
    #else
    #endif
    
    PL_Redraw(Files ,&CurFile, MarkLines, &TCFM, 0, 0);  // MarkLines тут не совсем подходит... Надо будет подкорректировать...   AAA
    
  }
}

void FreeMemFM();

static int OnKeyFM(SHOW_FM_GUI *data, GUI_MSG *msg)//горячо любимый онкей
{
  FSTATS fstats;
  unsigned int err;
  char* p=malloc(256);
 int sh=msg->gbsmsg->msg;
  switch(sh)
  {
   case KEY_DOWN:
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      FreeMemFM();
      return (1);
    case LEFT_SOFT:
      LoadingDaemonList(MUSIC);
      break;
    case RED_BUTTON:
      
      break;
    case GREEN_BUTTON:
      CopyFName(Files, MarkLines, TCFM);
      break;
    case ENTER_BUTTON:
      ws_2str(Files[CurFile], p, 256);
      if (GetFileStats(p,&fstats,&err)!=-1) // Проверка файла на существование
      {
        PlayMP3File(Files[CurFile]);
      }else{
        LoadingDaemonList(p);
      }
      break;
    case UP_BUTTON:
      CurFile--;
      break;
    case DOWN_BUTTON:
      CurFile++;
      break;
    case RIGHT_BUTTON:
      
      break;
    case LEFT_BUTTON:
      
      break;
    case '1':
      
      break;
    case '2':
      
      break;
    case '0':
      MarkLines[CurFile]=!MarkLines[CurFile];
      break;
    case '*':
      for(unsigned int i=0; i<TCFM; i++) {MarkLines[i]=!MarkLines[i];}
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
  NULLmass(MarkLines, TCFM);
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
    #ifdef ELKA
    DisableIconBar(1);//эт убить иконбар,можно и убрать
    #endif
    DisableIDLETMR();
    data->gui.state=2;
}

//Unfocus
static void OnUnfocus(SHOW_FM_GUI *data,void (*mfree_adr)(void *))
{
    #ifdef ELKA
    DisableIconBar(0);
    #endif
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
}
