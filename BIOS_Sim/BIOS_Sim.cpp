#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <deque>
using namespace std;

enum Borders { LEFT_MAIN = 0,			RIGHT_MAIN = 91,			TOP_MAIN = 1,			BOTTOM_MAIN = 27,			RIGHT_SIDE = 129 };
enum Main	 { LEFT_MAIN_IN = 1,		RIGHT_MAIN_IN = 90,			TOP_MAIN_IN = 2,		BOTTOM_MAIN_IN = 26 };
enum Side    { LEFT_SIDE_IN = 92,		RIGHT_SIDE_IN = 128 };
enum Controls{ TOP_CONTROLS_IN = 28,	BOTTOM_BOTTOM_IN = 30 };
enum Colors  { BLUE_BG_WHITE_TEXT = 23, GREY_BG_BLACK_TEXT = 112 ,	GREY_BG_BLUE_TEXT = 121, CYAN_BG_BLACK_TEXT = 176,	CYAN_BG_WHITE_TEXT = 191};
enum Keys	 { LEFT_ARROW = 75,			F1 = 59,					RIGHT_ARROW = 77};
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

/// <summary>
/// Moving console handler around the console window.
/// </summary>
/// <param name="i">Needed X coord.</param>
/// <param name="j">Needed Y coord.</param>
void Goto(int i, int j) {
	SetConsoleCursorPosition(h, { (short)i, (short)j });
}
void print(int x, int y, int _char) {
	Goto(x, y);
	cout << unsigned char(_char);
}
void print(int _char) {
	cout << unsigned char(_char);
}

/// <summary>
/// Item of the menu class.
/// </summary>
class Item {
public:
	/// <summary>
	/// Name of the Item.
	/// </summary>
	string name;
	/// <summary>
	/// Index of the Item represents the number of the line on the screen from the top.
	/// </summary>
	int index;
	/// <summary>
	/// Empty default constructor. "name" member will be "default", "index" member will be 0.
	/// </summary>
	Item() : name("default"), index(0) {}
	/// <summary>
	/// Main class constructor.
	/// </summary>
	/// <param name="name">Desired name of the new Item.</param>
	/// <param name="i">Desired index of the new Item.</param>
	Item(string name, int i) : name(name), index(i) {}
	/// <summary>
	/// Outputs a name of the Item from the top of the console and offsets "default" parameter by 20 characters in the same line.
	/// </summary>
	void Show() {
		Goto(0, index);
		cout << name;
		Goto(20, index);
		cout << "default";
	}
	/// <summary>
	/// Outputs a name of the Item from the top of the console + indent and offsets "default" parameter by 40 characters in the same line.
	/// </summary>
	/// <param name="indent">Desired indent from the top of the console screen.</param>
	void Show(int indent) {
		Goto(LEFT_MAIN_IN, index + indent);
		cout << name;
		Goto(LEFT_MAIN_IN + 40, index + indent);
		cout << "default";
	}
};

/// <summary>
/// Top menu of the BIOS class.
/// </summary>
class Menu {
public:
	/// <summary>
	/// Displayed name of the manu.
	/// </summary>
	string name;
	/// <summary>
	/// IsSelected flag.
	/// </summary>
	bool selected = false;
	/// <summary>
	/// Items list.
	/// </summary>
	deque<Item> items;

	Menu() : name("default"), items(deque<Item>()), selected(false){	}
	Menu(string name) {
		this->name = name;
		items = deque<Item>();
	}

	void Setup(int index) {
		Goto(index, 0);
		if (selected)
		{
			SetConsoleTextAttribute(h, GREY_BG_BLUE_TEXT);
		}
		else {
			SetConsoleTextAttribute(h, BLUE_BG_WHITE_TEXT);
		}
		for (int i = 0; i < (15 - name.length()) / 2; i++) { cout << ' '; }
		cout << name;
		for (int i = 0; i < (15 - name.length()) / 2; i++) { cout << ' '; }
		SetConsoleTextAttribute(h, 121);
	}

