#include "C:\arm\inc\swilib.h"

const char elfpath[]="4:\\Zbin\\altdaemons\\";
void RunElfs()
{
  WSHDR *ws;
  ws=AllocWS(150);
  DIR_ENTRY de; //����������
  unsigned int err;//������
  char name[256];//�������� ����������
  strcpy(name,elfpath);//����������� ������ ������ � ���������� name
  strcat(name,"*.elf");//�������� ������ � ����������� �lf
  if (FindFirstFile(&de,name,&err))//ec�� �����, � ���������� � �����
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
