#include "../inc/swilib.h"
#include "main.h"
#include "playlist.h"
#include "mylib.h" 
#include "langpack.h"

WSHDR *playlist_lines[TCPL][512];  // ������ ���������� �� ����� ������ � ��   Mr. Anderstand: �������� ����� � �����!

// �� �������
extern char COLOR_TEXT[];
extern char COLOR_TEXT_CURSOR[]; //��� �������  AAA
extern char COLOR_TEXT_PLAY[];   //� ��� AAA
extern char COLOR_BANDROLL[];    //���� ������ ���������
extern char COLOR_BANDROLL_C[];
extern const int SHOW_NAMES;
extern const char PLAYLISTS[];
extern const char PIC_DIR[];           // ��� ������� AAA
extern const int EXT;                  // ���������� �� ���������
extern const int soundvolume;          // ���������
extern const unsigned int SizeOfFont;  // ����� AAA
extern const unsigned int SCROLL_MULT; // �������� ��������   ������� � ������  AAA

// ��� ����������
unsigned short SoundVolume;           // ���������
unsigned short SVforToggle = 0;       // ������� ���������
unsigned short PlayingStatus = 0;     // ������ ������ (0 - ����, 1 - �����, 2 - ������)   // ���� char ����� unsigned short! :D   AAA
short phandle = -1;                   // ��� ������

int CurrentTrack[TCPL];                 // ������� ����
int PlayedTrack[TCPL];                  // ������������� ����   AAA
int CurrentPL=0;                     // ������� ��   AAA
int PlayedPL=0;                      // �� ���������������   AAA
unsigned int TC[TCPL];                  // ���������� ������ � �� 
unsigned int ready[TCPL];
extern const unsigned int LinesInPL_C; // ���������� ������ (����)
unsigned int LinesInPL;
int PlayTime;
unsigned short NextPlayedTrack[2];   // � ����� � �� � �������
unsigned short ShowNamesNoConst;       // � ��������� �� ���������� ��������   AAA
extern const char p_3s[];

extern unsigned short CTmy_x;     // ���������� CurrentTrack
extern unsigned short CTmy_y;
extern unsigned short s;          // �������� �� ���������
extern unsigned short NUMmy_x;    // ������
extern unsigned short NUMmy_y;
// ������ ���������
unsigned short BR_x;  //=129;
unsigned short BR1_y;  //=50;
unsigned short BR2_y;  //=152;
unsigned short BR_w;  //=1;
unsigned short BRC_x;  //=128;
unsigned short BRC_w;  //=2;
// ������ ���������

// ������ "������" ����������
extern unsigned int playmode;
extern unsigned short copy;
extern const unsigned int GrafOn; // 1,���� �������� ������� ���� �������   AAA
extern const unsigned int GrafOn1; // 1,���� �������� ��������   AAA
extern const unsigned int InfoOn; // 1,���� ������� ����� ����������   Vedan
unsigned short stop=1; // 1, ���� ������������� ��������   AAA
extern unsigned short Stat_keypressed;
unsigned short FM_o=0;
// ������ "������" ����������

extern unsigned int MAINGUI_ID;

// --- ��������� ---

#define TMR_SEC 216*2
GBSTMR tmr_scroll;
GBSTMR tmr_displacement;
GBSTMR tmr_cursor_move;
volatile int scroll_disp;
volatile int max_scroll_disp;

void scroll_timer_proc(void)
{
  int i=max_scroll_disp;
  if (i&&IsGuiOnTop(MAINGUI_ID))
  {
    if (scroll_disp>=i)
    {
      scroll_disp=0;
      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
    }
    else
    {
     scroll_disp=scroll_disp+5;
     if(IsGuiOnTop(MAINGUI_ID)) GBS_StartTimerProc(&tmr_scroll,scroll_disp!=i?TMR_SEC>>4:TMR_SEC,scroll_timer_proc);  //scroll_disp!=i?TMR_SEC>>5:TMR_SEC
    }
    REDRAW();
  }
  else
  {
    DisableScroll();
  }
}

void DisableScroll(void)
{
  GBS_DelTimer(&tmr_scroll);
  max_scroll_disp=0;
  scroll_disp=0;
}

// --- ��������� ---

// ��������� ���������
void VolumeUp()
{
#ifdef NEWSGOLD
  if(SoundVolume<5)SoundVolume++;
#else
  if(SoundVolume<14)SoundVolume++;
#endif
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  REDRAW();
}

// �������� ���������
void VolumeDown()
{
  if(SoundVolume>0)SoundVolume--;
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  REDRAW();
}

