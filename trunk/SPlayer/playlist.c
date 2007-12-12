#include "../inc/swilib.h"
#include "main.h"
#include "playlist.h"

char ***playlist_lines;  // ������ ���������� �� ����� ������ � ��   Mr. Anderstand: �������� ����� � �����!
char **id3tags1_lines;  // ������ ���������� �� ID3v1-����

// �� �������
extern char COLOR_TEXT[];
extern char COLOR_TEXT_CURSOR[]; //��� �������  AAA
extern char COLOR_TEXT_PLAY[];   //� ��� AAA
extern char COLOR_BANDROLL[];    //���� ������ ���������
extern char COLOR_BANDROLL_C[];
extern const int SHOW_FULLNAMES;
extern const char PIC_DIR[];           // ��� ������� AAA
extern const int EXT;                  // ���������� �� ���������
extern const int soundvolume;          // ���������

// ��� ����������
unsigned short SoundVolume;           // ���������
unsigned short SVforToggle = 0;       // ������� ���������
unsigned short PlayingStatus = 0;     // ������ ������ (0 - ����, 1 - �����, 2 - ������)   // ���� char ����� unsigned short! :D   AAA
short phandle = -1;                   // ��� ������

int CurrentTrack[5];                 // ������� ����
int PlayedTrack[5];         // ������������� ����   AAA
int CurrentPL=0;
int PlayedPL=0;
unsigned int TC[5];                  // ���������� ������ � �� 
/*extern */const unsigned int TCPL=5;
extern const unsigned int LinesInPL;
int PlayTime;
unsigned short NextPlayedTrack[2];

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
extern unsigned short w;
extern int playmode;
extern unsigned short copy;
extern const unsigned int GrafOn; // 1,���� �������� ������� ���� �������   AAA
unsigned short stop=1; // 1, ���� ������������� ��������   AAA
// ������ "������" ����������

extern unsigned int MAINGUI_ID;

// --- ��������� ---

#define TMR_SEC 216*2
GBSTMR tmr_scroll;
GBSTMR tmr_displacement;
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
  return((time.hour+time.min+time.sec+time.millisec+date.day+date.month+date.year)%max+1);
}

// ��������� ���� DemonGloom
void RandTrack() 
{ 
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
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
}

//������������� ����       ������ ����� �� ��������...  AAA
void RepeatTrack()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(NextPlayedTrack[1]){PlaySetTrack();}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
}

// ��� plamode==1       ������ ����� �� ��������...  AAA // �� ����� � ����� ������... DG
void NextTrackX()
{
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

// ��������� ���� �� AAA
void NextTrack()
{
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
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
}

// ���������� ���� �� AAA
void PreviousTrack()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  if(PlayedTrack[PlayedPL]>1) {PlayedTrack[PlayedPL]--;}
  else {PlayedTrack[PlayedPL]=TC[PlayedPL];}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
}

// �����/���������������
void TogglePlayback()
{
  switch(PlayingStatus)
  {
  case 0:
    // ���� ����, �� ������������� �������...
    PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL] = 1)); //����� �������   AAA
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
  if(PlayedTrack[PlayedPL]!=0)PlayedTrack[PlayedPL] = 0;
}

//������� �������� ���� AAA
void CTDown()
{
  DisableScroll();
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
  if (CurrentTrack[CurrentPL]>1)
  {
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    CurrentTrack[CurrentPL] = TC[CurrentPL];
  }
}
#ifdef NEWSGOLD
#define SCROLL_MULT 1
#else 
#define SCROLL_MULT 10
#endif

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
void CTDovnSix()
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
  StopAllPlayback();
  PlayMP3File(GetCurrentTrack(CurrentTrack[CurrentPL]));
  if(PlayedPL!=CurrentPL)
  {
    PlayedTrack[PlayedPL] = 0;
    PlayedPL=CurrentPL;
  }
  PlayedTrack[PlayedPL] = CurrentTrack[CurrentPL];
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

/*
 ����� ���������� ������ � ����������...
*/

