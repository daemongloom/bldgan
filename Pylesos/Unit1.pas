{===============================================}
{= �������� ��������������� �����������        =}
{= ����������� ����������� "���������"         =}
{=  ������� ������ ���������                   =}
{= ������: ������� �������� (NT)...            =}
{= ����: 2008.02.08                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons, XPMan, AboutUnit;

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
  private
    { Private declarations }
  public
    { Public declarations }
    procedure DrawField;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

const Offset = 6; // ��������� �������� ��� ������ ������
      EMPTY = 0;  // �����
      ePYLS = 1;  // �������
      eSTUL = 2;  // ����
      eSTOL = 3;  // ����
      eDIVAN = 4; // �����
      eSHKAF = 5; // ����
      MaxPylsCount = 1; // ������������ ���������� ��������� �� ����

{���� �������� (������ �������): }
{0 - 0}
{1 - 90}
{2 - 180}
{3 - 270}
type TElem = EMPTY..eSHKAF+Offset;  // ��� ��������
     TRotation = 0..3;      // ���� ��������
     TFieldElem = record
       ElemT: TElem;        // ��� ��������
       rotation: TRotation; // ���� ��������
     end;
     TField = array [1..25,1..25] of TFieldElem;
     // ������� ��������� ������ 
     TElemSize = record
        w,h : integer;
     end;
     // ������ ��������
     TSizes = array [EMPTY..eSHKAF] of TElemSize;
     // ������ �������� ������ 
     TBMPs = array [TRotation] of TBitmap;

const DivanSize: TElemSize = (w: 3; h: 2);
      ShkafSize: TElemSize = (w: 3; h: 2);
      StolSize: TElemSize = (w: 3; h: 2);
      EmptySize: TElemSize = (w: 1; h: 1);
      // ������� ��������� ������
      Sizes: TSizes = ((w: 1; h: 1),
                       (w: 1; h: 1),
                       (w: 1; h: 1),
                       (w: 3; h: 2),
                       (w: 3; h: 1),
                       (w: 3; h: 2));

var asize: integer = 24;      // ������ ������ � ��������
    fsize_h, fsize_w: integer;// ������ ���� � �������
    // ������� �������� �������� � ������
    pylesos, stul, stol, shkaf, divan: TBMPs;
    field: TField;            // ����
    InsMode: boolean;         // ����������� �� �������
    InsType: TElem;           // ��� ���������
    field_file: file of integer; // ���� ����
    ffname: string;           // ��� ����� ���� ��� ���������� ��� ��������
    pylsc: integer;           // ���������� ��������� �� ����

procedure TForm1.DrawField;
var i,j: integer;
    r: TRotation;
begin
   // ���������� ������� ����
   fsize_w := StrToInt(FieldW.Text);
   fsize_h := StrToInt(FieldH.Text);
   Panel1.Width := fsize_w*asize + 1;
   Panel1.Height := fsize_h*asize + 1;
   FieldBox.Width := Panel1.Width;
   FieldBox.Height := Panel1.Height;
   // �������� ���
   FieldBox.Canvas.Brush.Color := clBlack;
   FieldBox.Canvas.Rectangle(0,0,FieldBox.Width,FieldBox.Height);
   // ������ ����� � ������ ��������
   FieldBox.Canvas.Pen.Color := clWhite;
   FieldBox.Canvas.Brush.Color := clGreen;
   for i:=1 to fsize_w do begin
      for j:=1 to fsize_h do begin
         r := field[i,j].rotation;
         case field[i,j].ElemT of
           EMPTY: FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize);
           ePYLS: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,pylesos[r]);
           eSTUL: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,stul[r]);
           eSTOL: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,stol[r]);
           eDIVAN: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,divan[r]);
           eSHKAF: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,shkaf[r]);
         end;
      end;
   end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
   DrawField;
   GroupBox2.Top := Panel1.Top + Panel1.Height + 15;
end;

procedure TForm1.FormCreate(Sender: TObject);
var k: TRotation;
begin
   // �������� ProgressBar1 � ������ �����
   ProgressBar1.Parent := StatusBar1;
   ProgressBar1.Top := 1;
   ProgressBar1.Left := StatusBar1.Panels[0].Width+1;
   ProgressBar1.Height := StatusBar1.Height - 2;
   StatusBar1.Panels[1].Width := StatusBar1.Width - StatusBar1.Panels[0].Width;
   ProgressBar1.Width := StatusBar1.Panels[1].Width - 2;
   ProgressBar1.Position := 15;
   // �������� ��������
   for k:=0 to 3 do begin
      pylesos[k] := TBitmap.Create;
      pylesos[k].LoadFromResourceName(HInstance,'PylesosBMP'+IntToStr(k));
      stul[k] := TBitmap.Create;
      stul[k].LoadFromResourceName(HInstance,'StulBMP'+IntToStr(k));
      stol[k] := TBitmap.Create;
      stol[k].LoadFromResourceName(HInstance,'StolBMP'+IntToStr(k));
      shkaf[k] := TBitmap.Create;
      shkaf[k].LoadFromResourceName(HInstance,'ShkafBMP'+IntToStr(k));
      divan[k] := TBitmap.Create;
      divan[k].LoadFromResourceName(HInstance,'DivanBMP'+IntToStr(k));
   end;
   // �������� ���� ��������
   FillChar(field,SizeOf(field),0);
   pylsc := 0;
   // ������� �������� �� ��������
   {
   InsertPyls.Glyph := pylesos[0];
   InsertStul.Glyph := stul[0];
   InsertStol.Glyph := stol[0];
   InsertShkaf.Glyph := shkaf[0];
   }
   // ����������� � ������� �������
   InsMode := false;
   InsType := EMPTY;
   // �������� ����
   DrawField;
   // �������� ������ �������������� ��� ����
   GroupBox2.Top := Panel1.Top + Panel1.Height + 15;
   // ��������� ��������
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
end;

