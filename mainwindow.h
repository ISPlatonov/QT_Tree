#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>
#include <QtWidgets>
#include <QTreeWidget>
#include "structdep.h"
#include "dataxml.h"
#include "path.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVector<department*> deps;

public:
    MainWindow(/*QVector<department*>& deps,*/ QWidget *parent = nullptr);
    ~MainWindow();

//private:
    Ui::MainWindow *ui;
    void showChild(QTreeWidgetItem *par, empl* empl);
    void setTreeView(Ui::MainWindow *ui, QVector<department*>& deps);
    void showDepartment(Ui::MainWindow *ui, department* dep);
    void clearTreeWidget(Ui::MainWindow *ui);
    void addDepartment(QVector<department*>& deps, QString& name);
    void addChild(department* dep, QString name, QString sal, QString func);

public slots:
    void getChDep(department* dep);

private slots:
    void on_openFile_triggered();
    void on_but_add_dep_clicked();
    void on_but_add_empl_clicked();
};
#endif // MAINWINDOW_H
