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

extern "C" __declspec(dllexport) void ZeroMain()
{
	std::vector<wchar_t *> args;
    init_rundll_pg(args);

    if (getenv("CYG_NAME"))
    {
        printf("CYG_NAME=%s\n", getenv("CYG_NAME"));
        printf("SCRIPT_CURRENT_DIR=%s\n", getenv("SCRIPT_CURRENT_DIR"));
        
    }
    system("pause");
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
        fprintf(stderr, "Error=%s\n", lua_tostring(L, -1)); // tell us what mistake we made
        system("pause");
        return;
      }
    }
  
    lua_close(L); // Close Lua
  
    system("pause");
	return;
}

extern "C" __declspec(dllexport) void CALLBACK runServer(HWND hwnd, HINSTANCE hinst, const char * /*lpszCmdLine*/, int nCmdShow)
{
	std::vector<wchar_t *> args;
    init_rundll_pg(args);
    ZeroMain();
}
#endif //if !defined(__HTOD__)
