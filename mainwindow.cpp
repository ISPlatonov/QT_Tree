#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setPath(QString _path)
{
    path = _path;
    fileName = path.split('/').last();
    this->setWindowTitle("Список подразделений - " + fileName);
}

void MainWindow::showChild(QTreeWidgetItem *par, empl* empl)
{
    QTreeWidgetItem *tree = new QTreeWidgetItem();

    tree->setData(0, 0, empl->fio());
    tree->setData(1, 0, empl->func);
    tree->setData(2, 0, empl->sal);

    par->addChild(tree);
}

void MainWindow::showDepartment(Ui::MainWindow *ui, department* dep)
{
    QTreeWidgetItem *tree = new QTreeWidgetItem(ui->treeWidget);

    tree->setData(0, 0, dep->name);
    tree->setData(1, 0, dep->num());
    tree->setData(2, 0, dep->midsal());
    ui->treeWidget->addTopLevelItem(tree);

    size_t len = dep->empls.count();
    for (uint16_t j = 0; j < len; ++j)
        showChild(tree, dep->empls[j]);
}

void MainWindow::addDepartment(QVector<department *> &deps, QString& name)
{
    if (name.isEmpty())
    {
        ui->statusbar->showMessage("Введите название", 5000);
        return;
    }
    for (auto* d : deps)
        if (d->name == name)
        {
            ui->statusbar->showMessage("Подразделение уже существует", 5000);
            return;
        }
    auto *dep = new department;
    dep->name = name;
    deps.push_back(dep);

    showDepartment(ui, dep);
}

void MainWindow::addChild(department *dep, QString surname, QString name, QString midname, QString sal, QString func)
{
    empl *empl = new struct empl;
    empl->sal = sal;
    empl->func = func;
    empl->surname = surname;
    empl->name = name;
    empl->midname = midname;
    dep->empls.push_back(empl);

    //надо подумать с выводом
    auto item = ui->treeWidget->findItems(dep->name, Qt::MatchContains, 0)[0];
    showChild(item, empl);
}

void MainWindow::clearTreeWidget(Ui::MainWindow *ui)
{
    while (ui->treeWidget->topLevelItemCount() > 0)
        ui->treeWidget->takeTopLevelItem(0);
}

void MainWindow::delDep(Ui::MainWindow *ui, QString name)
{
    bool f = 0;
    for (uint16_t i = 0; i < deps.length(); ++i)
        if (deps[i]->name == name)
        {
            f = true;
            deps.remove(i);
            break;
        }
    if (!f)
    {
        ui->statusbar->showMessage("Подразделение не выбрано", 5000);
        return;
    }
}

void MainWindow::delEmpl(Ui::MainWindow *ui, QString name, QString func, QString salary)
{
    if (ui->treeWidget->selectedItems()[0]->parent() == nullptr)
    {
        ui->statusbar->showMessage("Выберите именно сотрудника", 5000);
        return;
    }
    QString dep_name = ui->treeWidget->selectedItems()[0]->parent()->text(0);
    department* dep = nullptr;
    for (uint16_t i = 0; i < deps.length(); ++i)
        if (deps[i]->name == dep_name)
        {
            dep = deps[i];
            break;
        }
    if (dep == nullptr)
    {
        ui->statusbar->showMessage("Сотрудник не выбран", 5000);
        return;
    }
    for (uint16_t i = 0; i < dep->empls.length(); ++i)
        if (dep->empls[i]->fio() == name && dep->empls[i]->sal == salary && dep->empls[i]->func == func)
            dep->empls.remove(i);
}

void MainWindow::editDep(Ui::MainWindow *ui, QString name)
{
    bool f = 0;
    QString newName = ui->line_add_dep->text();
    if (newName.isEmpty())
    {
        ui->statusbar->showMessage("Не написано новое название", 5000);
        return;
    }
    for (uint16_t i = 0; i < deps.count(); ++i)
    {
        if (newName == deps[i]->name)
        {
            ui->statusbar->showMessage("Подразделение уже существует", 5000);
            return;
        }
    }
    for (uint16_t i = 0; i < deps.length(); ++i)
        if (deps[i]->name == name)
        {
            f = true;
            deps[i]->name = newName;
            break;
        }
    if (!f)
    {
        ui->statusbar->showMessage("Подразделение не выбрано", 5000);
        return;
    }
}

