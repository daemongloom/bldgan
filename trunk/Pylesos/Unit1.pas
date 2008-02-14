{===============================================}
{= Пермский Государственный Университет        =}
{= Графический исполнитель "Пылесосик"         =}
{=  Главный модуль программы                   =}
{= Авторы: Николай Трубинов (NT)...            =}
{= Дата: 2008.02.09                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons, XPMan, AboutUnit,
  ToolWin, NewPrgUnit;

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
  private
    { Private declarations }
    procedure OnMouseWheel(var message: TMessage); message CM_MOUSEWHEEL;
  public
    { Public declarations }
    procedure DrawField;
    procedure MoveForward;
    procedure Rotate(angle: integer);
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

const Offset = 6; // Константа смещения для частей мебели
      EMPTY = 0;  // Пусто
      RUBSH = 1;  // Мусор
      ePYLS = 2;  // Пылесос
      eSTUL = 3;  // Стул
      eSTOL = 4;  // Стол
      eDIVAN = 5; // Диван
      eSHKAF = 6; // Шкаф
      MaxPylsCount = 1; // Максимальное количество пылесосов на поле

type TElem = EMPTY..eSHKAF; // Тип элемента
     // Размеры элементов мебели
     TElemSize = record
        w,h : integer;
     end;
     TRotation = 0..3;
     TFieldElem = record
       ElemT: TElem;        // Тип элемента
       Rot: TRotation;      // Поворот (для пылесоса)
     end;
     TPylsPos = record            // Положение пылесоса на поле
        x,y: integer;
        rot: TRotation;
     end;
     TField = array [1..25,1..25] of TFieldElem;

var asize: integer = 24;      // Размер клетки в пикселах
    fsize_h, fsize_w: byte;   // Размер поля в клетках
    field: TField;            // Поле
    InsMode: boolean;         // Выполняется ли вставка
    InsType: TElem;           // Что вставлять
    InsRotation: TRotation;   // Поворот
    field_file: file of byte; // Файл поля
    ffname: string;           // Имя файла поля для сохранения или загрузки
    pylsc: integer;           // Количество пылесосов на поле
    pylpos: TPylsPos;         // Положение пылесоса на поле
    startpoint, finpoint: TPoint;

procedure TForm1.DrawField;
var i,j: integer;
    p: array [1..3] of TPoint;
begin
   // Устанавливаем размеры
   Panel1.Width := fsize_w*asize + 1;
   form1.autosize:=false;
   Panel1.Height := fsize_h*asize + 1;
   FieldBox.Width := Panel1.Width;
   FieldBox.Height := Panel1.Height;
   groupbox1.Left:=max(GroupBox2.Width,panel1.Width)+6;
   form1.autosize:=true;
   // Выводим буковки и циферки
   Form1.Canvas.Font.Color := clGreen;
   for i:=1 to fsize_w do
      with Form1.Canvas do begin
         TextOut(Panel1.Left + (i-1)*asize + asize div 2,Panel1.Top-15,Chr(Ord('А')+(i-1)));
      end;
   for i:=1 to fsize_h do
      with Form1.Canvas do begin
         TextOut(Panel1.Left - 15,Panel1.Top + (i-1)*asize + asize div 2,IntToStr(i));
      end;
   // Заливаем фон
   FieldBox.Canvas.Brush.Color := clBlack;
   FieldBox.Canvas.Rectangle(0,0,FieldBox.Width,FieldBox.Height);
   // Рисуем сетку и ставим предметы
   FieldBox.Canvas.Pen.Color := clWhite;
   FieldBox.Canvas.Brush.Color := clGreen;
   for i:=1 to fsize_w do begin
      for j:=1 to fsize_h do begin
         case field[i,j].ElemT of
           EMPTY: FieldBox.Canvas.Brush.Color := clGreen;
           RUBSH: FieldBox.Canvas.Brush.Color := clGray;
           ePYLS: FieldBox.Canvas.Brush.Color := clRed;
           eSTUL: FieldBox.Canvas.Brush.Color := clLime;
           eSTOL: FieldBox.Canvas.Brush.Color := clBlue;
           eDIVAN: FieldBox.Canvas.Brush.Color := clAqua;
           eSHKAF: FieldBox.Canvas.Brush.Color := clTeal;
         end;
         if field[i,j].ElemT<>ePYLS then FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize) else begin
            case field[i,j].Rot of
              // тут надо нарисовать треугольники
              0: begin
                 p[1].X := (i-1)*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := (j-1)*asize;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := j*asize;
              end;
              1: begin
                 p[1].X := i*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := j*asize;
                 p[3].X := (i-1)*asize;
                 p[3].Y := (j-1)*asize + asize div 2;
              end;
              2: begin
                 p[1].X := i*asize;
                 p[1].Y := j*asize;
                 p[2].X := (i-1)*asize;
                 p[2].Y := j*asize;
                 p[3].X := (i-1)*asize + asize div 2;
                 p[3].Y := (j-1)*asize;
              end;
              3: begin
                 p[1].X := (i-1)*asize;
                 p[1].Y := (j-1)*asize;
                 p[2].X := i*asize;
                 p[2].Y := (j-1)*asize + asize div 2;
                 p[3].X := (i-1)*asize;
                 p[3].Y := j*asize;
              end;
            end;
            FieldBox.Canvas.Polygon(p);
         end;     
      end;
   end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
   DrawField;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   // Инициализируем размеры поля
   fsize_w := 10;
   fsize_h := 10;
   // Поставим ProgressBar1 в нужное место
   ProgressBar1.Parent := StatusBar1;
   ProgressBar1.Top := 1;
   ProgressBar1.Left := StatusBar1.Panels[0].Width+StatusBar1.Panels[1].Width+1;
   ProgressBar1.Height := StatusBar1.Height - 2;
   StatusBar1.Panels[2].Width := StatusBar1.Width - ProgressBar1.Left;
   ProgressBar1.Width := StatusBar1.Panels[2].Width - 2;
   ProgressBar1.Position := 15;
   // Заполним поле мусором
   FillChar(field,SizeOf(field),1);
   pylsc := 0;
   // Разбираемся с режимом вставки
   InsMode := false;
   InsType := EMPTY;
   InsRotation := 1;
   // Нарисуем поле
   DrawField;
   // Настройка диалогов
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   // Создадим новую программу
   ListBox1.Clear;
   ListBox1.Items.Add('Программа НОВАЯ_ПРОГРАММА');
   ListBox1.Items.Add('Конец программы.');
   ListBox1.ItemIndex := 1;
   GroupBox1.Enabled := true;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
