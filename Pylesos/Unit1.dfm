object Form1: TForm1
  Left = 191
  Top = 113
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1055#1099#1083#1077#1089#1086#1089#1080#1082
  ClientHeight = 506
  ClientWidth = 827
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 24
    Top = 112
    Width = 41
    Height = 41
    Color = clMedGray
    TabOrder = 0
    object FieldBox: TImage
      Left = 1
      Top = 1
      Width = 39
      Height = 39
      Align = alClient
      Stretch = True
      OnMouseDown = FieldBoxMouseDown
      OnMouseMove = FieldBoxMouseMove
    end
  end
  object GroupBox1: TGroupBox
    Left = 424
    Top = 0
    Width = 403
    Height = 487
    Align = alRight
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
    Enabled = False
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 8
      Top = 16
      Width = 65
      Height = 25
      Caption = #1042#1087#1077#1088#1077#1076
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 80
      Top = 16
      Width = 73
      Height = 25
      Caption = #1055#1099#1083#1077#1089#1086#1089#1080#1090#1100
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 161
      Top = 17
      Width = 81
      Height = 25
      Caption = #1055#1099#1083#1077#1089#1086#1089#1080#1090#1100'+'
      OnClick = SpeedButton3Click
    end
    object SpeedButton4: TSpeedButton
      Left = 248
      Top = 16
      Width = 73
      Height = 25
      Caption = #1042#1083#1077#1074#1086
      OnClick = SpeedButton4Click
    end
    object SpeedButton5: TSpeedButton
      Left = 8
      Top = 48
      Width = 65
      Height = 25
      Caption = #1045#1089#1083#1080
      OnClick = SpeedButton5Click
    end
    object SpeedButton6: TSpeedButton
      Left = 80
      Top = 48
      Width = 73
      Height = 25
      Caption = #1055#1086#1082#1072
      OnClick = SpeedButton6Click
    end
    object SpeedButton7: TSpeedButton
      Left = 160
      Top = 48
      Width = 81
      Height = 25
      Caption = #1055#1086#1074#1090#1086#1088#1080
      OnClick = SpeedButton7Click
    end
    object SpeedButton8: TSpeedButton
      Left = 7
      Top = 80
      Width = 66
      Height = 25
      Cursor = crHandPoint
      Caption = #1047#1072#1087#1091#1089#1082
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333333333333333333EEEEEEEEEEEEEEE333FFFFFFFFFFFFF3E00000000000
        00E337777777777777F3E0F77777777770E337F33333333337F3E0F333333333
        70E337F3333F333337F3E0F33303333370E337F3337FF33337F3E0F333003333
        70E337F33377FF3337F3E0F33300033370E337F333777FF337F3E0F333000033
        70E337F33377773337F3E0F33300033370E337F33377733337F3E0F333003333
        70E337F33377333337F3E0F33303333370E337F33373333337F3E0F333333333
        70E337F33333333337F3E0FFFFFFFFFFF0E337FFFFFFFFFFF7F3E00000000000
        00E33777777777777733EEEEEEEEEEEEEEE33333333333333333}
      NumGlyphs = 2
      OnClick = SpeedButton8Click
    end
    object SpeedButton9: TSpeedButton
      Left = 248
      Top = 48
      Width = 73
      Height = 25
      Caption = #1042#1087#1088#1072#1074#1086
      OnClick = SpeedButton9Click
    end
    object SpeedButton10: TSpeedButton
      Left = 160
      Top = 80
      Width = 81
      Height = 25
      Caption = #1057#1073#1088#1086#1089
      OnClick = SpeedButton10Click
    end
    object Label1: TLabel
      Left = 328
      Top = 8
      Width = 73
      Height = 25
      Alignment = taCenter
      AutoSize = False
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103
      WordWrap = True
    end
    object SpeedButton11: TSpeedButton
      Left = 80
      Top = 80
      Width = 73
      Height = 25
      Caption = #1064#1072#1075
      OnClick = SpeedButton11Click
    end
    object ListBox1: TListBox
      Left = 2
      Top = 120
      Width = 399
      Height = 365
      Align = alBottom
      ExtendedSelect = False
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
      OnKeyDown = ListBox1KeyDown
    end
    object Edit1: TEdit
      Left = 160
      Top = 72
      Width = 81
      Height = 21
      Color = clYellow
      TabOrder = 1
      Text = '0'
      Visible = False
      OnExit = Edit1Exit
      OnKeyPress = Edit1KeyPress
      OnKeyUp = Edit1KeyUp
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 0
    Width = 409
    Height = 73
    Align = alCustom
    Caption = #1069#1083#1077#1084#1077#1085#1090#1099
    TabOrder = 2
    object InsertPyls: TSpeedButton
      Left = 8
      Top = 24
      Width = 65
      Height = 31
      AllowAllUp = True
      Caption = #1055#1099#1083#1077#1089#1086#1089
      Transparent = False
      OnClick = InsertPylsClick
    end
    object InsertStol: TColorButton
      Left = 88
      Top = 24
      Width = 65
      Height = 31
      Caption = #1057#1090#1086#1083
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = InsertStolClick
      ButtonColor = clBlue
    end
    object InsertDivan: TColorButton
      Left = 168
      Top = 24
      Width = 65
      Height = 31
      Caption = #1044#1080#1074#1072#1085
      TabOrder = 1
      OnClick = InsertDivanClick
      ButtonColor = clAqua
    end
    object InsertStul: TColorButton
      Left = 248
      Top = 24
      Width = 65
      Height = 31
      Caption = #1057#1090#1091#1083
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clDefault
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = InsertStulClick
      ButtonColor = clLime
    end
    object InsertShkaf: TColorButton
      Left = 328
      Top = 24
      Width = 65
      Height = 31
      Caption = #1064#1082#1072#1092
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = InsertShkafClick
      ButtonColor = clTeal
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 336
    Width = 313
    Height = 81
    Caption = #1056#1072#1079#1084#1077#1088#1099' '#1087#1086#1083#1103
    TabOrder = 3
    Visible = False
    object Label2: TLabel
      Left = 160
      Top = 21
      Width = 51
      Height = 16
      Caption = #1042#1099#1089#1086#1090#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 8
      Top = 21
      Width = 54
      Height = 16
      Caption = #1064#1080#1088#1080#1085#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Button1: TButton
      Left = 8
      Top = 48
      Width = 113
      Height = 25
      Caption = #1055#1077#1088#1077#1088#1080#1089#1086#1074#1072#1090#1100' '#1087#1086#1083#1077
      TabOrder = 0
      OnClick = Button1Click
    end
    object FieldH: TEdit
      Left = 224
      Top = 16
      Width = 57
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = '20'
    end
    object FieldW: TEdit
      Left = 72
      Top = 16
      Width = 57
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Text = '20'
    end
    object UpDown1: TUpDown
      Left = 129
      Top = 16
      Width = 16
      Height = 24
      Associate = FieldW
      Min = 5
      Max = 20
      Position = 20
      TabOrder = 3
    end
    object UpDown2: TUpDown
      Left = 281
      Top = 16
      Width = 16
      Height = 24
      Associate = FieldH
      Min = 5
      Max = 20
      Position = 20
      TabOrder = 4
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 487
    Width = 827
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 50
      end
      item
        Text = #1055#1088#1086#1094#1077#1089#1089':'
        Width = 60
      end
      item
        Width = 0
      end>
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 429
    Width = 150
    Height = 17
    TabOrder = 5
  end
  object TrackBar1: TTrackBar
    Left = 776
    Top = 34
    Width = 33
    Height = 80
    Hint = #1057#1082#1086#1088#1086#1089#1090#1100' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099'. '#1063#1077#1084' '#1074#1099#1096#1077' '#1087#1086#1083#1079#1091#1085#1086#1082' - '#1090#1077#1084' '#1073#1099#1089#1090#1088#1077#1077
    Max = 100
    Min = 10
    Orientation = trVertical
    ParentShowHint = False
    Frequency = 20
    Position = 55
    ShowHint = True
    TabOrder = 6
  end
  object MainMenu1: TMainMenu
    Left = 64
    Top = 272
    object N30: TMenuItem
      Caption = #1055#1088#1086#1077#1082#1090
      object N32: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N32Click
      end
      object N31: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
        OnClick = N31Click
      end
      object N33: TMenuItem
        Caption = '-'
      end
      object N5: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N5Click
      end
    end
    object N1: TMenuItem
      Caption = #1055#1086#1083#1077
      object N2: TMenuItem
        Caption = #1053#1086#1074#1086#1077
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
        OnClick = N4Click
      end
    end
    object N8: TMenuItem
      Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
      object N9: TMenuItem
        Caption = #1053#1086#1074#1072#1103
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N10Click
      end
      object N11: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
        OnClick = N11Click
      end
      object N12: TMenuItem
        Caption = '-'
      end
      object N13: TMenuItem
        Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
        Enabled = False
      end
    end
    object N28: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object N29: TMenuItem
        Caption = #1057#1087#1088#1072#1074#1082#1072
        OnClick = N29Click
      end
      object N6: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = N6Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.pf'
    Filter = #1055#1086#1083#1103' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pf)|*.pf'
    Left = 96
    Top = 272
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.pf'
    Filter = #1055#1086#1083#1103' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pf)|*.pf'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 128
    Top = 272
  end
  object XPManifest1: TXPManifest
    Left = 160
    Top = 272
  end
  object ConditionsPopup: TPopupMenu
    MenuAnimation = [maTopToBottom]
    Left = 192
    Top = 272
    object N14: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1089#1090#1091#1083
    end
    object N15: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1089#1090#1086#1083
    end
    object N16: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1096#1082#1072#1092
    end
    object N17: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1076#1080#1074#1072#1085
    end
    object N18: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1085#1077' '#1089#1090#1091#1083
    end
    object N19: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1085#1077' '#1089#1090#1086#1083
    end
    object N20: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1085#1077' '#1096#1082#1072#1092
    end
    object N21: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1085#1077' '#1076#1080#1074#1072#1085
    end
    object N26: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1082#1088#1072#1081
    end
    object N27: TMenuItem
      Caption = #1074#1087#1077#1088#1077#1076#1080' '#1085#1077' '#1082#1088#1072#1081
    end
    object N22: TMenuItem
      Caption = #1095#1080#1089#1090#1086
    end
    object N23: TMenuItem
      Caption = #1095#1080#1089#1090#1086'+'
    end
    object N24: TMenuItem
      Caption = #1075#1088#1103#1079#1085#1086
    end
    object N25: TMenuItem
      Caption = #1075#1088#1103#1079#1085#1086'+'
    end
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = '*.pp'
    Filter = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pp)|*.pp'
    Left = 96
    Top = 304
  end
  object OpenDialog2: TOpenDialog
    DefaultExt = '*.pp'
    Filter = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pp)|*.pp'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 128
    Top = 304
  end
  object SaveDialog3: TSaveDialog
    DefaultExt = '*.prj'
    Filter = #1055#1088#1086#1077#1082#1090#1099' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.prj)|*.prj'
    Left = 96
    Top = 240
  end
  object OpenDialog3: TOpenDialog
    DefaultExt = '*.prj'
    Filter = #1055#1088#1086#1077#1082#1090#1099' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.prj)|*.prj'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 128
    Top = 240
  end
end
