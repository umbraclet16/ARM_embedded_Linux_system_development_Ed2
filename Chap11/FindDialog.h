// FindDialog.h
#ifndef _FINDDIALOG_H_
#define _FINDDIALOG_H_

#include <qdialog.h>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
  Q_OBJECT
public:
  FindDialog(QWidget *parent = 0);

signals:
  void FindNext(const QString &str, bool caseSensitive);
  void FindPrev(const QString &str, bool caseSensitive);

private slots:
 void FindClicked();
  void EnableFindButton(const QString &text);

private:
  QLabel *Label;
  QLineEdit *LineEdit;
  QCheckBox *CaseCB;
  QCheckBox *BackwardCB;
  QPushButton *FindBtn;
  QPushButton *CloseBtn;
};

#endif//_FINDDIALOG_H_
