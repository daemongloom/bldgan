{===============================================}
{= Пермский Государственный Университет        =}
{= Графический исполнитель "Пылесосик"         =}
{=  Главный модуль программы                   =}
{= Авторы: Николай Трубинов                    =}
{=         Николай Козаченко                   =}
{= Дата: 2008.06.07                            =}
{===============================================}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  StdCtrls, ExtCtrls, ComCtrls, Menus, Buttons, XPMan, AboutUnit,
  NewPrgUnit, ShellAPI, Dialogs, Spin, ColorButton;

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
    SpeedButton9: TSpeedButton;
    TrackBar1: TTrackBar;
    SaveDialog2: TSaveDialog;
    OpenDialog2: TOpenDialog;
    N26: TMenuItem;
    N27: TMenuItem;
    N28: TMenuItem;
    N29: TMenuItem;
    InsertStol: TColorButton;
    InsertDivan: TColorButton;
    InsertStul: TColorButton;
    InsertShkaf: TColorButton;
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
    N35: TMenuItem;
    N36: TMenuItem;
    Label1: TLabel;
    XPManifest1: TXPManifest;
    Image1: TImage;
    N37: TMenuItem;
    ClearButton: TColorButton;
    DirtyButton: TColorButton;
    RadioGroup1: TRadioGroup;
    AutoMode: TRadioButton;
    RadioButton2: TRadioButton;
    SpeedButton8: TSpeedButton;
    SpeedButton10: TSpeedButton;
    Button2: TButton;
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
    procedure CPClick3(Sender: TObject);
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
    procedure N37Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure AutoModeClick(Sender: TObject);
    procedure Button2Click(Sender: TObject);
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
    function GetSpacesCount(s: string): integer;
  end;

var
  Form1: TForm1;
  ProgName: string;
  FirstDotColor:TColor;

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
      ePYLS = 1;  // Пылесос
      eSTUL = 2;  // Стул
      eSTOL = 3;  // Стол
      eDIVAN = 4; // Диван
      eSHKAF = 5; // Шкаф
      RUBSH = 6;  // Мусор
      MaxPylsCount = 1; // Максимальное количество пылесосов на поле

type TElem = EMPTY..eSHKAF+Offset; // Тип элемента
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

var asize: integer = 24;              // Размер клетки в пикселах
    fsize_h, fsize_w: byte;           // Размер поля в клетках
    field, backup_field: TField;      // Поле
    InsMode: boolean;                 // Выполняется ли вставка
    InsType: TElem;                   // Что вставлять
    InsRotation: TRotation;           // Поворот
    field_file: file of byte;         // Файл поля
    ffname: string;                   // Имя файла поля для сохранения или загрузки
    pylsc: integer;                   // Количество пылесосов на поле
    pylpos, backup_pylpos: TPylsPos;  // Положение пылесоса на поле
    startpoint, finpoint: TPoint;
    execute: boolean;                 // Выполняется ли программа
    ifstart: boolean;                 // Для расстановки мебели
    // Цикл Повтори
    repeatneed: integer;              // Сколько надо повторений
    inrepeat: boolean;                // Внутри цикла повтори Н
    repeatend: integer;               // КОНЕЦ ПОВТОРИ для текущего цикла
    // Цикл Пока
    inwhile: boolean;                 // Находимся ли внутри цикла Пока
    whileend: integer;                // КОНЕЦ ПОКА для текущего цикла

// Выдает значение логического выражения для конструкций ЕСЛИ и ПОКА 
function ExpressionResult(exp: string): boolean;
var x,y: integer;
    e: TElem;

 // Впереди край?
 function Kray: boolean;
 begin
    Result := (((pylpos.x=1) and (pylpos.rot=3)) or
     ((pylpos.x=fsize_w) and (pylpos.rot=1)) or
     ((pylpos.y=1) and (pylpos.rot=0)) or
     ((pylpos.y=fsize_h) and (pylpos.rot=2)));
 end;

 // Чисто ли в x,y?
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
   if exp='впереди край' then Result := Kray else
    if exp='впереди не край' then Result := not Kray else begin
       if (not Kray) then begin
          case pylpos.rot of
             0: Dec(y);
             1: Inc(x);
             2: Inc(y);
             3: Dec(x);
          end;
          e := field[x,y].ElemT;
          // Отбросим мусор
          e := (e+Offset) mod Offset;
          // Впереди мебель
          if ((exp='впереди стул') and (e=eSTUL)) or
           ((exp='впереди стол') and (e=eSTOL)) or
           ((exp='впереди диван') and (e=eDIVAN)) or
           ((exp='впереди шкаф') and (e=eSHKAF)) then
             Result := true else
          // Впереди не мебель
          if ((exp='впереди не стул') and (e<>eSTUL)) or
           ((exp='впереди не стол') and (e<>eSTOL)) or
           ((exp='впереди не диван') and (e<>eDIVAN)) or
           ((exp='впереди не шкаф') and (e<>eSHKAF)) then
             Result := true else
          // Впереди пусто-не пусто
          if ((exp='впереди пусто') and (e=EMPTY)) or
           ((exp='впереди не пусто') and (e<>EMPTY)) then
             Result := true else   
          if (exp='чисто') then Result := Chisto(x,y) else
           if exp='грязно' then Result := not Chisto(x,y) else begin
              case pylpos.rot of
                 0: Dec(y);
                 1: Inc(x);
                 2: Inc(y);
                 3: Dec(x);
              end;
              if (x in [1..fsize_w]) and (y in [1..fsize_h]) then begin
               if exp='чисто+' then Result := Chisto(x,y) else
                if exp='грязно+' then Result := not Chisto(x,y);
              end;
           end;
       end;
    end;   
