// qt_widget.cpp
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qslider.h>
#include <qspinbox.h>
#include <qwidget.h>

class MyWidget : public QWidget	// 定义MyWidget类继承自QWidget基类
{
public:
        MyWidget(QWidget *parent = 0);	// 声明MyWidget类的构造函数
};

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)	// 定义MyWidget类构造函数
{
        QSpinBox *agenum_sb = new QSpinBox();	// 创建Spin控件
        agenum_sb->setRange(0, 100);	// 设置Spin数值范围
        agenum_sb->setValue(0);		// 设置初始数值为0

        QSlider *agenum_sl = new QSlider(Qt::Horizontal);	// 创建Slider控件
        agenum_sl->setRange(0, 100);	// 设置Slider数值范围
       agenum_sl->setValue(0);		// 设置初始数值为0

        connect(agenum_sb, SIGNAL(valueChanged(int)), agenum_sl, SLOT(setValue(int)));	// 设置Spin控件修改数值响应函数
        connect(agenum_sl, SIGNAL(valueChanged(int)), agenum_sb, SLOT(setValue(int)));	// 设置Slider控件修改数值响应函数

        QHBoxLayout *layout = new QHBoxLayout;	// 创建列布局的对象
        layout->addWidget(agenum_sb);		// 添加Spin控件
        layout->addWidget(agenum_sl);		// 添加Slider控件
        setLayout(layout);	// 设置MyWidget使用列布局
        setWindowTitle("Enter a number");	// 设置窗体标题
};

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        MyWidget widget;	// 创建MyWidgt类型的容器

        widget.show();		// 显示容器
        return app.exec();
}
