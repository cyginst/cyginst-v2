extern "C" {
#define EXPORT_FUNCTION extern "C" __declspec(dllexport)
} // extern "C"

#ifndef __HTOD__
#include <winsock2.h>
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

//#include <stdio.h>
extern "C" 
{
//    #include <ruby.h>
}
#include <ruby.h>

extern "C" __declspec(dllexport) void CALLBACK runServer(HWND hwnd, HINSTANCE hinst, const char * /*lpszCmdLine*/, int nCmdShow)
{
	std::vector<wchar_t *> args;
    init_rundll_pg(args);
    if (getenv("CYG_NAME"))
    {
        printf("CYG_NAME=%s\n", getenv("CYG_NAME"));
        printf("SCRIPT_CURRENT_DIR=%s\n", getenv("SCRIPT_CURRENT_DIR"));
        
    }
    ruby_init();
    
    // スクリプトの実行
    rb_eval_string("puts 'Hello World!'");
    
    // Rubyインタプリタのクリーンアップ
    ruby_cleanup(0);

    system("pause");
	return;
}
#endif //if !defined(__HTOD__)
