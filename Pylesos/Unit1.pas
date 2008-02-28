{===============================================}
{= �������� ��������������� �����������        =}
{= ����������� ����������� "���������"         =}
{=  ������� ������ ���������                   =}
{= ������: ������� ��������                    =}
{=         ������� ���������                   =}
{= ����: 2008.02.26                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons, XPMan, AboutUnit,
  ToolWin, NewPrgUnit, ShellAPI, ColorButton, Spin;

type
  TForm1 = class(TForm)
    Button1: TButton;
    FieldBox: TImage;
    FieldW: TEdit;
    UpDown1: TUpDown;
    FieldH: TEdit;
    UpDown2: TUpDown;
    Panel1: TPanel;
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    InsertPyls: TSpeedButton;
    GroupBox3: TGroupBox;
    Label2: TLabel;
    Label3: TLabel;
    StatusBar1: TStatusBar;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    N5: TMenuItem;
    XPManifest1: TXPManifest;
    N6: TMenuItem;
    ProgressBar1: TProgressBar;
    N8: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    ListBox1: TListBox; 
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    N12: TMenuItem;
    N13: TMenuItem;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    SpeedButton6: TSpeedButton;
    SpeedButton7: TSpeedButton;
    ConditionsPopup: TPopupMenu;
    N14: TMenuItem;
    N15: TMenuItem;
    N16: TMenuItem;
    N17: TMenuItem;
    N18: TMenuItem;
    N19: TMenuItem;
    N20: TMenuItem;
    N21: TMenuItem;
    N22: TMenuItem;
    N23: TMenuItem;
    N24: TMenuItem;
    N25: TMenuItem;
    SpeedButton8: TSpeedButton;
    SpeedButton9: TSpeedButton;
    TrackBar1: TTrackBar;
    SaveDialog2: TSaveDialog;
    OpenDialog2: TOpenDialog;
    N26: TMenuItem;
    N27: TMenuItem;
    N28: TMenuItem;
    N29: TMenuItem;
    SpeedButton10: TSpeedButton;
    InsertStol: TColorButton;
    InsertDivan: TColorButton;
    InsertStul: TColorButton;
    InsertShkaf: TColorButton;
    Label1: TLabel;
    SpeedButton11: TSpeedButton;
    N30: TMenuItem;
    N32: TMenuItem;
    N33: TMenuItem;
    N31: TMenuItem;
    SaveDialog3: TSaveDialog;
    OpenDialog3: TOpenDialog;
    Edit1: TSpinEdit;
    CodePopupMenu1: TPopupMenu;
    N7: TMenuItem;
    N34: TMenuItem;
    BackupListBox: TListBox;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Rotating(x,y: integer);
    procedure Inserting(x,y: integer);
    procedure Deleting(x,y: integer);
    procedure FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure InsertPylsClick(Sender: TObject);
    procedure InsertStulClick(Sender: TObject);
    procedure InsertStolClick(Sender: TObject);
    procedure InsertShkafClick(Sender: TObject);
    procedure InsertDivanClick(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure N6Click(Sender: TObject);
    procedure FieldBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure N9Click(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure CPClick1(Sender: TObject);
    procedure SpeedButton5Click(Sender: TObject);
    procedure CPClick2(Sender: TObject);
    procedure SpeedButton6Click(Sender: TObject);
    procedure SpeedButton7Click(Sender: TObject);
    procedure Edit1KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure SpeedButton8Click(Sender: TObject);
    procedure SpeedButton9Click(Sender: TObject);
    procedure ListBox1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure N10Click(Sender: TObject);
    procedure N11Click(Sender: TObject);
    procedure N29Click(Sender: TObject);
    procedure SpeedButton10Click(Sender: TObject);
    procedure Edit1Exit(Sender: TObject);
    procedure SpeedButton11Click(Sender: TObject);
    procedure N32Click(Sender: TObject);
    procedure N31Click(Sender: TObject);
    procedure N7Click(Sender: TObject);
    procedure N34Click(Sender: TObject);
    procedure CodePopupMenu1Popup(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure DrawField;
    procedure DoComand(str: string; var k: integer);
    procedure MoveForward;
    procedure Rotate(angle: integer);
    procedure Clean(plus: boolean);
    procedure RepeatN(k: integer);
    procedure ElseHandler(var k: integer);
    procedure IFHandler(var k: integer);
    procedure WhileHandler(var k: integer);
    procedure SetButtonsState(state:boolean);
    function GetSpaces(k: integer): string; 
  end;

var
  Form1: TForm1;
  ProgName: string;

implementation

{$R *.dfm}   

function MAX(a,b:integer):integer;
begin
  if a>b then max:=a else max:=b;
end;

procedure SwapValues(var a,b: integer);
begin
   a := a xor b;
   b := a xor b;
   a := a xor b;
end;

const Offset = 6; // ��������� �������� ��� ������ ������
      EMPTY = 0;  // �����
      ePYLS = 1;  // �������
      eSTUL = 2;  // ����
      eSTOL = 3;  // ����
      eDIVAN = 4; // �����
      eSHKAF = 5; // ����
      RUBSH = 6;  // �����
      MaxPylsCount = 1; // ������������ ���������� ��������� �� ����

type TElem = EMPTY..eSHKAF+Offset; // ��� ��������
     // ������� ��������� ������
     TElemSize = record
        w,h : integer;
     end;
     TRotation = 0..3;
     TFieldElem = record
       ElemT: TElem;        // ��� ��������
       Rot: TRotation;      // ������� (��� ��������)
     end;
     TPylsPos = record            // ��������� �������� �� ����
        x,y: integer;
        rot: TRotation;
     end;
     TField = array [1..25,1..25] of TFieldElem;

var asize: integer = 24;              // ������ ������ � ��������
    fsize_h, fsize_w: byte;           // ������ ���� � �������
    field, backup_field: TField;      // ����
    InsMode: boolean;                 // ����������� �� �������
    InsType: TElem;                   // ��� ���������
    InsRotation: TRotation;           // �������
    field_file: file of byte;         // ���� ����
    ffname: string;                   // ��� ����� ���� ��� ���������� ��� ��������
    pylsc: integer;                   // ���������� ��������� �� ����
    pylpos, backup_pylpos: TPylsPos;  // ��������� �������� �� ����
    startpoint, finpoint: TPoint;
    execute: boolean;                 // ����������� �� ���������
    ifstart: boolean;                 // ��� ����������� ������ 

// ������ �������� ����������� ��������� ��� ����������� ���� � ���� 
function ExpressionResult(exp: string): boolean;
var x,y: integer;
    e: TElem;

 // ������� ����?
 function Kray: boolean;
 begin
    Result := (((pylpos.x=1) and (pylpos.rot=3)) or
     ((pylpos.x=fsize_w) and (pylpos.rot=1)) or
     ((pylpos.y=1) and (pylpos.rot=0)) or
     ((pylpos.y=fsize_h) and (pylpos.rot=2)));
 end;

 // ����� �� � x,y?
 function Chisto(x,y: integer): boolean;
 var t: integer;
     e: TElem;
 begin
    e := field[x,y].ElemT;
    t := e-Offset;
    Result := (-Offset<=t) and (t<=eSHKAF) and (t<>EMPTY);
 end;

begin
   x:=pylpos.x;
   y:=pylpos.y;
   Result := false;
   if exp='������� ����' then Result := Kray else
    if exp='������� �� ����' then Result := not Kray else begin
       if (not Kray) then begin
          case pylpos.rot of
             0: Dec(y);
             1: Inc(x);
             2: Inc(y);
             3: Dec(x);
          end;
          e := field[x,y].ElemT;
          // �������� �����
          e := (e+Offset) mod Offset;   
          // ������� ������
          if ((exp='������� ����') and (e=eSTUL)) or
           ((exp='������� ����') and (e=eSTOL)) or
           ((exp='������� �����') and (e=eDIVAN)) or
           ((exp='������� ����') and (e=eSHKAF)) then
             Result := true else
          // ������� �� ������
          if ((exp='������� �� ����') and (e<>eSTUL)) or
           ((exp='������� �� ����') and (e<>eSTOL)) or
           ((exp='������� �� �����') and (e<>eDIVAN)) or
           ((exp='������� �� ����') and (e<>eSHKAF)) then
             Result := true else
          if (exp='�����') then Result := Chisto(x,y) else
           if exp='������' then Result := not Chisto(x,y) else begin
              case pylpos.rot of
                 0: Dec(y);
                 1: Inc(x);
                 2: Inc(y);
                 3: Dec(x);
              end;
              if (x in [1..fsize_w]) and (y in [1..fsize_h]) then begin
               if exp='�����+' then Result := Chisto(x,y) else
                if exp='������+' then Result := not Chisto(x,y);
              end else
                 ShowMessage('������ �������� �� ������� ����!'); 
           end;
       end;
    end;   
end;

procedure TForm1.DrawField;
var i,j: integer;
    p: array [1..3] of TPoint;
begin
   // ������������� �������
   Panel1.Width := fsize_w*asize + 1;
   Form1.autosize:=false;
   Panel1.Height := fsize_h*asize + 1;
   FieldBox.Width := Panel1.Width;
   FieldBox.Height := Panel1.Height;
//   GroupBox1.Left:=max(GroupBox2.Width,Panel1.Width)+6;
   Form1.Autosize:=true;
   // ������� ������� � �������
   Form1.Canvas.Font.Color := clGreen;
   for i:=1 to fsize_w do
      with Form1.Canvas do begin
         TextOut(Panel1.Left + (i-1)*asize + asize div 2,Panel1.Top-15,Chr(Ord('�')+(i-1)));
      end;
   for i:=1 to fsize_h do
      with Form1.Canvas do begin
         TextOut(Panel1.Left - 15,Panel1.Top + (i-1)*asize + asize div 2,IntToStr(i));
      end;
   // �������� ���
   FieldBox.Canvas.Brush.Color := clBlack;
   FieldBox.Canvas.Rectangle(0,0,FieldBox.Width,FieldBox.Height);
   // ������ ����� � ������ ��������
   FieldBox.Canvas.Pen.Color := clWhite;
   FieldBox.Canvas.Brush.Color := clGreen;
   for i:=1 to fsize_w do begin
      for j:=1 to fsize_h do begin
         case field[i,j].ElemT of
           EMPTY: FieldBox.Canvas.Brush.Color := clGreen;
           RUBSH: FieldBox.Canvas.Brush.Color := clGray;
           eSTUL,eSTUL+Offset: FieldBox.Canvas.Brush.Color := clLime;
           eSTOL,eSTOL+Offset: FieldBox.Canvas.Brush.Color := clBlue;
           eDIVAN,eDIVAN+Offset: FieldBox.Canvas.Brush.Color := clAqua;
           eSHKAF,eSHKAF+Offset: FieldBox.Canvas.Brush.Color := clOlive;
         end;
         if (field[i,j].ElemT<>ePYLS) and (field[i,j].ElemT<>ePYLS+Offset)
          then FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize)
         else begin
            if field[i,j].ElemT=ePYLS then FieldBox.Canvas.Brush.Color := clGreen
               else FieldBox.Canvas.Brush.Color := clGray;
            FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize);
            case field[i,j].Rot of
              // ��� ���� ���������� ������������
              0: begin
                 p[1].X := i*asize-3;
                 p[1].Y := j*asize-3;
                 p[2].X := (i-1)*asize+3;
                 p[2].Y := j*asize-3;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := (j-1)*asize+3;
              end;
              1: begin
                 p[1].X := (i-1)*asize+3;
                 p[1].Y := (j-1)*asize+3;
                 p[2].X := i*asize-3;
                 p[2].Y := (j-1)*asize + asize div 2;
                 p[3].X := (i-1)*asize+3;
                 p[3].Y := j*asize-3;
              end;
              2: begin
                 p[1].X := (i-1)*asize+3;
                 p[1].Y := (j-1)*asize+3;
                 p[2].X := i*asize-3;
                 p[2].Y := (j-1)*asize+3;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := j*asize-3;
              end;
              3: begin
                 p[1].X := i*asize-3;
                 p[1].Y := (j-1)*asize+3;
                 p[2].X := i*asize-3;
                 p[2].Y := j*asize-3;
                 p[3].X := (i-1)*asize+3;
                 p[3].Y := (j-1)*asize + asize div 2;
              end;
            end;
            FieldBox.Canvas.Brush.Color := clRed;
            FieldBox.Canvas.Polygon(p);
         end;
      end;
   end;
   FieldBox.Refresh;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
   DrawField;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   // �������������� ������� ����
   fsize_w := 10;
   fsize_h := 10;
   // �������� ProgressBar1 � ������ �����
   ProgressBar1.Parent := StatusBar1;
   ProgressBar1.Top := 1;
   ProgressBar1.Left := StatusBar1.Panels[0].Width+StatusBar1.Panels[1].Width+1;
   ProgressBar1.Height := StatusBar1.Height - 2;
   StatusBar1.Panels[2].Width := StatusBar1.Width - ProgressBar1.Left;
   ProgressBar1.Width := StatusBar1.Panels[2].Width - 2;
   ProgressBar1.Position := 0;
   // �������� ���� �������
   FillChar(field,SizeOf(field),RUBSH);
   pylsc := 0;
   // ����������� � ������� �������
   InsMode := false;
   InsType := EMPTY;
   InsRotation := 1;
   startpoint.X := 0;
   startpoint.Y := 0;
   finpoint.X := 0;
   finpoint.Y := 0;
   // �������� ����
   DrawField;
   // ��������� ��������
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   SaveDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   SaveDialog3.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog3.InitialDir := ExtractFilePath(Application.ExeName);
   // �������� ����� ���������  
   BackupListBox.Clear;
   ListBox1.Clear;
   N7.Enabled:=false;
   ListBox1.Items.Add('��������� �����_���������');
   ListBox1.Items.Add('����� ���������.');
   ListBox1.ItemIndex := 1;
   GroupBox1.Enabled := true;

   // �������� ����
   backup_field := field;
   // ������� ���� ���������� ���������
   execute := false;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
end;

// ��������� ����������� �������
function InsertEnable(f: TField; x,y: integer): boolean;
begin
   Result := false;
   if (x in [1..fsize_w]) and (y in [1..fsize_h]) then
      if (f[x,y].ElemT = EMPTY) or
       (f[x,y].ElemT = RUBSH) then
         Result := true;
end;

function InsertElement(xp,yp: integer;ElemT: TElem;Rot: TRotation): boolean;
var ins_pos: TPoint;
begin
   Result := false;
   // �������� �� ����� �������
   if InsMode then begin
      // ���������� ����������
      ins_pos.X := xp;
      ins_pos.Y := yp;
      // ��������� ������� �� ����, ���� �����
      if (field[xp,yp].ElemT=EMPTY) or (field[xp,yp].ElemT=RUBSH) then begin
         if field[xp,yp].ElemT=RUBSH then field[xp,yp].ElemT := ElemT+Offset
            else field[xp,yp].ElemT := ElemT;
         field[xp,yp].Rot := Rot;
         case ElemT of
            ePYLS: begin
               Inc(pylsc);
               pylpos.x := xp;
               pylpos.y := yp;
               pylpos.rot := InsRotation;
             end;
         end;
      end;
      // ������ ���������
      Result := true;
   end;
end;

procedure TForm1.Rotating(x,y: integer);
begin
   field[x,y].Rot := (field[x,y].Rot+1) mod 4;
   pylpos.rot := field[x,y].Rot;
   DrawField;
end;

// ��������� ������� �� ����
procedure TForm1.Inserting(x,y: integer);
var i,j: integer;
    inserted,freespaceavail: boolean;
begin
   if (InsType=ePYLS) or (InsType=eSTUL) then begin
      // ��������� ������� ��� ����
      if InsertEnable(field,x,y) then begin
         if InsertElement(x,y,InsType,InsRotation) then begin
            // ���������� ����
            DrawField;
            // ����������� ���������� ���������
            if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
            // ������� ����� �������
            InsMode := false;
            InsType := EMPTY;
            InsRotation := 1;
            // �������� ������
            {
            InsertPyls.Down:=false;
            InsertStul.Down:=false;
            InsertStol.Down:=false;
            InsertShkaf.Down:=false;
            InsertDivan.Down:=false;
            }
         end;
      end else
         MessageDlg('�� ����!',mtError,[mbOK],0);
   end else begin
      if InsMode=false then exit;
      // ��������� �� ���� � �� �������
      if (ifstart) then begin
         startpoint.X := x;
         startpoint.Y := y;
         // ������� ������ �����
         FieldBox.Canvas.Brush.Color := clWhite;
         FieldBox.Canvas.Ellipse((x-1)*asize+5,(y-1)*asize+5,x*asize-5,y*asize-5);
         ifstart := false;
      end else begin
         finpoint.X := x;
         finpoint.Y := y;

         if startpoint.X>finpoint.X then SwapValues(startpoint.X,finpoint.X);
         if startpoint.Y>finpoint.Y then SwapValues(startpoint.Y,finpoint.Y);
         inserted := false;
         freespaceavail:=true;
         for i:=startpoint.X to finpoint.X do begin
            for j:=startpoint.Y to finpoint.Y do begin
               if InsertEnable(field,i,j)then{}
               else begin
                  MessageDlg('�� ����!',mtError,[mbOK],0);
                  freespaceavail:=false;
                  inserted:=true; // ��� �� �������������� � ����������
                  break;
               end;
            end;
            if not freespaceavail then break;
         end;
         if freespaceavail then
         for i:=startpoint.X to finpoint.X do
            for j:=startpoint.Y to finpoint.Y do begin
                  inserted := InsertElement(i,j,InsType,InsRotation)
            end;
         if inserted then begin
            // ���������� ����
            DrawField;
            // ������� ����� �������
            InsMode := false;
            InsType := EMPTY;
            InsRotation := 1;
            // �������� ������
            {
            InsertPyls.Down:=false;
            InsertStul.Down:=false;
            InsertStol.Down:=false;
            InsertShkaf.Down:=false;
            InsertDivan.Down:=false;
            }
         end;
      end;

   end;
end;

procedure TForm1.Deleting(x,y: integer);
begin
   // ���� ������� �������
   if (startpoint.X=x) and (startpoint.Y=y) then begin
      ifstart:=true;
      startpoint.X := 0;
      startpoint.Y := 0;
      DrawField;
   end;
   // ���� ������� ������� � ����
   if (field[x,y].ElemT=EMPTY) or (field[x,y].ElemT=RUBSH) then exit else begin
      // �������
      if (field[x,y].ElemT<>ePYLS) and (field[x,y].ElemT<>ePYLS+Offset) then begin
         // ���� ���� ��� �������, ����������
         if MessageDlg('������� ���� �������?',mtConfirmation,[mbYes,mbNo],0)=mrYes then begin
            // ������� �� �������
            if field[x,y].ElemT in [RUBSH..eSHKAF+Offset] then field[x,y].ElemT:=RUBSH else
               field[x,y].ElemT:=EMPTY;
            DrawField;
         end;
      end else begin
         // ������� �������
      end;      
   end;
end;

// ���������� ������ �� ����
procedure TForm1.FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
   x := x div 24 +1;
   y := y div 24 +1;
   case Button of
      mbLeft: if (field[X,Y].ElemT=ePYLS) or (field[X,Y].ElemT=ePYLS+Offset) then Rotating(X,Y)
                 else Inserting(X,Y);
      mbRight: Deleting(X,Y);
   end;
end;

procedure TForm1.InsertPylsClick(Sender: TObject);
begin           
   DrawField;      // ���� ����������...
   InsMode := true;
   InsType := ePYLS;
   ifstart := false;
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertStulClick(Sender: TObject);
begin        
   DrawField;      // ���� ����������...
   InsMode := true;
   InsType := eSTUL;
   ifstart := false;
end;

procedure TForm1.InsertStolClick(Sender: TObject);
begin
   DrawField;      // ���� ����������...
   InsMode := true;
   InsType := eSTOL;
   ifstart := true;
end;

procedure TForm1.InsertShkafClick(Sender: TObject);
begin              
   DrawField;      // ���� ����������...
   InsMode := true;
   InsType := eSHKAF;
   ifstart := true;
end;

procedure TForm1.InsertDivanClick(Sender: TObject);
begin               
   DrawField;      // ���� ����������...
   InsMode := true;
   InsType := eDIVAN;
   ifstart := true;
end;

// �������� ������ ����
procedure TForm1.N2Click(Sender: TObject);
begin
   if MessageDlg('������� ����� ����?'+#10#13+'������� ���� ����� �������!',mtConfirmation,[mbYes,mbNo],0)<>mrYes then exit;
   // �������� ���� �������
   FillChar(field,SizeOf(field),RUBSH);
   pylsc := 0;
   InsertPyls.Enabled := true;
   // ����������� � ������� �������
   InsMode := false;
   InsType := EMPTY;
   InsRotation := 1;
   // �������� ����
   DrawField;
end;

// ���������� ����
procedure TForm1.N3Click(Sender: TObject);
var i,j: integer;
begin
   with SaveDialog1 do begin
      if Execute then begin
         if FileName<>'' then  begin
            ffname := FileName;
            AssignFile(field_file,ffname);
            Rewrite(field_file);
            // ���������� �������
            Write(field_file,fsize_w,fsize_h);
            for i:=1 to fsize_w do
               for j:=1 to fsize_h do begin
                  // ���������� ������������� ��������
                  Write(field_file,field[i,j].ElemT,field[i,j].Rot);
               end;
            CloseFile(field_file);
         end;
      end;
   end;
end;

// ��������� ���� �� �����
procedure TForm1.N4Click(Sender: TObject);
var i,j: integer;
    temp_ElemT, temp_rotation: byte;
begin
   with OpenDialog1 do begin
      if Execute then begin
         if FileName<>'' then  begin
            ffname := FileName;
            AssignFile(field_file,ffname);
            Reset(field_file);
            // ������ �������
            Read(field_file,fsize_w,fsize_h);
            for i:=1 to fsize_w do
               for j:=1 to fsize_h do begin
                  // ������ ������ �� ��������� ����������
                  Read(field_file,temp_ElemT,temp_rotation);
                  // ��������� �� ������������ �����
                  if (temp_ElemT in [EMPTY..eSHKAF+Offset]) then
                     field[i,j].ElemT := TElem(temp_ElemT);
                  if (temp_rotation in [0..3]) then
                     field[i,j].Rot := TRotation(temp_rotation);
               end;
            CloseFile(field_file);
         end;   
      end;
   end;
   DrawField;
end;

procedure TForm1.N5Click(Sender: TObject);
begin
   Application.Terminate;
end;

// � ���������
procedure TForm1.N6Click(Sender: TObject);
begin
   Form2.ShowModal;
end;

procedure TForm1.N7Click(Sender: TObject);
begin
  ListBox1.Items:=BackupListBox.Items;
  ListBox1.ItemIndex:=BackupListBox.ItemIndex;  
  N7.Enabled:=false;
end;

// ����� ������ ����� �� ����
procedure TForm1.FieldBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1);   
end;

procedure TForm1.N9Click(Sender: TObject);
begin
   if MessageDlg('������� ����� ���������?'+#10#13+'��� �������� � �������� ������!',mtConfirmation,[mbYes,mbNo],0)<>mrYes then exit;
   // �������� ����� ���������
   Form3.ShowModal;
   if ProgName='###NewProgramCanceled' then exit;
   ListBox1.Clear;
   ListBox1.Items.Add('��������� '+ProgName);
   ListBox1.Items.Add('����� ���������.');
   ListBox1.ItemIndex := 1;
   GroupBox1.Enabled := true;
end;

// ���� ������ �� ListBox'e
procedure TForm1.ListBox1Click(Sender: TObject);
begin
   if ListBox1.ItemIndex=0 then ListBox1.ItemIndex := 1;
end;

procedure TForm1.ListBox1KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
var i:integer;
    str: string;
begin
   // ������� ��������� �����
   BackupListBox.Items:=ListBox1.Items;
   BackupListBox.ItemIndex:=ListBox1.ItemIndex; 
   N7.Enabled:=true;

   i:=ListBox1.ItemIndex; // �������� ������� �������
   str := ListBox1.Items.Strings[i];
   if Key=46 then begin
      if (ListBox1.ItemIndex in [1..ListBox1.Items.count-2]) then begin
         if (pos('�����',str)>0) or (pos('����� ����',str)>0) or
          (pos('����� �������',str)>0) or (pos('����� ����',str)>0)
         then {nothing} else begin
            ListBox1.Items.Delete(ListBox1.ItemIndex);
            if (pos('����',str)>0) and (pos('�����',str)<=0) then begin
               while pos('����� ����',ListBox1.Items.Strings[i])<=0 do
                  ListBox1.Items.Delete(i);
               ListBox1.Items.Delete(i);
            end;
            if (pos('�������',str)>0) and (pos('�����',str)<=0) then begin
               while pos('����� �������',ListBox1.Items.Strings[i])<=0 do
                  ListBox1.Items.Delete(i);
               ListBox1.Items.Delete(i);   
            end;
            if (pos('����',str)>0) and (pos('�����',str)<=0) then begin
               while pos('����� ����',ListBox1.Items.Strings[i])<=0 do
                  ListBox1.Items.Delete(i);
               ListBox1.Items.Delete(i);   
            end;
            ListBox1.ItemIndex:=i;
         end;
      end;
   end;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'������');
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'����������');
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'����������+');
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'�����');
end;

