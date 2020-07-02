#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QFileDialog>

class Path
{
public:
    Path();
    QString getPath();
    void setPath();
private:
    QString path;
};

#endif // PATH_H
