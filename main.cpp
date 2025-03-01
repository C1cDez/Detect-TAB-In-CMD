#include <iostream>
#include <string>
#include <windows.h>

//Macro to print ANSI easily 
#define ANSI(code) ((char) 0x1b) << "[" << (code)

//Gets pressed key (I stole this code)
int GetKey()
{
	INPUT_RECORD InputRecord;
	DWORD Writtten;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	
	while (true)
	{
	    ReadConsoleInputA(hStdIn, &InputRecord, 1, &Writtten);
	    if (InputRecord.EventType == KEY_EVENT && InputRecord.Event.KeyEvent.bKeyDown) break;
	}
	return InputRecord.Event.KeyEvent.wVirtualKeyCode;
}

//Waiting for key press
int WaitKey()
{
	int key = 0;
	while (true)
	{
		key = GetKey();
		if (key) break;   //If key != 0x00
	}
	return key;
}

//Prints possible variants and highlights 'selected'
void printVars(std::string *variants, int const count, int selected)
{
	for (int i = 0; i < count; i++)
	{
		if (i == selected) 
			std::cout << ANSI("47m") << ANSI("30m");   //Turn on white background and black foreground
		std::cout << variants[i] << ANSI("0m\n");
	}
}

//Removes previously printed lines
void clear(int linesUp)
{
	for (int i = 0; i < linesUp; i++)
		std::cout << ANSI("F") << ANSI("0K");
}

//Main
int main()
{
	using namespace std;

	cout << "Hi! How are you?\n";

	//Possible variants
	int const varc = 4;
	string variants[varc] = {"Fine", "OK", "Nah", "Bad"};

	//Selected variant
	int selected = -1;   //If selected = -1, then 'printVars' doesn't highlight anything
	printVars(variants, varc, selected);

	//Infinite loop
	while (true)
	{
		int key = WaitKey();

		//Checks which key was pressed
		if (key == VK_RETURN)    //VK_RETURN is the ID of Enter
		{
			clear(varc);
			printVars(variants, varc, -1);
			break;   //Exit infinite loop
		}
		if (key == VK_TAB)
		{
			selected = (selected + 1) % varc;   //Choose the next option (selected++)
			clear(varc);
			printVars(variants, varc, selected);
		}
	}

	//Possible answers
	string answers[varc] = {
		"That's good!", "Normal", "But it's fair", "What happened?"
	};

	if (selected == -1) cout << "You didn't select the option!\n";
	else cout << "------\n" << answers[selected] << "\n";

	return 0;
}
