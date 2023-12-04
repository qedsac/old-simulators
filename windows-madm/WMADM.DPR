program Wmadm;

uses
  Forms,
  Madm1 in 'MADM1.PAS' {Form1},
  Mabout in 'MABOUT.PAS' {AboutBox};

{$R *.RES}

begin
  Application.Title := 'Baby Mark I';
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.Run;
end.
