{===============================================}
{= Пермский Государственный Университет        =}
{= Графический исполнитель "Пылесосик"         =}
{= Авторы: Николай Трубинов (NT)...            =}
{=         Николай Козаченко                   =}
{===============================================}

program Pylesos;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  AboutUnit in 'AboutUnit.pas' {Form2},
  NewPrgUnit in 'NewPrgUnit.pas' {Form3};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.CreateForm(TForm3, Form3);
  Application.Run;
end.
