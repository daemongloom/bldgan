#ifndef _MAIN_H_
  #define _MAIN_H_

#define VIBRA_POWER 10 // Сила вибры для событий разного рода

#define USE_PNG_EXT   // Использовать ли расширение PNG для картинок (ELFLoader >2.0)

#define USE_LOG  // Вести лог, если нет - строку закомментировать

#define MAX_INIBUF 256  // Размер буфера ини-файла

typedef void (*INIPROC) (char *name, char *value); // Процедура обработки ини-файла

// Общие функции модуля MAIN.C

//#define color(x) (char *)(&(x))

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
/*
typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;
*/
// Структура плейлиста
typedef struct
{
  char *filename;
  char *name;
  void *next;
}PLIST;

typedef struct
{
  WSHDR* full_name; // Путь к файлу   AAA
  char istagg[3]; // Слово "TAG"
  char title[30]; // Название
  char artist[30]; // Исполнитель
  char album[30]; // Альбом
  char year[4]; // Год
  char comment[30]; // Комментарий
  int number; // Номер   AAA
  int genre; // Жанр
  int version1_1; // 1 - версия 1.1, 0 - версия 1.0   AAA
  int present; // Присутствует
}ID3TAGDATA;

int ReadID3v1(WSHDR* fnamews, ID3TAGDATA *tag); // Чтение ID3 v1

#define TOTAL_ITEMS_1 15
#define ALLPNG 40

// Лепота... Но за один запуск жрет много   AAA
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
 ".png", // Перед пунктом лепим все новое   AAA
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

void SendNULL();    // Послать по окончании воспр.   AAA

void ToDevelop();   // Развернуть   AAA

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
