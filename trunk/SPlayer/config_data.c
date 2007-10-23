#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Default playlist",3,127};
__root const char DEFAULT_PLAYLIST[128] = DEFAULT_DISK ":\\Music\\Playlist.m3u";
#else
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Default playlist",3,127};
__root const char DEFAULT_PLAYLIST[128] = DEFAULT_DISK ":\\Sounds\\Playlist.m3u";
#endif

__root const CFG_HDR cfghdr01={CFG_COORDINATES,"Idle coordinates",0,0};
__root const unsigned int IDLE_X = 5;
__root const unsigned int IDLE_Y = 50;

__root const CFG_HDR cfghdr02={CFG_CBOX,"Show full names",0,2};
__root const int SHOW_FULLNAMES = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr03={CFG_CBOX,"Playmode",0,4};  // Временно убрал варинг Blind007
__root const int PlayMode = 0;
__root const CFG_CBOX_ITEM cfgcbox2[4]={"Play all","Repeat all","Random","Repeat one"};

__root const CFG_HDR cfghdr04={CFG_CBOX,"Extension of playlist",0,2};
__root const int EXT = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"spl","m3u"};

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr05={CFG_INT,"Default volume",0,5};
__root const int soundvolume=2;
#else
__root const CFG_HDR cfghdr05={CFG_INT,"Default volume",0,14};
__root const int soundvolume=6;
#endif

//Level 1
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Paths",1,0};

__root const CFG_HDR cfghdr12={CFG_STR_UTF8,"Picture folder",3,127};
__root const char PIC_DIR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\";

__root const CFG_HDR cfghdr13={CFG_STR_UTF8,"Playlist folder",3,127};
__root const char PLAYLISTS[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Playlists\\";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

// Level 2
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Skin",1,0};

__root const CFG_HDR cfghdr22={CFG_STR_UTF8,"Backgroung",3,127};
__root const char I_BACKGROUND[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\background.png";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Progressbar",3,127};
__root const char I_PROGRESSBAR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\progressbar.png";
/*
__root const CFG_HDR cfghdr24={CFG_STR_UTF8,"Coordinates",3,127};
__root const char COORD[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Skin\\skin.cfg";

__root const CFG_HDR cfghdr25={CFG_STR_UTF8,"Colours",3,127};
__root const char COLOR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Skin\\colour.cfg";
*/
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};


