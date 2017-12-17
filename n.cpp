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

#include <stdio.h>
extern "C" 
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
    #include "luajit.h"
}

extern "C" __declspec(dllexport) void CALLBACK runServer(HWND hwnd, HINSTANCE hinst, const char * /*lpszCmdLine*/, int nCmdShow)
{
	std::vector<wchar_t *> args;
    init_rundll_pg(args);
    if (getenv("CYG_NAME"))
    {
        printf("CYG_NAME=%s\n", getenv("CYG_NAME"));
        printf("SCRIPT_CURRENT_DIR=%s\n", getenv("SCRIPT_CURRENT_DIR"));
        
    }
    #if 0x0
    HMODULE hmod = LoadLibraryA("root.dll");
    printf("hmod=0x%08x\n", hmod);
    system("pause");
    typedef void (*proto_run_chicken)();
    proto_run_chicken addr_run_chicken = (proto_run_chicken)GetProcAddress(hmod, "run_chicken");
    printf("addr_run_chicken=0x%08x\n", addr_run_chicken);
    system("pause");
    addr_run_chicken();
    #endif

    int status;
    lua_State *L;
    
    L = luaL_newstate(); // open Lua
    if (!L) {
      return; // Checks that Lua started up
    }
    
    luaL_openlibs(L); // load Lua libraries
    //if (argc > 1)
     {
      status = luaL_loadfile(L, "luatest.lua");  // load Lua script
      int ret = lua_pcall(L, 0, 0, 0); // tell Lua to run the script
      if (ret != 0) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1)); // tell us what mistake we made
        system("pause");
        return;
      }
    }
  
    lua_close(L); // Close Lua
  
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
