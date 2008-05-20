
void lgpInitLangPack ();
void lgpFreeLangPack ();

enum LGP_ID
{
  LGP_Menu=0,              
  LGP_SetNextPlayed, 
  LGP_ShowID3, 
  LGP_FM,
  LGP_Settings, 
  LGP_AboutDlg, 
  LGP_Exit_SPlayer,
  LGP_SELECT,
  LGP_BACK, 
  LGP_Sets_Menu,
  LGP_SetEditPL,
  LGP_Coordinates,
  LGP_Colours,
  LGP_Refresh,
  LGP_ID3_Tag_Info,
  LGP_Full_name,
  LGP_Size,
  LGP_Title,
  LGP_Artist,
  LGP_Album,
  LGP_Year,
  LGP_Comment,
  LGP_Number,
  LGP_Genre,
  LGP_Can_not_find_file,
  LGP_Load_a_playlist,
  LGP_Keypad_Unlock,
  LGP_Keypad_Lock,
  LGP_Config_Updated,
  LGP_PL_Saved,
  LGP_Exit,
  LGP_Is_not_selected,
  LGP_No_Tags,
  LGP_Already_Started,
  LGP_Error_1,
  LGP_Error_2,
  LGP_LangCode,
  LGP_DATA_NUM
};

extern char *lgpData[LGP_DATA_NUM];