// ��������� �� ����
void ToggleVolume()
{
  if(SVforToggle!=0)
  {
    SoundVolume = SVforToggle;
    SVforToggle = 0;
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  } else 
  {
    SVforToggle = SoundVolume;
    SoundVolume = 0;
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  }
  REDRAW();
}

int random(int max)
{
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  return((time.hour+time.min*time.sec+time.millisec+date.day+date.month+date.year+time.millisec*time.sec)%max+1);
}

// ��������� ���� DemonGloom
void RandTrack() 
{
  if(ready[PlayedPL]){
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(NextPlayedTrack[1]){PlaySetTrack();}
  else{
  int prevtrack=PlayedTrack[PlayedPL];
  while (PlayedTrack[PlayedPL]==prevtrack) {
    PlayedTrack[PlayedPL]=random(TC[PlayedPL]);
  }
  if(PlayedTrack[PlayedPL]>TC[PlayedPL])PlayedTrack[PlayedPL]=1;
  if (CurrentPL==PlayedPL){
  if (CurrentTrack[CurrentPL]==prevtrack){  // ������� ������� �� ��������� �����
    CurrentTrack[CurrentPL]=PlayedTrack[PlayedPL];
    }
  if (0==prevtrack){  // ������� ������� �� ��������� �����
    CurrentTrack[CurrentPL]=PlayedTrack[PlayedPL];
  }
  }
  }
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

//������������� ����       ������ ����� �� ��������...  AAA
void RepeatTrack()
{
  if(ready[PlayedPL]){
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(NextPlayedTrack[1]){PlaySetTrack();}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

// ��� plamode==1       ������ ����� �� ��������...  AAA // �� ����� � ����� ������... DG
void NextTrackX()
{
  if(ready[PlayedPL]){
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  
  if(PlayedTrack[PlayedPL]<TC[PlayedPL]||NextPlayedTrack[1])
  {
    if(NextPlayedTrack[1]){PlaySetTrack();}
    else {PlayedTrack[PlayedPL]++;}
    PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
  }
  else
  {
    PlayedTrack[PlayedPL]=1;
  }
  }
}

// ��������� ���� �� AAA
void NextTrack()
{
  if(ready[PlayedPL]){
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
//  if (CurrentTrack==(PlayedTrack-1)){// ������� ������� �� ��������� �����  // � �����? �� �������� �� ��������� ������
//    CurrentTrack=PlayedTrack;        // ����������� ������, � ���... � ��� ������ ���� � ��������� ������� ��� ������������ ��������??  AAA
//    if(PlayedTrack>TC) CurrentTrack=1;
//    }
  if(NextPlayedTrack[1]){PlaySetTrack();}
  else{
  if(PlayedTrack[PlayedPL]<TC[PlayedPL]) {PlayedTrack[PlayedPL]++;}
  else {PlayedTrack[PlayedPL]=1;}
  }
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

// ���������� ���� �� AAA
void PreviousTrack()
{
  if(ready[PlayedPL]){
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(PlayedTrack[PlayedPL]>1) {PlayedTrack[PlayedPL]--;}
  else {PlayedTrack[PlayedPL]=TC[PlayedPL];}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

// �����/���������������
void TogglePlayback()
{
  Stat_keypressed = 1;
  switch(PlayingStatus)
  {
  case 0:
    // ���� ����, �� ������������� �������...
    if(ready[PlayedPL]) {PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL] = 1));} //����� �������   AAA
    break;
  case 1:
    // ���� ����� - ���������� ���������������...
    if (phandle!=-1)
    {
      PlayMelody_ResumePlayBack(phandle);
      PausingTime(1);
      PlayingStatus = 2;
    }
    break;
  case 2:
    // ���� ������ - ������ �����...
    if (phandle!=-1)
    {
      PlayMelody_PausePlayback(phandle);
      PausingTime(0);
      PlayingStatus = 1;
    }
    break;
  }
}

// ������������� ������������
void StopAllPlayback()
{
  SendNULL();
  Stat_keypressed = 1;
  if(PlayingStatus==0)return;
  if (phandle!=-1){
    PlayMelody_StopPlayback(phandle);
    PlayingStatus = 0;
  }
}

// ���������� � �������   AAA
void SetNextPlayed()
{
  NextPlayedTrack[0]=CurrentPL;
  NextPlayedTrack[1]=CurrentTrack[CurrentPL];
}

// ��������������� ������������� � �������   AAA
void PlaySetTrack()
{
  PlayedTrack[PlayedPL]=0;
  PlayedPL=NextPlayedTrack[0];
  PlayedTrack[PlayedPL]=NextPlayedTrack[1];
  CurrentTrack[PlayedPL]=PlayedTrack[PlayedPL];
  NextPlayedTrack[0]=NULL;
  NextPlayedTrack[1]=NULL;
}

// ��������� ��   AAA
void NextPL()
{
  DisableScroll();
  if(CurrentPL<TCPL-1)
  {
  //  if(TC[CurrentPL+1]==0) {CurrentTrack[CurrentPL+1]=1;/*PlayedTrack[PlayedPL+1] = 0;*/}
    CurrentPL++;
  }
  else
  {
  //  if(TC[0]==0) {CurrentTrack[0]=1;/*PlayedTrack[0] = 0;*/}
    CurrentPL=0;
  }
  REDRAW();
}

// ���������� ��   AAA
void PrevPL()
{
  DisableScroll();
  if(CurrentPL>0)
  {
  //  if(TC[CurrentPL-1]==0) {CurrentTrack[CurrentPL-1]=1;/*PlayedTrack[PlayedPL-1] = 0;*/}
    CurrentPL--;
  }
  else
  {
  //  if(TC[4]==0) {CurrentTrack[4]=1;/*PlayedTrack[4] = 0;*/}
    CurrentPL=TCPL-1;
  }
  REDRAW();
}

// ������������� ��� ����������� ����� AAA
void CTtoFirst()
{
  if(CurrentTrack[CurrentPL]!=1)CurrentTrack[CurrentPL] = 1;
}

// ������ � ��� ��� �������� AAA
void PTtoFirst()
{
  if(PlayedPL==CurrentPL&&PlayedTrack[PlayedPL]!=0)PlayedTrack[PlayedPL] = 0;
}


// ��������, ����������, � ���������� ����������   AAA
short p, p1, p3;
short n, d, v, v1, v2;
unsigned short i;
void PL(void)
{
 // unsigned short i=0;
 // unsigned short n=0;
  if(i<4&&GrafOn1)
  {
    i++;
    n-=s/4;
    p=n;
    p3=n;
    
    d-=s/2;
    p1=d;
    
    REDRAW();
    GBS_StartTimerProc(&tmr_cursor_move,10,PL);
    
  }else{
    
    p1=0;
    p3=0;
    p=0;
    REDRAW();
    GBS_DelTimer(&tmr_cursor_move);
    d=0;
    n=0;
    i=0;
  }
}

//������� �������� ���� AAA
void CTDown()
{
  DisableScroll();
  v=-1;
  v1=0;
  v2=1;
  PL();
  if (CurrentTrack[CurrentPL]<TC[CurrentPL])
  {
    CurrentTrack[CurrentPL]++;
  }
  else
  {
    CurrentTrack[CurrentPL] = 1;
  }
}

//������� �������� ����� AAA
void CTUp()
{
  DisableScroll();
  v=1;
  v1=1;
  v2=0;
  PL();
  if (CurrentTrack[CurrentPL]>1)
  {
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    CurrentTrack[CurrentPL] = TC[CurrentPL];
  }
}

// ������� �������� ���� AAA
void CTDownSpeed(void)
{
  DisableScroll();
  if(stop==0)
  {
    if (CurrentTrack[CurrentPL]<TC[CurrentPL])
    {
      CurrentTrack[CurrentPL]++;
    }
    else
    {
      CurrentTrack[CurrentPL] = 1;
    }
    REDRAW();
    GBS_StartTimerProc(&tmr_displacement,10*SCROLL_MULT,CTDownSpeed); // ���� ��� sgold
    
  }else{
    
    GBS_DelTimer(&tmr_displacement);
  }
}


// ������� �������� ����� AAA
void CTUpSpeed(void)
{
  DisableScroll();
  if(stop==0)
  {
    if (CurrentTrack[CurrentPL]>1)
    {
      CurrentTrack[CurrentPL]--;
    }
    else
    {
      CurrentTrack[CurrentPL] = TC[CurrentPL];
    }
    REDRAW();
    GBS_StartTimerProc(&tmr_displacement,10*SCROLL_MULT,CTUpSpeed); // ���� ��� sgold
    
  }else{
    
    GBS_DelTimer(&tmr_displacement);
  }
}


//�������� �������� ���� AAA
void CTDownSix()
{
  DisableScroll();
  if ((TC[CurrentPL]>6)&&(CurrentTrack[CurrentPL]+6<TC[CurrentPL]+1))
  {
    CurrentTrack[CurrentPL] = CurrentTrack[CurrentPL]+6;
  }
  else
  {
    CurrentTrack[CurrentPL] = TC[CurrentPL];
  }
}

//�������� �������� ����� AAA
void CTUpSix()
{
  DisableScroll();
  if ((TC[CurrentPL]>6)&&(CurrentTrack[CurrentPL]-6>0))
  {
    CurrentTrack[CurrentPL] = CurrentTrack[CurrentPL]-6;
  }
  else
  {
    CurrentTrack[CurrentPL] = 1;
  }
}

//������������� AAA
void PlayTrackUnderC()
{
  if(ready[CurrentPL]){
  Stat_keypressed = 1;
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(PlayedPL!=CurrentPL)
  {
    PlayedTrack[PlayedPL] = 0;
    PlayedPL=CurrentPL;
  }
  PlayedTrack[PlayedPL] = CurrentTrack[CurrentPL];
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
  }else{
    char p[256];
    ws_2str(GetCurrentTrack(CurrentTrack[CurrentPL]),p,256);
    LoadingPlaylist(p);
  }
}

// ������ ������� ������
char GetPlayingStatus()
{
  return PlayingStatus;
}

// ���������
unsigned short GetVolLevel()
{
  return SoundVolume;
}

// ������������� ������
void SetPlayingStatus(char PS)
{
  PlayingStatus = PS;
}

// ��������� ��������� �� ������������� �������...
void SetPHandle(short ph)
{
  phandle = ph;
}

// ���������� ���-�� ������ � ����������� ��
int GetTC()
{
  return TC[CurrentPL];
}

/*
 �������� � mp3-�������
*/
/*
// ���������� ��������� mp3-����
int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag)
{
  int fh = -1;
  unsigned int err;
  if ((fh=fopen(fname,A_TXT+A_ReadOnly,P_READ,&err))!=-1)
  {
    unsigned int size = lseek(fh,0,S_END,&err,&err);
    lseek(fh,size-128,S_SET,&err,&err);
    zeromem(&tag,sizeof(MP3Tagv1));
    fread(fh,tag->id,3,&err);
    if (tag->id=="TAG")
    {
      fread(fh,tag->title,30,&err);
      fread(fh,tag->artist,30,&err);
      fread(fh,tag->album,30,&err);
      fread(fh,tag->year,4,&err);
      fread(fh,tag->comment,30,&err);
      return 1;
    }
    fclose(fh,&err);
  }
  return 0;
}
*/
/*
 ����� ���������� ������ � ����������...
*/

// ������� ������   AAA
void Memory()
{
 // LinesInPL=LinesInPL_C;
  for(unsigned int i=0;i<5;i++)
  {
    for(unsigned int j=0;j<256;j++)
    {
      playlist_lines[i][j]=AllocWS(256);
    }
  }
}

// ������� ��!
void FreePlaylist(void)
{
   /* for(unsigned int i=0;i<5;i++)
    {
      for(unsigned int j=0;j<256;j++)
      {
        FreeWS(playlist_lines[i][j]);
        playlist_lines[i][j]=NULL;
      }
    }*/
  for(unsigned int i=0; i<TCPL; i++) {
  while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
    if(CurrentPL<TCPL-1) {CurrentPL++;}
    else {CurrentPL=0;}
  }
}


unsigned int char8to16(int c)
{
  if (c==0xA8) c=0x401;
  if (c==0xAA) c=0x404;
  if (c==0xAF) c=0x407;
  if (c==0xB8) c=0x451;
  if (c==0xBA) c=0x454;
  if (c==0xBF) c=0x457;
  if (c==0xB2) c=0x406;
  if (c==0xB3) c=0x456;
  if ((c==0xC0)&&(c==0x100)) c+=0x350;
  return c;
}

void ascii2ws(char *s, WSHDR *ws)
{
  int c;
  while ((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

// ��������� ��!     ���� ��� ������� :)   AAA
void SavePlaylist(char *fn)
{
  int j=0;
  int f;
  char* p=malloc(256);
  char m[256];
  char s[]={0x0D,0x0A}; // ������ ������������� � m3u 
  if(EXT==0){sprintf(m,"%s%s",fn,".spl");}
  else{sprintf(m,"%s%s",fn,".m3u");}                      // ----------- 
  FSTATS fstats;
  unsigned int err;
  while (GetFileStats(m,&fstats,&err)!=-1)       // �������� ����� �� �������������
  {
    j++;
    if(EXT==0){sprintf(m,"%s%i%s",fn,j,".spl");}
    else{sprintf(m,"%s%i%s",fn,j,".m3u");}
  }
  f=fopen(m,A_ReadWrite/*+A_MMCStream*/+A_Create+A_BIN,P_READ+P_WRITE,&err);
  if(EXT==1){fwrite(f,"#EXTM3U",7,&err); fwrite(f,s,2,&err);}
  for (unsigned int i=0;i<TC[CurrentPL];i++)
  {
    ws_2str(playlist_lines[CurrentPL][i+1],p,256);
    fwrite(f,p,strlen(p),&err);
    fwrite(f,s,2,&err);
  }
  mfree(p);
  fclose(f,&err);
  ShowMSG(1,(int)lgpData[LGP_PL_Saved]);
}

/////////////////////////////////////////////////////<<<�������������� ��>>>/////////////////////////////////////////////////////////
// ��������� ������ � ��   AAA
void PastLine(WSHDR *p, unsigned short i) // ��������� ������ �� � [0][0], � [0][1] ������-��... �������� ������ ��� �� �����   AAA
{
  playlist_lines[CurrentPL][TC[CurrentPL]+1]=AllocWS(256);
  wstrcpy(playlist_lines[CurrentPL][TC[CurrentPL]+1],p);
  TC[CurrentPL]++;
  if(i) {CurrentTrack[CurrentPL]=TC[CurrentPL];}
}

// �������� ������ � ��   AAA
void CopyLine(WSHDR *p)
{
  TC[CurrentPL]++;
  for(int i=TC[CurrentPL];i>CurrentTrack[CurrentPL]-1;i--)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i-1]);
    }
  wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],p);
  if(PlayedTrack[PlayedPL]>CurrentTrack[CurrentPL]-1) {PlayedTrack[PlayedPL]++;}
  copy=0;
}

// ������� ������ �� ��   AAA
void DeleteLine()  // ������� ������ ���� �� [0][1] � ������� � ������ ������������ �� �����.   AAA
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0&&TC[CurrentPL]>0)
  {
  if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=0;}
  else{if(CurrentTrack[CurrentPL]<PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
  
  int i=CurrentTrack[CurrentPL];
  if(i!=TC[CurrentPL])
  {
    while(i<TC[CurrentPL])
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i+1]);
      i++;
    }
  }
  else
  {
    if(CurrentTrack[CurrentPL]>1) {CurrentTrack[CurrentPL]--;}   // �� ���� ���� ���� ���, ������������ ���   AAA
  }
  FreeWS(playlist_lines[CurrentPL][TC[CurrentPL]]);
  playlist_lines[CurrentPL][TC[CurrentPL]]=NULL;
  TC[CurrentPL]--;
  }
}

