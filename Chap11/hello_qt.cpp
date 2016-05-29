// hello_qt.cpp
#include <qapplication.h>
#include <qpushbutton.h>


int main( int argc, char **argv )
{
    QApplication a( argc, argv );	// 定义应用对象

    QPushButton hello( "Hello world!", 0 );	// 定义按钮对象
    hello.resize( 100, 30 );	// 设置按钮大小

    a.setMainWidget( &hello );	// 设置主窗体控件
    hello.show();	// 显示按钮
    return a.exec();
}
