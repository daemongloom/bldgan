{===============================================}
{= �������� ��������������� �����������        =}
{= ����������� ����������� "���������"         =}
{=  ������� ������ ���������                   =}
{= ������: ������� �������� (NT)...            =}
{= ����: 2008.02.06                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons;

type
  TForm1 = class(TForm)
    Button1: TButton;
    FieldBox: TImage;
    Label1: TLabel;
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

var asize: integer = 24;      // ������ ������ � ��������
    fsize_h, fsize_w: integer;// ������ ���� � �������
    // ������� �������� �������� � ������
    pylesos, stul, stol, shkaf, divan: TBitmap;
    field: TField;            // ����
    InsMode: boolean;         // ����������� �� �������
    InsType: TElem;           // ��� ���������
    field_file: file of integer; // ���� ����
    ffname: string;           // ��� ����� ���� ��� ���������� ��� ��������

procedure TForm1.DrawField;
var i,j: integer;
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
         case field[i,j].ElemT of
           EMPTY: FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize);
           ePYLS: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,pylesos);
           eSTUL: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,stul);
           eSTOL: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,stol);
           eDIVAN: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,divan);
           eSHKAF: FieldBox.Canvas.Draw((i-1)*asize,(j-1)*asize,shkaf);
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
begin
   // �������� ��������
   pylesos := TBitmap.Create;
   pylesos.LoadFromFile('pylesos.bmp');
   stul := TBitmap.Create;
   stul.LoadFromFile('stul.bmp');
   stol := TBitmap.Create;
   stol.LoadFromFile('stol.bmp');
   shkaf := TBitmap.Create;
   shkaf.LoadFromFile('shkaf.bmp');
   divan := TBitmap.Create;
   divan.LoadFromFile('divan.bmp');
   // �������� ���� ��������
   FillChar(field,SizeOf(field),0);
   // ������� �������� �� ��������
   InsertPyls.Glyph := pylesos;
   InsertStul.Glyph := stul;
   InsertStol.Glyph := stol;
   InsertShkaf.Glyph := shkaf;
   InsertDivan.Glyph := divan;
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
begin
   // ��������� ������ �� ��� ��������
   pylesos.Free;
   stul.Free;
   stol.Free;
   shkaf.Free;
   divan.Free;
end;

// ���������� ������ �� ����
procedure TForm1.FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var xp,yp: integer;
    txp, typ: integer; // ��� �������� � ���������� �������� ������
    ienable: boolean;  // ����� �� ���������?
begin
   // �������� �� ����� �������
   if InsMode then begin
      // ���������� ����������
      xp := X div 24 + 1;
      yp := Y div 24 + 1;
      // ������� ����
      ienable := (field[xp,yp].ElemT = EMPTY);
      // ��������� �������� ������
      if InsType in [eSTOL,eDIVAN,eSHKAF] then begin
         txp := xp;
         typ := yp;
         case field[xp,yp].rotation of
           0: txp := xp+1;
           1: typ := yp+1;
           2: typ := yp-1;
           3: txp := xp-1;
         end;
         ienable := ienable and (field[txp,typ].ElemT = EMPTY);
      end;
      // ��������� ������� �� ����, ���� �����
      if ienable then begin
         field[xp,yp].ElemT := InsType;
         if InsType in [eSTOL,eDIVAN,eSHKAF] then begin
            txp := xp;
            typ := yp;
            case field[xp,yp].rotation of
              0: txp := xp+1;
              1: typ := yp+1;
              2: typ := yp-1;
              3: txp := xp-1;
            end;
            field[txp,typ].ElemT := InsType + Offset;
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

end.