procedure TForm1.FormDestroy(Sender: TObject);
var k: TRotation;
begin
   // ��������� ������ �� ��� ��������
   for k:=0 to 3 do begin
      pylesos[k].Free;
      stul[k].Free;
      stol[k].Free;
      shkaf[k].Free;
      divan[k].Free;
   end;
end;

// ��������� ����������� �������
function InsertEnable(f: TField; esize: TElemSize; ins_pos: TPoint): boolean;
var i,j: integer;
begin
   Result := false;
   if (ins_pos.X + esize.w <= fsize_w) and
    (ins_pos.Y + esize.h <=fsize_h) then begin
      // �� �������� ������ � ����
      // ���������� ��������
      Result := true;
      for i:=ins_pos.X to (ins_pos.X + esize.w -1) do
         for j:=ins_pos.Y to (ins_pos.Y + esize.h -1) do begin
            // � �����-�� ������ �� �����, ������� ����������!
            if f[i,j].ElemT <> EMPTY then Result := false;
         end;
   end;
end;

// ���������� ������ �� ����
procedure TForm1.FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var xp,yp: integer;
    ins_pos: TPoint;   // ������� ��� �������
    esize: TElemSize;  // ������ ��������
    i,j: integer;
begin
   // �������� �� ����� �������
   if InsMode then begin
      // ���������� ����������
      xp := X div 24 + 1;
      yp := Y div 24 + 1;
      ins_pos.X := xp;
      ins_pos.Y := yp;
      // ���������� ������ ������������ ��������
      esize := Sizes[InsType];
      // ��������� ������� �� ����, ���� �����
      if (InsertEnable(field,esize,ins_pos)) then begin
         field[xp,yp].ElemT := InsType;
         case InsType of
            ePYLS: begin
               Inc(pylsc);
               if pylsc=MaxPylsCount then InsertPyls.Enabled := false;
             end;
         end;
         // ��������� �������� ��������
         for i:=ins_pos.X+1 to (ins_pos.X + esize.w -1) do
            field[i,ins_pos.Y].ElemT := InsType + Offset;
         for j:=ins_pos.Y+1 to (ins_pos.Y + esize.h -1) do
            field[ins_pos.X,j].ElemT := InsType + Offset;
         for i:=ins_pos.X+1 to (ins_pos.X + esize.w -1) do
            for j:=ins_pos.Y+1 to (ins_pos.Y + esize.h -1) do begin
               field[i,j].ElemT := InsType + Offset;
            end;
         // ���������� ����
         DrawField;
      end;
      // ������� ����� �������
      InsMode := false;
      InsType := EMPTY;
   end;
end;

procedure TForm1.InsertPylsClick(Sender: TObject);
begin
   InsMode := true;
   InsType := ePYLS;
end;

procedure TForm1.InsertStulClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSTUL;
end;

procedure TForm1.InsertStolClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSTOL;
end;

procedure TForm1.InsertShkafClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eSHKAF;
end;

procedure TForm1.InsertDivanClick(Sender: TObject);
begin
   InsMode := true;
   InsType := eDIVAN;
end;

// �������� ������ ����
procedure TForm1.N2Click(Sender: TObject);
begin
   // �������� ���� ��������
   FillChar(field,SizeOf(field),0);
   // ����������� � ������� �������
   InsMode := false;
   InsType := EMPTY;
   // �������� ����
   DrawField;
   // �������� ������ �������������� ��� ����
   GroupBox2.Top := Panel1.Top + Panel1.Height + 15;
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
                  // ���������� ������������� �������� � ���� ��������
                  Write(field_file,field[i,j].ElemT,field[i,j].rotation);
               end;
            CloseFile(field_file);
         end;   
      end;
   end;   
end;

// ��������� ���� �� �����
procedure TForm1.N4Click(Sender: TObject);
var i,j: integer;
    temp_ElemT, temp_rotation: integer;
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
                     field[i,j].rotation := TRotation(temp_rotation);   
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

end.
