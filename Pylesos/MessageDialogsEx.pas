unit MessageDialogsEx;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm4 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Label1: TLabel;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }   
    Result:boolean;
  end;

var
  Form4: TForm4;

implementation

{$R *.dfm}

procedure TForm4.Button1Click(Sender: TObject);
begin
result:=false;
Form4.Close;
end;

procedure TForm4.Button2Click(Sender: TObject);
begin
result:=true;
Form4.Close;
end;

procedure TForm4.FormShow(Sender: TObject);
begin
result:=false;
end;

end.