// ���������� ������ � �� �����   AAA
void MoveLineUp()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=1)
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}
    else{if(CurrentTrack[CurrentPL]-1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}}
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1]);
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1],p);
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=TC[CurrentPL];}
    else{if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]--;}}
    for(int i=1;i<TC[CurrentPL];i++)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i+1]);
    }
    wstrcpy(playlist_lines[CurrentPL][TC[CurrentPL]],p);
    CurrentTrack[CurrentPL]=TC[CurrentPL];
  }
  }
  FreeWS(p);
  }
}

// ���������� ������ � �� ����   AAA
void MoveLineDown()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=TC[CurrentPL])
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}
    else{if(CurrentTrack[CurrentPL]+1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1]);
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1],p);
    CurrentTrack[CurrentPL]++;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=1;}
    else {if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]++;}}
    for(int i=TC[CurrentPL];i>1;i--)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i-1]);
    }
    wstrcpy(playlist_lines[CurrentPL][1],p);
    CurrentTrack[CurrentPL]=1;
  }
  }
  FreeWS(p);
  }
}

// ���������� ������ � ��������� ��   AAA
void MoveLineRight()
{
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  NextPL();
  PastLine(p, 1);
  FreeWS(p);
}

// ���������� ������ � ���������� ��   AAA
void MoveLineLeft()
{
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  PrevPL();
  PastLine(p, 1);
  FreeWS(p);
}
/////////////////////////////////////////////////////<<<�������������� ��>>>/////////////////////////////////////////////////////////

