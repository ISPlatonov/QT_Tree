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
#include <QObject>
#include "w_add_empl.h"
#include "structdep.h"
#include "dataxml.h"
#include "path.h"
#include "createnewfiledialog.h"

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
    void addChild(department *dep, QString surname, QString name, QString midname, QString sal, QString func);
    void delDep(Ui::MainWindow *ui, QString name);
    void delEmpl(Ui::MainWindow *ui, QString name, QString func, QString salary);
    void editDep(Ui::MainWindow *ui, QString name);
    void editEmpl(Ui::MainWindow *ui, QString name, QString func, QString salary);

private:
    QString path;

public slots:
    void getChDep();
    void getAcceptionCreateNewFile();

private slots:
    void on_openFile_triggered();
    void on_but_add_dep_clicked();
    void on_but_add_empl_clicked();
    void on_but_del_dep_clicked();
    void on_but_del_empl_clicked();
    void on_createFile_triggered();
    void on_saveFileAs_triggered();
    void on_saveFile_triggered();
    void on_but_edit_dep_clicked();
    void on_but_edit_empl_clicked();
};
#endif // MAINWINDOW_H
