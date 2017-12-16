WScript.Echo("boot.js is loaded!漢字");
var env = new ActiveXObject("WScript.Shell").Environment("PROCESS");
  var CYG_OPTS = {
    debug:       (env.item("CYG_DEBUG") == "1"),
    root:         env.item("CYG_ROOT"),
    name:         env.item("CYG_NAME"),
    bits:         env.item("CYG_BITS"),
    dt_icons:    (env.item("DT_ICONS") == "1"),
    home:         env.item("CYG_HOME").replace(/^\s+|\s+$/g, ''), /*trim()*/
    asis:        (env.item("CYG_ASIS") == "1"),
    lang:         env.item("CYG_LANG"),
    font:         env.item("CYG_FONT"),
    font_height:  env.item("CYG_FONT_HEIGHT"),
    cursor_type:  env.item("CYG_CURSOR_TYPE"),
    confirm_exit: env.item("CYG_CONFIRM_EXIT")
  };

  var COMMON = getCommonObjects();
  function getCommonObjects() {
    var result = {};
    result.fso = new ActiveXObject("Scripting.FileSystemObject");
    result.shell = new ActiveXObject("WScript.Shell");
    result._json_html = WScript.CreateObject('htmlfile');
    result._json_html.write('<meta http-equiv="x-ua-compatible" content="IE=9" />');
    result._json_html.close(result.JSON = result._json_html.parentWindow.JSON);
    return result;
  }

  WScript.Echo(COMMON.JSON.stringify(CYG_OPTS));
 
  COMMON.shell.Run( "rundll32 n.dll,runServer@16 a b c", 1, true );

  throw new Error("ERROR");

  WScript.Echo( "インストールは終了しました。" );