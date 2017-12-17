pexports e:\opt\bin32\lua51.dll > lua51.def
dlltool --input-def lua51.def --output-lib liblua51.a
g++ -shared -o n.dll -IE:\d-dev\d17\LuaJIT-2.0.5\src n.cpp -L. -llua51
rundll32 n.dll,runServer@16 a b c