#ifndef W_ADD_EMPL_H
#define W_ADD_EMPL_H

#include <QWidget>
#include <QDialog>
#include <QValidator>
#include <QMessageBox>
#include "structdep.h"

#include <QDebug>

namespace Ui {
class w_add_empl;
}

class w_add_empl : public QDialog
{
    Q_OBJECT

public:
    explicit w_add_empl(department* _dep, QWidget *parent = nullptr);
    explicit w_add_empl(empl* empl, QWidget *parent = nullptr);
    ~w_add_empl();
    void addEmpl(department* dep);
    void editEmpl(struct empl* empl);

private slots:
    void on_but_func_clicked();

private:
    Ui::w_add_empl *ui;
    department* dep;
    empl* empl = nullptr;
public: signals:
    void sendDep();
};

#endif // W_ADD_EMPL_H