void MainWindow::editEmpl(Ui::MainWindow *ui, QString name, QString func, QString salary)
{
    if (ui->treeWidget->selectedItems()[0]->parent() == nullptr)
    {
        ui->statusbar->showMessage("Выберите именно сотрудника", 5000);
        return;
    }
    QString dep_name = ui->treeWidget->selectedItems()[0]->parent()->text(0);
    department* dep = nullptr;
    for (uint16_t i = 0; i < deps.length(); ++i)
        if (deps[i]->name == dep_name)
        {
            dep = deps[i];
            break;
        }
    if (dep == nullptr)
    {
        ui->statusbar->showMessage("Сотрудник не выбран", 5000);
        return;
    }
    for (uint16_t i = 0; i < dep->empls.length(); ++i)
        if (dep->empls[i]->fio() == name && dep->empls[i]->sal == salary && dep->empls[i]->func == func)
        {
            dep->empls[i]->name = name;
            dep->empls[i]->sal = salary;
            dep->empls[i]->func = func;
        }
}

void MainWindow::setTreeView(Ui::MainWindow *ui, QVector<department*>& deps)
{
    for (auto dep : deps)
        showDepartment(ui, dep);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->header()->setMinimumSectionSize(35);
    ui->treeWidget->header()->setVisible(true);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeMode::Interactive);//?
}

MainWindow::~MainWindow()
{
    deps.~QVector();
    delete ui;
}

//open file
void MainWindow::on_openFile_triggered()
{
    DataXML data;
    Path path_w(this);
    if (!path_w.getPath().size())
    {
        ui->statusbar->showMessage("Не был выбран файл для открытия", 5000);
        return;
    }
    this->setPath(path_w.getPath());
    clearTreeWidget(ui);
    data.Open(path, deps);
    setTreeView(ui, deps);
}

//add dep.
void MainWindow::on_but_add_dep_clicked()
{
    QString txt = ui->line_add_dep->text();
    addDepartment(deps, txt);
}

//add empl.
void MainWindow::on_but_add_empl_clicked()
{
    if (ui->treeWidget->selectedItems().count() == 0)
    {
        ui->statusbar->showMessage("Подразделение не выбрано", 5000);
        return;
    }
    else
    {
        //qDebug() << ui->treeWidget->selectedItems()[0]->parent()->text(0)
        QString name = ui->treeWidget->selectedItems()[0]->text(0);
        department* dep = nullptr;
        for (auto d : deps)
            if (d->name == name)
                dep = d;
        if (dep == nullptr)
        {
            ui->statusbar->showMessage("Нужно выбрать именно подразделение", 5000);
            return;
        }
        w_add_empl* add_w = new w_add_empl(dep, this);
        QObject::connect(add_w, SIGNAL(sendDep()), this, SLOT(getChDep()));
        add_w->setWindowFlag(Qt::WindowStaysOnTopHint);
        add_w->setModal(true);
        add_w->show();
        add_w->exec();
    }
}

//delete dep.
void MainWindow::on_but_del_dep_clicked()
{
    if (ui->treeWidget->selectedItems().count() == 0)
    {
        ui->statusbar->showMessage("Ничего не выбрано", 5000);
        return;
    }
    delDep(ui, ui->treeWidget->selectedItems()[0]->text(0));
    clearTreeWidget(ui);
    setTreeView(ui, deps);
}

//delete empl.
void MainWindow::on_but_del_empl_clicked()
{
    if (ui->treeWidget->selectedItems().count() == 0)
    {
        ui->statusbar->showMessage("Ничего не выбрано", 5000);
        return;
    }
    delEmpl(ui, ui->treeWidget->selectedItems()[0]->text(0), ui->treeWidget->selectedItems()[0]->text(1), ui->treeWidget->selectedItems()[0]->text(2));
    clearTreeWidget(ui);
    setTreeView(ui, deps);
}

