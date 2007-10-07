#include "../inc/swilib.h"
#include "main.h"
#include "playlist.h"

char **playlist_lines;  // ������ ���������� �� ����� ������ � ��
char **id3tags1_lines;  // ������ ���������� �� ID3v1-����

// �� �������
extern const char COLOR_TEXT[];
extern const char COLOR_TEXT_CURSOR[]; //��� �������  AAA
extern const char COLOR_TEXT_PLAY[];   //� ��� AAA
extern const char COLOR_BANDROLL[];      //���� ������ ���������
extern const char COLOR_BANDROLL_C[];
extern const int SHOW_FULLNAMES;
extern const char PIC_DIR[];           // ��� ������� AAA
extern const int EXT;                  // ���������� �� ���������

// ��� ����������
unsigned short SoundVolume = 2;       // ���������
unsigned short SVforToggle = 0;       // ������� ���������
unsigned short PlayingStatus = 0;     // ������ ������ (0 - ����, 1 - �����, 2 - ������)   // ���� char ����� unsigned short! :D   AAA
short phandle = -1;                   // ��� ������
int CurrentTrack = 1;                 // ������� ����
unsigned int TC = 0;                  // ���������� ������ � �� 
unsigned int PlayedTrack = 0;         // ������������� ����   AAA
char * l_color_text;                  // ����������� ����
int PlayTime;

extern unsigned short CTmy_x;     // ���������� CurrentTrack
extern unsigned short CTmy_y;
extern unsigned short s;          // �������� �� ���������
extern unsigned short NUMmy_x;    // ������
extern unsigned short NUMmy_y;

extern unsigned short w;
extern int playmode;

extern unsigned int MAINGUI_ID;

// --- ��������� ---

#define TMR_SEC 216*2
GBSTMR tmr_scroll;
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
      scroll_disp=scroll_disp+5; //scroll_disp++;
      GBS_StartTimerProc(&tmr_scroll,scroll_disp!=i?TMR_SEC>>4:TMR_SEC,scroll_timer_proc);  //scroll_disp!=i?TMR_SEC>>5:TMR_SEC
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
  int prevtrack=PlayedTrack;
  while (PlayedTrack==prevtrack) {
    PlayedTrack=random(TC);
  }
  if(PlayedTrack>TC)PlayedTrack=1;
  PlayMP3File(GetPlayedTrack(PlayedTrack));
}

//������������� ����       ������ ����� �� ��������...  AAA
void RepeatTrack()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  PlayMP3File(GetPlayedTrack(PlayedTrack));
}

// ��� plamode==1       ������ ����� �� ��������...  AAA
void NextTrackX()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  PlayedTrack++;
  if(PlayedTrack>TC)
  {
    PlayedTrack=1;
  }
  else
  {
    PlayMP3File(GetPlayedTrack(PlayedTrack));
  }
}

// ��������� ���� �� AAA
void NextTrack()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  PlayedTrack++;
  if(PlayedTrack>TC)PlayedTrack=1;
  PlayMP3File(GetPlayedTrack(PlayedTrack));
}

// ���������� ���� �� AAA
void PreviousTrack()
{
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
  PlayedTrack--;
  if(PlayedTrack==0)PlayedTrack=TC;
  PlayMP3File(GetPlayedTrack(PlayedTrack));
}

