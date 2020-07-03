#ifndef DATAXML_H
#define DATAXML_H

#include <QMainWindow>
#include <QObject>
#include <QtWidgets>
#include <QFile>
#include <QtXml>
#include "structdep.h"
#include "mainwindow.h"
#include "structdep.h"

#include <QDebug>

class DataXML
{
public:
    void Open(QString path, QVector<department*>& deps);
    int countElements(QDomElement root, QString tagname);
private:
    void ListElements(QDomElement root, QVector<department*>& deps, QString tagname, QString attribute);
};

#endif // DATAXML_H
