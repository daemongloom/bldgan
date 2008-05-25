
void lgpInitLangPack ();
void lgpFreeLangPack ();

enum LGP_ID
{
  ///////////MainMenu///////////
  LGP_Menu=0,
  LGP_SetNextPlayed,
  LGP_ShowID3,
  LGP_FM,
  LGP_Settings,
  LGP_AboutDlg,
  LGP_Exit_SPlayer,
  LGP_SELECT,
  LGP_BACK,
  ///////////Menu 1///////////
  LGP_Sets_Menu,
  LGP_SetEditPL,
  LGP_Coordinates,
  LGP_Colours,
  LGP_Refresh,
  ///////////Attributes///////////
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
  ///////////Config///////////
 /* LGP_Default_playlist,
  LGP_Default_playlist_2,
  LGP_Default_playlist_3,
  LGP_Music_folder,
  LGP_Idle_coordinates,
  LGP_Auto_Exit_Min,
  LGP_Speed_Moving,
  LGP_Show_Anim,
  LGP_Sets,
  LGP_Show_full_names,
  LGP_Key_Settings,
  LGP_LoadKeys,
  LGP_KeySet_Path,

  LGP_No,
  LGP_Yes,

  LGP_Show_effects,
  LGP_Show_info,
  LGP_Playmode,
  LGP_Play_all,
  LGP_Repeat_all,
  LGP_Random,
  LGP_Repeat_one,
  LGP_Extension_of_playlist,
  LGP_spl,
  LGP_m3u,
  LGP_Default_volume,
  LGP_Amount_of_lines,
  LGP_Size_Of_Font,
  LGP_Send_fname,
  LGP_Paths,
  LGP_Picture_folder,
  LGP_Playlist_folder,
  LGP_Path_To_SCE,
  LGP_Path_To_Lang,*/
  ///////////ShowMSG/MsgBoxError///////////
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
  LGP_Spkeys_er,
  LGP_PNG_er,
  LGP_LangCode,
  LGP_DATA_NUM
};

extern char *lgpData[LGP_DATA_NUM];
