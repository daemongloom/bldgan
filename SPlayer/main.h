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
  char*full_name; // Путь к файлу   AAA
  char istagg[3]; // Слово "TAG"
  char title[30]; // Название
  char artist[30]; // Исполнитель
  char album[30]; // Альбом
  char year[4]; // Год
  char comment[30]; // Комментарий
  int genre; // Жанр
  int present; // Присутствует
}ID3TAGDATA;

int ReadID3v1(char*fname, ID3TAGDATA *tag); // Чтение ID3 v1


#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

void load_skin(char const* cfgname);

void PlayMP3File(const char * fname);

void PausingTime(unsigned short action);

void QuitCallbackProc(int decision);
#endif
