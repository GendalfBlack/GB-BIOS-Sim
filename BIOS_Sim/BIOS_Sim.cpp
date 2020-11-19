#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

/// <summary>
/// Moving console handler around the console window.
/// </summary>
/// <param name="i">Needed X coord.</param>
/// <param name="j">Needed Y coord.</param>
void Goto(int i, int j) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)i, (short)j });
}

/// <summary>
/// Item of the menu class.
/// </summary>
class Item {
public:
	/// <summary>
	/// Name of the Item.
	/// </summary>
	const char* name;
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
	Item(const char* name, int i) : name(name), index(i) {}
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
		Goto(0, index + indent);
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
	const char* name;
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

	void Show() {
		Goto(0, 2);
		for (int i = 0; i < items_length; i++) {
			items[i].Show(2);
		}
	}
};

void Clear() {
	Goto(0, 2);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 91; j++)
		{
			cout << ' ';
		}
		cout << '\n';
	}
}

int main()
{	
	//Needed serious refactoring!!!
	setlocale(LC_ALL, "ru");
	
	Menu m1 = Menu();
	Menu m2 = Menu();
	Menu m25 = Menu();
	Menu m3 = Menu();
	Menu m4 = Menu();
	Menu m5 = Menu();

	m1.name = "Main";
	m2.name = "Advanced";
	m25.name = "Security";
	m3.name = "Power";
	m4.name = "Boot";
	m5.name = "Exit";
	m1.x = 4;
	m2.x = 8;
	m25.x = 8;
	m3.x = 5;
	m4.x = 4;
	m5.x = 4;
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

	Menu menues[6] = { m1,m2,m25,m3,m4,m5 };
	int n = 6;
	for (int i = 0; i < n; i++) {
		Goto(i * 15, 0);
		cout << menues[i].name;
	}
	cout << '\n';
	for (int i = 0; i < 91; i++) { cout << '-'; }

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
	}
	
}
