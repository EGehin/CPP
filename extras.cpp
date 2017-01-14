#include <windows.h>
#include "extras.h"
#include <iostream>
#include <string>

using namespace std;

void extras::textColour(char c){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (c == 'p') //pink
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY ));
	else if (c== 'g') //green
	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY ));	
	else if (c=='b') //blue
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_INTENSITY ));	
	else if (c=='r')
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY ));	

	else if (c == 't') //reset
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));

}

void extras::clearCMD(){
	cout << string(50, '\n');
}