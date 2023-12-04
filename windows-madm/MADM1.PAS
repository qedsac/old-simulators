unit Madm1;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, Menus, ExtCtrls, StdCtrls, Mabout;

type
  TForm1 = class(TForm)
	RunButton: TButton;
	StopButton: TButton;
    StepButton: TButton;
    ClearButton: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    A_Display: TImage;
	C_Display: TImage;
	S_Display: TImage;
    MainMenu1: TMainMenu;
    OpenDialog1: TOpenDialog;
	SaveDialog1: TSaveDialog;
    File1: TMenuItem;
    Load1: TMenuItem;
    Save1: TMenuItem;
    SaveAs1: TMenuItem;
    N1: TMenuItem;
    Exit1: TMenuItem;
    Help1: TMenuItem;
    About1: TMenuItem;
	Print1: TMenuItem;
	procedure About1Click(Sender: TObject);
	procedure RunButtonClick(Sender: TObject);
	procedure Exit1Click(Sender: TObject);
	procedure FormCreate(Sender: TObject);
	procedure FormShow(Sender: TObject);
	procedure Load1Click(Sender: TObject);
	procedure Save1Click(Sender: TObject);
	procedure SaveAs1Click(Sender: TObject);
	procedure ClearButtonClick(Sender: TObject);
	procedure StopButtonClick(Sender: TObject);
	procedure StepButtonClick(Sender: TObject);
	procedure Print1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

