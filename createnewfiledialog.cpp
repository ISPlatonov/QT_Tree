#include "createnewfiledialog.h"
#include "ui_createnewfiledialog.h"

createNewFileDialog::createNewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createNewFileDialog)
{
    ui->setupUi(this);
}

createNewFileDialog::~createNewFileDialog()
{
    delete ui;
}

void createNewFileDialog::on_buttonBox_accepted()
{
    emit accepted();
}