	void Show() {
		SetConsoleTextAttribute(h, GREY_BG_BLUE_TEXT);
		for (int i = 0; i < items.size(); i++) {
			items.at(i).Show(2);
		}
		SetConsoleTextAttribute(h, BLUE_BG_WHITE_TEXT);
	}
	operator bool() { return name.length(); }
};

void ClearMain() {
	Goto(LEFT_MAIN_IN, TOP_MAIN_IN);
	for (int i = TOP_MAIN_IN; i < BOTTOM_MAIN_IN + TOP_MAIN_IN; i++)
	{
		for (int j = 0; j < RIGHT_MAIN_IN; j++)
		{
			cout << ' ';
		}
		Goto(LEFT_MAIN_IN, i);
	}
}
void ClearSide() {
	Goto(LEFT_SIDE_IN, TOP_MAIN_IN);
	for (int i = TOP_MAIN_IN; i < BOTTOM_MAIN_IN + TOP_MAIN_IN; i++)
	{
		for (int j = LEFT_SIDE_IN; j < RIGHT_SIDE_IN + 1; j++)
		{
			cout << ' ';
		}
		Goto(LEFT_SIDE_IN, i);
	}
}
void ClearControls() {
	SetConsoleTextAttribute(h, CYAN_BG_WHITE_TEXT);
	Goto(LEFT_MAIN, TOP_CONTROLS_IN);
	for (int i = TOP_CONTROLS_IN; i < BOTTOM_BOTTOM_IN + TOP_CONTROLS_IN; i++)
	{
		for (int j = LEFT_MAIN; j < RIGHT_SIDE + 1; j++)
		{
			cout << ' ';
		}
		Goto(LEFT_MAIN, i);
	}
}
void DrawBG() {
	SetConsoleTextAttribute(h, BLUE_BG_WHITE_TEXT);
	Goto(LEFT_MAIN, 0);
	for (int i = LEFT_MAIN; i < RIGHT_SIDE_IN + 2; i++){ cout << ' '; }
	SetConsoleTextAttribute(h, GREY_BG_BLUE_TEXT);
	ClearMain();
	ClearSide();
	ClearControls();
}
void DrawGrid() {
	SetConsoleTextAttribute(h, GREY_BG_BLACK_TEXT);
		print(LEFT_MAIN,		TOP_MAIN,		218);
		print(RIGHT_MAIN,		TOP_MAIN,		194);
		print(LEFT_MAIN,		BOTTOM_MAIN,	192);
		print(RIGHT_MAIN,		BOTTOM_MAIN,	193);
		print(RIGHT_SIDE,		TOP_MAIN,		191);
		print(RIGHT_SIDE,		BOTTOM_MAIN,	217);

	for (int i = 1; i < RIGHT_MAIN; i++) {
		print(i,				TOP_MAIN,		196);
		print(i,				BOTTOM_MAIN,	196);
	}
	for (int i = 1; i < RIGHT_SIDE - RIGHT_MAIN; i++)
	{
		print(i + RIGHT_MAIN,	TOP_MAIN,		196);
		print(i + RIGHT_MAIN,	BOTTOM_MAIN,	196);
	}
	for (int i = 2; i < BOTTOM_MAIN; i++){
		print(LEFT_MAIN,		i,				179);
		print(RIGHT_MAIN,		i,				179);
		print(RIGHT_SIDE,		i,				179);
	}
}
void DrawControls(string key, string description) {
	SetConsoleTextAttribute(h, CYAN_BG_WHITE_TEXT);
	cout << key << "\t";
	SetConsoleTextAttribute(h, CYAN_BG_BLACK_TEXT);
	cout << description;
}
void UpdateControls() {
	Goto(130 / 4 * 0, TOP_CONTROLS_IN);
	DrawControls("   F1", "Hepl");
	Goto(130 / 4 * 0, TOP_CONTROLS_IN + 1);
	DrawControls("   ESC", "Exit");

	Goto(130 / 4 * 1, TOP_CONTROLS_IN);
	DrawControls("UP/DOWN  ", "Select Item");
	Goto(130 / 4 * 1, TOP_CONTROLS_IN + 1);
	DrawControls("LEFT/RIGHT", "Exit");

	Goto(130 / 4 * 2, TOP_CONTROLS_IN);
	DrawControls("+/-", "Change Values");
	Goto(130 / 4 * 2, TOP_CONTROLS_IN + 1);
	DrawControls("Enter", "Select > Sub Menu");

	Goto(130 / 4 * 3, TOP_CONTROLS_IN);
	DrawControls("F9", "Setup Defaults");
	Goto(130 / 4 * 3, TOP_CONTROLS_IN + 1);
	DrawControls("F10", "Save and Exit");
}

