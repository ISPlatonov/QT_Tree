#include "path.h" 

Path::Path()
{
    setPath();
}

void Path::setPath()
{
    path = QFileDialog::getOpenFileName(nullptr, QFileDialog::tr("Open File"), "/", QFileDialog::tr("*.xml"));
}

QString Path::getPath()
{
    return path;
}