type
	TTube = class
	private
		canvas: Tcanvas;
	public
		lastline: 0..31;
		Line: array[0..31] of longint; {can't have dynamic size}
		procedure setup(n: integer; c: Tcanvas);
		procedure clear;
		procedure show;
		procedure save(var f: text);
		procedure showline(n: integer);
	end;
const
	A_LINE = 0;
	CI_LINE = 0;
	PI_LINE = 1;
var
	currentfile: Tfilename;
	Accumulator, Control, Store: TTube;
	status: (Stopped, Running, Manual);
	timing: boolean;
const
	FUNC_BITS = 3;
	MAX_FUNC = (not((not 0) shl FUNC_BITS));
	ADDR_BITS = 13;
	UNUSED_ADDR_BITS = 8;
	MAX_ADDR = (not((not 0) shl (ADDR_BITS-UNUSED_ADDR_BITS)));
type
	addr = 0..MAX_ADDR;
	func = 0..MAX_FUNC;

procedure execute;
var s: addr; f: func; msg: Tmsg;
begin
	repeat
		with Control do begin
			inc(Line[CI_LINE]);
			Line[PI_LINE] := Store.Line[Line[CI_LINE] and MAX_ADDR];
			show;
			s := Line[PI_LINE] and MAX_ADDR;
			f := (Line[PI_LINE] shr ADDR_BITS) and MAX_FUNC;
		end;
		case f of
		0:		   	{jump}
			with Control do begin
				Line[CI_LINE] := Store.Line[s];
				showline(CI_LINE);
			end;
		1:  		{relative jump}
			with Control do begin
				inc(Line[CI_LINE], Store.Line[s]);
				showline(CI_LINE);
			end;
		2:  		{load negative}
			with Accumulator do begin
				Line[A_LINE] := -Store.Line[s];
				showline(A_LINE);
			end;
		3:  		{store accumulator}
			with Store do begin
				Line[s] := Accumulator.Line[A_LINE];
				showline(s);
			end;
		4,
		5:  		{subtract; 5 undocumented}
			with Accumulator do begin
				dec(Line[A_LINE], Store.Line[s]);
				showline(A_LINE);
			end;
		6:  		{test}
			if Accumulator.Line[A_LINE] < 0 then with Control do begin
				inc(Line[CI_LINE]);
				showline(CI_LINE);
			end;
		7:  		{stop}
			begin
				status := Stopped
			end;
		end;
		{allow other apps to run}
		while PeekMessage(msg, 0, 0, 0, PM_REMOVE) do begin
			if msg.message = WM_QUIT then Halt;
			TranslateMessage(msg);
			DispatchMessage(msg);
		end;
	until status <> Running;
end;

procedure TForm1.About1Click(Sender: TObject);
begin
	AboutBox.Show;
end;

procedure TForm1.RunButtonClick(Sender: TObject);
var t1, t2: TDateTime;
begin
	status := Running;
	RunButton.Enabled := false;
	StepButton.Enabled := false;
	ClearButton.Enabled := false;
	t1 := Time;
	execute;
	if timing then begin
		t2 := Time;
		showmessage('Started: '+timetostr(t1)+'; stopped: '+timetostr(t2));
	end;
	RunButton.Enabled := true;
	StepButton.Enabled := true;
	ClearButton.Enabled := true;
end;

procedure TForm1.Exit1Click(Sender: TObject);
begin
	Halt;
end;

procedure TForm1.FormCreate(Sender: TObject);
var b1, b2, b3: TBitmap;
begin
	b1 := Tbitmap.Create;
	b2 := Tbitmap.Create;
	b3 := Tbitmap.Create;
	b1.width := 265; b2.width := 265; b3.width := 265;
	b1.height := 17; b2.height := 25; b3.height := 265;
	A_Display.Picture.Graphic := b1;
	C_Display.Picture.Graphic := b2;
	S_Display.Picture.Graphic := b3;
end;

procedure clean_line(var s: string);
var i: integer;
begin
	s := s + '#';	{sentinel}
	i := 1;
	{strip leading whitespace}
	while s[i] in [' ', chr(9)] do inc(i);
	delete(s,1,i-1);
end;

procedure settube(s:string; var tube: TTube; var line: integer);
var i: integer;
begin
	case UpCase(s[1]) of
	'A': tube := Accumulator;
	'C': tube := Control;
	'S': tube := Store;
	end;
	delete(s,1,1);
	i :=1; while s[i] in ['0'..'9'] do inc(i);
	delete(s,i,maxint);		{get rid of non-digits}
	line := strtointdef(s,0) mod succ(tube.lastline);
end;

function getnumber(const s: string): longint;
var i: integer;
begin
	{get to end of number for backwards binary}
	i := 1; while s[i] in ['0', '1'] do inc(i);
	dec(i);		{went one too far}
	result := 0;
	while i > 0 do begin
		result := result shl 1;
		inc(result, ord(s[i]) - ord('0'));
		dec(i);
	end;
end;

{pretty robust(?), but will accept almost anything, even garbage}
procedure doload(const fname: string);
var f: text; s: string; currtube: TTube; currline: integer;
begin
	assign(f, fname);
	reset(f);
	currtube := Store;
	currline := 0;
	while not eof(f) do begin
		readln(f, s);
		clean_line(s);
		case UpCase(s[1]) of
		'#':			{ignore comments and blank lines}
			continue;
		'A', 'C', 'S':	{process tube name}
			settube(s, currtube, currline);
		else
			begin
				currtube.Line[currline] := getnumber(s);
				currtube.showline(currline);
				currline := succ(currline) mod succ(currtube.lastline)
			end;
		end;
	end;
	CloseFile(f);
end;

procedure TForm1.FormShow(Sender: TObject);
var i: integer;
begin
	with A_Display.Canvas do begin
		Pen.Color := clWhite;
		Brush.Color := clBlack;
		FloodFill(10, 10, clWhite, fsSurface);
	end;
	with C_Display.Canvas do begin
		Pen.Color := clWhite;
		Brush.Color := clBlack;
		FloodFill(10, 10, clWhite, fsSurface);
	end;
	with S_Display.Canvas do begin
		Pen.Color := clWhite;
		Brush.Color := clBlack;
		FloodFill(10, 10, clWhite, fsSurface);
	end;
	Accumulator.setup(1, A_Display.Canvas);
	Control.setup(2, C_Display.Canvas);
	Store.setup(32, S_Display.Canvas);
	for i := 1 to paramcount do begin
		if paramstr(i) = '-t' then timing := true
		else if paramstr(i)[1] <> '-' then currentfile := paramstr(1);
	end;
	if (currentfile <> '') and FileExists(currentfile) then doload(currentfile);
end;

procedure TForm1.Load1Click(Sender: TObject);
begin
	if opendialog1.execute then begin
		currentfile := opendialog1.filename;
		doload(currentfile);
	end;
end;

procedure saveline(var f: text; val: longint);
begin
	repeat
		if odd(val) then write(f, '1')
		else write(f, '0');
		val := val shr 1;
	until val = 0;
	writeln(f);
end;

procedure TTube.save(var f: text);
var i: integer;
begin
	for i := 0 to lastline do
		saveline(f, Line[i]);
end;

procedure dosave(const fname: string);
var f: text;
begin
	assign(f, fname);
	rewrite(f);
	writeln(f, 'A:'); Accumulator.save(f);
	writeln(f, 'C:'); Control.save(f);
	writeln(f, 'S:'); Store.save(f);
    CloseFile(f);
end;

procedure TForm1.Save1Click(Sender: TObject);
begin
	if currentfile = '' then SaveAs1Click(Sender)
	else dosave(currentfile);
end;

procedure TForm1.SaveAs1Click(Sender: TObject);
begin
	if savedialog1.execute then begin
		currentfile := savedialog1.filename;
		dosave(currentfile);
	end;
end;

procedure TForm1.ClearButtonClick(Sender: TObject);
begin
	Accumulator.clear; Control.clear; Store.clear;
end;

procedure TTube.showline(n:integer);
var j: integer; val: longint;
begin
	j := 9; val := Line[n];
	n := succ(n) shl 3;
	while j <= 257 do with canvas do begin
		moveto(j, n);
		if odd(val) then pen.color := clWhite
		else pen.color := clBlack;
		lineto(j+3, n);
		val := val shr 1;
		inc(j, 8);
	end;
end;

procedure TTube.setup(n: integer; c: Tcanvas);
var i, j, k, m: integer;
begin
	lastline := pred(n);
	canvas := c;
	clear;
	{set dots}
	for i := 1 to n do with c do begin
		j := 7;
		m := i shl 3;
		pen.color := clWhite;
		for k := 0 to 31 do begin
			moveto(j,m);
			lineto(j+2, m);
			inc(j, 8);
		end;
	end;
end;

procedure TTube.clear;
var i: integer;
begin
	for i := 0 to lastline do
		Line[i] := 0;
	show;
end;

Procedure TTube.show;
var i: integer;
begin
	for i := 0 to lastline do
		showline(i);
end;


procedure TForm1.StopButtonClick(Sender: TObject);
begin
	status := Stopped;
end;

procedure TForm1.StepButtonClick(Sender: TObject);
begin
	Status := Manual;
	execute;
end;

procedure TForm1.Print1Click(Sender: TObject);
begin
	Print;
end;

initialization
	timing := false;
	currentfile := '';
	status := Stopped;
    NEW(Accumulator); NEW(Control); NEW(Store);
end.

