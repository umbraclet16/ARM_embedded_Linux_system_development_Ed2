// FindDialog.cpp
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)		// 构造函数
{
  Label = new QLabel(tr("Find &String:"), this);	// 创建文本标签控件
  LineEdit = new QLineEdit(this);	// 创建文本框控件
  Label->setBuddy(LineEdit);	// 绑定文本框控件和标签控件

  CaseCB = new QCheckBox(tr("Match &Case"), this);	// 创建大小写CheckBox
  BackwardCB = new QCheckBox(tr("Search &backward"), this);	// 创建搜索方向CheckBox

  FindBtn = new QPushButton(tr("&Find"), this);	// 创建查找按钮
  FindBtn->setDefault(true);	// 设置查找按钮为激活状态

  CloseBtn = new QPushButton(tr("Close"), this);	// 创建关闭按钮
  connect(LineEdit, SIGNAL(textChanged(const QString&)), this,
     SLOT(enableFindButton(const QString &)));	// 设置修改文本框事件响应函数
  connect(FindBtn, SIGNAL(clicked()), this, SLOT(findClicked()));	// 设置单击查找按钮响应函数
  connect(CloseBtn, SIGNAL(clicked()), this, SLOT(close()));		// 设置单击关闭按钮响应函数

  QHBoxLayout *TopLeft = new QHBoxLayout;		// 创建列对齐的布局对象
  TopLeft->addWidget(Label);		// 添加文本标签控件到列对齐布局
  TopLeft->addWidget(LineEdit);	// 添加文本框控件到列对齐布局

  QVBoxLayout *Left = new QVBoxLayout;	// 创建行对齐的布局对象
  Left->addLayout(TopLeft);		// 添加列对齐布局到行对齐布局
  Left->addWidget(CaseCB);		// 添加大小写复选CheckBox控件到行布局
  Left->addWidget(BackwardCB);	// 添加前后向搜索CheckBox控件到行布局

  QVBoxLayout *Right = new QVBoxLayout;	// 创建右对齐的行布局对象
  Right->addWidget(FindBtn);		// 添加查找对象布局到右对齐布局
  Right->addWidget(CloseBtn);		// 添加关闭按钮到右对齐布局
  Right->addStretch(1);

  QHBoxLayout *Main = new QHBoxLayout(this);	// 创建行排列的主布局对象
  Main->setMargin(11);
  Main->setSpacing(4);		// 设置控件留空距离
  Main->addLayout(Left);		// 添加左对齐布局
 Main->addLayout(Right);		// 添加右对齐布局
  setLayout(Main);			// 设置应用程序使用主布局

  setWindowTitle(tr("Find Dialog"));	// 设置窗体标题

}

void FindDialog::FindClicked()	// 查找按钮响应函数
{
  QString text = LineEdit->text();	// 从查找文本框读取要查找的文本
  bool CaseSensitive = CaseCB->isChecked();		// 获取是否需要大小写敏感

  if (BackwardCB->isChecked())	// 判断向前还是向后搜索
    FindPrev(text, CaseSensitive);	// 向前搜索文本
  else
    FindNext(text, CaseSensitive);	// 向后搜索文本
}

void FindDialog::EnableFindButton(const QString &Text)	// 激活搜索按钮
{
}
