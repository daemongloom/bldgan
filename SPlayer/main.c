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

const int minus11=-11; // �������� ��������� =)

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int mode; // 1, ���� ������� ������� ������� �������
int KeyLock; // 1, ���� �������������;
short Stat_keypressed = 0; // ������ �� ������� ��������� �������?
short Mode_keypressed = 0; // ������ �� ������� ��������� ������ ������������?
short N_keypressed = 0;
short P_keypressed = 0;

unsigned short w;

//--- ����������, ���������� ��������� AAA ---
unsigned short VOLmy_x;
unsigned short VOLmy_y;
unsigned short STATmy_x;
unsigned short STATmy_y;
unsigned short CTmy_x;  // ���������� CurrentTrack
unsigned short CTmy_y;
unsigned short s;     // �������� �� ���������
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
//--- ����������, ���������� ��������� AAA ---

//--- ��������� �� ������� ---
extern const char COLOR_BG[];
extern const char COLOR_TEXT[];
extern const char I_BACKGROUND[];
extern const char PIC_DIR[];
extern const char SKIN[];
extern const char PLAYLISTS[];
extern const char DEFAULT_PLAYLIST[];
extern const unsigned int IDLE_X;
extern const unsigned int IDLE_Y;
extern const int PlayMode; 
//--- ��������� �� ������� ---

//--- ���������� ---
extern short phandle;  // ��� ����������� ����� �����.  AAA
extern char GetAccessoryType();   // �� �����   AAA
extern unsigned short PlayingStatus;
extern unsigned int TC;
char Quit_Required = 0;     // ���� ������������� ��������� ������
char list[256];
char sfname[256];
int playmode;     // 0 - ������ ���, 1 - ��������� ���, 2 - ����������, 3 - ��������� ����  AAA
//--- ���������� ---

void load_skin();       // �� skin.cfg AAA
void UpdateCSMname(WSHDR * tname);

// ������ MP3 ����
void PlayMP3File(const char * fname)
{
if(TC>0)            // ������ �� ������� ��� ���������� ������������ ��   AAA
{
  if (!IsCalling()) // ��� �� ������
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1) // �������� ����� �� �������������
    {
      PLAYFILE_OPT pfopt;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      
      const char *p=strrchr(fname,'\\')+1; // ��������� ���� ���� ������... (c) Rst7  // DemonGloom :) 
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
      SetPHandle(PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt)); // ������ 0xC ���� 0x10 ... �������� ���!!
      SetPlayingStatus(2);
      PlayMelody_ChangeVolume(phandle,GetVolLevel());  // ��� �� ���� ���������� ��������� - ����� �����...
#else 
      pfopt.unk4=0x80000000;
      pfopt.unk5=1;
      SetPHandle(PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt));
      SetPlayingStatus(2);
      PlayMelody_ChangeVolume(phandle,GetVolLevel());  // ��� �� ���� ���������� ��������� - ����� �����...
      
#endif
      UpdateCSMname(sndFName); // ������� ��� ������ XTask Blind007
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
      // ���� ��� ������ �����!
      ShowMSG(1,(int)"Can't find file!");
    }
  }
}
else
{
  ShowMSG(1,(int)"Load a playlist, please!");
}
}

