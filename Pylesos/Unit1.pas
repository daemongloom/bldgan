{===============================================}
{= �������� ��������������� �����������        =}
{= ����������� ����������� "���������"         =}
{=  ������� ������ ���������                   =}
{= ������: ������� ��������                    =}
{=         ������� ���������                   =}
{= ����: 2008.02.16                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons, XPMan, AboutUnit,
  ToolWin, NewPrgUnit, ShellAPI;

type
  // �������
  TComandList = ^TComanda;
  TComanda = record
     text: string;
     vlozh: TComandList;
     next: TComandList;
  end;
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
    InsertStul: TSpeedButton;
    GroupBox3: TGroupBox;
    Label2: TLabel;
    Label3: TLabel;
    InsertStol: TSpeedButton;
    InsertShkaf: TSpeedButton;
    InsertDivan: TSpeedButton;
    StatusBar1: TStatusBar;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    N5: TMenuItem;
    XPManifest1: TXPManifest;
    N6: TMenuItem;
    N7: TMenuItem;
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
    Edit1: TEdit;
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
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
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
    procedure FieldBoxMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ListBox1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure N10Click(Sender: TObject);
    procedure N11Click(Sender: TObject);
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure N29Click(Sender: TObject);
    procedure SpeedButton10Click(Sender: TObject);
  private
    { Private declarations }
    procedure OnMouseWheel(var message: TMessage); message CM_MOUSEWHEEL;
  public
    { Public declarations }
    procedure DrawField;
    procedure DoComand(str: string; var k: integer);
    procedure MoveForward;
    procedure Rotate(angle: integer);
    procedure Clean(plus: boolean);
    procedure RepeatN(var k: integer);
    procedure WhileHandler(var k: integer);
    procedure AddToComandList(var head: TComandList; k: integer);
    procedure SetButtonsState(state:boolean);
  end;

const WheelUp = 120;
      WheelDown = 65416;

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
    chead: TComandList;               // ������ ������
    execute: boolean;                 // ����������� �� ���������

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
    t:=e-Offset;
    Result := ((-Offset<=t) and (t<=eSHKAF));
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
          if ((exp='������� ����') and (e=eSTUL)) or
           ((exp='������� ����') and (e=eSTOL)) or
           ((exp='������� �����') and (e=eDIVAN)) or
           ((exp='������� ����') and (e=eSHKAF)) then
             Result := true;
          if ((exp='������� �� ����') and (e<>eSTUL)) or
           ((exp='������� �� ����') and (e<>eSTOL)) or
           ((exp='������� �� �����') and (e<>eDIVAN)) or
           ((exp='������� �� ����') and (e<>eSHKAF)) then
             Result := true;
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
           eSHKAF,eSHKAF+Offset: FieldBox.Canvas.Brush.Color := clTeal;
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
                 p[1].X := i*asize;
                 p[1].Y := j*asize;
                 p[2].X := (i-1)*asize;
                 p[2].Y := j*asize;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := (j-1)*asize;
              end;
              1: begin
                 p[1].X := (i-1)*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := (j-1)*asize + asize div 2;
                 p[3].X := (i-1)*asize;
                 p[3].Y := j*asize;
              end;
              2: begin
                 p[1].X := (i-1)*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := (j-1)*asize;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := j*asize;
              end;
              3: begin
                 p[1].X := i*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := j*asize;
                 p[3].X := (i-1)*asize;
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
   // �������� ����
   DrawField;
   // ��������� ��������
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   SaveDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   // �������� ����� ���������
   ListBox1.Clear;
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
var d: TComandList;
begin
   while chead<>nil do begin
      d := chead;
      chead := chead^.next;
      Dispose(d);
   end;
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

// ���������� ������ �� ����
procedure TForm1.FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
   startpoint.X := X div 24 +1;
   startpoint.Y := Y div 24 +1;
end;

procedure TForm1.InsertPylsClick(Sender: TObject);
begin
   InsMode := true;
   InsType := ePYLS;
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertStulClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSTUL; 
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertStolClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSTOL;  
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertShkafClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSHKAF; 
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertDivanClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eDIVAN;
   (Sender as TSpeedButton).Down:=true;
end;

// �������� ������ ����
procedure TForm1.N2Click(Sender: TObject);
begin
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
                  if (temp_ElemT in [EMPTY..eSHKAF]) then
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

// ����� ������ ����� �� ����
procedure TForm1.FieldBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   if InsMode then
      StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1) + ';' + IntToStr(InsRotation)
   else
      StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1);   
end;

// ������ ��������� ��������...
procedure TForm1.OnMouseWheel;
begin
   if not InsMode then
      {nothing}
   else
      case Message.WParamHi of
         WheelUp: if InsRotation=0 then InsRotation := 3 else Dec(InsRotation);
         WheelDown: if InsRotation=3 then InsRotation := 0 else Inc(InsRotation);
      end;
