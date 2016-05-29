// hello_qt.cpp
#include <qapplication.h>
#include <qlabel.h>

int main( int argc, char **argv )
{
  QApplication a( argc, argv );	// 定义应用程序对象
  QLabel hello("<h1><i>Hello,World!</i></h1>", 0);	// 定义标签

  hello.show();	// 显示标签
  return a.exec();
}
