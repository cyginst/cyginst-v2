g++ -shared -o r.dll -IE:\d-dev\d17\d17.m32\mingw32\include\ruby-2.3.0 -IE:\d-dev\d17\d17.m32\mingw32\include\ruby-2.3.0\i386-mingw32 r.cpp -LE:\d-dev\d17\d17.m32\mingw32\lib -lmsvcrt-ruby230-static -lgmp -lWs2_32 -lIphlpapi -lShlwapi -limagehlp -static
32\include\luajit-2.0 n.cpp -LE:\d-dev\d17\d17.m32\mingw32\lib -lluajit-5.1 -static
rundll32 r.dll,runServer@16 a b c