end;

procedure TForm1.N9Click(Sender: TObject);
begin
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
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ������');
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ����������');
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ����������+');
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  �����');
end;

// ������������ �������� ����
procedure TForm1.CPClick1(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ���� '+(Sender as TMenuItem).Caption+' ��');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  �����');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ����� ����');
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
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ���� '+(Sender as TMenuItem).Caption+' �����');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ����� ����');
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
   Edit1.Visible := true;
end;

procedure TForm1.DoComand(str: string; var k: integer);
begin
   if not execute then exit;
   ListBox1.ItemIndex := k;
   sleep(1000-(110-trackbar1.Position)*10);
   if (str = '  ������') then MoveForward;
   if (str = '  ������') then Rotate(1);
   if (str = '  �����') then Rotate(-1);
   if (str = '  ����������') then Clean(false);
   if (str = '  ����������+') then Clean(true);
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
end;

procedure TForm1.SpeedButton8Click(Sender: TObject);
var k: integer;
begin
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
  SetButtonsState(true);
end;

procedure TForm1.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key=13 then begin
      ListBox1.Items.Insert(ListBox1.ItemIndex,'  ������� '+Edit1.Text);
      ListBox1.Items.Insert(ListBox1.ItemIndex,'  ����� �������');
      Edit1.Visible := false;
   end;   
end;

procedure TForm1.SpeedButton9Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ������');
end;

procedure TForm1.FieldBoxMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var i,j: integer;
    inserted: boolean;
begin
   finpoint.X := X div 24 +1;
   finpoint.Y := Y div 24 +1;
   if InsType<>ePYLS then begin
      if startpoint.X>finpoint.X then SwapValues(startpoint.X,finpoint.X);
      if startpoint.Y>finpoint.Y then SwapValues(startpoint.Y,finpoint.Y);
      inserted := false;
      for i:=startpoint.X to finpoint.X do
         for j:=startpoint.Y to finpoint.Y do
            inserted := InsertElement(i,j,InsType,InsRotation);
      if inserted then begin
         // ���������� ����
         DrawField;
         // ������� ����� �������
         InsMode := false;
         InsType := EMPTY;
         InsRotation := 1;
         // �������� ������
         InsertPyls.Down:=false;
         InsertStul.Down:=false;
         InsertStol.Down:=false;
         InsertShkaf.Down:=false;
         InsertDivan.Down:=false;
      end;
   end else begin
      if InsertElement(startpoint.X,startpoint.Y,InsType,InsRotation) then begin
         // ���������� ����
         DrawField;
         // ����������� ���������� ���������
         if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
         // ������� ����� �������
         InsMode := false;
         InsType := EMPTY;
         InsRotation := 1;
         // �������� ������
         InsertPyls.Down:=false;
         InsertStul.Down:=false;
         InsertStol.Down:=false;
         InsertShkaf.Down:=false;
         InsertDivan.Down:=false;
      end;
   end;      
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
      ShowMessage('������������ ����������!'); // ������!
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
   if ((not(ppos_x in [1..fsize_w])) or (not(ppos_y in [1..fsize_h]))) then      // or � �� and!!!
      ShowMessage('������ ���������� �� �������� ����!')
   else begin
      case field[ppos_x,ppos_y].ElemT of
         RUBSH: field[ppos_x,ppos_y].ElemT := EMPTY;
         ePYLS: ShowMessage('�� ���� ���������� �������!');
         eSTOL,eSTUL: {nothing};
         eSTOL+Offset,eSTUL+Offset: Dec(field[ppos_x,ppos_y].ElemT,Offset);
         eSHKAF,eDIVAN,eSHKAF+Offset,eDIVAN+Offset:
            ShowMessage('������ ���������� ��� ������ � ��� �������!');
      end;
      DrawField;
   end;
end;

// ���� �������
procedure TForm1.RepeatN(var k: integer);
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

// ����������� �� ���� ������������� �������!
procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
   if not(Key in ['0'..'9',#8,#13,#27]) then Key := #0 else
      if Key=#27 then begin
         Edit1.Visible := false;
         Edit1.Text := '0';
      end;   
end;

procedure TForm1.AddToComandList(var head: TComandList;k: integer);
var newc,tek: TComandList;
    str: string;
begin
   if k<ListBox1.Items.Count then begin
      str := ListBox1.Items.Strings[k];
      New(newc);
      newc^.text := str;
      newc^.next := nil;
      newc^.vlozh := nil;
      if head=nil then head:=newc else begin
         tek := head;
         while tek<>nil do tek:=tek^.next;
         tek:=newc;
      end;
      if pos('����',str)>0 then AddToComandList(newc^.vlozh,k+1) else
         AddToComandList(head^.next,k+1);
   end;   
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

end.