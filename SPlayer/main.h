#ifndef _MAIN_H_
  #define _MAIN_H_

#define VIBRA_POWER 10 // ���� ����� ��� ������� ������� ����

#define USE_PNG_EXT   // ������������ �� ���������� PNG ��� �������� (ELFLoader >2.0)

#define USE_LOG  // ����� ���, ���� ��� - ������ ����������������

// ����� ������� ������ MAIN.C

#define color(x) (char *)(&(x))

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

typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;

// ��������� ���������
typedef struct
{
  char *filename;
  char *name;
  void *next;
}PLIST;

// ��������� mp3-����
typedef struct
{
  char id[3];
  char title[30];
  char artist[30];
  char album[30];
  char year[4];
  char comment[30];
  short genre;
}MP3Tagv1;

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

void PlayMP3File(const char * fname);

void PausingTime(unsigned short action);

void QuitCallbackProc(int decision);
#endif