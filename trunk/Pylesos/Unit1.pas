{===============================================}
{= Пермский Государственный Университет        =}
{= Графический исполнитель "Пылесосик"         =}
{=  Главный модуль программы                   =}
{= Авторы: Николай Трубинов (NT)...            =}
{= Дата: 2008.02.06                            =}
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

const Offset = 6; // Константа смещения для частей мебели
      EMPTY = 0;  // Пусто
      ePYLS = 1;  // Пылесос
      eSTUL = 2;  // Стул
      eSTOL = 3;  // Стол
      eDIVAN = 4; // Диван
      eSHKAF = 5; // Шкаф

{Угол поворота (против часовой): }
{0 - 0}
{1 - 90}
{2 - 180}
{3 - 270}
type TElem = EMPTY..eSHKAF+Offset;  // Тип элемента
     TRotation = 0..3;      // Угол поворота
     TFieldElem = record
       ElemT: TElem;        // Тип элемента
       rotation: TRotation; // Угол поворота
     end;
     TField = array [1..25,1..25] of TFieldElem;

var asize: integer = 24;      // Размер клетки в пикселах
    fsize_h, fsize_w: integer;// Размер поля в клетках
    // Битмапы картинок пылесоса и мебели
    pylesos, stul, stol, shkaf, divan: TBitmap;
    field: TField;            // Поле
    InsMode: boolean;         // Выполняется ли вставка
    InsType: TElem;           // Что вставлять
    field_file: file of integer; // Файл поля
    ffname: string;           // Имя файла поля для сохранения или загрузки

procedure TForm1.DrawField;
var i,j: integer;
begin
   // Определяем размеры поля
   fsize_w := StrToInt(FieldW.Text);
   fsize_h := StrToInt(FieldH.Text);
   Panel1.Width := fsize_w*asize + 1;
   Panel1.Height := fsize_h*asize + 1;
   FieldBox.Width := Panel1.Width;
   FieldBox.Height := Panel1.Height;
   // Заливаем фон
   FieldBox.Canvas.Brush.Color := clBlack;
   FieldBox.Canvas.Rectangle(0,0,FieldBox.Width,FieldBox.Height);
   // Рисуем сетку и ставим предметы
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
   // Загрузим картинки
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
   // Заполним поле пустотой
   FillChar(field,SizeOf(field),0);
   // Выведем картинки на кнопочки
   InsertPyls.Glyph := pylesos;
   InsertStul.Glyph := stul;
   InsertStol.Glyph := stol;
   InsertShkaf.Glyph := shkaf;
   InsertDivan.Glyph := divan;
   // Разбираемся с режимом вставки
   InsMode := false;
   InsType := EMPTY;
   // Нарисуем поле
   DrawField;
   // Поставим панель редиктирования под поле
   GroupBox2.Top := Panel1.Top + Panel1.Height + 15;
   // Настройка диалогов
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
   // Освободим память из под картинок
   pylesos.Free;
   stul.Free;
   stol.Free;
   shkaf.Free;
   divan.Free;
end;

// Нажимается кнопка на поле
procedure TForm1.FieldBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var xp,yp: integer;
    txp, typ: integer; // Для проверки и заполнения соседних клеток
    ienable: boolean;  // Можно ли вставлять?
begin
   // Проверим на режим вставки
   if InsMode then begin
      // Определяем координаты
      xp := X div 24 + 1;
      yp := Y div 24 + 1;
      // Изменим поле
      ienable := (field[xp,yp].ElemT = EMPTY);
      // Проверяем соседние клетки
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
      // Вставляем элемент на поле, если можно
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
         // Перерисуем поле
         DrawField;
      end;
      // Сбросим режим вставки
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

// Создание нового поля
procedure TForm1.N2Click(Sender: TObject);
begin
   // Заполним поле пустотой
   FillChar(field,SizeOf(field),0);
   // Разбираемся с режимом вставки
   InsMode := false;
   InsType := EMPTY;
   // Нарисуем поле
   DrawField;
   // Поставим панель редиктирования под поле
   GroupBox2.Top := Panel1.Top + Panel1.Height + 15;
end;

// Сохранение поля
procedure TForm1.N3Click(Sender: TObject);
var i,j: integer;
begin
   with SaveDialog1 do begin
      if Execute then begin
         if FileName<>'' then  begin
            ffname := FileName;
            AssignFile(field_file,ffname);
            Rewrite(field_file);
            // Записываем размеры
            Write(field_file,fsize_w,fsize_h);
            for i:=1 to fsize_w do
               for j:=1 to fsize_h do begin
                  // Записываем идентификатор элемента и угол поворота
                  Write(field_file,field[i,j].ElemT,field[i,j].rotation);
               end;
            CloseFile(field_file);
         end;   
      end;
   end;   
end;

// Загружаем поле из файла
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
            // Читаем размеры
            Read(field_file,fsize_w,fsize_h);
            for i:=1 to fsize_w do
               for j:=1 to fsize_h do begin
                  // Читаем данные во временные переменные
                  Read(field_file,temp_ElemT,temp_rotation);
                  // Проверяем на соответствие типов
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
