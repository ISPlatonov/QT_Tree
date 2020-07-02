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
    void addChild(QTreeWidgetItem *par, /*int row,*/ empl* empl);
    void setTreeView(Ui::MainWindow *ui, QVector<department*>& deps);
    void MainWindow::addDepartment(Ui::MainWindow *ui, /*int row,*/ department* dep);
    void MainWindow::clearTree(Ui::MainWindow *ui);
private slots:
    void on_openFile_triggered();
};
#endif // MAINWINDOW_H
