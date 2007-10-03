#include "../inc/swilib.h"
#include "../inc/playsound.h"
#include "conf_loader.h"
#include "main.h"
#include "mainmenu.h"
#include "playlist.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

const int minus11=-11; // стремная константа =)

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

//--- Собственно, переменные координат AAA ---
unsigned int VOLmy_x;
unsigned int VOLmy_y;
unsigned int STATmy_x;
unsigned int STATmy_y;
unsigned int CTmy_x;  // Координаты CurrentTrack
unsigned int CTmy_y;
unsigned int s;     // Смещение по вертикали
unsigned int NUMmy_x;
unsigned int NUMmy_y;
unsigned int RANDmy_x;
unsigned int RANDmy_y;
//--- Собственно, переменные координат AAA ---

//--- настройки из конфига ---
extern const char COLOR_BG[];
extern const char COLOR_TEXT[];
extern const char PIC_DIR[];
extern const char I_BACKGROUND[];
extern const char SKIN[];
extern const char DEFAULT_PLAYLIST[];
extern const unsigned int IDLE_X;
extern const unsigned int IDLE_Y;
//--- настройки из конфига ---

//--- Переменные! --- Не путать с константами из конфига!
extern short phandle;  // Для определения конца воспр.  AAA
extern char GetAccessoryType();
extern char PlayingStatus;
char Quit_Required = 0;     // Флаг необходимости завершить работу
int playmode; // 0 - играем все, 1 - повторить все, 2 - перемешать, 3 - повторять один  AAA
int mode; // 1, если длинное нажатие боковой клавиши
//--- Переменные! ---

void load_skin();       // Из skin.cfg AAA
void UpdateCSMname(WSHDR * tname);

//--- Наши переменные ---

// Играем MP3 файл
void PlayMP3File(const char * fname)
{
  if (!IsCalling()) // Нет ли звонка
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1) // Проверка файла на существование
    {
      PLAYFILE_OPT pfopt;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      
      const char *p=strrchr(fname,'\\')+1; // Переписал этот блок нахрен... (c) Rst7  // DemonGloom :) 
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      zeromem(&pfopt,sizeof(PLAYFILE_OPT));
      pfopt.repeat_num=1;
      pfopt.time_between_play=0;
      pfopt.play_first=0;
      pfopt.volume=GetVolLevel();
#ifdef NEWSGOLD
      pfopt.unk6=1;
      pfopt.unk7=1;
      pfopt.unk9=2;
      SetPHandle(PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt)); // Вместо 0xC было 0x10 ... Пробуйте так!!
      SetPlayingStatus(2);
      PlayMelody_ChangeVolume(phandle,GetVolLevel());  // Что бы была нормальная громкость - иначе криво...
#else 
      pfopt.unk4=0x80000000;
      pfopt.unk5=1;
      SetPHandle(PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt));
      SetPlayingStatus(2);
      PlayMelody_ChangeVolume(phandle,GetVolLevel());  // Что бы была нормальная громкость - иначе криво...
      
#endif
      UpdateCSMname(sndFName); // Покажем что играем XTask Blind007
      FreeWS(sndPath);
      FreeWS(sndFName);
    } else {
      // Если нет такого файла!
      ShowMSG(1,(int)"Can't find file!");
    }
  }
}

