pexports e:\opt\bin32\lua51.dll > lua51.def
dlltool --input-def lua51.def --output-lib liblua51.a
g++ -shared -o n.dll -IE:\d-dev\d17\d17.m32\mingw32\include\luajit-2.0 n.cpp -LE:\d-dev\d17\d17.m32\mingw32\lib -lluajit-5.1 -static
rundll32 n.dll,runServer@16 a b c