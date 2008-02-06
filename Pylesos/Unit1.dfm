object Form1: TForm1
  Left = 192
  Top = 122
  Width = 870
  Height = 500
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
  object Label1: TLabel
    Left = 128
    Top = 8
    Width = 77
    Height = 13
    Caption = #1056#1072#1079#1084#1077#1088#1099' '#1087#1086#1083#1103':'
  end
  object Panel1: TPanel
    Left = 8
    Top = 56
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
    end
  end
  object GroupBox1: TGroupBox
    Left = 456
    Top = 0
    Width = 398
    Height = 425
    Align = alRight
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072
    TabOrder = 1
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 112
    Width = 385
    Height = 65
    Align = alCustom
    Caption = #1069#1083#1077#1084#1077#1085#1090#1099
    TabOrder = 2
    object InsertPyls: TSpeedButton
      Left = 8
      Top = 24
      Width = 31
      Height = 31
      Transparent = False
      OnClick = InsertPylsClick
    end
    object InsertStul: TSpeedButton
      Left = 48
      Top = 24
      Width = 31
      Height = 31
      Transparent = False
      OnClick = InsertStulClick
    end
    object InsertStol: TSpeedButton
      Left = 88
      Top = 24
      Width = 56
      Height = 31
      Margin = 0
      Transparent = False
      OnClick = InsertStolClick
    end
    object InsertShkaf: TSpeedButton
      Left = 152
      Top = 24
      Width = 56
      Height = 31
      Margin = 0
      Transparent = False
      OnClick = InsertShkafClick
    end
    object InsertDivan: TSpeedButton
      Left = 216
      Top = 24
      Width = 56
      Height = 31
      Margin = 0
      OnClick = InsertDivanClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 0
    Width = 441
    Height = 49
    Caption = #1056#1072#1079#1084#1077#1088#1099' '#1087#1086#1083#1103
    TabOrder = 3
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
    Top = 425
    Width = 854
    Height = 19
    Panels = <>
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 56
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
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.pf'
    Filter = #1055#1086#1083#1103' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pf)|*.pf'
    Left = 88
    Top = 56
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.pf'
    Filter = #1055#1086#1083#1103' '#1055#1099#1083#1077#1089#1086#1089#1080#1082#1072' (*.pf)|*.pf'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 120
    Top = 56
  end
end