// ���������� ��� ����� �� ������� ����...
void FullpathToFilename(WSHDR * fnamews, WSHDR * wsFName)
{
  char* fname=malloc(256);
  ws_2str(fnamews,fname,256);

      const char *p=strrchr(fname,0x1f)+1;
      const char *p2=strrchr(fname,'\\')+1;                         // ���� ��� �������� ����� ��������� �������... ������ ������� ���� ���������
       if (p2>p){
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-1;
         utf8_2ws(wsFName,p2,length);
       }else{
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-2;
         utf8_2ws(wsFName,p,length);
       }
  mfree(fname);
}

// ���������� ��� ����� �� ������� ����...        ������ ������� ��������   AAA
void FullpathToFile(WSHDR * fnamews, WSHDR * wsFName)
{
  char* fname=malloc(256);
  ws_2str(fnamews,fname,256);
  unsigned int len=strlen(fname);

  if(fname[len-1]=='\\') {fname[len]=0; fname[len-1]='\0';}
  
  const char *p=strrchr(fname,0x1f)+1;
  const char *p2=strrchr(fname,'\\')+1;
  if (p2>p){
    utf8_2ws(wsFName,p2,strlen(p2)+1);
  }else{
    utf8_2ws(wsFName,p,strlen(p)+2);
  }
  
  if(fname[len-1]=='\0') {wsprintf(wsFName,"%w\\",wsFName);}
  
  mfree(fname);
}
/*
void FullpathToFile(WSHDR * fnamews, WSHDR * wsFName)
{
  unsigned int err;
  char* fname=malloc(256);
  ws_2str(fnamews,fname,256);

  if (!isdir(fname, &err))
  {
      const char *p=strrchr(fname,0x1f)+1;
      const char *p2=strrchr(fname,'\\')+1;                         // ���� ��� �������� ����� ��������� �������... ������ ������� ���� ���������
       if (p2>p){
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-1;
         utf8_2ws(wsFName,p2,length);
       }else{
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-2;
         utf8_2ws(wsFName,p,length);
       }
  }else{
    fix(fname);
      fname[strlen(fname)-1]=0;
      const char *p=strrchr(fname,'\\')+1;
      utf8_2ws(wsFName,p,strlen(p));
      wsprintf(wsFName,"%w\\",wsFName);
  }
  mfree(fname);
}*/

