{===============================================}
{= �������� ��������������� �����������        =}
{= ����������� ����������� "���������"         =}
{= ������: ������� �������� (NT)...            =}
{= ����: 2008.02.06                            =}
{= ������� ������:                             =}
{= *08.02.07                                   =}
{=  + ������ � ��������� (NT)                  =}
{=  + ����������� �� ���������� ��������� (NT) =}
{= *08.02.06                                   =}
{=  + �������� ������� ����� ����������� (NT)  =}
{=  + ������������ ��������, ����������� ����  =}
{=    � ���� (NT)                              =}
{===============================================}

program Pylesos;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  AboutUnit in 'AboutUnit.pas' {Form2};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