// Грузим координаты из skin.cfg AAA
void load_skin(void)
{
  char *data; 
  unsigned int err; 
  int handle; 
  handle=fopen(SKIN, A_ReadOnly, P_READ,&err); 
  if(handle!=-1)
  {
    data=malloc(19);
    if(data!=0)
      {
        fread(handle,data,19,&err); // Экономим память! :)
        
        VOLmy_x=data[2];
        VOLmy_y=data[3]+data[4];
        STATmy_x=data[5];
        STATmy_y=data[6]+data[7];
        CTmy_x=data[8];
        CTmy_y=data[9]+data[10];
        s=data[11];
        NUMmy_x=data[12];
        NUMmy_y=data[13]+data[14];
        RANDmy_x=data[15];
        RANDmy_y=data[16]+data[17];
  
        mfree(data);
      }
    fclose(handle,&err);
  }
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  if(IsGuiOnTop(MAINGUI_ID))
  {
  int w = ScreenW();
  int h = ScreenH();
  int left = 0;
#ifdef ELKA
  int top = 24;
#else
  int top = 0;
#endif
//  DrawRoundedFrame(left+1,top,w-1,h-1,0,0,0,GetPaletteAdrByColorIndex(1),color(COLOR_BG));  // А это зачем??? Если нужно - объясни!   AAA
#ifdef USE_PNG_EXT
  // --- Делаем типа скин ---
  DrawImg(left,top,(int)I_BACKGROUND);  // Рисуем фон
  // Громкость
  char vfname[256];
  sprintf(vfname,"%s%s%i%s",PIC_DIR,"volume",GetVolLevel(),".png");
  DrawImg(VOLmy_x,top+VOLmy_y,(int)vfname);
  // Статус плеера
  char sfname[256];
  switch(GetPlayingStatus())
  {
  case 0:
    sprintf(sfname,"%s%s",PIC_DIR,"stop.png");
    break;
  case 1:
    sprintf(sfname,"%s%s",PIC_DIR,"pause.png");
    break;
  case 2:
    sprintf(sfname,"%s%s",PIC_DIR,"play.png");
    break;
  }
  DrawImg(STATmy_x,top+STATmy_y,(int)sfname);
  // Режим воспроизв
  char pfname[256];
  switch(playmode)
  {
  case 0:
    sprintf(pfname,"%s%s",PIC_DIR,"playall.png");
    break;
  case 1:
    sprintf(pfname,"%s%s",PIC_DIR,"repeat.png");
    break;
  case 2:
    sprintf(pfname,"%s%s",PIC_DIR,"random.png");
    break;
  case 3:
    sprintf(pfname,"%s%s",PIC_DIR,"repeatone.png");
    break;
  }
  DrawImg(RANDmy_x,RANDmy_y,(int)pfname);  // Позиционируем все что видим!   AAA
#endif

    PL_Redraw();
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  DisableIDLETMR(); //Дабы не закрывался сам AAA
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  DisableIDLETMR(); //Дабы не закрывался сам AAA
}

void QuitCallbackProc(int decision)
{
  if(decision==0)Quit_Required = 1;
}

/*
  Обработчик нажатий клавиш. Сюда передаются нажатия клавиш
  в виде сообщения GUI_MSG, пример декодирования ниже.
*/
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if(Quit_Required)return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      MsgBoxYesNo(1,(int)"Закрыть SPlayer?",QuitCallbackProc);
      break;
    case LEFT_SOFT:
      MM_Show();
      break;
    case GREEN_BUTTON:  // По зеленой кнопке загружаем плейлист по умолчанию...
      CTandPTtoFirst();
      LoadingPlaylist(DEFAULT_PLAYLIST);
      break;
    case ENTER_BUTTON:  // на будущее...
      PlayTrackUnderC();
      break;
    case UP_BUTTON:
      CTUp();
      break;
    case DOWN_BUTTON:
      CTDown();
      break;
//    case VOL_UP_BUTTON:
//      VolumeUp();
//      break;
//    case VOL_DOWN_BUTTON:
//      VolumeDown();
//      break;
    case '0':           // Останавливаем воспроизведение
      StopAllPlayback();
      break;
    case '5':           // Play/Pause
      TogglePlayback();
      break;
    case '4':           // Переключение на предыдущий трек
      PreviousTrack();
      break;
    case '7':           // Переключение на предыдущий трек6
      CTUpSix();
      break;
    case '1':           // Забиваем. Здесь будет перемотка :)
      break;
    case '3':           // Забиваем. Здесь будет перемотка :)
      break;
    case '6':           // Переключение на следующий трек
      if (playmode==2) RandTrack(); else NextTrack();
      break;
    case '9':           // Переключение на предыдущий трек6
      CTDovnSix();
      break;
    case '*':
      ToggleVolume();
      break;
    case '#':
      playmode+=1;
      if (playmode==4) playmode=0;
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:
        CTUp();
      break;
      case DOWN_BUTTON:
        CTDown();
      break;
      case '2':
        PreviousTrack();
      break;
      case '3':
        CTUpSix();
      break;
      case '8':
        NextTrack();
      break;
      case '9':
        CTDovnSix();
      break;
    }
    REDRAW();
  }
  return(0);
}

int my_keyhook(int submsg,int msg)
{
#ifdef ELKA
  if (submsg==POC_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {StopAllPlayback(); mode=1;  REDRAW(); return 2;}
    case KEY_UP: if (mode==0) TogglePlayback(); else {mode=0;  REDRAW(); return 2;}
    }}
#endif
  if (submsg==VOL_UP_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  REDRAW(); return 2;
      case KEY_UP: if (mode==0) VolumeUp(); else mode=0;  REDRAW(); return 2;
    }}
  if (submsg==VOL_DOWN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS: if (mode==0) {PreviousTrack(); mode=1; }  REDRAW(); return 2;
      case KEY_UP: if (mode==0) VolumeDown(); else mode=0;  REDRAW(); return 2;
    }}
  
  REDRAW();
  return(0);
}


