#include <Windows.h>
#include <Pdh.h>
#include "resource.h"

#pragma comment(lib, "Pdh.lib")

HRESULT hr;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND controlWnd;

void _SetupControlWindow(HINSTANCE, int);
void _InitializeDiagnosticsQuery(HINSTANCE);
void _GetCounterData(void);
void _ExecuteQuery(void);

PDH_HQUERY hqReadQuery;
PDH_HQUERY hqWriteQuery;
PDH_HCOUNTER hcReadCounter;
PDH_HCOUNTER hcWriteCounter;

HICON hIconFree;
HICON hIconBusy;

NOTIFYICONDATA NotifyIconData;

PDH_FMT_COUNTERVALUE R;
PDH_FMT_COUNTERVALUE W;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int iCmdShow)
{
	//ZeroMemory(&hr, sizeof(hr));

	_SetupControlWindow(hInstance, iCmdShow);
	_InitializeDiagnosticsQuery(hInstance);

	while (true) {
		_ExecuteQuery();
	}
}

void _GetCounterData(void)
{
	PdhCollectQueryData(hqReadQuery);
	PdhCollectQueryData(hqWriteQuery);

	PdhGetFormattedCounterValue(hcReadCounter, PDH_FMT_DOUBLE, NULL, &R);
	PdhGetFormattedCounterValue(hcWriteCounter, PDH_FMT_DOUBLE, NULL, &W);
}

void _InitializeDiagnosticsQuery(HINSTANCE hInstance)
{
	ZeroMemory(&NotifyIconData, sizeof(NotifyIconData));

	hIconFree = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	hIconBusy = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (hIconFree == NULL || hIconBusy == NULL) {
		MessageBox(NULL, "Failed to load icon(s).", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

	NotifyIconData.hWnd = controlWnd;
	NotifyIconData.uID = 0;
	NotifyIconData.uFlags = NIF_ICON;
	NotifyIconData.hIcon = hIconFree;
	NotifyIconData.cbSize = sizeof(NotifyIconData);

	Shell_NotifyIcon(NIM_ADD, &NotifyIconData);
	
	hr = PdhOpenQuery(NULL, NULL, &hqReadQuery);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to open read query.", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

	hr = PdhOpenQuery(NULL, NULL, &hqWriteQuery);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to open write query.", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

	hr = PdhAddEnglishCounter(hqReadQuery, "\\LogicalDisk(_Total)\\Disk Read Bytes/sec", NULL, &hcReadCounter);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to add read counter.", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

	hr = PdhAddEnglishCounter(hqWriteQuery, "\\LogicalDisk(_Total)\\Disk Write Bytes/sec", NULL, &hcWriteCounter);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to add write counter.", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}
}

void _SetupControlWindow(HINSTANCE hInstance, int iCmdShow)
{
	WNDCLASS wndClass;

	wndClass.style = NULL;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "ControlWindow";

	if (!RegisterClass(&wndClass)) {
		MessageBox(NULL, "Could not register control window class.", "HDLc", MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

	controlWnd = CreateWindow("ControlWindow", NULL, NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//ShowWindow(controlWnd, iCmdShow);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void _ExecuteQuery(void)
{
	_GetCounterData();
	if (R.doubleValue + W.doubleValue != 0) {
		NotifyIconData.hIcon = hIconBusy;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		Shell_NotifyIcon(NIM_MODIFY, &NotifyIconData);
	}
	else {
		NotifyIconData.hIcon = hIconFree;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		Shell_NotifyIcon(NIM_MODIFY, &NotifyIconData);
	}

	Sleep(15);
}