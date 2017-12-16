extern "C" {
#define EXPORT_FUNCTION extern "C" __declspec(dllexport)
} // extern "C"

#ifndef __HTOD__
#include <windows.h>
#include <stdio.h>
//#include <map>
//#include <mutex>
//#include <string>
#include <vector>
static void init_rundll_pg(std::vector<wchar_t *> &args)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	args.clear();
	LPWSTR *szArglist;
	int nArgs;
	//LPWSTR szCmdline = GetCommandLineW();
	//printf("szCmdline=%ls\n", szCmdline);
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	for (int i = 1; i < nArgs; i++)
	{
		//printf("szArglist[%d]=%ls\n", i, szArglist[i]);
		printf("%ls ", szArglist[i]);
		args.push_back(szArglist[i]);
	}
	printf("\n");
}
extern "C" __declspec(dllexport) void CALLBACK runServer(HWND hwnd, HINSTANCE hinst, const char * /*lpszCmdLine*/, int nCmdShow)
{
	std::vector<wchar_t *> args;
    init_rundll_pg(args);
    if (getenv("CYG_NAME"))
    {
        printf("CYG_NAME=%s\n", getenv("CYG_NAME"));
    }
	system("pause");
	return;
}
extern "C" __declspec(dllexport) void CALLBACK runClient(HWND hwnd, HINSTANCE hinst, const char * /*lpszCmdLine*/, int nCmdShow)
{
	std::vector<wchar_t *> args;
	init_rundll_pg(args);
    HANDLE hPipe = CreateFile("\\\\.\\pipe\\mypipe",
        GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {
        return;
    }
    while (1) {
        char szBuff[32];
        DWORD dwBytesWritten;
        fgets(szBuff, sizeof(szBuff), stdin);
        if (!WriteFile(hPipe, szBuff, strlen(szBuff), &dwBytesWritten, NULL)) {
            break;
        }
    }
    CloseHandle(hPipe);
	system("pause");
	return;
}
#endif //if !defined(__HTOD__)