// �����/���������������
void TogglePlayback()
{
  switch(PlayingStatus)
  {
  case 0:
    // ���� ����, �� ������������� �������...
    PlayMP3File(GetPlayedTrack(PlayedTrack = 1)); //����� �������   AAA
    break;
  case 1:
    // ���� ����� - ���������� ���������������...
    if (phandle!=-1)
    {
      PlayMelody_ResumePlayBack(phandle);
      PlayingStatus = 2;
    }
    break;
  case 2:
    // ���� ������ - ������ �����...
    if (phandle!=-1)
    {
      PlayMelody_PausePlayback(phandle);
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

// ������������� ��� ����������� ����� AAA
void CTandPTtoFirst()
{
  if(CurrentTrack>1)CurrentTrack = 1;
  if(PlayedTrack>0)PlayedTrack = 0;
}

//������� �������� ���� AAA
void CTDown()
{
  if (CurrentTrack<TC)
  {
    CurrentTrack++;
  }
  else
  {
    CurrentTrack = 1;
  }
  DisableScroll();
}

//������� �������� ����� AAA
void CTUp()
{
  if (CurrentTrack>1)
  {
    CurrentTrack--;
  }
  else
  {
    CurrentTrack = TC;
  }
  DisableScroll();
}

//�������� �������� ���� AAA
void CTDovnSix()
{
  if ((TC>6)&&(CurrentTrack+6<TC+1))
  {
    CurrentTrack = CurrentTrack+6;
  }
  else
  {
    CurrentTrack = TC;
  }
  DisableScroll();
}

//�������� �������� ����� AAA
void CTUpSix()
{
  if ((TC>6)&&(CurrentTrack-6>0))
  {
    CurrentTrack = CurrentTrack-6;
  }
  else
  {
    CurrentTrack = 1;
  }
  DisableScroll();
}

//������������� AAA
void PlayTrackUnderC()
{
  StopAllPlayback();
  PlayMP3File(GetCurrentTrack(CurrentTrack));
  PlayedTrack = CurrentTrack;
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
  return TC;
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

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn)
{
  if(LoadPlaylist(fn)-1>0) {TC = LoadPlaylist(fn)-1;}   // �������� ������ + ����������� �� ������� �������   AAA
  else {TC=0;}
//  if (TC>0)   // � ���������� �����? ���� "Playlist loaded!", �� �� ������ ������ => ����� ������ ������?
//  {
//    LockSched();
//    ShowMSG(1,(int)"Playlist loaded!");
//    UnlockSched();
//  }
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
  FreePlaylist();

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
	playlist_lines=realloc(playlist_lines,(i+1)*sizeof(char *));
//        id3tags1_lines=realloc(id3tags1_lines,(i+1)*sizeof(char *));
	playlist_lines[i++]=pp;
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
  l_color_text = Lighten((char*)COLOR_TEXT);
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
  for (i=0;i<TC+1;i++)
  {
  fwrite(f,playlist_lines[i],strlen(playlist_lines[i]),&err);
  fwrite(f,s,1,&err);
  fwrite(f,s2,1,&err);
  }
  fclose(f,&err);
  ShowMSG(1,(int)"Playlist saved!");
}

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
  return playlist_lines[CurrentTrack];
}

char * GetPlayedTrack()
{
  return playlist_lines[PlayedTrack];
}

// ���������� ��� ���������������� �� ������ � ��
char * GetTrackByNumber(int number)
{
  return playlist_lines[number];
}

// ���������� �����-������
char * Lighten(char * source)
{
  char * dest = "";
  if((source[3]-=0x15)<=0x00)source[3]=0x00;
  setColor(source[0],source[1],source[2],source[3],dest);
  return dest;
}

// �����������
void PL_Redraw()
{
  unsigned short c = 0;  // ����������  AAA
  unsigned short my_x;
  unsigned short my_y;
  
  // ��� �����...
  if (TC>0)
  {
    my_x = CTmy_x;
    my_y = CTmy_y;

    WSHDR * out_ws = AllocWS(128);

    // ������������  AAA
  if (TC>5)
  {
    if (CurrentTrack==1) {my_y = my_y-2*s;}
    if (CurrentTrack==2) {my_y = my_y-s;}
    if (CurrentTrack==TC-2) {my_y = my_y+s;}
    if (CurrentTrack==TC-1) {my_y = my_y+2*s;}
    if (CurrentTrack==TC) {my_y = my_y+3*s;}
  }
  else
  {
    if (TC<6)
    {
      if (CurrentTrack==1) {my_y = my_y-2*s;}
      if (CurrentTrack==2) {my_y = my_y-s;}
      if (CurrentTrack==4) {my_y = my_y+s;}
      if (CurrentTrack==5) {my_y = my_y+2*s;}
    }
  }

    // -5
    int i = CurrentTrack-5;
    if((CurrentTrack==TC)&&(TC>5))
    {
    c = -s*5;
    if(i<0)i=TC+i;
    if(i==0)i=TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // -4
    if(((TC>5)&&(CurrentTrack>TC-2))||((TC<6)&&(CurrentTrack==5)))
    {
    i = CurrentTrack-4;
    c = -s*4;
    if(i<0)i=TC+i;
    if(i==0)i=TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    
    // -3
    if(((TC>5)&&(CurrentTrack>TC-3))||((TC<6)&&(CurrentTrack>3)))
    {
    i = CurrentTrack-3;
    c = -s*3;
    if(i<0)i=TC+i;
    if(i==0)i=TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // -2
    if(((TC>5)&&(CurrentTrack>2))||((TC<6)&&(CurrentTrack>2)))
    {
    i = CurrentTrack-2;
    c = -s*2;
    if(i<0)i=TC+i;
    if(i==0)i=TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // -1
    if(((TC>5)&&(CurrentTrack>1))||((TC<6)&&(CurrentTrack>1)))
    {
    i = CurrentTrack-1;
    c = -s;
    if(i==0)i=TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    
    // ������ ������ ���� ��� �� �������� �����...
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // ������� 0
    char sfname[256];
    sprintf(sfname,"%s%s",PIC_DIR,"cursor.png");
    DrawImg(my_x-1,my_y-2,(int)sfname);
    
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetCurrentTrack(),strlen(GetCurrentTrack()));
    }
    else
    {
      FullpathToFilename(GetCurrentTrack(),out_ws);
    };
     if (PlayedTrack==CurrentTrack)
    {
//      DrawString(out_ws,my_x,my_y,w,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      int i=Get_WS_width(out_ws,FONT_SMALL);  //���������� ���-�� �������� ��� ���� ������ (��� ��� �� ����� ����...)
	  i-=(w-7);   //�� ���� �����������
	  if (i<0)
	  {
	    DisableScroll();
	  }
	  else
	  {
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
      DrawScrollString(out_ws,my_x,my_y,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   scroll_disp+1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y,w,my_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//               color(COLOR_TEXT),0);

	  int i=Get_WS_width(out_ws,FONT_SMALL);
	  i-=(w-7);
	  if (i<0)
	  {
	    DisableScroll();
	  }
	  else
	  {
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
      DrawScrollString(out_ws,my_x,my_y,w-5,my_y+GetFontYSIZE(FONT_SMALL),
                   scroll_disp+1,FONT_SMALL,0,color(COLOR_TEXT),0);
    }
    
    // +1
    if(((CurrentTrack<TC)&&(TC>5))||((TC<6)&&(CurrentTrack<TC)))
    {
    i = CurrentTrack+1;
    c = s*2;
    
    if(i>TC)i=i-TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
      
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // +2
    if(((CurrentTrack<TC-1))&&((TC>5)||(TC<6)&&(CurrentTrack<TC-1)))
    {
    i = CurrentTrack+2;
    c = s*3;
    
    if(i>TC)i=i-TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };
    
    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0); 
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // +3
    if(((CurrentTrack<TC-2)&&(TC>5))||((TC<6)&&(CurrentTrack<TC-2)))
    {
    i = CurrentTrack+3;
    c = s*4;
    
    if(i>TC)i=i-TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };

    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // +4
    if(((CurrentTrack<3)&&(TC>5))||((TC<6)&&(CurrentTrack<TC-3)))
    {
    i = CurrentTrack+4;
    c = s*5;
    
    if(i>TC)i=i-TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };

    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
    
    // +5
    if((CurrentTrack==1)&&(TC>5))
    {
    i = CurrentTrack+5;
    c = s*6;
    
    if(i>TC)i=i-TC;
    if (SHOW_FULLNAMES)
    {
      utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
    }
    else
    {
      FullpathToFilename(GetTrackByNumber(i),out_ws);
    };

    if (PlayedTrack==i)
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_PLAY),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_PLAY),0);
    }
    else
    {
//      DrawString(out_ws,my_x,my_y+c,w,my_y+c+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
//                 color(COLOR_TEXT_CURSOR),0);
      
      DrawScrollString(out_ws,my_x,my_y+c,w-5,my_y+c+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT_CURSOR),0);
    }
    }
  // ��������� �� ������� ��� ����������... :)
  /*
  DrawScrollString(filen,my_x,my_y,w,my_y+GetFontYSIZE(FONT_SMALL),
                   1,FONT_SMALL,0,color(COLOR_TEXT),0);
  */
    FreeWS(out_ws);
  }

  // ��������
  WSHDR * pl_c = AllocWS(64);
  wsprintf(pl_c,"%i/%i/%i",PlayedTrack,CurrentTrack,TC);
  DrawString(pl_c,NUMmy_x,NUMmy_y,NUMmy_x+50,NUMmy_y+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,
           color(COLOR_TEXT),0);
  FreeWS(pl_c);
  BandRoll();
}

// ������ ���������. �������   AAA
void BandRoll()
{
  if(TC>6)
  {
    int yy=CurrentTrack*102/TC;
    DrawRoundedFrame(129,50,w-3,152,0,0,0,0,color(COLOR_BANDROLL));
    DrawRoundedFrame(128,50+yy-102/TC,w-3,50+yy,0,0,0,0,color(COLOR_BANDROLL_C));
  }
}
/*
void DrawPlayTime(char* fname)
{
  PlayTime = GetWavLen(fname);
  WSHDR * t = AllocWS(64);
  wsprintf(t,"%i",PlayTime);
  DrawString(t,NUMmy_x,NUMmy_y+10,NUMmy_x+50,NUMmy_y+GetFontYSIZE(FONT_SMALL)+10,FONT_SMALL,0,
           color(COLOR_TEXT),0);
  FreeWS(t);
}*/
double GetWavkaLength(char *fpath,char *fname) //�����
{
  int f;
  unsigned int ul;
  
  int DataLength;//4
  int BytePerSec;//28  
  
  char ffn[128];
  strcpy(ffn, fpath);
  strcat(ffn, fname);
  if ((f=fopen(ffn,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    lseek(f,4,S_SET,&ul,&ul);
    fread(f,&DataLength,sizeof(DataLength),&ul);
    
    lseek(f,28,S_SET,&ul,&ul);
    fread(f,&BytePerSec,sizeof(BytePerSec),&ul);
    
    fclose(f,&ul);
    
    return (((((double)DataLength/(double)BytePerSec)*(double)1000)*0.216)/*+dop_delay*/);
  }
    else
      return 0;
}