// ������� ������   AAA
void Memory()
{
  playlist_lines=malloc(TCPL*sizeof(char *)); // 5 �� �� 256 �����
  for(unsigned int i=0;i<TCPL;i++)
  {
    playlist_lines[i]=malloc(LinesInPL*sizeof(char *));
  }
 // CurrentTrack=malloc(TCPL*sizeof(int *));
 // PlayedTrack=malloc(TCPL*sizeof(int *));
 // TC=malloc(TCPL*sizeof(unsigned int *));
}

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn)
{
  if(LoadPlaylist(fn)-1>0) {TC[CurrentPL] = LoadPlaylist(fn)-1; CTtoFirst();}   // �������� ������ + ����������� �� ������� ������� + �� ������ ��������   AAA
  else {TC[CurrentPL]=0;}
}

// ������� ��!
void FreePlaylist(void)
{
  if (playlist_lines) mfree(playlist_lines);
  playlist_lines=NULL;
  if (id3tags1_lines) mfree(id3tags1_lines);
  id3tags1_lines=NULL;
}

// ��������� ��!
int LoadPlaylist(const char * fn)
{
  FSTATS stat;
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
 // FreePlaylist();

  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<16)
    {
      if (pp&&(pp!=p))
      {
	//playlist_lines=realloc(playlist_lines,(i+1)*sizeof(char *));
//        id3tags1_lines=realloc(id3tags1_lines,(i+1)*sizeof(char *));
     //   playlist_lines[CurrentPL][i+1]=malloc(256);
      //  playlist_lines=realloc(playlist_lines,(1)*sizeof(char *));
       // playlist_lines[CurrentPL]=realloc(playlist_lines[CurrentPL],(i+1)*sizeof(char *));
	playlist_lines[CurrentPL][i++]=pp;
        
        /*
        MP3Tagv1 * mytag = malloc(sizeof(MP3Tagv1)+1);
        if (GetMP3Tag_v1(playlist_lines[i],mytag))
        {
          char str[128];
          sprintf(str,"%s - %s",mytag->artist,mytag->title);
          strcpy(id3tags1_lines[i],str);
        }
        else
        {
          id3tags1_lines[i]=NULL;
        } 
        mfree(mytag);
        */
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
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
  int i;
  int f;
  char m[256];
  char s[]={0x0D}; 
  char s2[]={0x0A};                                // ������ ������������� � m3u 
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
  f=fopen(m,A_WriteOnly+A_MMCStream+A_Create,P_WRITE,&err);
  for (i=0;i<TC[CurrentPL]+1;i++)
  {
  fwrite(f,playlist_lines[CurrentPL][i],strlen(playlist_lines[CurrentPL][i]),&err);
  fwrite(f,s,1,&err);
  fwrite(f,s2,1,&err);
  }
  fclose(f,&err);
  ShowMSG(1,(int)"Playlist saved!");
}

/////////////////////////////////////////////////////<<<�������������� ��>>>/////////////////////////////////////////////////////////
// ��������� ������ � ��   AAA
void PastLine(char *p)
{
  playlist_lines[CurrentPL][TC[CurrentPL]+1]=p;
  TC[CurrentPL]++;
  CurrentTrack[CurrentPL]=TC[CurrentPL];
}

// �������� ������ � ��   AAA
void CopyLine(char *p)
{
  TC[CurrentPL]++;
  for(int i=TC[CurrentPL];i>CurrentTrack[CurrentPL]-1;i--)
    {
      playlist_lines[CurrentPL][i]=playlist_lines[CurrentPL][i-1];
    }
  playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]=p;
  if(PlayedTrack[PlayedPL]>CurrentTrack[CurrentPL]-1) {PlayedTrack[PlayedPL]++;}
  copy=0;
}

// ������� ������ �� ��   AAA
void DeleteLine()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  int i=CurrentTrack[CurrentPL];
  if(i!=TC[CurrentPL])
  {
    while(i<TC[CurrentPL])
    {
      playlist_lines[CurrentPL][i]=playlist_lines[CurrentPL][i+1];
      i++;
    }
  }
  else
  {
    CurrentTrack[CurrentPL]--;
  }
