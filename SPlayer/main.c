#include "../inc/swilib.h"
#include "../inc/playsound.h"
#include "conf_loader.h"
#include "main.h"
#include "mainmenu.h"
#include "playlist.h"
#include "lang.h"

/*
typedef struct {
 unsigned short type; //00 
 WSHDR *wfilename; //04 
 int unk_08 ; //08 
 int unk_0C; //0C 
 int unk_10 ; //10 
 int unk_14 ; //14 
 long length; //18 <-- return 
 int unk_1C; //1C 
 int unk_20 ; //20 
} TWavLen;*/

#pragma swi_number=0x45 
#ifdef NEWSGOLD 
__swi __arm int GetWavLen(char *filename); 
#else 
__swi __arm int GetWavLen(TWavLen *wl);
#endif

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

void Log(int dummy, char *txt)
{
  unsigned int ul;
  int f=fopen("0:\\SPlayer.log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
    fclose(f,&ul);
  }
}

const int minus11=-11; // стремная константа =)

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

extern int CurrentPL;
extern int PlayedPL;
extern unsigned short stop; // 1, если останавливаем листание   AAA
unsigned short copy=0; // 1, если копируем   AAA
unsigned short move=0; // 1, если перемещаем   AAA
unsigned short EditPL=0; // 1, если редактируем   AAA
int mode; // 1, если длинное нажатие боковой клавиши
int KeyLock; // 1, если заблокирована;
short Stat_keypressed = 0; // нажата ли клавиша изменения статуса?
short Mode_keypressed = 0; // нажата ли клавиша изменения режима проигрывания?
short N_keypressed = 0;
short P_keypressed = 0;

unsigned short w;

//--- Собственно, переменные координат AAA ---
unsigned short VOLmy_x;
unsigned short VOLmy_y;
unsigned short STATmy_x;
unsigned short STATmy_y;
unsigned short CTmy_x;  // Координаты CurrentTrack
unsigned short CTmy_y;
unsigned short s;     // Смещение по вертикали
unsigned short NUMmy_x;
unsigned short NUMmy_y;
unsigned short RANDmy_x;
unsigned short RANDmy_y;
unsigned short KeyLock_x;
unsigned short KeyLock_y;
unsigned short Next_x;
unsigned short Next_y;
unsigned short Prev_x;
unsigned short Prev_y;
// Полоса прокрутки
extern unsigned short BR_x;
extern unsigned short BR1_y;
extern unsigned short BR2_y;
extern unsigned short BR_w;
extern unsigned short BRC_x;
extern unsigned short BRC_w;
// Время
unsigned short time_x;
unsigned short time_y;
// Длительность
unsigned short length_x;
unsigned short length_y;
// Прогрессбар
unsigned short progress_x;
unsigned short progress_y;
unsigned short progress_x2;
unsigned short progress_y2;

//--- Собственно, переменные координат AAA ---

//--- Цвета AAA ---
char COLOR_TEXT[4];
char LINE_COLOR[4];
char COLOR_BG[4];
char COLOR_BG_CURSOR[4];
char COLOR_TEXT_CURSOR[4];
char COLOR_TEXT_PLAY[4];
char COLOR_BANDROLL[4];
char COLOR_BANDROLL_C[4];
char COLOR_PROG_BG[4];               // Фон прогрессбара
char COLOR_PROG_BG_FRAME[4];               // Ободок
char COLOR_PROG_MAIN[4];             // Сам прогресс
char COLOR_PROG_MAIN_FRAME[4];             // Ободок
//--- Цвета AAA ---

//--- настройки из конфига ---
//extern const char COLOR_BG[];
//extern const char COLOR_TEXT[];
//extern const char I_BACKGROUND[];
extern const char PIC_DIR[];
extern const char MUSIC[];
extern const char PLAYLISTS[];
extern const char DEFAULT_PLAYLIST[];
extern const char DEFAULT_PLAYLIST1[];
extern const char DEFAULT_PLAYLIST2[];
extern const unsigned int IDLE_X;
extern const unsigned int IDLE_Y;
extern const int PlayMode; 
extern const int soundvolume; 
//--- настройки из конфига ---

//--- Переменные ---
extern short phandle;  // Для определения конца воспр.  AAA
extern unsigned short PlayingStatus;
extern unsigned int TC[5];
char Quit_Required = 0;     // Флаг необходимости завершить работу
char list[256];
char sfname[256];
extern unsigned short SoundVolume;
int playmode;     // 0 - играем все, 1 - повторить все, 2 - перемешать, 3 - повторять один  AAA

