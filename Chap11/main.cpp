// main.cpp
#include <qapplication.h>
#include "FindDialog.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);		// 创建主应用程序对象
  FindDialog *dialog = new FindDialog;	// 创建FindDialog对象
  dialog->show();	// 显示FindDialog
  return app.exec();
}