end;

// Проверяет возможность вставки
function InsertEnable(f: TField; esize: TElemSize; ins_pos: TPoint): boolean;
var i,j: integer;
begin
   Result := false;
   if (ins_pos.X + esize.w -1 <= fsize_w) and
    (ins_pos.Y + esize.h -1 <=fsize_h) then begin
      // По размерам входит в поле
      // Продолжаем проверку
      Result := true;
      for i:=ins_pos.X to (ins_pos.X + esize.w -1) do
         for j:=ins_pos.Y to (ins_pos.Y + esize.h -1) do begin
            // В какой-то клетке не пусто, вставка невозможна!
            if f[i,j].ElemT <> EMPTY then Result := false;
         end;
   end;
end;

function InsertElement(xp,yp: integer;ElemT: TElem;Rot: TRotation): boolean;
var ins_pos: TPoint;
begin
   Result := false;
   // Проверим на режим вставки
   if InsMode then begin
      // Определяем координаты
      ins_pos.X := xp;
      ins_pos.Y := yp;
      // Вставляем элемент на поле, если можно
      if (field[xp,yp].ElemT=EMPTY) or (field[xp,yp].ElemT=RUBSH) then begin
         field[xp,yp].ElemT := ElemT;
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
      // Вернем результат
      Result := true;
   end;
end;

// Нажимается кнопка на поле
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

// Создание нового поля
procedure TForm1.N2Click(Sender: TObject);
begin
   // Заполним поле мусором
   FillChar(field,SizeOf(field),1);
   pylsc := 0;
   InsertPyls.Enabled := true;
   // Разбираемся с режимом вставки
   InsMode := false;
   InsType := EMPTY;
   InsRotation := 1;
   // Нарисуем поле
   DrawField;
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
                  // Записываем идентификатор элемента
                  Write(field_file,field[i,j].ElemT,field[i,j].Rot);
               end;
            CloseFile(field_file);
         end;   
      end;
   end;   
end;

// Загружаем поле из файла
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
            // Читаем размеры
            Read(field_file,fsize_w,fsize_h);
            for i:=1 to fsize_w do
               for j:=1 to fsize_h do begin
                  // Читаем данные во временные переменные
                  Read(field_file,temp_ElemT,temp_rotation);
                  // Проверяем на соответствие типов
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

// О программе
procedure TForm1.N6Click(Sender: TObject);
begin
   Form2.ShowModal;
end;

// Когда мышкой водят по полю
procedure TForm1.FieldBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   if InsMode then
      StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1) + ';' + IntToStr(InsRotation)
   else
      StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1);   
end;

// Хитрая процедура поворота...
procedure TForm1.OnMouseWheel;
begin
   if not InsMode then
      {nothing}
   else
      case Message.WParamHi of
         WheelUp: if InsRotation=3 then InsRotation := 0 else Inc(InsRotation);
         WheelDown: if InsRotation=0 then InsRotation := 3 else Dec(InsRotation);
      end;
end;

procedure TForm1.N9Click(Sender: TObject);
begin
   // Создадим новую программу
   Form3.ShowModal;
   if ProgName='###NewProgramCanceled' then exit;
   ListBox1.Clear;
   ListBox1.Items.Add('Программа '+ProgName);
   ListBox1.Items.Add('Конец программы.');
   ListBox1.ItemIndex := 1;
   GroupBox1.Enabled := true;
