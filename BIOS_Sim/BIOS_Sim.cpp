#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

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
		Goto(1, index + indent);
		cout << name;
		Goto(40, index + indent);
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
	/// Length of the name of the Menu.
	/// </summary>
	int x = 0;
	/// <summary>
	/// Items list.
	/// </summary>
	Item* items;
	/// <summary>
	/// Length of the items list.
	/// </summary>
	int items_length;

	Menu() : name("default"), items(nullptr), items_length(0){}
	Menu(string name) {
		this->name = name;
		this->x = name.length();
	}

	void Setup(int index) {
		Goto(index, 0);
		if (selected)
		{
			SetConsoleTextAttribute(h, 121);
		}
		else {
			SetConsoleTextAttribute(h, 23);
		}
		cout << name;
		SetConsoleTextAttribute(h, 121);
	}

	void Show() {
		Goto(1, 3);
		SetConsoleTextAttribute(h, 121);
		for (int i = 0; i < items_length; i++) {
			items[i].Show(2);
		}
		SetConsoleTextAttribute(h, 23);
	}
};

void Clear() {
	Goto(1, 2);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 91; j++)
		{
			cout << ' ';
		}
		cout << '\n';
	}
}

Menu * menues = new Menu[6];

enum { LEFT_MAIN = 0, RIGHT_MAIN = 91, TOP_MAIN = 1, BOTTOM_MAIN = 27, RIGHT_SIDE = 128 };

void DrawBG() {
	SetConsoleTextAttribute(h, 23);
	Goto(LEFT_MAIN, 0);
	for (int i = LEFT_MAIN; i < 129; i++)
	{
		cout << ' ';
	}
	SetConsoleTextAttribute(h, 121);
	Goto(TOP_MAIN, 2);
	for (int i = LEFT_MAIN; i < RIGHT_SIDE * BOTTOM_MAIN; i++)
	{
		cout << ' ';
	}
}

void DrawGrid() {
	SetConsoleTextAttribute(h, 112);
	print(LEFT_MAIN,	TOP_MAIN,		218);
	print(RIGHT_MAIN,	TOP_MAIN,		194);
	print(LEFT_MAIN,	BOTTOM_MAIN,	192);
	print(RIGHT_MAIN,	BOTTOM_MAIN,	193);
	print(RIGHT_SIDE,	TOP_MAIN,		191);
	print(RIGHT_SIDE,	BOTTOM_MAIN,	217);

	for (int i = 1; i < RIGHT_MAIN; i++) {
		print(i, TOP_MAIN,		196);
		print(i, BOTTOM_MAIN,	196);
	}
	for (int i = 1; i < 37; i++)
	{
		print(i + RIGHT_MAIN, TOP_MAIN,		196);
		print(i + RIGHT_MAIN, BOTTOM_MAIN,	196);
	}
	for (int i = 2; i < 26; i++){
		print(LEFT_MAIN,	i,	179);
		print(RIGHT_MAIN,	i,	179);
		print(RIGHT_SIDE,	i,	179);
	}
}

void UpdateHeadMenu() {
	cout << '\n';
	SetConsoleTextAttribute(h, 121);
	int n = 6;
	for (int i = 0; i < n; i++) {
		menues[i].Setup(i * 15);
	}
}

int main()
{	
	//Needed serious refactoring!!!
	system("chcp 437");
	system("cls");
	DrawBG();

	Menu m1 = Menu("Main");
	Menu m2 = Menu("Advanced");
	Menu m25 = Menu("Security");
	Menu m3 = Menu("Power");
	Menu m4 = Menu("Boot");
	Menu m5 = Menu("Exit");

	m1.selected = true;

	Item items[5] = {Item("System Time", 0), Item("System Date",1), Item("Legacy Diskette A",2), Item("Legacy Diskette B", 3), Item("Floppy 3 Mode Support", 4)};
	m1.items = items;
	m1.items_length = 5;

	Item items2[5] = { Item("CPU Speed", 0), Item("CPU: System Frequency Multiple",1), Item("System/PCI Frequency (Mhz)",2), Item("System /SDRAM Frequency Ratio", 3), Item("Load Performance Setting", 4) };
	m2.items = items2;
	m2.items_length = 5;

	Item items3[5] = { Item("Power Management", 0), Item("Video Off Option",1), Item("Video Off Method",2), Item("HDD Power Down", 3), Item("Suspend-RAM Capability", 4) };
	m3.items = items3;
	m3.items_length = 5;

	Item items4[4] = { Item("1. IDE Hard Drive", 0), Item("2. ATAPI CD-ROM",1), Item("3. Removable Device",2), Item("4. Other Boot Device", 3) };
	m4.items = items4;
	m4.items_length = 4;

	Item items5[5] = { Item("Exit Saving Changes", 0), Item("Exit Discarding Changes",1), Item("Load Setup Defaults",2), Item("Discard Changes", 3), Item("Save Changes", 4)};
	m5.items = items5;
	m5.items_length = 5;

	menues[0] = m1;
	menues[1] = m2;
	menues[2] = m25;
	menues[3] = m3;
	menues[4] = m4;
	menues[5] = m5;
	
	UpdateHeadMenu();

	int m = 0;
	menues[0].Show();
	Goto(menues[0].x, 0);

	while (true) {
		
		int keycode = _getch();
		if (keycode == 77) //right arrow
		{
			if (m <= 4)
			{
				m++;
				menues[m - 1].selected = false;
				menues[m].selected = true;
				Clear();
				menues[m].Show();
				Goto(m * 15 + menues[m].x, 0);
			}
		}
		else if (keycode == 75) { //left arrow
			if (m >= 1)
			{
				m--;
				menues[m + 1].selected = false;
				menues[m].selected = true;
				Clear();
				menues[m].Show();
				Goto(m * 15 + menues[m].x, 0);
			}
		}
		UpdateHeadMenu();
		DrawGrid();
	}
	
}