void fix(char* p)  // ������� �������� ������ (������ � ��������� �� WSHDR)   AAA
{
  unsigned short j=0;
  char* p1=malloc(256);
  for(unsigned short i=0;i<256;i++)
  {
    if(p[i]!=0x1f) {p1[j++]=p[i];}
  }
  strcpy(p,p1);
  mfree(p1);
}

// ����������� ���� �� ������ � ��
WSHDR * GetCurrentTrack()
{
  return playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
}

WSHDR * GetPlayedTrack()
{
  return playlist_lines[PlayedPL][PlayedTrack[PlayedPL]];
}

// ���������� ��� ���������������� �� ������ � ��
WSHDR * GetTrackByNumber(WSHDR**mass, int number)
{
  return mass[number];
}

// ��� �������� ��������� ��������!!   AAA
void PL_Redraw(WSHDR** mass, int* CurLine, int* MarkLine, int* MarkLines, unsigned int* AllLines, int CurList, int MarkList)
{
  unsigned short w = ScreenW();
  unsigned short my_x;
  unsigned short my_y;
  unsigned short k;
  short p2=0;
  short v3=1;
  unsigned short c = 0;  // ����������  AAA
  int i;
 // char* str;
 // ID3TAGDATA *ShowTag;
  
  
  // ��� �����...
  if (AllLines[CurList]>0)
  {
    //---- ���������� � ����������������� ����� (������, �����, ������� �������������), ����� ������� ��� AIMP, ������� �� ������  - Vedan
    WSHDR * info_pf = AllocWS(32); 
    if(InfoOn)
  {
// ��� ����������
char chanel[8],
       freq[8],
     format[8];
//����������� ������ 
    if(*RamChannel()==0)strcpy(chanel," mono"); else strcpy(chanel," stereo");   
//���������� ������� 
    switch (*RamFormatTrack())
    {
    case 0xA: strcpy(format,"MP3 ::"); break;
    case 0x8: strcpy(format,"WAV ::"); break;
    case 0x4: strcpy(format,"MID ::"); break;
    case 0x2: strcpy(format,"3GP ::"); break;
    default:  strcpy(format," - "); 
    }
//����������� �������
    switch (*RamFreq())
    {
    case 0x4: strcpy(freq,", 22 kHz"); break;
    case 0x5: strcpy(freq,", 32 kHz"); break;
    case 0x7: strcpy(freq,", 44 kHz"); break;
    case 0x8: strcpy(freq,", 48 kHz"); break;
    default:  strcpy(freq," - "); 
    }
    //strcpy(format,null);
    //strcpy(freq,null);
    //strcpy(chanel,null);
    
    wsprintf(info_pf,"%t%t%t",format,chanel,freq); //������ ���������� (�����, �����, �������)
  }
  
    my_x = CTmy_x;
    my_y = CTmy_y;

    WSHDR * out_ws = AllocWS(128);
/*
    switch(CurrentTrack[CurrentPL])
    {
    case 1:
      k=0;
      break;
    case 2:
      k=1;
      break;
    case TC[CurrentPL]-2:
      k=3;
      break;
    case TC[CurrentPL]-1:
      k=4;
      break;
    case TC[CurrentPL]:
      k=5;
      break;
    case default:
      k=2;
      break;
    }
*/
    if (AllLines[CurList]>5)
    {
    if(CurLine[CurList]==1) {k=0; v3=0;}
    else{ if(CurLine[CurList]==2) {k=1; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]-2) {k=3; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]-1) {k=4; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]) {k=5; v3=0;} else {k=2;}}}}}
    }else{
    if(CurLine[CurList]==1) {k=0; v3=0;}
    else{ if(CurLine[CurList]==2) {k=1; v3=0;}
    else{ if(CurLine[CurList]==3) {k=2; v3=0;}
    else{ if(CurLine[CurList]==4) {k=3; v3=0;}
    else{ if(CurLine[CurList]==5) {k=4; v3=0;}}}}}
    }
    
    for(int l=0;l<6;l++)
    {
    i = CurLine[CurList]+l-k;
    if(AllLines[CurList]>l)
    {
      switch(ShowNamesNoConst)
      {
      case 0:// �� �������  AAA
       /* ShowTag=malloc(sizeof(ID3TAGDATA));
        str=malloc(256);
        ReadID3v1(GetTrackByNumber(i), ShowTag);
        
        if(strlen(ShowTag->artist)&&strlen(ShowTag->title))
        {
          sprintf(str,"%s - %s",ShowTag->artist,ShowTag->title);
          utf8_2ws(out_ws,str,strlen(str));
          
        }else{
          utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        }
        mfree(ShowTag);
        mfree(str);*/
        break;
      case 1:
        wstrcpy(out_ws,GetTrackByNumber(mass, i));
       // utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        break;
      case 2:
        FullpathToFilename(GetTrackByNumber(mass, i),out_ws);
        break;
      case 3:
        FullpathToFile(GetTrackByNumber(mass, i),out_ws);
        break;
      }
        /*
        if (SHOW_FULLNAMES)
        {
          utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        
        }else{
        
        FullpathToFilename(GetTrackByNumber(i),out_ws);
        }*/
    if(k!=l)
    {
    // ������ ������ ���� ��� �� �������� �����...
    if (MarkLine[CurList]==i||MarkLines[i]==1)
    {
      DrawScrollString(out_ws,my_x,my_y+c+(p2-p3*v)*v3,w-7,my_y+GetFontYSIZE(SizeOfFont)+c+(p2-p3*v)*v3,
                   1,SizeOfFont,0,COLOR_TEXT_PLAY,0);
    }else{
      DrawScrollString(out_ws,my_x,my_y+c+(p2-p3*v)*v3,w-7,my_y+GetFontYSIZE(SizeOfFont)+c+(p2-p3*v)*v3,
                   1,SizeOfFont,0,COLOR_TEXT_CURSOR,0);
    }
    p2=0;
    }else{
      short v4=1;
      if(v3!=0) {v4=0;}
      char sfname[256];
      sprintf(sfname,p_3s,PIC_DIR,items1[12],PNGEXT);
      DrawImg(my_x-1,my_y+c-3+p*v*v4,(int)sfname);
      
      p2=-p1*v1;
      
    if (MarkLine[CurList]==CurLine[CurList]||MarkLines[CurLine[CurList]]==1)
    {
      if(GrafOn)
      {
          int i=Get_WS_width(out_ws,SizeOfFont);  //���������� ���-�� �������� ��� ���� ������ (��� ��� �� ����� ����...)
	  i-=(w-9);   //�� ���� �����������
	  if (i<0)
	  {
	    DisableScroll();
	  }else{
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
      }
      DrawScrollString(out_ws,my_x,my_y+c-(p1*v2+p3*v1)*v3*v,w-7,my_y+GetFontYSIZE(SizeOfFont)+c-(p1*v2+p3*v1)*v3*v,
                   scroll_disp+1,SizeOfFont,0,COLOR_TEXT_PLAY,0);
      if(InfoOn&&MarkLine)
     {
        
        DrawString(info_pf,my_x,GetFontYSIZE(SizeOfFont)+2+my_y+c-(p1*v2+p3*v1)*v3*v,w-7,my_y+2*GetFontYSIZE(SizeOfFont)+c-(p1*v2+p3*v1)*v3*v+2,SizeOfFont,0,COLOR_TEXT_PLAY,0);
     }
      
      
    }else{
	if(GrafOn)
        {
          int i=Get_WS_width(out_ws,SizeOfFont);
	  i-=(w-9);
	  if (i<0)
	  {
	    DisableScroll();
	  }else{
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
        }
      DrawScrollString(out_ws,my_x,my_y+c-(p1*v2+p3*v1)*v3*v,w-7,my_y+GetFontYSIZE(SizeOfFont)+c-(p1*v2+p3*v1)*v3*v,
                   scroll_disp+1,SizeOfFont,0,COLOR_TEXT,0);
    }
    c+=s;
    }
    c+=s;
    }
    }
    if(n==0) {n=s;}
    if(d==0) {d=2*s;}
    FreeWS(out_ws);
    FreeWS(info_pf);
  }else{
    if(!FM_o) {LoadPlaylists(PLAYLISTS);}
  }
  // ��������
  WSHDR * pl_c = AllocWS(64);
  if(MarkLine){
  wsprintf(pl_c,"%i/%i/%i;%i/%i",CurLine[CurList],AllLines[CurList],CurList+1,MarkLine[MarkList],MarkList+1);
  }else{
  unsigned int nLines=0;
  for(unsigned int i=0; i<AllLines[CurList]+1; i++) {if(MarkLines[i]==1) {nLines++;}}
  wsprintf(pl_c,"%i/%i;%i(%i)",CurLine[CurList],AllLines[CurList],nLines,TC[CurrentPL]);
  }
  DrawString(pl_c,NUMmy_x,NUMmy_y,w,NUMmy_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,COLOR_TEXT,0);
  FreeWS(pl_c);
  BandRoll(CurLine[CurList], AllLines[CurList]);
}

