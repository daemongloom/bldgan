#include "../inc/swilib.h"
#include "main.h"
#include "lang.h"
// ������� Ganster'� �� ��������������� ���!
// ��������� ����� ID3v1

//ID3TAGDATA *MainTag; // ���������, ��� ������� ����� �������� ������, ���� MainTag=malloc(sizeof(ID3TAGDATA)); �� ��������� ������ �� �������� ������ �����������

/*******************************************************************************
  ������ ID3v1.
����: ���� � ��3 - �����; ���������, � ������� ���� ������
�����: ���� ����������� ����� � �����
*******************************************************************************/
int ReadID3v1(char*fname, ID3TAGDATA *tag) // ������ ID3 v1
{
  tag->full_name=fname;
  unsigned int err;
  int f;
  FSTATS stat;
  zeromem(tag, sizeof(ID3TAGDATA)); // ������� ������
  f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &err); // ��������� ���� ��� ������
  GetFileStats(fname, &stat, &err); // ����� ������ �����
  lseek(f,(stat.size-128), 0, &err, &err); // ��������� �� 128 ���� � �����
  fread( f, tag->istagg, 3, &err ); // ������ ����� "TAG"
  if((tag->istagg[0]=='T')&&(tag->istagg[1]=='A')&&(tag->istagg[2]=='G'))// ���� ��� ������������� �������� "TAG",
  {
    tag->present=1; // ������ ��� � ����� ����
    char *tagtext=malloc(125); // �������� ������ ��� ���
    fread( f,tagtext, 125, &err ); // ������ ��� � ������
    memcpy(tag->title, &tagtext[0],30); // ������ ���
    memcpy(tag->artist,&tagtext[30],30);
    memcpy(tag->album,&tagtext[60],30);
    memcpy(tag->year,&tagtext[90],4);
    memcpy(tag->comment,&tagtext[94],30);
    tag->genre = tagtext[124];
    mfree(tagtext); // ����������� ������
  }
  else {tag->present=0; ShowMSG(1,(int)LG_No_Tags);} // ���� �������� �� ������, ������ ����� ���
  fclose(f,&err); // ��������� ����
  REDRAW(); // �������������� �����
  return (tag->present); // ���������� ���� ����������� �����
}

// ReadID3v1(0:\\Music\\1.mp3, MainTag)