end;

procedure TForm1.DrawField;
var i,j: integer;
    p: array [1..3] of TPoint;
const alphabet: string='АБВГДЕЖЗИК';
begin
   Form1.Autosize:=true;
   // Выводим буковки и циферки
   with Image1.Canvas do begin
      Font.Color := clGreen;
      for i:=1 to fsize_w do
         TextOut((i-1)*asize+23,0,alphabet[i]);
      for i:=1 to fsize_h do
         TextOut(0,(i-1)*asize+23,IntToStr(i));
   end;
   // Заливаем фон
   FieldBox.Canvas.Brush.Color := clGray;
   FieldBox.Canvas.Rectangle(0,0,FieldBox.Width,FieldBox.Height);
   // Рисуем сетку и ставим предметы
   FieldBox.Canvas.Brush.Color := clGreen;
   for i:=1 to fsize_w do begin
      for j:=1 to fsize_h do begin
         FieldBox.Canvas.Pen.Color := clWhite;
         FieldBox.Canvas.Brush.Style := bsSolid;
         case field[i,j].ElemT of
           EMPTY: FieldBox.Canvas.Brush.Color := ClearButton.ButtonColor;
           RUBSH: FieldBox.Canvas.Brush.Color := DirtyButton.ButtonColor;
           eSTUL: begin
              FieldBox.Canvas.Brush.Color := InsertStul.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
           end;
           eSTUL+Offset: begin
              FieldBox.Canvas.Brush.Color := InsertStul.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
              FieldBox.Canvas.Brush.Style := bsDiagCross;
           end;
           eSTOL: begin
              FieldBox.Canvas.Brush.Color := InsertStol.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
           end;
           eSTOL+Offset: begin
              FieldBox.Canvas.Brush.Color := InsertStol.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
              FieldBox.Canvas.Brush.Style := bsDiagCross;
           end;
           eDIVAN,eDIVAN+Offset: begin
              FieldBox.Canvas.Brush.Color := InsertDivan.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
           end;
           eSHKAF,eSHKAF+Offset: begin
              FieldBox.Canvas.Brush.Color := InsertShkaf.ButtonColor;
              FieldBox.Canvas.Pen.Color := clBlack;
           end;
         end;
         if (field[i,j].ElemT<>ePYLS) and (field[i,j].ElemT<>ePYLS+Offset)
          then FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize)
         else begin
            if field[i,j].ElemT=ePYLS then FieldBox.Canvas.Brush.Color := ClearButton.ButtonColor
               else FieldBox.Canvas.Brush.Color := DirtyButton.ButtonColor;
            FieldBox.Canvas.Rectangle((i-1)*asize,(j-1)*asize,i*asize,j*asize);
            case field[i,j].Rot of
              // тут надо нарисовать треугольники
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
   ProgressBar1.Position := 0;
   // Заполним поле мусором
   FillChar(field,SizeOf(field),RUBSH);
   pylsc := 0;
   // Разбираемся с режимом вставки
   InsMode := false;
   InsType := EMPTY;
   InsRotation := 1;
   startpoint.X := 0;
   startpoint.Y := 0;
   finpoint.X := 0;
   finpoint.Y := 0;
   // Устанавливаем размеры
   Panel1.Width := fsize_w*asize + 1;
   Form1.Autosize:=false;
   Panel1.Height := fsize_h*asize + 1;
   FieldBox.Width := Panel1.Width;
   FieldBox.Height := Panel1.Height;
   // Поставим поле в нужное место
   Panel1.Left:=(groupbox2.Width+groupbox2.left) div 2 - (panel1.Width div 2);
   Panel1.Top:= (Form1.Height - (groupbox2.height+groupbox2.top)) div 2 - (panel1.height div 2);
   // Для прорисовки букв
   Image1.Top := Panel1.Top -15;
   Image1.Left := Panel1.Left -15;
   Image1.Height := Panel1.Height +15;
   Image1.Width := Panel1.Width +15;
   Image1.Canvas.Brush.Color := Form1.Color;
   Image1.Canvas.Pen.Color := Form1.Color;
   Image1.Canvas.Rectangle(0,0,Image1.Width,Image1.Height);
   // Нарисуем поле
   DrawField;
   // Настройка диалогов
   SaveDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName);
   SaveDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog2.InitialDir := ExtractFilePath(Application.ExeName);
   SaveDialog3.InitialDir := ExtractFilePath(Application.ExeName);
   OpenDialog3.InitialDir := ExtractFilePath(Application.ExeName);

   // Создадим новую программу  
   BackupListBox.Clear;
   ListBox1.Clear;
   N7.Enabled:=false;
   ListBox1.Items.Add('Программа НОВАЯ_ПРОГРАММА');
   ListBox1.Items.Add('Конец программы.');
   ListBox1.ItemIndex := 1;
   GroupBox1.Enabled := true;

   // Сохраним поле
   backup_field := field;
   // Сбросим флаг выполнения программы
   execute := false;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
