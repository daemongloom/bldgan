#include "..\inc\swilib.h"
#include "lang.h"
#include "item_info.h"
#include "mainmenu.h"
#include "main.h"
#include "ID3Genres.h"

#define MAX_SYMB 1024
WSHDR* ws_info = NULL;

int info_onkey(GUI *gui, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    return(-1); //do redraw
  }
  return(0); //Do standart keys

}

void info_ghook(GUI *gui, int cmd)
{
  if (cmd==2)
  {
    //Called after onCreate
  }

  if (cmd==7)
  {

  }

  if(cmd==0xA)
  {
    DisableIDLETMR();   // ��������� ������ ������ �� ��������
  }

  if(cmd==0x03)     // onDestroy
  {
    FreeWS(ws_info);
    ws_info = NULL;
  }
}

SOFTKEY_DESC info_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB info_skt=
{
  info_sk,0
};

INPUTDIA_DESC info_desc=
{
  1,
  info_onkey,
  info_ghook,
  (void *)inp_locret,
  0,
  &info_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// �������� ����-������
};

HEADER_DESC info_hdr={0,0,0,0,NULL,(int)LG_ID3_Tag_Info,LGP_NULL};

void Disp_Info(ID3TAGDATA *tag)
{
  // ������ �������� ������������� ������ ������� �����
  ws_info = AllocWS(MAX_SYMB);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  // ��������� �������� - ������ �������, ����������� ����� �����, � ������ ������
  wsprintf(ws_info,"");
  ConstructEditControl(&ec,ECT_READ_ONLY,0,ws_info,1);
  AddEditControlToEditQend(eq,&ec,ma);
  
/*  // File
  wsprintf(ws_info,"%t",LG_Full_name);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ws_info,"%w",tag->full_name);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);
  // Size
  wsprintf(ws_info,"%t",LG_Size);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
  AddEditControlToEditQend(eq,&ec,ma);
  FSTATS stat;
  unsigned int err;
  int fsize;
  GetFileStats(tag->full_name,&stat,&err);
  fsize=stat.size;
  wsprintf(ws_info,"%i",fsize);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,128);
  AddEditControlToEditQend(eq,&ec,ma);*/
  // Title
  if(strlen(tag->title))
  {
    wsprintf(ws_info,"%t",LG_Title);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  
    wsprintf(ws_info,"%t",tag->title);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Artist
  if(strlen(tag->artist))
  {
    wsprintf(ws_info,"%t",LG_Artist);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  
    wsprintf(ws_info,"%t",tag->artist);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Album
  if(strlen(tag->album))
  {
    wsprintf(ws_info,"%t",LG_Album);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
    
    wsprintf(ws_info,"%t",tag->album);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Year
  if(strlen(tag->year))
  {
    wsprintf(ws_info,"%t",LG_Year);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  
    wsprintf(ws_info,"%t",tag->year);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,4);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Comment
  if(strlen(tag->comment))
  {
    wsprintf(ws_info,"%t",LG_Comment);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  
    wsprintf(ws_info,"%t",tag->comment);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Number
  if(tag->version1_1&&tag->number)
  {
    wsprintf(ws_info,"%t",LG_Number);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
    
    wsprintf(ws_info,"%i",tag->number);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,128);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  // Genre
  if(tag->genre<149)
  {
    wsprintf(ws_info,"%t",LG_Genre);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,30);
    AddEditControlToEditQend(eq,&ec,ma);
  
    wsprintf(ws_info,"%t",ID3v1_genre[tag->genre]);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,128);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  patch_header(&info_hdr);
  patch_input(&info_desc);
  CreateInputTextDialog(&info_desc,&info_hdr,eq,1,0);
}
