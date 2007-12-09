#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Default playlist",3,127};
__root const char DEFAULT_PLAYLIST[128] = "0:\\Sounds\\Playlist.m3u";

__root const CFG_HDR cfghdr01={CFG_STR_UTF8,"Music folder",3,127};
__root const char MUSIC[128] = DEFAULT_DISK ":\\Music\\";

__root const CFG_HDR cfghdr02={CFG_COORDINATES,"Idle coordinates",0,0};
__root const unsigned int IDLE_X = 5;
__root const unsigned int IDLE_Y = 50;

//Level 1
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Sets",1,0};

__root const CFG_HDR cfghdr12={CFG_CBOX,"Show full names",0,2};
__root const int SHOW_FULLNAMES = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr13={CFG_CBOX,"Show effects",0,2};
__root const unsigned int GrafOn = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr14={CFG_CBOX,"Playmode",0,4};  // Временно убрал варинг Blind007
__root const int PlayMode = 0;
__root const CFG_CBOX_ITEM cfgcbox3[4]={"Play all","Repeat all","Random","Repeat one"};

__root const CFG_HDR cfghdr15={CFG_CBOX,"Extension of playlist",0,2};
__root const int EXT = 0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"spl","m3u"};

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr16={CFG_INT,"Default volume",0,5};
__root const int soundvolume=2;
#else
__root const CFG_HDR cfghdr16={CFG_INT,"Default volume",0,14};
__root const int soundvolume=6;
#endif
/*
__root const CFG_HDR cfghdr17 = {CFG_INT,"Amount of playlists",0,100};
__root const unsigned int TCPL = 5;
*/
__root const CFG_HDR cfghdr17 = {CFG_INT,"Amount of lines",0,2000};
__root const unsigned int LinesInPL = 256;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//Level 2
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Paths",1,0};

__root const CFG_HDR cfghdr22={CFG_STR_UTF8,"Picture folder",3,127};
__root const char PIC_DIR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Playlist folder",3,127};
__root const char PLAYLISTS[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Playlists\\";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};
/*
// Level 3
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Skin",1,0};

__root const CFG_HDR cfghdr32={CFG_STR_UTF8,"Progressbar",3,127};
__root const char I_PROGRESSBAR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\progressbar.png";

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};*/
