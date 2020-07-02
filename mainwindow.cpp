#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "w_add_empl.h"
#include <QObject>

void MainWindow::showChild(QTreeWidgetItem *par, empl* empl)
{
    QTreeWidgetItem *tree = new QTreeWidgetItem();

    tree->setData(0, 0, empl->name);
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
    for (size_t j = 0; j < len; ++j)
        showChild(tree, dep->empls[j]);
}

void MainWindow::addDepartment(QVector<department *> &deps, QString& name)
{
    auto *dep = new department;
    dep->name = name;
    deps.push_back(dep);

    showDepartment(ui, dep);
}

void MainWindow::addChild(department *dep, QString name, QString sal, QString func)
{
    empl *empl = new struct empl;
    empl->sal = sal;
    empl->func = func;
    empl->name = name;
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

void MainWindow::setTreeView(Ui::MainWindow *ui, QVector<department*>& deps)
{
    for (auto dep : deps)
        showDepartment(ui, dep);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    deps.~QVector();
    delete ui;
}

void MainWindow::on_openFile_triggered()
{
    DataXML data;
    Path path;
    clearTreeWidget(ui);
    data.Open(path.getPath(), deps);
    setTreeView(ui, deps);
}

void MainWindow::on_but_add_dep_clicked()
{
    QString txt = ui->line_add_dep->text();
    addDepartment(deps, txt);
}

void MainWindow::on_but_add_empl_clicked()
{
    if (ui->treeWidget->selectedItems().count() == 0)
    {
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
            qDebug() << "stop";
            return;
        }
        w_add_empl* add_w = new w_add_empl(dep, this);
        QObject::connect(add_w, SIGNAL(sendDep(department*)), this, SLOT(getChDep(department*)));
        add_w->setWindowFlag(Qt::WindowStaysOnTopHint);
        add_w->show();
        add_w->exec();
    }
}

void MainWindow::getChDep(department* dep)
{
    for (auto d : deps)
        if (d->name == dep->name)
            *d = *dep;
    clearTreeWidget(ui);
    setTreeView(ui, deps);
}