deque<Menu> menues;

void UpdateHeadMenu() {
	SetConsoleTextAttribute(h, GREY_BG_BLACK_TEXT);
	int n = 6;
	for (int i = 0; i < n; i++) {
		menues[i].Setup(i * 15);
	}
}

int main()
{	
	system("chcp 437");
	system("cls");
	DrawBG();

	menues.push_back(Menu("Main"));
	menues.push_back(Menu("Advanced"));
	menues.push_back(Menu("Security"));
	menues.push_back(Menu("Power"));
	menues.push_back(Menu("Boot"));
	menues.push_back(Menu("Exit"));

	menues[0].selected = true;

	menues[0].items.push_back(Item("System Time", 0));
	menues[0].items.push_back(Item("System Date", 1));
	menues[0].items.push_back(Item("Legacy Diskette A", 2));
	menues[0].items.push_back(Item("Legacy Diskette B", 3));
	menues[0].items.push_back(Item("Floppy 3 Mode Support", 4));

	menues[1].items.push_back(Item("CPU Speed", 0));
	menues[1].items.push_back(Item("CPU: System Frequency Multiple", 1));
	menues[1].items.push_back(Item("System/PCI Frequency (Mhz)", 2));
	menues[1].items.push_back(Item("System /SDRAM Frequency Ratio", 3));
	menues[1].items.push_back(Item("Load Performance Setting", 4));
	
	menues[3].items.push_back(Item("Power Management", 0));
	menues[3].items.push_back(Item("Video Off Option", 1));
	menues[3].items.push_back(Item("Video Off Method", 2));
	menues[3].items.push_back(Item("HDD Power Down", 3));
	menues[3].items.push_back(Item("Suspend-RAM Capability", 4));

	menues[4].items.push_back(Item("1. IDE Hard Drive", 0));
	menues[4].items.push_back(Item("2. ATAPI CD-ROM", 1));
	menues[4].items.push_back(Item("3. Removable Device", 2));
	menues[4].items.push_back(Item("4. Other Boot Device", 3));
	
	menues[5].items.push_back(Item("Exit Saving Changes", 0));
	menues[5].items.push_back(Item("Exit Discarding Changes", 1));
	menues[5].items.push_back(Item("Load Setup Defaults", 2));
	menues[5].items.push_back(Item("Discard Changes", 3));
	menues[5].items.push_back(Item("Save Changes", 4));
		
	UpdateHeadMenu();
	UpdateControls();
	DrawGrid();
	int m = 0;
	menues[0].Show();
	Goto(menues[0].name.length(), 0);

	while (true) {
		
		int keycode = _getch();
		if (keycode == RIGHT_ARROW)
		{
			if (m <= 4)
			{
				m++;
				menues[m - 1].selected = false;
				menues[m].selected = true;
				ClearMain();
				menues[m].Show();
			}
		}
		else if (keycode == LEFT_ARROW) {
			if (m >= 1)
			{
				m--;
				menues[m + 1].selected = false;
				menues[m].selected = true;
				ClearMain();
				menues[m].Show();
			}
		}
		UpdateHeadMenu();
		DrawGrid();
	}
	
}