// ������ ���������� �� skin.cfg AAA
void load_skin(void)
{
  char *data; 
  unsigned int err; 
  int handle; 
  handle=fopen(SKIN, A_ReadOnly, P_READ,&err); 
  if(handle!=-1)
  {
    data=malloc(28);
    if(data!=0)
      {
        fread(handle,data,28,&err); // �������� ������! :)
        
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
        KeyLock_x=data[18];
        KeyLock_y=data[19]+data[20];
        Next_x=data[21];
        Next_y=data[22]+data[23];
        Prev_x=data[24];
        Prev_y=data[25]+data[26];
  
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
//  DrawRoundedFrame(left+1,top,w-1,h-1,0,0,0,GetPaletteAdrByColorIndex(1),color(COLOR_BG));  // � ��� �����??? ���� ����� - �������!   AAA
//#ifdef USE_PNG_EXT                         // � ��� ��� ����????
  // --- ������ ���� ���� ---
  DrawImg(left,top,(int)I_BACKGROUND);  // ������ ���
  // ���������
  char vfname[256];
  sprintf(vfname,"%s%s%i%s",PIC_DIR,"volume",GetVolLevel(),".png");
  DrawImg(VOLmy_x,VOLmy_y,(int)vfname);
  // ������ ������
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
  // ����� ���������   AAA
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
  DrawImg(RANDmy_x,RANDmy_y,(int)pfname);  // ������������� ��� ��� �����!   AAA
  // ������ ����/���� ����   AAA
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
  // ���� ������������� DemonGloom
  if (KeyLock){
    sprintf(pfname,"%s%s",PIC_DIR,"keylock.png");
    DrawImg(KeyLock_x,KeyLock_y,(int)pfname);
  } 
// #endif

    PL_Redraw();
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // ��� ����� ������� ����������
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // ��� ����� ���������� ���������� ������
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  DisableIDLETMR(); //���� �� ���������� ��� AAA
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  DisableIDLETMR(); //���� �� ���������� ��� AAA
}

void QuitCallbackProc(int decision)
{
  if(decision==0)Quit_Required = 1;
}

/*
  ���������� ������� ������. ���� ���������� ������� ������
  � ���� ��������� GUI_MSG, ������ ������������� ����.
*/
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if(Quit_Required)return 1; //���������� ����� GeneralFunc ��� ���. GUI -> �������� GUI
  if (KeyLock){
    if ((msg->gbsmsg->msg==LONG_PRESS)&&(msg->gbsmsg->submess=='#')){
     KeyLock=(KeyLock+1)%2;
     ShowMSG(1,(int)"���������� ��������������");
     REDRAW();}
     return 0;
     }
  else{
  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON:  // Play
      Stat_keypressed = 0;
      break;
    case '0':           // Stop
      Stat_keypressed = 0;
      break;
    case '4':           // ������������ �� ���������� ����
      P_keypressed = 0;
      break;
    case '5':           // Play/Pause
      Stat_keypressed = 0;
      break;
    case '6':           // ������������ �� ��������� ����
      N_keypressed = 0;
      break;
    case '#':           // Mode
      Mode_keypressed = 0;
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      MsgBoxYesNo(1,(int)"������� SPlayer?",QuitCallbackProc);
      break;
    case RED_BUTTON:
      MsgBoxYesNo(1,(int)"������� SPlayer?",QuitCallbackProc);
      break;
    case LEFT_SOFT:
      MM_Show();
      break;
    case GREEN_BUTTON:  // �� ������� ������ ��������� �������� �� ���������...
      CTandPTtoFirst();
      LoadingPlaylist(DEFAULT_PLAYLIST);
      break;
    case ENTER_BUTTON:
      Stat_keypressed = 1;
      PlayTrackUnderC();
      break;
    case UP_BUTTON:
      CTUp();
      break;
    case DOWN_BUTTON:
      CTDown();
      break;
    case '0':           // ������������� ���������������
      Stat_keypressed = 1;
      StopAllPlayback();
      break;
    case '1':           // ��������. ����� ����� ��������� :)
      break;
    case '3':           // ��������. ����� ����� ��������� :)
      break;
    case '2':
      CTUpSix();
      break;
    case '4':           // ������������ �� ���������� ����
      P_keypressed = 1;
      PreviousTrack();
      break;
    case '5':           // Play/Pause
      Stat_keypressed = 1;
      TogglePlayback();
      break;
    case '6':           // ������������ �� ��������� ����
      N_keypressed = 1;
      if (playmode==2) RandTrack(); else NextTrack();
      break;
    case '7':
      break;
    case '8':
      CTDovnSix();
      break;
    case '9':
      break;
    case '*':
      ToggleVolume();
      break;
    case '#':
        Mode_keypressed = 1;
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
        sprintf(list,"%s%s",PLAYLISTS,"playlist");
        SavePlaylist(list);
      break;
      case '3':
        CTUpSix();
      break;
      case '8':
      break;
      case '9':
        CTDovnSix();
      break;
      case '#':
       if (KeyLock==0){
          Mode_keypressed = 0;
          playmode-=1;
          if (playmode==-1) playmode=3;
          ShowMSG(1,(int)"���������� �������������");
          KeyLock=1;
       }
      break;
    }
    REDRAW();
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
#endif
  if (submsg==VOL_UP_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // ��������� ����
      case KEY_UP: if (mode==0) VolumeUp(); else mode=0;  N_keypressed = 0; REDRAW(); return 2; // ��������� ����
    }}
  if (submsg==VOL_DOWN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS: if (mode==0) {PreviousTrack(); mode=1; }  P_keypressed = 1; REDRAW(); return 2;  // ���������� ����
      case KEY_UP: if (mode==0) VolumeDown(); else mode=0;  P_keypressed = 0; REDRAW(); return 2;  // ��������� ����
    }}
  
  if ((submsg==0x27)){//&& !(IsCalling())){  // ���� ������ ��������� � �� ������
    switch (msg){
    case (KEY_DOWN): return 2;
    case (LONG_PRESS):  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // ��������� ����
    case (KEY_UP): if (mode==0) TogglePlayback(); else mode=0; N_keypressed = 0; REDRAW(); return 2;  // ������������ pause/play 
    }
  }
  
  return(0);
}


