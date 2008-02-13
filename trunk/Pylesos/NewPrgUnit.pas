unit NewPrgUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm3 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation

uses Unit1;

{$R *.dfm}

procedure TForm3.BitBtn1Click(Sender: TObject);
begin
   ProgName := Edit1.Text;
   Form3.Close;
end;

procedure TForm3.BitBtn2Click(Sender: TObject);
begin
   ProgName := '###NewProgramCanceled';
   Form3.Close;
end;

procedure TForm3.FormCreate(Sender: TObject);
begin
   ProgName := '###NewProgramCanceled';
end;

end.