//  mfree(playlist_lines[CurrentPL][TC[CurrentPL]]);
  playlist_lines[CurrentPL][TC[CurrentPL]]=NULL;
  if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=0;}
  else{if(CurrentTrack[CurrentPL]<PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
  TC[CurrentPL]--;
  }
}

// ���������� ������ � �� �����   AAA
void MoveLineUp()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  char *p=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=1)
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}
    else{if(CurrentTrack[CurrentPL]-1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}}
    playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1];
    playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1]=p;
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=TC[CurrentPL];}
    else{if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]--;}}
    for(int i=1;i<TC[CurrentPL];i++)
    {
      playlist_lines[CurrentPL][i]=playlist_lines[CurrentPL][i+1];
    }
    playlist_lines[CurrentPL][TC[CurrentPL]]=p;
    CurrentTrack[CurrentPL]=TC[CurrentPL];
  }
  }
  }
}

// ���������� ������ � �� ����   AAA
void MoveLineDown()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  char *p=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=TC[CurrentPL])
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}
    else{if(CurrentTrack[CurrentPL]+1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
    playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1];
    playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1]=p;
    CurrentTrack[CurrentPL]++;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=1;}
    else {if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]++;}}
    for(int i=TC[CurrentPL];i>1;i--)
    {
      playlist_lines[CurrentPL][i]=playlist_lines[CurrentPL][i-1];
    }
    playlist_lines[CurrentPL][1]=p;
    CurrentTrack[CurrentPL]=1;
  }
  }
  }
}

// ���������� ������ � ��������� ��   AAA
void MoveLineRight()
{
  char *p=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  NextPL();
  PastLine(p);
}

// ���������� ������ � ���������� ��   AAA
void MoveLineLeft()
{
  char *p=playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  PrevPL();
  PastLine(p);
}
/////////////////////////////////////////////////////<<<�������������� ��>>>/////////////////////////////////////////////////////////

// ���������� ��� ����� �� ������� ����...
void FullpathToFilename(char * fname, WSHDR * wsFName)
{
  const char *p=strrchr(fname,0x1f)+1;
  const char *p2=strrchr(fname,'\\')+1;                         // ���� ��� �������� ����� ��������� �������... ������ ������� ���� ���������
  if (p2>p){
  int length=strrchr(fname,'.')-strrchr(fname,'\\')-1;
  utf8_2ws(wsFName,p2,length);
  } else{
  int length=strrchr(fname,'.')-strrchr(fname,'\\')-2;
  utf8_2ws(wsFName,p,length);
  }
}

// ����������� ���� �� ������ � ��
char * GetCurrentTrack()
{
  return playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
}

char * GetPlayedTrack()
{
  return playlist_lines[PlayedPL][PlayedTrack[PlayedPL]];
}

// ���������� ��� ���������������� �� ������ � ��
char * GetTrackByNumber(int number)
{
  return playlist_lines[CurrentPL][number];
}

