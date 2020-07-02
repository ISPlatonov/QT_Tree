#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::addChild(QTreeWidgetItem *par, empl* empl)
{
    QTreeWidgetItem *tree = new QTreeWidgetItem();

    tree->setData(0, 0, empl->name);
    tree->setData(1, 0, empl->func);
    tree->setData(2, 0, empl->sal);

    par->addChild(tree);
}

void MainWindow::addDepartment(Ui::MainWindow *ui, department* dep)
{
    QTreeWidgetItem *tree = new QTreeWidgetItem(ui->treeWidget);

    tree->setData(0, 0, dep->name);
    tree->setData(1, 0, dep->num());
    tree->setData(2, 0, dep->midsal());
    ui->treeWidget->addTopLevelItem(tree);

    size_t len = dep->empls.count();
    for (size_t j = 0; j < len; ++j)
        addChild(tree, dep->empls[j]);
}

void MainWindow::clearTreeWidget(Ui::MainWindow *ui)
{
    while (ui->treeWidget->topLevelItemCount() > 0)
        ui->treeWidget->takeTopLevelItem(0);
    //deps.clear();
}

void MainWindow::setTreeView(Ui::MainWindow *ui, QVector<department*>& deps)
{
    //ui->treeWidget->setColumnCount(3);

    /*QTreeWidgetItem *tree = new QTreeWidgetItem(ui->treeWidget);

    tree->setText(0, "Название");
    tree->setText(1, "Кол-во сотрудников");
    tree->setText(2, "Ср. зарплата");

    ui->treeWidget->setHeaderItem(tree);*/

    for (auto dep : deps)
        addDepartment(ui, dep);
}

MainWindow::MainWindow(/*QVector<department*>& deps,*/ QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setTreeView(ui, deps);
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
    data.Open(/*"C:/file.xml"*/path.getPath(), deps);
    setTreeView(ui, deps);
}
