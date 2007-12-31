#include "../inc/swilib.h"
#include "main.h"
#include "lang.h"
// Респект Ganster'у за предоставленный код!
// Структура тегов ID3v1

//ID3TAGDATA *MainTag; // Структура, под которую нужно выделить память, типа MainTag=malloc(sizeof(ID3TAGDATA)); По окончанию работы не забываем память освобождать

/*******************************************************************************
  Чтение ID3v1.
Вход: путь к мр3 - файлу; структура, в которую теги читаем
Выход: флаг присутствия тегов в файле
*******************************************************************************/
int ReadID3v1(char*fname, ID3TAGDATA *tag) // Чтение ID3 v1
{
  tag->full_name=fname;
  unsigned int err;
  int f;
  FSTATS stat;
  zeromem(tag, sizeof(ID3TAGDATA)); // Очищаем память
  f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &err); // Открываем файл для чтения
  GetFileStats(fname, &stat, &err); // Берем размер файла
  lseek(f,(stat.size-128), 0, &err, &err); // Смещаемся на 128 байт с конца
  fread( f, tag->istagg, 3, &err ); // Читаем слово "TAG"
  if((tag->istagg[0]=='T')&&(tag->istagg[1]=='A')&&(tag->istagg[2]=='G'))// Если там действительно написано "TAG",
  {
    tag->present=1; // Значит тег в треке есть
    char *tagtext=malloc(125); // Выделяем память под тег
    fread( f,tagtext, 125, &err ); // Читаем тег в память
    memcpy(tag->title, &tagtext[0],30); // Парсим тег
    memcpy(tag->artist,&tagtext[30],30);
    memcpy(tag->album,&tagtext[60],30);
    memcpy(tag->year,&tagtext[90],4);
    memcpy(tag->comment,&tagtext[94],30);
    tag->genre = tagtext[124];
    mfree(tagtext); // Освобождаем память
  }
  else {tag->present=0; ShowMSG(1,(int)LG_No_Tags);} // Если проверку не прошли, значит тегов нет
  fclose(f,&err); // Закрываем файл
  REDRAW(); // Перерисовываем экран
  return (tag->present); // Возвращаем флаг присутствия тегов
}

// ReadID3v1(0:\\Music\\1.mp3, MainTag)
