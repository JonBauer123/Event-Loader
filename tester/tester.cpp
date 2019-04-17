// tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <process.h>
#include <TlHelp32.h>
#include <vector>
#include <tchar.h>

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
*/
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

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_SHOW);

	printf("Beginning Testing ...\n");

	killExplorer();

	printf("End Testing\n");

	return 0;
}