// Destroy
extern void kill_data(void *p, void (*func_p)(void *));

// Всё ясно из названия ;) оставить как есть
static void ElfKiller(void)      //Добавил static не знаю зачем, главное - работает! :)  AAA
{
  extern void *ELF_BEGIN;
  RemoveKeybMsgHook((void *)my_keyhook);               //НАДО!!  AAA . Надо :) DemonGloom
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

//===============================================================================================
// ELKA Compatibility
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
//===============================================================================================

// Оставить как есть
int method8(void){return(0);}

// Оставить как есть
int method9(void){return(0);}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,0,0};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  DisableScroll();       // Оказалось его перед закрытием еще и останавливать надо... А то такое начинается! :D
  StopAllPlayback();
  SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (Quit_Required)
  {
    csm->csm.state=-3;
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  // Нарисуем иконку статуса на IDLESCREEN
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует
    {
#ifdef ELKA
	void *canvasdata=BuildCanvas();
#else
	void *idata=GetDataOfItemByID(igui,2);
	if (idata)
	{
	  void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif
        char sfname[256];
        switch(GetPlayingStatus())
	{
        case 0:
          sprintf(sfname,"%s%s",PIC_DIR,"stop.png");
          break;
        case 1:
          sprintf(sfname,"%s%s",PIC_DIR,"pause.png");
          break;
        case 2:
          sprintf(sfname,"%s%s",PIC_DIR,"play.png");
          break;
	}
        DrawCanvas(canvasdata,IDLE_X,IDLE_Y,IDLE_X+16,IDLE_Y+16,1);
	DrawImg(IDLE_X,IDLE_Y,(int)sfname);
#ifdef ELKA
#else
	}
#endif
    }
  }

  // если реконфиг
  
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"SPlayer config updated!");
      InitConfig();
    }
  }
  
  // Если вход.звонок или звонок закончился Blind007
  if (((msg->msg==MSG_INCOMMING_CALL)&&(PlayingStatus==2))||((msg->msg==MSG_END_CALL)||(PlayingStatus==1)))
  {
    TogglePlayback();
  }
  /*
  if (((msg->msg==MSG_INCOMMING_CALL)||(msg->msg==MSG_END_CALL))&((PlayingStatus==1)||(PlayingStatus==2)))
  {
    TogglePlayback();
  }
  */
       
  if (msg->msg==MSG_PLAYFILE_REPORT)   // Для определения конца воспр.  AAA
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==phandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_DONE)//||pmsg->cmd==M_SAE_PLAYBACK_ERROR)  // А зачем на следующий при ошибке?
      {
        switch(playmode)
        {
          case 0:
            NextTrack();
            StopAllPlayback();    //Тупо, не спорю, если придумаете лучше...  AAA
            break;
          case 1:
            NextTrack();
            break;
          case 2:
            RandTrack();
            break;
          case 3:
            RepeatTrack();
            break;
        }
        REDRAW();
      }
      if (pmsg->cmd==M_SAE_HANDSFREE_UPDATED)
      {
        GetAccessoryType();
      }
    }
  }
/*  if (msg->msg==MSG_INCOMMING_CALL)     // Идея хорошая но не пашет   AAA
   {
     TogglePlayback();
   }
  else
  if (msg->msg==MSG_END_CALL)
   {
   TogglePlayback();
   }
*/  return(1);
}

// Инициализация структуры MAINCSM
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
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

// Функция, которая устанавливает название этого CSM для X-Task.
// Покажем в XTask'e что играем! Blind007
void UpdateCSMname(WSHDR * tname)
{
  WSHDR * xtaskname = AllocWS(128);
  if (tname) {
    wsprintf(xtaskname,"%s - %w","SPlayer",tname);
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%w",xtaskname);
  } else {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SPlayer");
  }
  FreeWS(xtaskname);
}


// Основная процедура. Она первой получает управление при старте эльфа.
int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  playmode=0; // Думаю, что по умолчанию должен быть выключен! Blind007
  InitConfig();
  load_skin();
  
  // Если что-то передали в параметре - загружаем...
  if (fname)
  {
    LoadingPlaylist(fname);
  }
  else
  {
    // Если нет - грузим DEFAULT плейлист
    if (DEFAULT_PLAYLIST!="")
    {
      LoadingPlaylist(DEFAULT_PLAYLIST);
    }
  }
  UpdateCSMname(NULL); // Всего-то исправить :) Blind007
  LockSched();
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook); //Ни скока ебался прежде чем сделал... Итак! Кейхук! AAA :) DemonGloom
  UnlockSched();
  return 0;
}
