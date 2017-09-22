#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <direct.h>

using namespace std;


bool CheckStorage(const DWORDLONG diskSpaceNeeded);

bool IsOnlyInstance(LPCTSTR gameTitle);

bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);

DWORD ReadCPUSpeed();

void ReadCPUArchitecture();

DWORDLONG GetPhysicalMem();

DWORDLONG GetVirtualMem();

DWORD ReadCPUSpeed();

int main()
{

	LPCTSTR gameTitle = "Project Low Brow";

	if (IsOnlyInstance(gameTitle))
	{
		cout << "This is the only instance running!" << endl;
	}
	else
	{
		cout << "Multiple instances detected!!!" << endl;
	}

	cout << "Physical Memory: " << GetPhysicalMem() << endl;

	cout << "Virtual Memory: " << GetVirtualMem() << endl;

	cout << "CPU Speed: " << ReadCPUSpeed() << endl;

	ReadCPUArchitecture();

	system("pause");
}

bool IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			cout << "Game cannot run!" << endl;
			return false;
		}
	}
	cout << "Game running!" << endl;
	return true;
}

bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	LPCTSTR         lpDirectoryName = nullptr;
	PULARGE_INTEGER lpFreeBytesAvailable;
	PULARGE_INTEGER lpTotalNumberOfBytes;
	PULARGE_INTEGER lpTotalNumberOfFreeBytes;

	//GetDiskFreeSpaceEx(lpDirectoryName, &lpFreeBytesAvailable, &lpTotalNumberOfBytes, &lpTotalNumberOfBytes);
	return true;
}


DWORDLONG GetPhysicalMem()
{
	MEMORYSTATUSEX status;

	status.dwLength = sizeof(status);

	GlobalMemoryStatusEx(&status);

	return status.ullAvailPhys;
}

DWORDLONG GetVirtualMem()
{
	MEMORYSTATUSEX vStatus;

	vStatus.dwLength = sizeof(vStatus);

	GlobalMemoryStatusEx(&vStatus);

	return vStatus.ullAvailVirtual;
}

DWORD ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMhz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~Mhz", NULL, &type, (LPBYTE)&dwMhz, &BufSize);
	}
	return dwMhz;
}

void ReadCPUArchitecture()
{
	DWORD BufSize;
	char CharBuf[256];
	DWORD dwMhz = 0;
	DWORD type = REG_SZ;
	HKEY hKey;
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	lError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &type, (LPBYTE)&CharBuf, &BufSize);

	if (lError == ERROR_SUCCESS)
	{
		while (lError == ERROR_MORE_DATA)
		{
			BufSize++;

			lError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &type, (LPBYTE)&CharBuf, &BufSize);

		}

		cout << "CPU Architecture" << CharBuf << endl;

	}
	//return CharBuf;
}