// ������ ���������   AAA
void BandRoll(int CurLine, int AllLines)
{
  if(AllLines>6)
  {
    int yy=CurLine*(BR2_y-BR1_y)/AllLines;
    DrawRoundedFrame(BR_x,BR1_y,BR_x+BR_w-1,BR2_y,0,0,0,0,COLOR_BANDROLL);
    DrawRoundedFrame(BRC_x,BR1_y+yy-(BR2_y-BR1_y)/AllLines,BRC_x+BRC_w-1,BR1_y+yy,0,0,0,0,COLOR_BANDROLL_C);
  }
}

// ������ ������   AAA
void NULLchar(char* p, unsigned int imax) {for(unsigned int i=0; i<imax+1; i++) {p[i]=0;}}  //{unsigned int i=0; while(p[i]!='\0') {p[i]=0; i++;} p[i]=0;}

// ��������� ��!
int LoadPlaylist(const char * fn)  // ���������. ��� ������� � ������!    AAA
{
  FSTATS stat;
  int f;
  unsigned int ul;
  unsigned int i=0;
  unsigned int j=0;
  unsigned int k=0;
  int fsize;
  char *pp=malloc(256);
  NULLchar(pp, 256);
  char *p;

  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=malloc(fsize+1);
  fread(f,p,fsize,&ul);
  fclose(f,&ul);
  while(i<fsize)
  {
    if(p[i]!=0x0D&&p[i+1]!=0x0A) {pp[j++]=p[i];}
    else
    {
      fix(pp);
      if(pp[0]!='#')
      {
        WSHDR* ppp=AllocWS(256);
        utf8_2ws(ppp,pp,strlen(pp));
        PastLine(ppp, 0);
        FreeWS(ppp);
        ppp=NULL;
        k++;
      }
      i++;
      j=0;
      NULLchar(pp, 256);
    }
    i++;
  }
  mfree(p);
  mfree(pp);
  return k;
}

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn)
{
  /*  if(TC[CurrentPL]>0)
    {
      MsgBoxYesNo(1,(int)"��������?",Change);
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
  CTtoFirst();
  PTtoFirst();
  CleanPlaylist();
  LoadPlaylist(fn);
  ready[CurrentPL]=1;
}

// ������ ��   AAA
void CleanPlaylist()
{
  while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
}

//LoadDaemonList(" 4:\\Doc\\");
void LoadPlaylists(const char* path) // ��� ��� ����� ����   AAA
{
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
        if(((a=='s'||a=='S')&&(b=='p'||b=='P')&&(c=='l'||c=='L'))||
               ((a=='m'||a=='M')&&b=='3'&&(c=='u'||c=='U')))   // ���������� �������   AAA
        {
          strcpy(p1,name);
          fix(p1);
          utf8_2ws(p,p1,256);
          PastLine(p, 0);
        }
      }
      else
      {
        strcat(name,"\\"); LoadPlaylists(name);
      }
      FreeWS(p);
      mfree(p1);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if(TC[CurrentPL]>0) {CTtoFirst(); PTtoFirst();}
  ready[CurrentPL]=0;
}

// ������ ������ � ����� ���� �������...   AAA
void MemoryFree()
{
  GBS_DelTimer(&tmr_scroll);
  GBS_DelTimer(&tmr_displacement);
  GBS_DelTimer(&tmr_cursor_move);
  FreePlaylist();
}