// Переписываем время... DemonGloom
TWavLen wl;
GBSTMR mytmr;
int fm; // Длительность
int fs;
int sh; // Начальные
int sm;
int ss;
int nh; // Новые
int nm;
int ns;
int ph; // Сдвиг для паузы
int pm;
int ps;

//--- Переменные ---

void load_skin();       // Из skin.cfg AAA
void UpdateCSMname(WSHDR * tname);

void TimeRedraw();

// Пауза счетчика DemonGloom
void PausingTime(unsigned short action)
{
  // action == 0 - поставили паузу
  // action == 1 - сняли паузу
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  ns=time.sec-ss;
  if (ns<0){
    ns=60+ns;
    time.min--;
  }
  if (ns>60){
    ns=ns-60;
    time.min++;
  }
  nm=time.min-sm;
  if (nm<0){
    nm=60+nm;
    time.hour--;
  }
  if (nm>60){
    nm=nm-60;
    time.hour++;
  }
  nh=time.hour-sh;
  if (nh<0){
    nh=24+nh;
  }
  if (action==0)
  {
    ph=nh;
    pm=nm;
    ps=ns;
  } else 
  {
    GetDateTime(&date,&time);
    ss=time.sec-ps;
    sh=time.hour-ph;
    sm=time.min-pm;
    TimeRedraw();
  }
}
// Отрисовка времени DemonGloom
void EXT_REDRAW(){REDRAW();}

void TimeRedraw()
{
  WSHDR * time_disp = AllocWS(32);
  if (PlayingStatus==2){
  TDate date;
  TTime time; 
  GetDateTime(&date,&time);
  ns=time.sec-ss;
  if (ns<0){
    ns=60+ns;
    time.min--;
  }
  nm=time.min-sm;
  if (nm<0){
    nm=60+nm;
    time.hour--;
  }
  nh=time.hour-sh;
  if (nh<0){
    nh=24+nh;
  }
  }
  wsprintf(time_disp,"%02i:%02i",nm,ns);
  DrawString(time_disp,time_x,time_y,time_x+Get_WS_width(time_disp,FONT_SMALL),time_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,color(COLOR_TEXT),0);
#ifdef X75
  wsprintf(time_disp,"%02i:%02i",fm,fs);
  DrawString(time_disp,length_x,length_y,length_x+Get_WS_width(time_disp,FONT_SMALL),length_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,color(COLOR_TEXT),0);
#endif
  FreeWS(time_disp);
  if(IsGuiOnTop(MAINGUI_ID)) GBS_StartTimerProc(&mytmr,216,EXT_REDRAW);}

// Играем MP3 файл

int findmp3length(char *playy) { 
  #ifdef NEWSGOLD 
  return ((GetWavLen(playy))/1000); 
  #else
  TWavLen wl;
  zeromem(&wl, sizeof(wl));
  wl.type=0x2000;
  wl.wfilename=AllocWS(128);
  str_2ws(wl.wfilename,playy,128); 
  GetWavLen(&wl); 
  return (wl.length/1000);
  #endif 

}

void PlayMP3File(const char * fname)
{
if(TC[PlayedPL]>0)            // Теперь не рубится при отсутствии загруженного пл   AAA
{
  if (!IsCalling()) // Нет ли звонка
  {
    FSTATS fstats;
    unsigned int err;
    
    ph=0;
    pm=0;
    ps=0;
    nh=0;
    nm=0;
    ns=0;
    TDate date;
    TTime time; 
    GetDateTime(&date,&time);
    ss=time.sec;
    sh=time.hour;
    sm=time.min;

    if (GetFileStats(fname,&fstats,&err)!=-1) // Проверка файла на существование
    {
      PLAYFILE_OPT pfopt;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      
      const char *p=strrchr(fname,'\\')+1; 
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      zeromem(&pfopt,sizeof(PLAYFILE_OPT));
      pfopt.repeat_num=1;
      pfopt.time_between_play=0;
      pfopt.play_first=0;
      pfopt.volume=GetVolLevel();
      char *pp=strrchr(fname,':')-1;
#ifdef X75
      fs=findmp3length(pp);
      fm=(fs-(fs%60))/60;
      fs=fs%60;
#endif
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
//      BeginTime = SetBeginTime(); // Время начала играния файла Blind007
      FreeWS(sndPath);
      FreeWS(sndFName);
 /*     int PlayTime = GetWavkaLength((char*)sndPath,(char*)sndFName);
  WSHDR * t = AllocWS(64);
  wsprintf(t,"%i",PlayTime);
  DrawString(t,NUMmy_x,NUMmy_y+10,NUMmy_x+50,NUMmy_y+GetFontYSIZE(FONT_SMALL)+10,FONT_SMALL,0,
           color(COLOR_TEXT),0);
  FreeWS(t);
  REDRAW();*/
    } else {
      // Если нет такого файла!
      ShowMSG(1,(int)LG_Can_not_find_file);
    }
  }
}
else
{
  ShowMSG(1,(int)LG_Load_a_playlist);
}
}

