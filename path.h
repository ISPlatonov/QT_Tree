#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QFileDialog>
#include <QWidget>

class Path
{
public:
    Path(QWidget* parent);
    QString getPath();
    void setPath(QWidget* parent);
private:
    QString path;
};

#endif // PATH_H
