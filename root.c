#include "chicken.h"
#include <windows.h>

//__declspec(dllexport) void CALLBACK DllEntry(HWND hwnd, HINSTANCE hinst, const char *lpszCmdLine, int nCmdShow)
__declspec(dllexport) void run_chicken()
{
    printf("run_chicken(1)\n");
	//CHICKEN_run(C_toplevel);
    C_word x;
     //CHICKEN_run(CHICKEN_default_toplevel);
     printf("run_chicken(2)\n");
     CHICKEN_eval_string("(print (+ 3 4))", &x);
     printf("run_chicken(3)\n");
     CHICKEN_eval_string("(+ 3 4)", &x);
     printf("run_chicken(4)\n");
     printf( "%d\n", C_immediatep(x) );
     printf( "%d\n", C_fitsinfixnump(x) );
     printf( "%d\n", C_ufitsinfixnump(x) );
     printf("run_chicken(5)\n");
     int d = C_unfix(x);
     printf( "%d\n", d );
     printf("run_chicken(6)\n");
}