// Грузим координаты из skin.cfg AAA
void load_skin(char const* cfgname)              // Извращенец... Такое создать... DG
{
  char *data; 
  unsigned int err; 
  int handle; 
  handle=fopen(cfgname, A_ReadOnly, P_READ,&err); 
  if(handle!=-1)
  {
    data=malloc(0xFF);
    if(data!=0)
      {
        fread(handle,data,0xFF,&err); // Экономим память! :)  Пошли вы куда подальше... Сами же забываете добавлять!!! DG
        if(data[2]==0x01)
        {
        // Полоса прокрутки
        BR_x=data[3];
        BR1_y=data[4]+data[5];
        BR2_y=data[6]+data[7];
        BR_w=data[8];
        BRC_x=data[9];
        BRC_w=data[10];
        // Полоса прокрутки
        s=data[11];
        CTmy_x=data[12];
        CTmy_y=data[13]+data[14];
        VOLmy_x=data[15];
        VOLmy_y=data[16]+data[17];
        STATmy_x=data[18];
        STATmy_y=data[19]+data[20];
        NUMmy_x=data[21];
        NUMmy_y=data[22]+data[23];
        RANDmy_x=data[24];
        RANDmy_y=data[25]+data[26];
        KeyLock_x=data[27];
        KeyLock_y=data[28]+data[29];
        Next_x=data[30];
        Next_y=data[31]+data[32];
        Prev_x=data[33];
        Prev_y=data[34]+data[35];
        // Время
        time_x=data[36];
        time_y=data[37]+data[38];
        // Длительность песни
        length_x=data[39];
        length_y=data[40]+data[41];
        // Прогрессбар
        progress_x=data[42];
        progress_y=data[43]+data[44];
        progress_x2=data[45];
        progress_y2=data[46]+data[47];
        }
        else
        {
          COLOR_TEXT[0]=data[3];
          COLOR_TEXT[1]=data[4];
          COLOR_TEXT[2]=data[5];
          COLOR_TEXT[3]=data[6];
          LINE_COLOR[0]=data[7];
          LINE_COLOR[1]=data[8];
          LINE_COLOR[2]=data[9];
          LINE_COLOR[3]=data[10];
          COLOR_BG[0]=data[11];
          COLOR_BG[1]=data[12];
          COLOR_BG[2]=data[13];
          COLOR_BG[3]=data[14];
          COLOR_BG_CURSOR[0]=data[15];
          COLOR_BG_CURSOR[1]=data[16];
          COLOR_BG_CURSOR[2]=data[17];
          COLOR_BG_CURSOR[3]=data[18];
          COLOR_TEXT_CURSOR[0]=data[19];
          COLOR_TEXT_CURSOR[1]=data[20];
          COLOR_TEXT_CURSOR[2]=data[21];
          COLOR_TEXT_CURSOR[3]=data[22];
          COLOR_TEXT_PLAY[0]=data[23];
          COLOR_TEXT_PLAY[1]=data[24];
          COLOR_TEXT_PLAY[2]=data[25];
          COLOR_TEXT_PLAY[3]=data[26];
          COLOR_BANDROLL[0]=data[27];
          COLOR_BANDROLL[1]=data[28];
          COLOR_BANDROLL[2]=data[29];
          COLOR_BANDROLL[3]=data[30];
          COLOR_BANDROLL_C[0]=data[31];
          COLOR_BANDROLL_C[1]=data[32];
          COLOR_BANDROLL_C[2]=data[33];
          COLOR_BANDROLL_C[3]=data[34];
          
          COLOR_PROG_BG[0]=data[35];
          COLOR_PROG_BG[1]=data[36];
          COLOR_PROG_BG[2]=data[37];
          COLOR_PROG_BG[3]=data[38];
          COLOR_PROG_BG_FRAME[0]=data[39];
          COLOR_PROG_BG_FRAME[1]=data[40];
          COLOR_PROG_BG_FRAME[2]=data[41];
          COLOR_PROG_BG_FRAME[3]=data[42];
          COLOR_PROG_MAIN[0]=data[43];
          COLOR_PROG_MAIN[1]=data[44];
          COLOR_PROG_MAIN[2]=data[45];
          COLOR_PROG_MAIN[3]=data[46];
          COLOR_PROG_MAIN_FRAME[0]=data[47];
          COLOR_PROG_MAIN_FRAME[1]=data[48];
          COLOR_PROG_MAIN_FRAME[2]=data[49];
          COLOR_PROG_MAIN_FRAME[3]=data[50];
        }
        mfree(data);
      }
    fclose(handle,&err);
  }
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  if(IsGuiOnTop(MAINGUI_ID))
  {
  w = ScreenW();
  unsigned short h = ScreenH();
  unsigned short left = 0;
#ifdef ELKA
  unsigned short top = 24;
#else
  unsigned short top = 0;
#endif
//  DrawRoundedFrame(left+1,top,w-1,h-1,0,0,0,GetPaletteAdrByColorIndex(1),color(COLOR_BG));  // А это зачем??? Если нужно - объясни!   AAA
#ifndef NO_PNG                         // Сделаем режим без скина - DG
  // --- Делаем типа скин ---
  char sfname[256];
  sprintf(sfname,"%s%s",PIC_DIR,"background.png");
  DrawImg(left,top,(int)sfname);  // Рисуем фон
  // Громкость
  char vfname[256];
  sprintf(vfname,"%s%s%i%s",PIC_DIR,"volume",GetVolLevel(),".png");
  DrawImg(VOLmy_x,VOLmy_y,(int)vfname);
  // Статус плеера
  if (Stat_keypressed==1)
  {
    switch(GetPlayingStatus())
    {
    case 0:
      sprintf(sfname,"%s%s",PIC_DIR,"stop_down.png");
      break;
    case 1:
      sprintf(sfname,"%s%s",PIC_DIR,"pause_down.png");
      break;
    case 2:
      sprintf(sfname,"%s%s",PIC_DIR,"play_down.png");
      break;
    }
  } else {
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
  }
  DrawImg(STATmy_x,STATmy_y,(int)sfname);
  // Режим воспроизв   AAA
  char pfname[256];
  if (Mode_keypressed==1)
  {
    switch(playmode)
    {
    case 0:
      sprintf(pfname,"%s%s",PIC_DIR,"playall_down.png");
      break;
    case 1:
      sprintf(pfname,"%s%s",PIC_DIR,"repeat_down.png");
      break;
    case 2:
      sprintf(pfname,"%s%s",PIC_DIR,"random_down.png");
      break;
    case 3:
      sprintf(pfname,"%s%s",PIC_DIR,"repeatone_down.png");
      break;
    }
  } else {
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
  }
  DrawImg(RANDmy_x,RANDmy_y,(int)pfname);  // Позиционируем все что видим!   AAA
  // Иконка пред/след трек   AAA
  char nextfname[256];
  if (N_keypressed==1)
  {
    sprintf(nextfname,"%s%s",PIC_DIR,"next_down.png");
  }
  else
  {
    sprintf(nextfname,"%s%s",PIC_DIR,"next.png");
  }
  DrawImg(Next_x,Next_y,(int)nextfname);
  char prevfname[256];
  if (P_keypressed==1)
  {
    sprintf(prevfname,"%s%s",PIC_DIR,"prev_down.png");
  }
  else
  {
    sprintf(prevfname,"%s%s",PIC_DIR,"prev.png");
  }
  DrawImg(Prev_x,Prev_y,(int)prevfname);
  // Если заблокировано DemonGloom
  if (KeyLock){
    sprintf(pfname,"%s%s",PIC_DIR,"keylock.png");
    DrawImg(KeyLock_x,KeyLock_y,(int)pfname);
  }
#else
#endif
                                     // Здесь будут универсальные строки, одинаковые как для png, так и для их отсутствия
#ifdef X75
  // Прогрессбар DG
  DrawRoundedFrame(progress_x,progress_y,progress_x2,progress_y2,2,2,0,
			COLOR_PROG_BG_FRAME,
			COLOR_PROG_BG);
  int ii=(progress_x2-progress_x)*(ns+nm*60);
  ii=ii/(fs+fm*60);
  DrawRoundedFrame(progress_x,progress_y,ii+progress_x,progress_y2,2,2,0,
			COLOR_PROG_MAIN_FRAME,
			COLOR_PROG_MAIN);
#endif
  
    PL_Redraw();
    TimeRedraw();
    
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

/* Блок функций. Неоходимо для конфига клавиш. */
void DoErrKey() {
  ShowMSG(1, (int)LG_Error_2);
}

void DoExit() {
  MsgBoxYesNo(1,(int)LG_Exit,QuitCallbackProc);
}

void LoadDefPlaylist() {
  CTtoFirst();
  PTtoFirst();
  LoadingPlaylist(DEFAULT_PLAYLIST);
}

void FindingMusic() {
  CTtoFirst();
  PTtoFirst();
  // FreePlaylist();
  FindMusic(MUSIC, 1);
}

void PrevTrackDown() {
  P_keypressed = 1;
  PreviousTrack();
}

void NextTrackDown() {
  N_keypressed = 1;
  if (playmode==2) RandTrack(); else NextTrack();
}

void SwitchPlayModeDown() {
  playmode+=1;
  if (playmode==4) playmode=0;
  Mode_keypressed = 1;
}
/* Блок функций. Неоходимо для конфига клавиш. */

/*
  Обработчик нажатий клавиш. Сюда передаются нажатия клавиш
  в виде сообщения GUI_MSG, пример декодирования ниже.
*/
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if(Quit_Required)return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
  if (KeyLock){
    if ((msg->gbsmsg->msg==LONG_PRESS)&&(msg->gbsmsg->submess=='#')){
     KbdUnlock();
     KeyLock=(KeyLock+1)%2;
     ShowMSG(1,(int)LG_Keypad_Unlock);
     REDRAW();}
     return 0;
     }
  else{
    if(EditPL==0)         //  Mr. Anderstand: самому не оч нравится такой вариант...
  {
  if (msg->gbsmsg->msg==KEY_UP) {
     Stat_keypressed = 0;
     P_keypressed = 0;
     N_keypressed = 0;
     Mode_keypressed = 0;
     REDRAW();
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    DoKey(msg->gbsmsg->submess,1);
    REDRAW();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:
        stop=0;
        CTUpSpeed();
      break;
      case DOWN_BUTTON:
        stop=0;
        CTDownSpeed();
      break;
      case '2':
        CTUpSix();
      break;
      case '3':
        sprintf(list,"%s%s",PLAYLISTS,"playlist");
        SavePlaylist(list);
      break;
      case '8':
        CTDownSix();
      break;
      case '9':
      break;
      case '#':
       if (KeyLock==0){
          KbdLock();
          Mode_keypressed = 0;
          ShowMSG(1,(int)LG_Keypad_Lock);
          KeyLock=1;
       }
      break;
      case '*':
        if (mode==0) {EditPL=!(EditPL); mode=1;}
      break;
    }
    REDRAW();
  }
  }else{
    
  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
      if(move==0) {stop=1;}
      break;
    case DOWN_BUTTON:
      if(move==0) {stop=1;}
      break;
    case '*':
      EditPL=!(EditPL);
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      MsgBoxYesNo(1,(int)LG_Exit,QuitCallbackProc);
      break;
    case RED_BUTTON:
      MsgBoxYesNo(1,(int)LG_Exit,QuitCallbackProc);
      break;
    case LEFT_SOFT:
      MM_Show();
      break;
    case GREEN_BUTTON:
      CTtoFirst();
      PTtoFirst();
      LoadingPlaylist(DEFAULT_PLAYLIST);
      break;
    case ENTER_BUTTON:
      move=!(move);
      break;
    case UP_BUTTON:
      if(move==0) {CTUp();}
      else {MoveLineUp();}
      break;
    case DOWN_BUTTON:
      if(move==0) {CTDown();}
      else {MoveLineDown();}
      break;
    case RIGHT_BUTTON:
      if(move==0) {NextPL();}
      else {MoveLineRight();}
      break;
    case LEFT_BUTTON:
      if(move==0) {PrevPL();}
      else {MoveLineLeft();}
      break;
    case '0':
      DeleteLine();
      break;
    case '2':
      if(move==0) {CTUpSix();}
      break;
    case '5':
      move=1;
      copy=1;
      break;
    case '8':
      if(move==0) {CTDownSix();}
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:
        if(move==0) {stop=0; CTUpSpeed();}
        else {MoveLineUp();}
      break;
      case DOWN_BUTTON:
        if(move==0) {stop=0; CTDownSpeed();}
        else {MoveLineDown();}
      break;
      case '2':
        CTUpSix();
      break;
      case '8':
        CTDownSix();
      break;
    }
    REDRAW();
  }
  }
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
  // А чем пл загружать?? AAA
