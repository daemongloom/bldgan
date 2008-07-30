#include "../inc/swilib.h"
#include "main.h"
#include "langpack.h"
// ������� Ganster'� �� ��������������� ���!
// ��������� ����� ID3v1

//ID3TAGDATA *MainTag; // ���������, ��� ������� ����� �������� ������, ���� MainTag=malloc(sizeof(ID3TAGDATA)); �� ��������� ������ �� �������� ������ �����������

/*******************************************************************************
  ������ ID3v1.
����: ���� � ��3 - �����; ���������, � ������� ���� ������
�����: ���� ����������� ����� � �����
*******************************************************************************/
int ReadID3v1(WSHDR* fnamews, ID3TAGDATA *tag) // ������ ID3 v1
{
  char* fname=malloc(256);
  ws_2str(fnamews,fname,256);
 // wstrcpy(tag->full_name,fnamews);
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
    // �������� ��� ��� :)   AAA 
    if(tagtext[122]!=0x00)   //  !!��� 0�20(������) ������ �� ������ ��� ������ �����...!!
    {
      memcpy(tag->comment,&tagtext[94],30);
    }else{
      tag->version1_1=1;   // ���������� ������ �����   AAA
      memcpy(tag->comment,&tagtext[94],28);
      tag->number = tagtext[123];
    }
    tag->genre = tagtext[124];
    mfree(tagtext); // ����������� ������
  }
  else {tag->present=0; extern const unsigned int SHOW_POPUP; if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_No_Tags]);} // ���� �������� �� ������, ������ ����� ���
  fclose(f,&err); // ��������� ����
  mfree(fname);
  REDRAW(); // �������������� �����
  return (tag->present); // ���������� ���� ����������� �����
}

// ReadID3v1(0:\\Music\\1.mp3, MainTag)