// ������������ �������� ����
procedure TForm1.CPClick1(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'���� '+(Sender as TMenuItem).Caption+' ��');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'�����');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-3)+'����� ����');
end;

procedure TForm1.SpeedButton5Click(Sender: TObject);
var i: integer;
    MyComp: TComponent;
begin
   ConditionsPopup.Popup(Form1.Left+GroupBox1.Left+SpeedButton5.Left,
     Form1.Top+SpeedButton5.Top+SpeedButton5.Height+5);
   for i:=14 to 27 do begin
      MyComp := FindComponent('N'+IntToStr(i)) as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick1;
   end;
end;

// ������������ ������ ����
procedure TForm1.CPClick2(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'���� '+(Sender as TMenuItem).Caption+' �����');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'����� ����');
end;

procedure TForm1.SpeedButton6Click(Sender: TObject);
var i: integer;
    MyComp: TComponent;
begin
   ConditionsPopup.Popup(Form1.Left+GroupBox1.Left+SpeedButton6.Left,
     Form1.Top+SpeedButton6.Top+SpeedButton6.Height+5);
   for i:=14 to 27 do begin
      MyComp := FindComponent('N'+IntToStr(i)) as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick2;
   end;
end;

// ������������ ��������
procedure TForm1.SpeedButton7Click(Sender: TObject);
begin
   if Edit1.Visible then begin
          if edit1.Value>max(fsize_w,fsize_h) then
            ShowMessage('�� ������ ������� ���������� ����������, ������� ������� ����. �� �������?'+#10#13+#10#13+#10#13+'�� ��� ��� �������?');
          ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'������� '+inttostr(strtoint(Edit1.Text)));
          ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'����� �������');
          Edit1.Visible := false;
          end
    else begin
          Edit1.Visible := true;
          Edit1.Text:='1';
          Edit1.SetFocus;
         end;