/*#else
  if (submsg==GREEN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {StopAllPlayback(); mode=1;  REDRAW(); return 2;}
    case KEY_UP: if (mode==0) TogglePlayback(); else {mode=0;  REDRAW(); return 2;}
    }}*/
#endif
  if (submsg==VOL_UP_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // Следующий трек
      case KEY_UP: if (mode==0) VolumeUp(); else mode=0;  N_keypressed = 0; REDRAW(); return 2; // Громкость выше
    }}
  if (submsg==VOL_DOWN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS: if (mode==0) {PreviousTrack(); mode=1; }  P_keypressed = 1; REDRAW(); return 2;  // Предыдущий трек
      case KEY_UP: if (mode==0) VolumeDown(); else mode=0;  P_keypressed = 0; REDRAW(); return 2;  // Громкость ниже
    }}
  
  if ((submsg==0x27)){//&& !(IsCalling())){  // Если кнопка гарнитуры и не звонок
    switch (msg){
    case (KEY_DOWN): return 2;
    case (LONG_PRESS):  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // Следующий трек
    case (KEY_UP): if (mode==0) TogglePlayback(); else mode=0; N_keypressed = 0; REDRAW(); return 2;  // Переключение pause/play 
    }
  }
  
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
  MemoryFree();
  GBS_DelTimer(&mytmr);
  StopAllPlayback();  
  FreePlaylist();
  FreeWS(wl.wfilename);
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
      ShowMSG(1,(int)LG_Config_Updated);
      InitConfig();
    }
  }
