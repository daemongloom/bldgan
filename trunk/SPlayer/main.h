#ifndef _MAIN_H_
  #define _MAIN_H_

#define VIBRA_POWER 10 // ���� ����� ��� ������� ������� ����

#define USE_PNG_EXT   // ������������ �� ���������� PNG ��� �������� (ELFLoader >2.0)

#define USE_LOG  // ����� ���, ���� ��� - ������ ����������������

#define MAX_INIBUF 256  // ������ ������ ���-�����

typedef void (*INIPROC) (char *name, char *value); // ��������� ��������� ���-�����

// ����� ������� ������ MAIN.C

//#define color(x) (char *)(&(x))

// ��� ������ main.c
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
// ��� ������ main.c
/*
typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;
*/
// ��������� ���������
typedef struct
{
  char *filename;
  char *name;
  void *next;
}PLIST;

typedef struct
{
  WSHDR* full_name; // ���� � �����   AAA
  char istagg[3]; // ����� "TAG"
  char title[30]; // ��������
  char artist[30]; // �����������
  char album[30]; // ������
  char year[4]; // ���
  char comment[30]; // �����������
  int number; // �����   AAA
  int genre; // ����
  int version1_1; // 1 - ������ 1.1, 0 - ������ 1.0   AAA
  int present; // ������������
}ID3TAGDATA;

int ReadID3v1(WSHDR* fnamews, ID3TAGDATA *tag); // ������ ID3 v1

#define TOTAL_ITEMS_1 15
#define ALLPNG 40

// ������... �� �� ���� ������ ���� �����   AAA
static const char * const items1[TOTAL_ITEMS_1] = {
/*  1*/ "background",
/*  2*/ "volume",   // x6
/*  3*/ "stop",     // x3
/*  4*/ "pause",    // x3
/*  5*/ "play",     // x3
/*  6*/ "playall",  // x2
/*  7*/ "repeat",   // x2
/*  8*/ "random",   // x2
/*  9*/ "repeatone",// x2
/* 10*/ "next",     // x2
/* 11*/ "prev",     // x2
/* 12*/ "keylock",
/* 13*/ "cursor",
/* 14*/ "_down",
/* 15*/ "_idle",
};
#define PNGEXT ".png"

/*
static const char * const items1[TOTAL_ITEMS] = {
 "background.png",
 "volume",   // x5
 "stop_down",
 "pause_down",
 "play_down",
 "stop",
 "pause",
 "play",
 "playall_down",
 "repeat_down",
 "random_down",
 "repeatone_down",
 "playall",
 "repeat",
 "random",
 "repeatone",
 "next_down",
 "next",
 "prev_down",
 "prev",
 "keylock",
 "cursor",
 "stop_idle",
 "pause_idle",
 "play_idle",
 ".png", // ����� ������� ����� ��� �����   AAA
};
*/
#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

void load_skin(char const* cfgname);

void PlayMP3File(WSHDR * fname);

void SendNULL();    // ������� �� ��������� �����.   AAA

void ToDevelop();   // ����������   AAA

void PausingTime(unsigned short action);

void QuitCallbackProc(int decision);

void DoErrKey();

void DoExit();

void LoadDefPlaylist();

void PrevTrackDown();

void NextTrackDown();

void SwitchPlayModeDown();

void DoKey(int key, int ka);

char *strtolower(char *src, char *dst, int sz);

int EnumIni(int local, char *ininame, INIPROC proc);

void LoadKeys();

#endif
