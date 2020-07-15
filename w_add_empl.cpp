#include "w_add_empl.h"
#include "ui_w_add_empl.h"

void w_add_empl::addEmpl(department* dep)
{
    bool f = true;
    if (ui->line_edit_surname->text().isEmpty())
    {
        ui->line_edit_surname->setPlaceholderText("Введите фамилию");
        f = false;
    }
    if (ui->line_edit_name->text().isEmpty())
    {
        ui->line_edit_name->setPlaceholderText("Введите имя");
        f = false;
    }
    if (ui->line_edit_func->text().isEmpty())
    {
        ui->line_edit_func->setPlaceholderText("Введите должность");
        f = false;
    }
    if (ui->line_edit_sal->text().isEmpty())
    {
        ui->line_edit_sal->setPlaceholderText("Введите зарплату");
        f = false;
    }
    if (!f)
        return;

    //здесь выделяется память для новой структуры,
    //создаётся указатель, который записывается в
    //вектор deps (через указатель на конкретный
    //департамент dep)
    //нельзя удалять empl тут - это не промежуточная,
    //а окончательно использующаяся структура
    auto *empl = new struct empl;
    empl->surname = ui->line_edit_surname->text();
    empl->name = ui->line_edit_name->text();
    empl->midname = ui->line_edit_midname->text();
    empl->sal = ui->line_edit_sal->text();
    empl->func = ui->line_edit_func->text();

    commit commit;
    commit.setPrev(*dep);

    dep->empls.push_back(empl);

    commit.setNew(*dep);
    //qDebug() << commit.getPrev()->empls.length() << commit.getNew()->empls.length();

    emit sendDep(commit);

    w_add_empl::~w_add_empl();
}

void w_add_empl::editEmpl(department* dep, struct empl *empl)
{
    commit commit;
    commit.setPrev(*dep);

    if (ui->line_edit_surname->text() != "")
        empl->surname = ui->line_edit_surname->text();
    if (ui->line_edit_name->text() != "")
        empl->name = ui->line_edit_name->text();
    if (ui->line_edit_midname->text() != "")
        empl->midname = ui->line_edit_midname->text();
    if (ui->line_edit_sal->text() != "")
        empl->sal = ui->line_edit_sal->text();
    if (ui->line_edit_func->text() != "")
        empl->func = ui->line_edit_func->text();

    commit.setNew(*dep);

    emit sendDep(commit);

    w_add_empl::~w_add_empl();
}

w_add_empl::w_add_empl(department* _dep, struct empl* _empl, QWidget* parent) : QDialog(parent), ui(new Ui::w_add_empl)
{
    ui->setupUi(this);
    auto* intVal = new QIntValidator;
    ui->line_edit_sal->setValidator(intVal);
    empl = _empl;
    dep = _dep;
    ui->line_edit_surname->setPlaceholderText(empl->surname);
    ui->line_edit_name->setPlaceholderText(empl->name);
    ui->line_edit_midname->setPlaceholderText(empl->midname);
    ui->line_edit_func->setPlaceholderText(empl->func);
    ui->line_edit_sal->setPlaceholderText(empl->sal);
    ui->but_func->setText("Править");

    setAttribute(Qt::WA_DeleteOnClose);
}

w_add_empl::w_add_empl(department* _dep, QWidget *parent) : QDialog(parent), ui(new Ui::w_add_empl)
{
    ui->setupUi(this);
    dep = _dep;
    auto* intVal = new QIntValidator;
    ui->line_edit_sal->setValidator(intVal);
    setAttribute(Qt::WA_DeleteOnClose);
}

w_add_empl::~w_add_empl()
{
    /*if (this->empl != nullptr)
        this->empl->del();*/

    delete ui;
}

void w_add_empl::on_but_func_clicked()
{
    if (empl == nullptr)
        addEmpl(dep);
    else
        editEmpl(dep, empl);
}
