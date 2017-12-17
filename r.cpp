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
#if 0x0
    ruby_init();
    
    // スクリプトの実行
    rb_eval_string("puts 'Hello World!'");
    
    // Rubyインタプリタのクリーンアップ
    ruby_cleanup(0);
#else
  // Rubyインタプリタの初期化
  ruby_init();
  ruby_init_loadpath();

  // スクリプトをファイルから読み込んで実行
  int state;
  rb_load_protect(rb_str_new2("./test.rb"), 0, &state);
  if (state)
  {
    VALUE err;
    VALUE msg;
    // エラーメッセージを出力
    err = rb_errinfo();
    msg = rb_obj_as_string(err);
    fprintf(stderr, "%s\n", StringValuePtr(msg));
  }

  // Rubyインタプリタのクリーンアップ
  ruby_cleanup(0);
#endif

    system("pause");
	return;
}
#endif //if !defined(__HTOD__)