end;

procedure TForm1.DoComand(str: string; var k: integer);
begin
   if not execute then exit;
   ListBox1.ItemIndex := k;
   sleep(1000-(110-trackbar1.Position)*10);
   if (pos('������',str)>0) then MoveForward;
   if (pos('������',str)>0) then Rotate(1);
   if (pos('�����',str)>0) then Rotate(-1);
   if (pos('����������+',str)>0) then Clean(true) else
      if (pos('����������',str)>0) then Clean(false);
   if (pos('�����',str)>0) then ElseHandler(k);
   if (pos('����',str)>0) and (pos('�����',str)<=0) then ifHandler(k);
   if (pos('�������',str)>0) and (pos('�����',str)<=0) then RepeatN(k);
   if (pos('����',str)>0) and (pos('�����',str)<=0) then WhileHandler(k);
end;          


procedure TForm1.SetButtonsState(state:boolean);
begin
  // �(�)������� �������
  n1.Enabled:=state;
  n8.Enabled:=state;
  n28.Enabled:=state;
  insertdivan.enabled:=state;
  insertstul.enabled:=state;
  insertstol.enabled:=state;
  insertshkaf.enabled:=state;
  speedbutton1.Enabled:=state;
  speedbutton2.Enabled:=state;
  speedbutton3.Enabled:=state;
  speedbutton4.Enabled:=state;
  speedbutton5.Enabled:=state;
  speedbutton6.Enabled:=state;
  speedbutton7.Enabled:=state;
  speedbutton8.Enabled:=state;
  speedbutton9.Enabled:=state;
  speedbutton11.Enabled:=state;
