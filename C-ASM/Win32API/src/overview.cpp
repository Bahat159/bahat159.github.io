#include <windows.h>
#include <shobjidl.h>
#include <comdef.h>
#include "../include/FirstWindowApp.h"

void DrawSomeShape(IDrawable **drawableArray, size_t count) {
	for (size_t i = 0; i < count; i++) {
		drawableArray[i]->Draw();
	}
}


inline void throw_if_fail(HRESULT hr) {
	if (FAILED(hr)) {
		throw _com_error(hr);
	}
}

/**

inline DWORD_PTR throw_if_success(HRESULT hr) {
	if (SUCCEEDED(hr)) {
		return 0;
	}
}

**/

DWORD MainWindow_Main(int nCmdShow) {
	MainWindow win;
	if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}
	ShowWindow(win.Window(), nCmdShow);
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int Get_FileDialog() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog *pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						MessageBoxW(NULL, pszFilePath, L"FIle Path", MB_OK);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return 0;
}
