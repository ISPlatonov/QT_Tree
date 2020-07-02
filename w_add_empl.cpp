#include "w_add_empl.h"
#include "ui_w_add_empl.h"

void w_add_empl::addEmpl(department* dep)
{
    auto *empl = new struct empl;
    empl->name = ui->line_edit_name->text();
    empl->sal = ui->line_edit_sal->text();
    empl->func = ui->line_edit_func->text();
    dep->empls.push_back(empl);
}

w_add_empl::w_add_empl(department* _dep, QDialog *parent) : QWidget(parent), ui(new Ui::w_add_empl)
{
    ui->setupUi(this);
    dep = _dep;
    //setAttribute(Qt::WA_DeleteOnClose);
}

w_add_empl::~w_add_empl()
{
    delete ui;
}

void w_add_empl::on_but_func_clicked()
{
    addEmpl(dep);
    w_add_empl::~w_add_empl();
}
