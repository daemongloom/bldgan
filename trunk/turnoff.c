#include "c:\arm\inc\swilib.h"
#include "main.h"


//extern void kill_data(void *p, void (*func_p)(void *));

//const int minus11=-11;
//int MAINCSM_ID=0;




extern const unsigned int CLOSE_BTN;
int MODE_KBD=0;
int MODE=1;

extern const int WHAT_DO;
extern const unsigned int PROFILE;

int CALL_BTN=RED_BUTTON;

//int mode;
//  0 - ждущий режим
//  1 - выключение
//  2 - перезагрузка




void method0()
{
 /* DrawRoundedFrame(0,0, ScreenW()-1, ScreenH()-1, 0, 0, 0,
			GetPaletteAdrByColorIndex(23),
			GetPaletteAdrByColorIndex(23));
  */
   /*int x, y;
   
   switch(mode)
    {
    case 0:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SR)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SR)/2;
        DrawImg(x, y, (int)ICONS_SR);
      }
      break;
    case 1:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SD)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SD)/2;
        DrawImg(x, y, (int)ICONS_SD);
      }
      break;
    case 2:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_RB)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_RB)/2;
        DrawImg(x, y, (int)ICONS_RB);
      }
      break;
    }  */
}


/*void DoIt(void)
{
  switch(mode)
    {
      case 0:
        if (WHAT_DO) KbdLock();
          else
            SetProfile(PROFILE-1);
      break;
      case 1:
        SwitchPhoneOff();
      break;
      case 2:
        RebootPhone();
      break;
     }
 
}*/



GBSTMR mytmr;

/*int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
  
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
    case UP_BUTTON: 
      {
        mode++;
        if (mode==3) mode=0;
      }
      break;
    case LEFT_BUTTON:
    case DOWN_BUTTON:
        mode--;
        if (mode==-1) mode=2;
      break;
     case ENTER_BUTTON:
       switch(mode)
        {
          case 0:DoIt(); break;
          case 1:DoIt(); break;
          case 2:DoIt(); break;
        }
      break;     
    }
  }

  return(0);
}*/






int maincsm_onmessage_GUI(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  
  /*if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      if ((msg->submess>>16)==PLAY_ID) 
      { 
        if (((msg->submess&0xFFFF)==7)||((msg->submess&0xFFFF)==5)) DoIt();
      }
        else
          PLAY_ID=0;
    }*/  
  
  return(1);
}






 

/*int my_keyhook(int key, int m)
{
  extern const int MODE_KBD;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==MODE_KBD+0x193))
     if (key==CALL_BTN) 
       {
         mode=MODE;
        // Check();
       }
  
  return 0;
}*/



/*static void Killer(void)
{
  extern void *ELF_BEGIN;
  if (MAINCSM_ID) CloseCSM(MAINCSM_ID);
  RemoveKeybMsgHook((void *)my_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
*/





void OpenTurnOff()
{
  method0();
  //LockSched();
  //InitConfig();  
  //AddKeybMsgHook((void *)my_keyhook);
 // UnlockSched();
 // return 0;
}