#ifdef NEWSGOLD
  // Если вход.звонок или звонок закончился Blind007
  // У кого руки такие кривые??
  // Blind007: А что не так?
  // Ы! В самом начале писал, что не пашет, так не пашет и теперь... AAA
  if (((msg->msg==MSG_INCOMMING_CALL)&&(PlayingStatus==2)) || ((msg->msg==MSG_END_CALL)&&(PlayingStatus==1)))  
    TogglePlayback();
  }
#else 
//  if (IsCalling()&&(PlayingStatus==2))
//  {
//    TogglePlayback();
//  }
#endif
       
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
            NextTrackX();         //Тупо, не спорю, если придумаете лучше...  AAA
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
//      if (pmsg->cmd==M_SAE_HANDSFREE_UPDATED)
//      {
//        GetAccessoryType();
//      }
    }
  }
  return(1);
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
  InitConfig();
  sprintf(sfname,"%s%s",PIC_DIR,"skin.cfg");
  load_skin(sfname);
  sprintf(sfname,"%s%s",PIC_DIR,"colour.cfg");
  load_skin(sfname);
  SUBPROC((void*)LoadKeys);
  playmode = PlayMode;
  SoundVolume = soundvolume;
  
  wl.wfilename=AllocWS(128);
  Memory();
  // Если что-то передали в параметре - загружаем...
  if (fname)
  {
    LoadingPlaylist(fname);
  }
  
  if(TC[CurrentPL]==0){ // если плейлист из параметра пустой или нет параметров-> грузим стандарт
    if (DEFAULT_PLAYLIST!="")
    {
      LoadingPlaylist(DEFAULT_PLAYLIST);
      CurrentPL++;
      LoadingPlaylist(DEFAULT_PLAYLIST1);
      CurrentPL++;
      LoadingPlaylist(DEFAULT_PLAYLIST2);
      CurrentPL=0;
    }
  }
  UpdateCSMname(NULL);
  LockSched();
  phandle=-1;
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  return 0;
}
