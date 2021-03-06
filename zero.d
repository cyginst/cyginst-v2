import core.sys.windows.windows;
import core.sys.windows.winbase;

import core.sys.windows.dll : SimpleDllMain; // file:///C:\D\dmd2\src\druntime\import\core\sys\windows\dll.d
mixin SimpleDllMain;

private void exit(int code)
{
    import std.c.stdlib;

    std.c.stdlib.exit(code);
}

static void init_rundll_pg(ref string[] args)
{
    string to_string(wchar* s)
    {
        import core.stdc.wchar_ : wcslen;
        import std.conv : to;

        wchar[] result = s ? s[0 .. wcslen(s)] : cast(wchar[]) null;
        return to!string(to!wstring(result));
    }

    import core.stdc.stdio; // : freopen, stderr, stdin, stdout;
    import core.sys.windows.windows;
    import core.sys.windows.winbase;

    AllocConsole();
    //if (!AttachConsole(ATTACH_PARENT_PROCESS))
    //	AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    args.length = 0;
    LPWSTR* szArglist;
    int nArgs;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    printf("nArgs=%d\n", nArgs);
    for (int i = 1; i < nArgs; i++)
    {
        args ~= to_string(szArglist[i]);
    }
}

static void pause()
{
    import std.process : executeShell;
    import std.stdio : stdin, stdout, write, writeln;

    write(`Press any key to continue . . .`);
    stdout.flush();
    stdin.readln();
}

alias extern (C) void function() proc_ZeroMain;

extern (Windows) export void run(HWND hwnd, HINSTANCE hinst, char*  /+lpszCmdLine+/ , int nCmdShow)
{
    import core.sys.windows.winbase;
    import std.stdio : writeln;

    string[] args;
    init_rundll_pg(args);
    writeln(args);
    //pause();
    HMODULE hmod = LoadLibraryA("n.dll");
    writeln(hmod);
    proc_ZeroMain addr_ZeroMain = cast(proc_ZeroMain) GetProcAddress(hmod, "ZeroMain".ptr);
    writeln(addr_ZeroMain);
    addr_ZeroMain();
    pause();
    return;
}

extern (C) export int add2(int a, int b)
{
    //import std.stdio : writeln;
    //writeln(`a=`, a);
    //writeln(`b=`, b);
    return a + b;
}
