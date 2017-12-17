#include <ruby.h>

int main()
{
  // Rubyインタプリタの初期化
  ruby_init();

  // スクリプトの実行
  rb_eval_string("print 'Hello World!'");

  // Rubyインタプリタのクリーンアップ
  ruby_cleanup(0);
  return 0;
}