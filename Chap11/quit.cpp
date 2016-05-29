// quit.cpp
#include <qapplication.h>
#include <qpushbutton.h>

int main( int argc, char **argv )
{
  QApplication app( argc, argv );		// 定义应用程序对象

  QPushButton quitButton( "Quit", 0 );	// 定义按钮
  quitButton.resize( 100, 30 );	// 设置按钮大小

  QObject::connect(&quitButton, SIGNAL(cliked()), &app, SLOT(quit()));	// 设置按钮单击事件处理函数

  quitButton.show();	// 显示按钮
  return app.exec();
}