end;

procedure TForm1.SpeedButton8Click(Sender: TObject);
var k: integer;
begin
  if InsertPyls.Enabled then ShowMessage('� �� ������ �� ������? ������� ��������...')     // ���� ������� �� ��� ��������, �� ������ ������ �� ����
  else begin
  k := 1;
  backup_pylpos := pylpos;
  backup_field := field;
  execute := true;
  SetButtonsState(false);
  while (k<ListBox1.Items.Count) and execute do begin
     DoComand(ListBox1.Items.Strings[k],k);
     Inc(k);
     Application.ProcessMessages;
  end;
  k:=1;
  SetButtonsState(true);
  execute:=false;
  end;
end;

procedure TForm1.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key=13 then SpeedButton7.Click;
end;

procedure TForm1.SpeedButton9Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'������');
end;

procedure TForm1.MoveForward;
var oldpos: TPylsPos;
begin
   // ��������� ������
   oldpos := pylpos;
   case pylpos.rot of
      0: Dec(pylpos.y);
      1: Inc(pylpos.x);
      2: Inc(pylpos.y);
      3: Dec(pylpos.x);
   end;
   if InsertEnable(field,pylpos.x,pylpos.y) then begin
      if field[oldpos.x,oldpos.y].ElemT=ePYLS+Offset then
       field[oldpos.x,oldpos.y].ElemT := RUBSH else
         if field[oldpos.x,oldpos.y].ElemT=ePYLS then
          field[oldpos.x,oldpos.y].ElemT := EMPTY;
      if field[pylpos.x,pylpos.y].ElemT=RUBSH then
       field[pylpos.x,pylpos.y].ElemT := ePYLS+Offset else
         if field[pylpos.x,pylpos.y].ElemT=EMPTY then
          field[pylpos.x,pylpos.y].ElemT := ePYLS;
      field[pylpos.x,pylpos.y].Rot := pylpos.rot;
      DrawField;
   end else begin
      pylpos := oldpos;
      if MessageDlg('������������ ����������!'+#10#13+'���������� ����������?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
   end;
end;

procedure TForm1.Rotate(angle: integer);
var rot: integer;
begin
   // �������
   rot := pylpos.rot;
   rot := rot+angle;
   rot := (rot+4) mod 4;
   pylpos.rot := rot;
   field[pylpos.x,pylpos.y].Rot := pylpos.rot;
   DrawField;
end;

procedure TForm1.Clean(plus: boolean);
var ppos_x,ppos_y: integer; // ��� ����������
begin
   // ����������, ����������+
   ppos_x := pylpos.x;
   ppos_y := pylpos.y;
   // ���������� ��� ����������
   if plus then begin
      case pylpos.rot of
         0: ppos_y := ppos_y-2;
         1: ppos_x := ppos_x+2;
         2: ppos_y := ppos_y+2;
         3: ppos_x := ppos_x-2;
      end;
   end else begin
      case pylpos.rot of
         0: ppos_y := ppos_y-1;
         1: ppos_x := ppos_x+1;
         2: ppos_y := ppos_y+1;
         3: ppos_x := ppos_x-1;
      end;
   end;
   if ((not(ppos_x in [1..fsize_w])) or (not(ppos_y in [1..fsize_h]))) then begin     // ��� begin-end ���������
      if MessageDlg('������ ���������� �� �������� ����!'+#10#13+'���������� ����������?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
   end else begin
      case field[ppos_x,ppos_y].ElemT of
         RUBSH: field[ppos_x,ppos_y].ElemT := EMPTY;
         ePYLS: if MessageDlg('�� ���� ���������� �������!'+#10#13+'���������� ����������?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
         eSTOL,eSTUL: {nothing};
         eSTOL+Offset,eSTUL+Offset: Dec(field[ppos_x,ppos_y].ElemT,Offset);
         eSHKAF,eDIVAN,eSHKAF+Offset,eDIVAN+Offset:
            if MessageDlg('������ ���������� ��� ������ � ��� �������!'+#10#13+'���������� ����������?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
      end;
      DrawField;
   end;
end;

procedure TForm1.CodePopupMenu1Popup(Sender: TObject);
begin
  N34.Enabled:=not( (ListBox1.ItemIndex=0) or (ListBox1.ItemIndex=ListBox1.Items.Count-1));
end;

// ���� �������
procedure TForm1.RepeatN(k: integer);
var i: integer;
    j: integer;
    n: integer;
    m: integer;
    str: string;
    cmds: TStringList;
    tk: integer;
begin
   str := ListBox1.Items.Strings[k];
   Delete(str,1,10);
   n := StrToInt(str);
   i := 0;
   // ���������� ������ ������ � �����
   cmds := TStringList.Create;
   Inc(k);
   tk:=k;
   while ListBox1.Items.Strings[k]<>'  ����� �������' do begin
      cmds.Add(ListBox1.Items.Strings[k]);
      Inc(k);
   end;
   // ���������� ���������� �����
   while i<n do begin
      for j:=0 to cmds.Count-1 do begin
         m:=j+tk;
         DoComand(cmds.Strings[j],m);
         Application.ProcessMessages;
      end;
      Inc(i);
   end;
   cmds.Destroy;
end;

{����������� ����� � ����}
procedure TForm1.ElseHandler(var k: integer);
var count:integer;
begin
  count:=-1;
  while count<>0 do begin
    inc(k);
    if pos('����� ����',ListBox1.Items.Strings[k])<>0 then count:=count+1;
    if pos('�����',ListBox1.Items.Strings[k])<>0 then count:=count-1;
  end;
end;

procedure TForm1.IFHandler(var k: integer);
var str: string;
    count:integer;
begin
   // ������� �������
   str := ListBox1.Items.Strings[k];
   Delete(str,1,7);
   Delete(str,length(str)-2,3);
   // ����������
   if (ExpressionResult(str)) then {������ �� ������}
                              else begin
                                count:=-1;
                                while count<>0 do begin
                                  inc(k);
                                  if pos('�����',ListBox1.Items.Strings[k])<>0 then count:=count+1;
                                  if pos('���� ',ListBox1.Items.Strings[k])<>0 then count:=count-1;
                                end;
                              end;

end;

{���������� ����� ����}
procedure TForm1.WhileHandler(var k: integer);
var j: integer;
    m: integer;
    str: string;
    cmds: TStringList;
    tk: integer;
begin
   str := ListBox1.Items.Strings[k];
   // ������� �������
   Delete(str,1,7);
   Delete(str,length(str)-5,6);
   // ���������� ������ ������ � �����
   cmds := TStringList.Create;
   Inc(k);
   tk:=k;
   while ListBox1.Items.Strings[k]<>'  ����� ����' do begin
      cmds.Add(ListBox1.Items.Strings[k]);
      Inc(k);
   end;
   // ���������� ���������� �����
   while (ExpressionResult(str)) and (execute) do begin
      for j:=0 to cmds.Count-1 do begin
         m:=j+tk;
         DoComand(cmds.Strings[j],m);
         Application.ProcessMessages;
      end;
   end;
   cmds.Destroy;
end;

// ����� ������ �� �����
procedure TForm1.FormMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   StatusBar1.Panels[0].Text := '';
end;

// ��������� ���������
procedure TForm1.N10Click(Sender: TObject);
begin
   with SaveDialog2 do
      if Execute then
         if FileName<>'' then begin
            ListBox1.Items.SaveToFile(FileName);
         end;   
end;

// ��������� ���������
procedure TForm1.N11Click(Sender: TObject);
begin
   with OpenDialog2 do
      if Execute then
         if FileName<>'' then begin
            ListBox1.Items.LoadFromFile(FileName);
            ListBox1.ItemIndex := 1;
         end;
end;

procedure TForm1.Edit1Exit(Sender: TObject);
begin
   Edit1.Visible := false;
end;

procedure TForm1.N29Click(Sender: TObject);
begin
   ShellExecute(0,nil,'help.mht',nil,nil,0);
end;

procedure TForm1.SpeedButton10Click(Sender: TObject);
begin
   SetButtonsState(true);
   if execute then execute:=false else begin
      pylpos := backup_pylpos;
      field := backup_field;
      DrawField;
   end;
end;

// ��������� ����������
procedure TForm1.SpeedButton11Click(Sender: TObject);
var k: integer;
begin
   k:=ListBox1.ItemIndex;
   execute:=true;
   DoComand(ListBox1.Items.Strings[k],k);
   execute:=false;
   Inc(k);
   ListBox1.ItemIndex := k;
end;

// ���������� �������
procedure TForm1.N32Click(Sender: TObject);
var fstream: TFileStream;
//    psc,k: integer;
//    ps: string;
begin
   with SaveDialog3 do begin
      if Execute then begin
         if FileName<>'' then  begin
            // �������� ������ � ����
            try
               fstream := TFileStream.Create(FileName,fmOpenReadWrite);
            except
               fstream := TFileStream.Create(FileName,fmCreate);
            end;
            // ������
            fstream.WriteBuffer(fsize_w,SizeOf(Byte));
            // ������
            fstream.WriteBuffer(fsize_h,SizeOf(Byte));
            // ����
            fstream.WriteBuffer(field,SizeOf(TField));
            // ���������
            ListBox1.Items.SaveToStream(fstream);      
            // ���������
            Form1.Caption:='���������'+' - ������ '+ FileName;
            // ��������� ������
            fstream.Free;
         end;
      end;
   end;
end;

procedure TForm1.N34Click(Sender: TObject);     // ��������
var key:word;
begin
  key:=46;
  ListBox1KeyDown(Sender,key,[]);
end;

// �������� �������
procedure TForm1.N31Click(Sender: TObject);
var fstream: TFileStream;
//    psc,k: integer;
//    ps: string;
begin
   with OpenDialog3 do begin
      if Execute then begin
         if FileName<>'' then  begin
            try
               // �������� ������ � ����
               fstream := TFileStream.Create(FileName,fmOpenRead);
               // ������
               fstream.ReadBuffer(fsize_w,SizeOf(Byte));
               // ������
               fstream.ReadBuffer(fsize_h,SizeOf(Byte));
               // ����
               fstream.ReadBuffer(field,SizeOf(TField));
               // ���������
               ListBox1.Items.LoadFromStream(fstream);
               // ���������
               Form1.Caption:='���������'+' - ������ '+ FileName;
               // ���������� ����
               DrawField;
               // ��������� ������
               fstream.Free;
            except
               MessageDlg('������ ��� �������� ����� � ��������',mtError,[mbOK],0);
            end;
         end;
      end;
   end;
end;

function TForm1.GetSpaces(k: integer): string;
var str: string;
    predsc: integer;
    i: integer;
begin
   str := ListBox1.Items.Strings[k];
   if (pos('���������',str)>0) then Result:='  ' else
      if ((pos('�������',str)>0) or (pos('����',str)>0) or (pos('����',str)>0)
       or (pos('�����',str)>0)) and (pos('�����',str)=0) then begin
         predsc:=max(pos('�������',str),pos('����',str));
         predsc:=max(predsc,pos('����',str));
         predsc:=max(predsc,pos('�����',str));
         Result:='';
         for i:=1 to predsc+1 do Result:=Result+' ';
      end else begin
         i:=1;
         Result:='';
         while str[i]=' ' do begin
            Result:=Result+' ';
            Inc(i);
         end;   
      end;
end;

end.
