#ifndef W_ADD_EMPL_H
#define W_ADD_EMPL_H

#include <QWidget>
#include <QDialog>
#include "structdep.h"

namespace Ui {
class w_add_empl;
}

class w_add_empl : public QWidget
{
    Q_OBJECT

public:
    explicit w_add_empl(department* _dep, QDialog *parent = nullptr);
    ~w_add_empl();
    void addEmpl(department* dep);

private slots:
    void on_but_func_clicked();

private:
    Ui::w_add_empl *ui;
    department* dep;
};

#endif // W_ADD_EMPL_H
