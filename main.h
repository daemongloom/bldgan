unsigned int MAINCSM_ID = 0;

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

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM_GUI;

