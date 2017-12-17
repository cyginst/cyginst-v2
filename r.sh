#! bash -uvx
g++ -shared -o r.dll -I/mingw32/include/ruby-2.3.0 -I/mingw32/include/ruby-2.3.0/i386-mingw32 r.cpp -L/mingw32/lib -lmsvcrt-ruby230-static -lgmp -lWs2_32 -lIphlpapi -lShlwapi -limagehlp -static
rundll32 r.dll,runServer@16 a b c
