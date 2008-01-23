#include "C:\arm\inc\swilib.h"

const char elfpath[]="4:\\Zbin\\altdaemons\\";
void RunElfs()
{
  WSHDR *ws;
  ws=AllocWS(150);
  DIR_ENTRY de; //директория
  unsigned int err;//ошибка
  char name[256];//описание переменной
  strcpy(name,elfpath);//копирование полной строки в переменную name
  strcat(name,"*.elf");//создание строки с расширением еlf
  if (FindFirstFile(&de,name,&err))//ecли поиск, в директории и имени
  {
    do
    {
      strcpy(name,de.folder_name);
      strcat(name,"\\");
      strcat(name,de.file_name);
      str_2ws(ws,name,128);
      ExecuteFile(ws,0,0);
    }
    while(FindNextFile(&de,&err));
  }
  FreeWS(ws);
}