end;

// Проверяет возможность вставки
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
   // Проверим на режим вставки
   if InsMode then begin
      // Определяем координаты
      ins_pos.X := xp;
      ins_pos.Y := yp;
      // Вставляем элемент на поле, если можно
      if (field[xp,yp].ElemT=EMPTY) or (field[xp,yp].ElemT=RUBSH) then begin
         if field[xp,yp].ElemT=RUBSH then begin
            field[xp,yp].ElemT := ElemT+Offset;
            if (ElemT=eDIVAN) or (ElemT=eSHKAF) then field[xp,yp].ElemT := field[xp,yp].ElemT - Offset;
         end else field[xp,yp].ElemT := ElemT;
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

procedure TForm1.Rotating(x,y: integer);
begin
   field[x,y].Rot := (field[x,y].Rot+1) mod 4;
   pylpos.rot := field[x,y].Rot;
   DrawField;
end;

// Вставляем элемент на поле
procedure TForm1.Inserting(x,y: integer);
var i,j: integer;
    inserted,freespaceavail: boolean;
begin
   if (InsType=ePYLS) or (InsType=eSTUL) then begin
      // Вставляем пылесос или стул
      if InsertEnable(field,x,y) then begin
         if InsertElement(x,y,InsType,InsRotation) then begin
            // Перерисуем поле
            DrawField;
            SetButtonsState(true);
            // Отслеживаем количество пылесосов
            if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
            // Сбросим режим вставки
            InsMode := false;
            InsType := EMPTY;
            InsRotation := 1;
         end;
      end else
         MessageDlg('Не могу!',mtError,[mbOK],0);
   end else begin
      if InsMode=false then exit;
      // Вставляем не стул и не пылесос
      if (ifstart) then begin
          if InsertEnable(field,x,y) then begin
              startpoint.X := x;
               startpoint.Y := y;
               // Отметим первую точку
               FieldBox.Canvas.Brush.Color := FirstDotColor;
               FieldBox.Canvas.Ellipse((x-1)*asize+5,(y-1)*asize+5,x*asize-5,y*asize-5);
             end
           else begin
              MessageDlg('Не могу!',mtError,[mbOK],0);
              InsMode:=false;
           end;
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
                  MessageDlg('Не могу!',mtError,[mbOK],0);
                  freespaceavail:=false;
                  inserted:=true; // что бы перерисовалось и сбросилось
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
            // Перерисуем поле
            DrawField;
            // Сбросим режим вставки
            InsMode := false;
            InsType := EMPTY;
            InsRotation := 1;
         end;
      end;

   end;
end;

// Удаляем элемент с поля
procedure TForm1.Deleting(x,y: integer);
var p: array [1..5] of TPoint;
begin
   // Если удаляем вставку
   if (startpoint.X=x) and (startpoint.Y=y) then begin
      ifstart:=true;
      startpoint.X := 0;
      startpoint.Y := 0;
      DrawField;
   end;
   // Если удаляем элемент с поля
   if (field[x,y].ElemT=EMPTY) or (field[x,y].ElemT=RUBSH) then exit else begin
      // Рисуем кайму для удаляемого элемента
      p[1].X:=(x-1)*asize;
      p[1].Y:=(y-1)*asize;
      p[2].X:=(x)*asize;
      p[2].Y:=(y-1)*asize;
      p[3].X:=(x)*asize;
      p[3].Y:=(y)*asize;
      p[4].X:=(x-1)*asize;
      p[4].Y:=(y)*asize;
      p[5]:=p[1];
      FieldBox.Canvas.Pen.Color := clRed;
      FieldBox.Canvas.Polyline(p);
      // Удаляем
      if (field[x,y].ElemT<>ePYLS) and (field[x,y].ElemT<>ePYLS+Offset) then begin
         // Если есть что удалять, спрашиваем
         if MessageDlg('Удалить этот элемент?',mtConfirmation,[mbYes,mbNo],0)=mrYes then begin
            // удаляем не пылесос
            if field[x,y].ElemT in [RUBSH..eSHKAF+Offset] then field[x,y].ElemT:=RUBSH else
               field[x,y].ElemT:=EMPTY;
         end;
      end else begin
          if MessageDlg('Удалить этот элемент?',mtConfirmation,[mbYes,mbNo],0)=mrYes then begin
             // Удаляем пылесос
             if field[x,y].ElemT=ePYLS then field[x,y].ElemT:=EMPTY else field[x,y].ElemT:=RUBSH;
             InsertPyls.Enabled:=true;
          end;
      end;
      DrawField;      
   end;