// ��� �������� ��������� ��������!!   AAA
void PL_Redraw()
{
  
  unsigned short my_x;
  unsigned short my_y;
  unsigned short k;
  unsigned short c = 0;  // ����������  AAA
  int i;
  
  // ��� �����...
  if (TC[CurrentPL]>0)
  {
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
    if (TC[CurrentPL]>5)
    {
    if(CurrentTrack[CurrentPL]==1) {k=0;}
    else{ if(CurrentTrack[CurrentPL]==2) {k=1;}
    else{ if(CurrentTrack[CurrentPL]==TC[CurrentPL]-2) {k=3;}
    else{ if(CurrentTrack[CurrentPL]==TC[CurrentPL]-1) {k=4;}
    else{ if(CurrentTrack[CurrentPL]==TC[CurrentPL]) {k=5;} else {k=2;}}}}}
    }else{
    if(CurrentTrack[CurrentPL]==1) {k=0;}
    else{ if(CurrentTrack[CurrentPL]==2) {k=1;}
    else{ if(CurrentTrack[CurrentPL]==3) {k=2;}
    else{ if(CurrentTrack[CurrentPL]==4) {k=3;}
    else{ if(CurrentTrack[CurrentPL]==5) {k=4;}}}}}
    }
    
    for(int l=0;l<6;l++)
    {
    i = CurrentTrack[CurrentPL]+l-k;
    if(TC[CurrentPL]>l)
    {
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    if(k!=l)
    {
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack[CurrentPL]==i)
    {
      DrawScrollString(out_ws,my_x,my_y+c,w-7,my_y+GetFontYSIZE(FONT_SMALL)+c,
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }else{
      DrawScrollString(out_ws,my_x,my_y+c,w-7,my_y+GetFontYSIZE(FONT_SMALL)+c,
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    
    }else{
      
      char sfname[256];
      sprintf(sfname,"%s%s",PIC_DIR,"cursor.png");
      DrawImg(my_x-1,my_y+c-3,(int)sfname);
      
    if (PlayedTrack[CurrentPL]==CurrentTrack[CurrentPL])
    {
//      DrawString(out_ws,my_x,my_y,w,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      if(GrafOn)
      {
          int i=Get_WS_width(out_ws,FONT_SMALL);  //���������� ���-�� �������� ��� ���� ������ (��� ��� �� ����� ����...)
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
      DrawScrollString(out_ws,my_x,my_y+c,w-7,my_y+GetFontYSIZE(FONT_SMALL)+c,
                   scroll_disp+1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }else{
//      DrawString(out_ws,my_x,my_y,w,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT),0);

	if(GrafOn)
        {
          int i=Get_WS_width(out_ws,FONT_SMALL);
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
      DrawScrollString(out_ws,my_x,my_y+c,w-7,my_y+GetFontYSIZE(FONT_SMALL)+c,
                   scroll_disp+1,FONT_SMALL,0,color(COLOR_TEXT),0);
    }
    c+=15;
    }
    c+=15;
    }
    }
    FreeWS(out_ws);
  }
  // ��������
  WSHDR * pl_c = AllocWS(64);
  wsprintf(pl_c,"%i/%i/%i;%i/%i",CurrentTrack[CurrentPL],TC[CurrentPL],CurrentPL+1,PlayedTrack[PlayedPL],PlayedPL+1);
  DrawString(pl_c,NUMmy_x,NUMmy_y,NUMmy_x+w,NUMmy_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,color(COLOR_TEXT),0);
  FreeWS(pl_c);
  BandRoll();
}

// ������ ���������   AAA
void BandRoll()
{
  if(TC[CurrentPL]>6)
  {
    int yy=CurrentTrack[CurrentPL]*(BR2_y-BR1_y)/TC[CurrentPL];
    DrawRoundedFrame(BR_x,BR1_y,BR_x+BR_w-1,BR2_y,0,0,0,0,color(COLOR_BANDROLL));
    DrawRoundedFrame(BRC_x,BR1_y+yy-(BR2_y-BR1_y)/TC[CurrentPL],BRC_x+BRC_w-1,BR1_y+yy,0,0,0,0,color(COLOR_BANDROLL_C));
  }
}

//���� ����� � �����   AAA
void FindMusic(const char *dir, int i)
{
 // int i;
  DIR_ENTRY de;
  unsigned int err;
  char path[256];
  memcpy(path,dir,strlen(dir)-1);
  char *ptr=path+strlen(path)+1;
  strcat(path,"\\*.mp3");
  if (FindFirstFile(&de,path,&err))
  {
   // i=1;
    do
    {
      strcpy(ptr,de.file_name);
      if(isdir(path,&err))
      {
       // FindMusic(path,i);
      }
      else
      {
        char *p=malloc(256);
        strncpy(p,path,256);
        //playlist_lines=realloc(playlist_lines,(i+1)*sizeof(p));
       // playlist_lines[CurrentPL][i+1]=malloc(256);
        playlist_lines[CurrentPL][i++]=p;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if(i>1) {TC[CurrentPL]=i-1;}
  else {TC[CurrentPL]=0;}
}

// ������ ������ � ����� ���� �������...   AAA
void MemoryFree()
{
  GBS_DelTimer(&tmr_scroll);
  GBS_DelTimer(&tmr_displacement);
}
