#ifndef CREATENEWFILEDIALOG_H
#define CREATENEWFILEDIALOG_H

#include <QDialog>
//#include "mainwindow.h"

namespace Ui {
class createNewFileDialog;
}

class createNewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createNewFileDialog(QWidget *parent = nullptr);
    ~createNewFileDialog();

private slots:
    void on_buttonBox_accepted();

public: signals:
    void signalAccepted();

private:
    Ui::createNewFileDialog *ui;
};

#endif // CREATENEWFILEDIALOG_H
