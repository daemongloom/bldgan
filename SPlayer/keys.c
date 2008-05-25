#include "../inc/swilib.h"
#include "main.h"
#include "mainmenu.h"
#include "playlist.h"

/*
  Будующий конфиг клавиш. Blind007
  Респект авторам MC :)
  То что в комментариях, не удаляйте, может пригодиться!
 */

extern const unsigned int LOAD_KEYS; // Грузить ли из файла
extern const char KEYCFG_PATH[];      // Откуда грузятся настройки

typedef void (*KEY_PROC) ();

/*
typedef struct {
  void (*ondown) ();
  void (*onup) ();
} KEY_PROC;
*/

typedef struct {
  int key;
  char* name;
} KEY_MAP;

const KEY_MAP keynames[] = {
 {LEFT_SOFT, "lsoft"},
 {RIGHT_SOFT, "rsoft"},
 {GREEN_BUTTON, "green"},
 {RED_BUTTON, "red"},
 {ENTER_BUTTON, "enter"},
 {UP_BUTTON, "up"},
 {DOWN_BUTTON, "down"},
 {LEFT_BUTTON, "left"},
 {RIGHT_BUTTON, "right"},
 {VOL_UP_BUTTON, "volup"},
 {VOL_DOWN_BUTTON, "voldown"},
 {'0', "0"},
 {'1', "1"},
 {'2', "2"},
 {'3', "3"},
 {'4', "4"},
 {'5', "5"},
 {'6', "6"},
 {'7', "7"},
 {'8', "8"},
 {'9', "9"},
 {'*', "*"},
 {'#', "#"}
};

/*
KEY_PROC procmap[] = {
  {MM_Show, NULL},
  {DoExit, NULL},
  {LoadDefPlaylist, NULL},
  {DoExit, NULL},
  {PlayTrackUnderC, NULL},
  {CTUp, NULL},
  {CTDown, NULL},
  {PrevPL, NULL},
  {NextPL, NULL},
  {VolumeUp, NULL},
  {VolumeDown, NULL},
  {StopAllPlayback, NULL},
  {NULL, NULL},
  {CTUpSix, NULL},
  {NULL, NULL},
  {PrevTrackDown, NULL},
  {TogglePlayback, NULL},
  {NextTrackDown, NULL},
  {NULL, NULL},
  {CTDownSix, NULL},
  {FindingMusic, NULL},
  {NULL, NULL},
  {NULL, NULL},
};
*/
KEY_PROC procmap[] = {
  MM_Show,
  DoExit,
  LoadDefPlaylist,
  DoExit,
  PlayTrackUnderC,
  CTUp,
  CTDown,
  PrevPL,
  NextPL,
  VolumeUp,
  VolumeDown,
  StopAllPlayback,
  NULL,
  CTUpSix,
  NULL,
  PrevTrackDown,
  TogglePlayback,
  NextTrackDown,
  NULL,
  CTDownSix,
  ToggleVolume,
  SwitchPlayModeDown
};

// Вот не могу понять как эта конструкция работает!
#define KEYS_COUNT (sizeof(procmap)/sizeof(procmap[0]))

void DoKey(int key, int ka)
{
  for(int cc=0;cc<KEYS_COUNT+1;cc++)
   if(keynames[cc].key==key)
   {
     /*
     switch (ka) {
      case (1):
        if(procmap[cc].ondown)procmap[cc].ondown();
        break;
      case (2):
        if(procmap[cc].onup)procmap[cc].onup();
        break;
     }
     */
     if(procmap[cc])procmap[cc]();
     return;
   }
}

typedef struct {
  char* name;
  KEY_PROC proc;
} PROC_MAP;

const PROC_MAP keyprocs[] = {
  {"none", NULL},
  {"mainmenu", MM_Show},
  {"exit", DoExit},
  {"loaddefpl", LoadDefPlaylist},
  {"playtrack", PlayTrackUnderC},
  {"goup", CTUp},
  {"godown", CTDown},
  {"go6up", CTUpSix},
  {"go6down", CTDownSix},
  {"nextpl", NextPL},
  {"prevpl", PrevPL},
  {"volup", VolumeUp},
  {"voldown", VolumeDown},
  {"togglevolume", ToggleVolume},
  {"togglepb", TogglePlayback},
  {"stopall", StopAllPlayback},
  {"nexttrack", NextTrackDown},
  {"prevtrack", PrevTrackDown},
  {"switchmode", SwitchPlayModeDown}
};

void KeysProc(char *name, char *value)
{
  strtolower(name, name, -1);
  strtolower(value, value, -1);

  int inkey=-1;
  KEY_PROC keyproc = DoErrKey;
  
  for(int cc=0;cc<KEYS_COUNT+1;cc++)
   if(strcmp(keynames[cc].name,name)==0)
   {
     inkey=cc;
     break;
   }
  if(inkey==-1) return;

  for(int cc=0;cc<sizeof(keyprocs)/sizeof(keyprocs[0]);cc++)
   if(strcmp(keyprocs[cc].name,value)==0)
   {
     keyproc=keyprocs[cc].proc;
     break;
   }
  
  procmap[inkey] = keyproc;    
}

void LoadKeys()
{
  if(LOAD_KEYS)
  EnumIni(1,(char*)&KEYCFG_PATH,KeysProc);
}