end;

// Нажимается кнопка на поле
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
   DrawField;      // фикс многоточий...
   InsMode := true;
   InsType := ePYLS;
   ifstart := false;
   FirstDotColor:=clWhite;
   (Sender as TSpeedButton).Down:=true;
end;

procedure TForm1.InsertStulClick(Sender: TObject);
begin
   DrawField;      // фикс многоточий...
   InsMode := true;
   InsType := eSTUL;
   ifstart := false;   
   FirstDotColor:=InsertStul.ButtonColor;
end;

procedure TForm1.InsertStolClick(Sender: TObject);
begin
   DrawField;      // фикс многоточий...
   InsMode := true;
   InsType := eSTOL;
   ifstart := true;
   FirstDotColor:=InsertStol.ButtonColor;
end;

procedure TForm1.InsertShkafClick(Sender: TObject);
begin
   DrawField;      // фикс многоточий...
   InsMode := true;
   InsType := eSHKAF;
   ifstart := true;   
   FirstDotColor:=InsertShkaf.ButtonColor;
end;

procedure TForm1.InsertDivanClick(Sender: TObject);
begin
   DrawField;      // фикс многоточий...
   InsMode := true;
   InsType := eDIVAN;
   ifstart := true;   
   FirstDotColor:=InsertDivan.ButtonColor;
end;

