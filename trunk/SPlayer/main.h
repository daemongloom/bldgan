#ifndef _MAIN_H_
  #define _MAIN_H_

#define VIBRA_POWER 10 // Сила вибры для событий разного рода

#define USE_PNG_EXT   // Использовать ли расширение PNG для картинок (ELFLoader >2.0)

#define USE_LOG  // Вести лог, если нет - строку закомментировать

// Общие функции модуля MAIN.C

#define color(x) (char *)(&(x))

// Для модуля main.c
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
// Для модуля main.c

typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;

// Структура плейлиста
typedef struct
{
  char *filename;
  char *name;
  void *next;
}PLIST;

// Структура mp3-тега
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

void StopTimeTimer();

void time_timer_proc();

void PlayMP3File(const char * fname);

void UpdateCSMname(WSHDR * tname);

void QuitCallbackProc(int decision);
#endif