end;

// Клик мышкой на ListBox'e
procedure TForm1.ListBox1Click(Sender: TObject);
begin
   if ListBox1.ItemIndex=0 then ListBox1.ItemIndex := 1;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ВПЕРЕД');
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ПЫЛЕСОСИТЬ');
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ПЫЛЕСОСИТЬ+');
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ВЛЕВО');
end;

// Обрабатываем кнопочку ЕСЛИ
procedure TForm1.CPClick1(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ЕСЛИ '+(Sender as TMenuItem).Caption+' ТО');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ИНАЧЕ');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  КОНЕЦ ЕСЛИ');
end;

procedure TForm1.SpeedButton5Click(Sender: TObject);
var i: integer;
    MyComp: TComponent;
begin
   ConditionsPopup.Popup(Form1.Left+GroupBox1.Left+SpeedButton5.Left,
     Form1.Top+SpeedButton5.Top+SpeedButton5.Height+5);
   for i:=14 to 25 do begin
      MyComp := FindComponent('N'+IntToStr(i)) as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick1;
   end;
end;

// Обрабатываем кнопку Пока
procedure TForm1.CPClick2(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ПОКА '+(Sender as TMenuItem).Caption+' ДЕЛАЙ');
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  КОНЕЦ ПОКА');
end;

procedure TForm1.SpeedButton6Click(Sender: TObject);
var i: integer;
    MyComp: TComponent;
begin
   ConditionsPopup.Popup(Form1.Left+GroupBox1.Left+SpeedButton6.Left,
     Form1.Top+SpeedButton6.Top+SpeedButton6.Height+5);
   for i:=14 to 25 do begin
      MyComp := FindComponent('N'+IntToStr(i)) as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick2;
   end;
end;

// Обрабатываем Повторяй
procedure TForm1.SpeedButton7Click(Sender: TObject);
begin
   Edit1.Visible := true;
end;

procedure TForm1.SpeedButton8Click(Sender: TObject);
var k: integer;
begin
  k := 1;
  while k<ListBox1.Items.Count do begin
     ListBox1.ItemIndex := k;
     if (ListBox1.Items.ValueFromIndex[k] = ' ВПЕРЕД') then MoveForward;
     if (ListBox1.Items.ValueFromIndex[k] = ' ВПРАВО') then Rotate(1);
     if (ListBox1.Items.ValueFromIndex[k] = ' ВЛЕВО') then Rotate(-1);
     Inc(k);
  end;
end;

procedure TForm1.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key=13 then begin
      ListBox1.Items.Insert(ListBox1.ItemIndex,'  ПОВТОРИ '+Edit1.Text);
      ListBox1.Items.Insert(ListBox1.ItemIndex,'  КОНЕЦ ПОВТОРИ');
      Edit1.Visible := false;
   end;   
end;

procedure TForm1.SpeedButton9Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,'  ВПРАВО');
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
         // Перерисуем поле
         DrawField;
         // Сбросим режим вставки
         InsMode := false;
         InsType := EMPTY;
         InsRotation := 1;
         // Поднимем кнопки
         InsertPyls.Down:=false;
         InsertStul.Down:=false;
         InsertStol.Down:=false;
         InsertShkaf.Down:=false;
         InsertDivan.Down:=false;
      end;
   end else begin
      if InsertElement(startpoint.X,startpoint.Y,InsType,InsRotation) then begin
         // Перерисуем поле
         DrawField;
         // Отслеживаем количество пылесосов
         if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
         // Сбросим режим вставки
         InsMode := false;
         InsType := EMPTY;
         InsRotation := 1;
         // Поднимем кнопки
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
   // Двигаемся вперед
   oldpos := pylpos;
   case pylpos.rot of
      0: if pylpos.y>1 then Dec(pylpos.y) else ShowMessage('Error!');
      1: if pylpos.x<fsize_w then Inc(pylpos.x) else ShowMessage('Error!');
      2: if pylpos.y<fsize_h then Inc(pylpos.y) else ShowMessage('Error!');
      3: if pylpos.x>1 then Dec(pylpos.x) else ShowMessage('Error!');
   end;
   field[oldpos.x,oldpos.y].ElemT := EMPTY;
   field[pylpos.x,pylpos.y].ElemT := ePYLS;
   field[pylpos.x,pylpos.y].Rot := pylpos.rot;
   DrawField;
end;

procedure TForm1.Rotate(angle: integer);
var rot: integer;
begin
   // Поворот
   rot := pylpos.rot;
   rot := rot+angle;
   if rot<0 then rot:=3 else
      if rot>3 then rot:=0;
   pylpos.rot := rot;   
   field[pylpos.x,pylpos.y].Rot := pylpos.rot;
   DrawField;   
end;

end.