// Destroy
extern void kill_data(void *p, void (*func_p)(void *));

// �� ���� �� �������� ;) �������� ��� ����
static void ElfKiller(void)      //������� static �� ���� �����, ������� - ��������! :)  AAA
{
  extern void *ELF_BEGIN;
  RemoveKeybMsgHook((void *)my_keyhook);               //����!!  AAA . ���� :) DemonGloom
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

// �������� ��� ����
int method8(void){return(0);}

// �������� ��� ����
int method9(void){return(0);}

// ������ � ��������, ����� ���� �� ����������, ����� ����� ��������
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

// ������ ��� ��������� GUI
const RECT Canvas={0,0,0,0};

// ���������� ��� �������� �������� CSM. � ������ �������
// �������� GUI, ��� ID ������������ � MAINGUI_ID
// �� ������ ������ - ����� ����������� ;)
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

// ���������� ��� �������� �������� CSM. ��� � ���������� ������
void maincsm_onclose(CSM_RAM *csm)
{
  DisableScroll();       // ��������� ��� ����� ��������� ��� � ������������� ����... � �� ����� ����������! :D
  StopAllPlayback();
  SUBPROC((void *)ElfKiller);
}

// ���������� ������� �������� CSM
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
  // �������� ������ ������� �� IDLESCREEN
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)) //���� IdleGui �� ����� �����
  {
    GUI *igui=GetTopGUI();
    if (igui) //� �� ����������
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

  // ���� ��������
  
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"SPlayer config updated!");
      InitConfig();
    }
  }
#ifdef NEWSGOLD
  // ���� ����.������ ��� ������ ���������� Blind007
  if (((msg->msg==MSG_INCOMMING_CALL)&&(PlayingStatus==2)) || ((msg->msg==MSG_END_CALL)&&(PlayingStatus==1)))  // � ���� ���� ����� ������??
  {
    TogglePlayback();
  }
#else 
  if (IsCalling()&&(PlayingStatus==2))
  {
    TogglePlayback();
  }
#endif
       
  if (msg->msg==MSG_PLAYFILE_REPORT)   // ��� ����������� ����� �����.  AAA
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==phandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_DONE)//||pmsg->cmd==M_SAE_PLAYBACK_ERROR)  // � ����� �� ��������� ��� ������?
      {
        switch(playmode)
        {
          case 0:
            NextTrackX();         //����, �� �����, ���� ���������� �����...  AAA
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
  return(1);
}

// ������������� ��������� MAINCSM
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

// �������, ������� ������������� �������� ����� CSM ��� X-Task.
// ������� � XTask'e ��� ������! Blind007
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


// �������� ���������. ��� ������ �������� ���������� ��� ������ �����.
int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  load_skin();
  playmode = PlayMode;
  
  // ���� ���-�� �������� � ��������� - ���������...
  if (fname)
  {
    LoadingPlaylist(fname);
  }
  else
  {
    // ���� ��� - ������ DEFAULT ��������
    if (DEFAULT_PLAYLIST!="")
    {
      LoadingPlaylist(DEFAULT_PLAYLIST);
    }
  }
  UpdateCSMname(NULL); // �����-�� ��������� :) Blind007
  LockSched();
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  return 0;
}
