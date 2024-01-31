

#include "main.h"
#include "manager.h"




const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ゲーム";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hWnd);
void AddControls();

HWND g_Window{};
HMENU g_Menu{};


HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wcex;
	{

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//カーソルの形を指定する
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);

		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		//WS_OVERLAPPEDWINDOW
		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

	}



	Manager::GetInstance()->Init();
	


	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);

	AllocConsole();
	freopen("CONOUT$", "w", stdout);


	DWORD dwExecLastTime{};
	DWORD dwCurrentTime{};
	DWORD dwFPSLastTime{};
	DWORD dwFrameCount{};


	int   FpsCount = 0;
	char  DebugStr[2048] = "DX11ゲーム";		// デバッグ文字表示用

	timeBeginPeriod(1);
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;



	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)
			{
//#ifdef _DEBUG
				FpsCount = dwFrameCount;
//#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
//#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(DebugStr, WINDOW_NAME);
				wsprintf(&DebugStr[strlen(DebugStr)], " FPS:%d", FpsCount);
				SetWindowText(g_Window, DebugStr);
//#endif

				Manager::GetInstance()->Update();
				Manager::GetInstance()->Draw();


				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);



	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::GetInstance()->Uninit();
	Manager::DeleteInstance();

	FreeConsole();

	return (int)msg.wParam;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case 1:
			MessageBeep(MB_OK);
			break;
		case 3:
			DestroyWindow(hWnd);
			break;
		case 4:
			if (flipflop())
			{
				Manager::GetInstance()->SetGui(false);
			}
			else
			{
				Manager::GetInstance()->SetGui(true);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_SIZE:
		
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



void AddMenus(HWND hWnd)
{
	g_Menu = CreateMenu();
	HMENU FileMenu = CreateMenu();
	HMENU SoundMenu = CreateMenu();
	HMENU WindowMenu = CreateMenu();

	AppendMenu(SoundMenu, MF_STRING, 1, "SystemSound");


	AppendMenu(FileMenu, MF_POPUP, (UINT_PTR)SoundMenu, "Sound");
	AppendMenu(FileMenu, MF_STRING, 2, "Save");
	AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(FileMenu, MF_STRING, 3, "Exit");

	//メニュー　種類　　	番号			名前
	AppendMenu(g_Menu, MF_POPUP, (UINT_PTR)FileMenu, "File");

	AppendMenu(g_Menu, MF_POPUP, (UINT_PTR)WindowMenu, "Window");
	AppendMenu(WindowMenu, MF_STRING, 4, "Gui");

	SetMenu(hWnd, g_Menu);

}

void AddControls()
{
	//CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_VISIBLE | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT,
	//	rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
}

bool flipflop()
{
	static float flipflop = false;
	flipflop = !flipflop;
	return flipflop;
}

void DisplayErrorMessage(HRESULT hr)
{
	LPWSTR errorMessage = nullptr;

	DWORD messageLength = FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&errorMessage), 0, nullptr);

	if (messageLength == 0) {
		// エラーメッセージの取得に失敗した場合は、エラーコードを直接表示する
		MessageBoxW(nullptr, L"Failed to get error message.", L"Error", MB_ICONERROR);
	}
	else {
		// エラーメッセージを表示し、バッファを解放する
		MessageBoxW(nullptr, errorMessage, L"Error", MB_ICONERROR);
		LocalFree(errorMessage);
	}
}