// Создание нового поля
procedure TForm1.N2Click(Sender: TObject);
begin
   if MessageDlg('Создать новое поле?'+#10#13+'Текущее поле будет удалено!',mtConfirmation,[mbYes,mbNo],0)<>mrYes then exit;
   // Заполним поле мусором
   FillChar(field,SizeOf(field),RUBSH);
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
                  if (temp_ElemT in [EMPTY..eSHKAF+Offset]) then
                     field[i,j].ElemT := TElem(temp_ElemT);
                  if (temp_rotation in [0..3]) then
                     field[i,j].Rot := TRotation(temp_rotation);
                  if (temp_ElemT=ePYLS) or (temp_ElemT=ePYLS+Offset) then begin
                     pylpos.x:=i;
                     pylpos.y:=j;
                     pylpos.rot:=temp_rotation;
                     // Отслеживаем количество пылесосов
                     Inc(pylsc);
                     if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
                  end;
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

procedure TForm1.N7Click(Sender: TObject);
begin
  ListBox1.Items:=BackupListBox.Items;
  ListBox1.ItemIndex:=BackupListBox.ItemIndex;
  N7.Enabled:=false;
end;

// Когда мышкой водят по полю
procedure TForm1.FieldBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   StatusBar1.Panels[0].Text := IntToStr(Y div 24 + 1)+':'+IntToStr(X div 24 + 1);   
end;

procedure TForm1.N9Click(Sender: TObject);
begin
   if MessageDlg('Создать новую программу?'+#10#13+'Это приведет к удалению старой!',mtConfirmation,[mbYes,mbNo],0)<>mrYes then exit;
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

procedure TForm1.ListBox1KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
var i:integer;
    str: string;
    spaces: string;
    k: integer;
begin
   // создаем резервную копию
   BackupListBox.Items:=ListBox1.Items;
   BackupListBox.ItemIndex:=ListBox1.ItemIndex;
   N7.Enabled:=true;

   i:=ListBox1.ItemIndex; // сохраним позицию курсора
   str := ListBox1.Items.Strings[i];
   // Пробелы
   k:=1;
   spaces := '';
   while str[k]=' ' do begin
      spaces := spaces+' ';
      Inc(k);
   end;
   if Key=46 then begin
      if (ListBox1.ItemIndex in [1..ListBox1.Items.count-2]) then begin
         if (pos('ИНАЧЕ',str)>0) or (pos('КОНЕЦ ЕСЛИ',str)>0) or
          (pos('КОНЕЦ ПОВТОРИ',str)>0) or (pos('КОНЕЦ ПОКА',str)>0)
         then {nothing} else begin
            ListBox1.Items.Delete(ListBox1.ItemIndex);
            // Удаляем ветвление
            if (pos('ЕСЛИ',str)=k) then begin
               while pos(spaces+'КОНЕЦ ЕСЛИ',ListBox1.Items.Strings[i])<>1 do
                  ListBox1.Items.Delete(i);
               ListBox1.Items.Delete(i);
            end;
            // Удаляем цикл повтори
            if (pos('ПОВТОРИ',str)=k) then begin
               while pos(spaces+'КОНЕЦ ПОВТОРИ',ListBox1.Items.Strings[i])<>1 do
                  ListBox1.Items.Delete(i);
               ListBox1.Items.Delete(i);   
            end;
            // Удаляем цикл пока
            if (pos('ПОКА',str)=k) then begin
               while pos('КОНЕЦ ПОКА',ListBox1.Items.Strings[i])<>1 do
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
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ВПЕРЕД');
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ПЫЛЕСОСИТЬ');
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ПЫЛЕСОСИТЬ+');
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ВЛЕВО');
end;

// Обрабатываем кнопочку ЕСЛИ
procedure TForm1.CPClick1(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ЕСЛИ '+(Sender as TMenuItem).Caption+' ТО');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'ИНАЧЕ');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-3)+'КОНЕЦ ЕСЛИ');
   ListBox1.ItemIndex:=ListBox1.ItemIndex-2;
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
      MyComp := FindComponent('N35') as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick1;
      MyComp := FindComponent('N36') as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick1;
end;

// Обрабатываем кнопку Пока
procedure TForm1.CPClick2(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ПОКА '+(Sender as TMenuItem).Caption+' ДЕЛАЙ');
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'КОНЕЦ ПОКА');
   ListBox1.ItemIndex:=ListBox1.ItemIndex-1;
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
      MyComp := FindComponent('N35') as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick2;
      MyComp := FindComponent('N36') as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick2;
end;

// Обрабатываем Повторяй
procedure TForm1.SpeedButton7Click(Sender: TObject);
var tempb:boolean;
begin
   tempb:=true;
   if Edit1.Visible then begin
      if edit1.Value>max(fsize_w,fsize_h) then
         tempb:=MessageDlg('Вы хотите указать количество повторений, большее размера поля.'+#10#13+'Вы уверены?',mtConfirmation,[mbYes,mbNo],0)=mrYes;
      if tempb then begin
         ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ПОВТОРИ '+inttostr(strtoint(Edit1.Text)));
         ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-2)+'КОНЕЦ ПОВТОРИ');
         ListBox1.ItemIndex:=ListBox1.ItemIndex-1;
         Edit1.Visible := false;
      end else begin
         Edit1.Visible := false;
      end;
   end else begin
       Edit1.Visible := true;
       Edit1.Text:='1';
       Edit1.SetFocus;
    end;
end;

procedure TForm1.DoComand(str: string; var k: integer);
var s: string;
    usl: string;
    sc: integer;
begin
   if not execute then exit;
   ListBox1.ItemIndex := k;
   sleep(1000-(110-trackbar1.Position)*10);
   if (pos('ВПЕРЕД',str)>0) then MoveForward;
   if (pos('ВПРАВО',str)>0) then Rotate(1);
   if (pos('ВЛЕВО',str)>0) then Rotate(-1);
   if (pos('ПЫЛЕСОСИТЬ+',str)>0) then Clean(true) else
      if (pos('ПЫЛЕСОСИТЬ',str)>0) then Clean(false);
   if (pos('ИНАЧЕ',str)>0) then ElseHandler(k);
   if (pos('ЕСЛИ',str)>0) and (pos('КОНЕЦ',str)<=0) then ifHandler(k);
   // Цикл ПОВТОРИ
   if (pos('ПОВТОРИ',str)>0) and (pos('КОНЕЦ',str)<=0) then begin
      if inrepeat then begin
         Dec(repeatneed);
      end else begin
         str := ListBox1.Items.Strings[k];
         Delete(str,1,pos('ПОВТОРИ',str)+7);
         repeatneed := StrToInt(str); // Столько повторять
         inrepeat:=true;
      end;
      if repeatneed>0 then begin
         k:=k+1;
         str := ListBox1.Items.Strings[k];
         DoComand(str,k);
      end else begin
         k := repeatend+1;
         str := ListBox1.Items.Strings[k];
         DoComand(str,k);
      end;
   end;
   if (pos('КОНЕЦ ПОВТОРИ',str)>0) then begin
      repeatend := k;
      sc:=GetSpacesCount(str);
      s:='';
      while sc>0 do begin
         s:=s+' ';
         Dec(sc);
      end;
      s:=s+'ПОВТОРИ';
      Dec(k);
      while pos(s,ListBox1.Items.Strings[k])<>1 do Dec(k);
      str := ListBox1.Items.Strings[k];
      DoComand(str,k);
   end;
   // Цикл ПОКА
   if (pos('ПОКА',str)>0) and (pos('КОНЕЦ',str)<=0) then begin
      // выделим условие
      usl := ListBox1.Items.Strings[k];
      Delete(usl,1,pos('ПОКА',usl)+4);
      Delete(usl,length(usl)-5,6);
      if ExpressionResult(usl) then begin
         Inc(k);
         str := ListBox1.Items.Strings[k];
         DoComand(str,k);
      end else begin
         // Найдем конец
         sc:=GetSpacesCount(str);
         s:='';
         while sc>0 do begin
            s:=s+' ';
            Dec(sc);
         end;
         s:=s+'КОНЕЦ ПОКА';
         while pos(s,ListBox1.Items.Strings[k])<>1 do Inc(k);
         Inc(k);
         str := ListBox1.Items.Strings[k];
         DoComand(str,k);
      end;   
   end;
   if (pos('КОНЕЦ ПОКА',str)>0) then begin
      sc:=GetSpacesCount(str);
      s:='';
      while sc>0 do begin
         s:=s+' ';
         Dec(sc);
      end;
      s:=s+'ПОКА';
      Dec(k);
      while pos(s,ListBox1.Items.Strings[k])<>1 do Dec(k);
      str := ListBox1.Items.Strings[k];
      DoComand(str,k);
   end;
end;

procedure TForm1.SetButtonsState(state:boolean);
begin
  // в(ы)ключаем менюшки
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
  speedbutton9.Enabled:=state;
end;

procedure TForm1.SpeedButton8Click(Sender: TObject);
var k: integer;
begin
  if pylsc=0 then ShowMessage('А вы ничего не забыли? Пылесос например...')     // если пылесос не был добавлен, то делать ничего не надо
  else begin
  if AutoMode.Checked then begin
  // Автоматический режим
     if execute then begin
        execute := false;
        SpeedButton8.Caption := 'Продолжить';
        SpeedButton10.Enabled := true;
     end else begin
        SpeedButton8.Caption := 'Стоп';
        SpeedButton10.Enabled := false;
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
        SpeedButton8.Caption := 'Пуск';
        SpeedButton10.Enabled := true;
        SetButtonsState(true);
        execute:=false;
     end;
  end else begin
  // Пошаговый режим
     SpeedButton10.Enabled := true;
     k:=ListBox1.ItemIndex;
     execute:=true;
     DoComand(ListBox1.Items.Strings[k],k);
     execute:=false;
     Inc(k);
     ListBox1.ItemIndex := k;
  end;
  end;
end;

procedure TForm1.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key=13 then SpeedButton7.Click;
end;

procedure TForm1.SpeedButton9Click(Sender: TObject);
begin
   ListBox1.Items.Insert(ListBox1.ItemIndex,GetSpaces(ListBox1.ItemIndex-1)+'ВПРАВО');
end;

procedure TForm1.MoveForward;
var oldpos: TPylsPos;
begin
   // Двигаемся вперед
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
      if MessageDlg('Передвижение невозможно!'+#10#13+'Продолжить выполнение?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
   end;
end;

procedure TForm1.Rotate(angle: integer);
var rot: integer;
begin
   // Поворот
   rot := pylpos.rot;
   rot := rot+angle;
   rot := (rot+4) mod 4;
   pylpos.rot := rot;
   field[pylpos.x,pylpos.y].Rot := pylpos.rot;
   DrawField;
end;

procedure TForm1.Clean(plus: boolean);
var ppos_x,ppos_y: integer; // Где пылесосить
begin
   // Пылесосить, Пылесосить+
   ppos_x := pylpos.x;
   ppos_y := pylpos.y;
   // Определили где пылесосить
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
   if ((not(ppos_x in [1..fsize_w])) or (not(ppos_y in [1..fsize_h]))) then begin     // зря begin-end экономишь
      if MessageDlg('Нельзя пылесосить за границей поля!'+#10#13+'Продолжить выполнение?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
   end else begin
      case field[ppos_x,ppos_y].ElemT of
         RUBSH: field[ppos_x,ppos_y].ElemT := EMPTY;
         ePYLS: if MessageDlg('Не умею пылесосить пылесос!'+#10#13+'Продолжить выполнение?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
         eSTOL,eSTUL: {nothing};
         eSTOL+Offset,eSTUL+Offset: Dec(field[ppos_x,ppos_y].ElemT,Offset);
         eSHKAF,eDIVAN,eSHKAF+Offset,eDIVAN+Offset:
            if MessageDlg('Нельзя пылесосить под шкафом и под диваном!'+#10#13+'Продолжить выполнение?',mtError,[mbYes,mbNo],0)<>mrYes then execute:=false;
      end;
      DrawField;
   end;
end;

procedure TForm1.CodePopupMenu1Popup(Sender: TObject);
var tempstr:string;
begin
   N34.Enabled:=(not((ListBox1.ItemIndex=0) or (ListBox1.ItemIndex=ListBox1.Items.Count-1)));
   tempstr:=ListBox1.Items[ListBox1.ItemIndex];
   N37.Enabled:=(not boolean(pos('КОНЕЦ',tempstr))) and ( boolean(pos('ПОКА',tempstr))or boolean(pos('ПОВТОРИ',tempstr)) or boolean(pos('ЕСЛИ',tempstr)));
   // Скроем меню, если программа запущена
   n7.Visible:=not execute;
   n34.Visible:=not execute;
   n37.Visible:=not execute;
end;

// Цикл Повтори
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
   Delete(str,1,pos('ПОВТОРИ',str)+7);
   repeatneed := StrToInt(str); // Столько повторять
   n := StrToInt(str);
   Inc(k);
   ListBox1.ItemIndex := k;
{   // Сформируем список команд в цикле
   cmds := TStringList.Create;
   Inc(k);
   tk:=k;
   while pos('КОНЕЦ ПОВТОРИ',ListBox1.Items.Strings[k])=0 do begin
      cmds.Add(ListBox1.Items.Strings[k]);
      Inc(k);
   end;
   // Собственно выполнение цикла
   while i<n do begin
      for j:=0 to cmds.Count-1 do begin
         m:=j+tk;
         DoComand(cmds.Strings[j],m);
         Application.ProcessMessages;
      end;
      Inc(i);
   end;
   cmds.Destroy;}
end;

{Обработчики ИНАЧЕ и ЕСЛИ}
procedure TForm1.ElseHandler(var k: integer);
var count:integer;
begin
  count:=-1;
  while count<>0 do begin
    inc(k);
    if pos('КОНЕЦ ЕСЛИ',ListBox1.Items.Strings[k])<>0 then count:=count+1;
    if pos('ИНАЧЕ',ListBox1.Items.Strings[k])<>0 then count:=count-1;
  end;
end;

procedure TForm1.IFHandler(var k: integer);
var str: string;
    count:integer;
begin
   // выделим условие
   str := ListBox1.Items.Strings[k];
   Delete(str,1,pos('ЕСЛИ',str)+4);
   Delete(str,length(str)-2,3);
   // обработаем
   if (ExpressionResult(str)) then {ничего не делаем}
                              else begin
                                count:=-1;
                                while count<>0 do begin
                                  inc(k);
                                  if pos('ИНАЧЕ',ListBox1.Items.Strings[k])<>0 then count:=count+1;
                                  if pos('ЕСЛИ ',ListBox1.Items.Strings[k])<>0 then count:=count-1;
                                end;
                              end;

end;

{Обработчик цикла ПОКА}
procedure TForm1.WhileHandler(var k: integer);
var j: integer;
    m: integer;
    str: string;
    cmds: TStringList;
    tk: integer;
begin
   str := ListBox1.Items.Strings[k];
   // выделим условие
   Delete(str,1,pos('ПОКА',str)+4);
   Delete(str,length(str)-5,6);
   // Сформируем список команд в цикле
   cmds := TStringList.Create;
   Inc(k);
   tk:=k;
   while pos('КОНЕЦ ПОКА',ListBox1.Items.Strings[k])=0 do begin
      cmds.Add(ListBox1.Items.Strings[k]);
      Inc(k);
   end;
   // Собственно выполнение цикла
   while (ExpressionResult(str)) and (execute) do begin
      for j:=0 to cmds.Count-1 do begin
         m:=j+tk;
         DoComand(cmds.Strings[j],m);
         Application.ProcessMessages;
      end;
   end;
   cmds.Destroy;
end;

// Мышка бегает по форме
procedure TForm1.FormMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
   StatusBar1.Panels[0].Text := '';
end;

// Сохранить программу
procedure TForm1.N10Click(Sender: TObject);
begin
   with SaveDialog2 do
      if Execute then
         if FileName<>'' then begin
            ListBox1.Items.SaveToFile(FileName);
         end;   
end;

// Загрузить программу
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
   pylpos := backup_pylpos;
   field := backup_field;
   ListBox1.ItemIndex := 1;
   // Готовим цикл repeat
   repeatneed := 0;
   inrepeat := false;
   DrawField;
   if AutoMode.Checked then
      SpeedButton8.Caption := 'Пуск';
end;

// Сброс на выполнение сначала
procedure TForm1.SpeedButton11Click(Sender: TObject);
var k: integer;
begin
{   k:=ListBox1.ItemIndex;
   execute:=true;
   DoComand(ListBox1.Items.Strings[k],k);
   execute:=false;
   Inc(k);
   ListBox1.ItemIndex := k;}
   pylpos := backup_pylpos;
   field := backup_field;
   ListBox1.ItemIndex := 1;
   DrawField;
end;

// Сохранение проекта
procedure TForm1.N32Click(Sender: TObject);
var fstream: TFileStream;
//    psc,k: integer;
//    ps: string;
begin
   with SaveDialog3 do begin
      if Execute then begin
         if FileName<>'' then  begin
            // Сохраним скопом в файл
            try
               fstream := TFileStream.Create(FileName,fmOpenReadWrite);
            except
               fstream := TFileStream.Create(FileName,fmCreate);
            end;
            // Ширина
            fstream.WriteBuffer(fsize_w,SizeOf(Byte));
            // Высота
            fstream.WriteBuffer(fsize_h,SizeOf(Byte));
            // Поле
            fstream.WriteBuffer(field,SizeOf(TField));
            // Программа
            ListBox1.Items.SaveToStream(fstream);      
            // Заголовок
            Form1.Caption:='Пылесосик'+' - Проект '+ FileName;
            // Освободим память
            fstream.Free;
         end;
      end;
   end;
end;

procedure TForm1.N34Click(Sender: TObject);     // удаление
var key:word;
begin
  key:=46;
  ListBox1KeyDown(Sender,key,[]);
end;

procedure TForm1.CPClick3(Sender: TObject);
var tempstr:string;
begin
   if pos('ЕСЛИ',ListBox1.Items[ListBox1.ItemIndex])<>0 then
    ListBox1.Items[ListBox1.ItemIndex]:=(GetSpaces(ListBox1.ItemIndex)+'ЕСЛИ '+(Sender as TMenuItem).Caption+' ТО');
   if pos('ПОКА',ListBox1.Items[ListBox1.ItemIndex])<>0 then
    ListBox1.Items[ListBox1.ItemIndex]:=(GetSpaces(ListBox1.ItemIndex)+'ПОКА '+(Sender as TMenuItem).Caption+' ДЕЛАЙ');
   // мелкий фикс
   tempstr:=ListBox1.Items[ListBox1.ItemIndex];
   delete(tempstr,1,2);         
   ListBox1.Items[ListBox1.ItemIndex]:=tempstr;
end;

procedure TForm1.N37CLick(Sender: TObject);
var tempstr:string;
    i:integer;
    MyComp: TComponent;
begin                  
   // создаем резервную копию
   BackupListBox.Items:=ListBox1.Items;
   BackupListBox.ItemIndex:=ListBox1.ItemIndex;
   N7.Enabled:=true;

   tempstr:=ListBox1.Items[ListBox1.ItemIndex];

   for i:=14 to 27 do begin
      MyComp := FindComponent('N'+IntToStr(i)) as TMenuItem;
      TMenuItem(MyComp).OnClick := CPClick3;
      end;
   MyComp := FindComponent('N35') as TMenuItem;
   TMenuItem(MyComp).OnClick := CPClick3;
   MyComp := FindComponent('N36') as TMenuItem;
   TMenuItem(MyComp).OnClick := CPClick3;

   if (pos('ПОКА',tempstr)) <> 0 then begin
                                        ConditionsPopup.Popup(Mouse.CursorPos.X,Mouse.CursorPos.Y);
                                      end;

   if (pos('ПОВТОРИ',tempstr)) <> 0 then begin
                                           Delete(tempstr,1,pos('ПОВТОРИ',tempstr)+7);
                                           Edit1.Value:=strtoint(tempstr);
                                           Edit1.Show;
                                           Edit1.SetFocus;
                                         end;

   if (pos('ЕСЛИ',tempstr)) <> 0 then begin   
                                        ConditionsPopup.Popup(Mouse.CursorPos.X,Mouse.CursorPos.Y);
                                      end;
end;

// Загрузка проекта
procedure TForm1.N31Click(Sender: TObject);
var fstream: TFileStream;
    i,j: integer;
begin
   with OpenDialog3 do begin
      if Execute then begin
         if FileName<>'' then  begin
            try
               // Сохраним скопом в файл
               fstream := TFileStream.Create(FileName,fmOpenRead);
               // Ширина
               fstream.ReadBuffer(fsize_w,SizeOf(Byte));
               // Высота
               fstream.ReadBuffer(fsize_h,SizeOf(Byte));
               // Поле
               fstream.ReadBuffer(field,SizeOf(TField));
               for i:=1 to fsize_w do
                  for j:=1 to fsize_h do begin
                     // Отслеживаем количество пылесосов
                     if (field[i,j].ElemT=ePYLS) or (field[i,j].ElemT=ePYLS+Offset) then begin
                        pylpos.x:=i;
                        pylpos.y:=j;
                        pylpos.rot:=field[i,j].Rot;
                        Inc(pylsc);
                        if pylsc>=MaxPylsCount then InsertPyls.Enabled := false;
                     end;
                  end;   
               // Программа
               ListBox1.Items.LoadFromStream(fstream);
               // Заголовок
               Form1.Caption:='Пылесосик'+' - Проект '+ FileName;
               // Кнопки покажем
               SetButtonsState(true);
               // Перерисуем поле
               DrawField;
               // Освободим память
               fstream.Free;
            except
               MessageDlg('Ошибка при открытии файла с проектом',mtError,[mbOK],0);
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
   if (pos('Программа',str)>0) then Result:='  ' else
      if ((pos('ПОВТОРИ',str)>0) or (pos('ПОКА',str)>0) or (pos('ЕСЛИ',str)>0)
       or (pos('ИНАЧЕ',str)>0)) and (pos('КОНЕЦ',str)=0) then begin
         predsc:=max(pos('ПОВТОРИ',str),pos('ПОКА',str));
         predsc:=max(predsc,pos('ЕСЛИ',str));
         predsc:=max(predsc,pos('ИНАЧЕ',str));
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

procedure TForm1.RadioButton2Click(Sender: TObject);
begin
   SpeedButton8.Caption := 'Шаг';
   SpeedButton10.Enabled := false;
   ListBox1.ItemIndex := 1;
   backup_pylpos := pylpos;
   backup_field := field;
end;

procedure TForm1.AutoModeClick(Sender: TObject);
begin
   SpeedButton8.Caption := 'Пуск';
   SpeedButton10.Enabled := false;
end;

{Возвращает кол-во лидирующих пробелов}
function TForm1.GetSpacesCount(s: string): integer;
begin
   Result := 0;
   while s[1]=' ' do begin
      Inc(Result);
      Delete(s,1,1);
   end
end;

// На кнопочке рисуется статистика, количество грязных ячеек
procedure TForm1.Button2Click(Sender: TObject);
var DCount: integer;
    i,j: integer;
begin
   DCount:=0;
   for i:=1 to fsize_w do
      for j:=1 to fsize_h do
         if (field[i,j].ElemT-Offset)>=0 then Inc(DCount);
   Button2.Caption := IntToStr(DCount);      
end;

end.