//create new empty file
void MainWindow::on_createFile_triggered()
{
    //ui->statusbar->showMessage("Такого действия пока нет", 5000);

    createNewFileDialog* dialog = new createNewFileDialog(this);
    QObject::connect(dialog, SIGNAL(signalAccepted()), this, SLOT(getAcceptionCreateNewFile()));
    dialog->setWindowFlag(Qt::WindowStaysOnTopHint);
    dialog->setModal(true);
    dialog->show();
    dialog->exec();
}

//save the structure as another file
void MainWindow::on_saveFileAs_triggered()
{
    auto dataxml = new DataXML;
    auto path_w = QFileDialog::getSaveFileName(this, QFileDialog::tr("Сохранить файл"), "/newFile.xml", QFileDialog::tr("*.xml"));
    if (!path_w.size())
    {
        ui->statusbar->showMessage("Файл не был сохранён", 5000);
        return;
    }
    this->setPath(path_w);
    dataxml->SaveAs(path, deps);
    ui->statusbar->showMessage("Файл сохранён как новый", 5000);
}

//save changes in the file
void MainWindow::on_saveFile_triggered()
{
    if (!path.count())
    {
        ui->statusbar->showMessage("Файл ещё не создан", 5000);
        on_saveFileAs_triggered();
        return;
    }
    auto dataxml = new DataXML;
    dataxml->SaveAs(path, deps);
    ui->statusbar->showMessage("Файл сохранён", 5000);
}

//edit chosen department
void MainWindow::on_but_edit_dep_clicked()
{
    if (ui->treeWidget->selectedItems().count() == 0)
    {
        ui->statusbar->showMessage("Ничего не выбрано", 5000);
        return;
    }
    editDep(ui, ui->treeWidget->selectedItems()[0]->text(0));
    clearTreeWidget(ui);
    setTreeView(ui, deps);
}

void MainWindow::on_but_edit_empl_clicked()
{
    if (ui->treeWidget->selectedItems()[0]->parent() == nullptr)
    {
        ui->statusbar->showMessage("Выберите именно сотрудника", 5000);
        return;
    }
    QString dep_name = ui->treeWidget->selectedItems()[0]->parent()->text(0);
    department* dep = nullptr;
    for (uint16_t i = 0; i < deps.length(); ++i)
        if (deps[i]->name == dep_name)
        {
            dep = deps[i];
            break;
        }
    if (dep == nullptr)
    {
        ui->statusbar->showMessage("Сотрудник не выбран", 5000);
        return;
    }

    QString fio = ui->treeWidget->selectedItems()[0]->text(0);
    QString func = ui->treeWidget->selectedItems()[0]->text(1);
    QString salary = ui->treeWidget->selectedItems()[0]->text(2);

    QStringList fioList = fio.split(' ');

    QString surname = fioList[0];
    QString name = fioList[1];
    QString midname = fioList[2];

    empl* empl;

    for (uint16_t i = 0; i < dep->empls.length(); ++i)
        if (dep->empls[i]->fio() == fio && dep->empls[i]->sal == salary && dep->empls[i]->func == func)
        {
            empl = dep->empls[i];
            empl->name = name;
            empl->surname = surname;
            empl->midname = midname;
            empl->sal = salary;
            empl->func = func;
        }

    w_add_empl* edit_w = new w_add_empl(empl, this);
    QObject::connect(edit_w, SIGNAL(sendDep()), this, SLOT(getChDep()));
    edit_w->setWindowFlag(Qt::WindowStaysOnTopHint);
    edit_w->setModal(true);
    edit_w->setWindowTitle("Править сотрудника");
    edit_w->show();
    edit_w->exec();
}

//slots for other windows

//this slot gets shanged dep. (with new empl) from the other window
void MainWindow::getChDep()
{
    clearTreeWidget(ui);
    setTreeView(ui, deps);
}

void MainWindow::getAcceptionCreateNewFile()
{
    auto dataxml = new DataXML;
    auto path_w = QFileDialog::getSaveFileName(this, QFileDialog::tr("Создать файл"), "/newFile.xml", QFileDialog::tr("*.xml"));
    if (!path_w.size())
    {
        ui->statusbar->showMessage("Файл не был создан", 5000);
        return;
    }
    this->setPath(path_w);
    deps.clear();
    clearTreeWidget(ui);
    dataxml->SaveAs(path, deps);
    ui->statusbar->showMessage("Новый файл создан", 5000);
}

