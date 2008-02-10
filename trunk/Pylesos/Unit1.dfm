object Form1: TForm1
  Left = 192
  Top = 123
  Width = 895
  Height = 527
  Caption = #1055#1099#1083#1077#1089#1086#1089#1080#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 24
    Top = 152
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
      OnMouseDown = FieldBoxMouseDown
      OnMouseMove = FieldBoxMouseMove
    end
  end
  object GroupBox1: TGroupBox
    Left = 481
    Top = 0
    Width = 398
    Height = 452
    Align = alRight
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
    TabOrder = 1
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 8
    Width = 241
    Height = 113
    Align = alCustom
    Caption = #1069#1083#1077#1084#1077#1085#1090#1099
    TabOrder = 2
    object InsertPyls: TSpeedButton
      Left = 8
      Top = 24
      Width = 65
      Height = 31
      Caption = #1055#1099#1083#1077#1089#1086#1089
      Transparent = False
      OnClick = InsertPylsClick
    end
    object InsertStul: TSpeedButton
      Left = 8
      Top = 64
      Width = 65
      Height = 31
      Caption = #1057#1090#1091#1083
      Transparent = False
      OnClick = InsertStulClick
    end
    object InsertStol: TSpeedButton
      Left = 88
      Top = 24
      Width = 65
      Height = 31
      Caption = #1057#1090#1086#1083
      Transparent = False
      OnClick = InsertStolClick
    end
    object InsertShkaf: TSpeedButton
      Left = 88
      Top = 64
      Width = 65
      Height = 31
      Caption = #1064#1082#1072#1092
      Transparent = False
      OnClick = InsertShkafClick
    end
    object InsertDivan: TSpeedButton
      Left = 168
      Top = 24
      Width = 65
      Height = 31
      Caption = #1044#1080#1074#1072#1085
      Layout = blGlyphTop
      NumGlyphs = 2
      OnClick = InsertDivanClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 368
    Width = 441
    Height = 49
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
      Left = 312
      Top = 16
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
    Top = 452
    Width = 879
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
    Left = 0
    Top = 432
    Width = 150
    Height = 17
    TabOrder = 5
  end
  object MainMenu1: TMainMenu
    Left = 64
    Top = 272
    object N1: TMenuItem
      Caption = #1055#1086#1083#1077
      object N2: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100
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
      object N7: TMenuItem
        Caption = '-'
      end
      object N5: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N5Click
      end
    end
    object N8: TMenuItem
      Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
      Enabled = False
      object N9: TMenuItem
        Caption = #1053#1086#1074#1072#1103
      end
      object N10: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      end
      object N11: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
      end
    end
    object N6: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = N6Click
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
end
