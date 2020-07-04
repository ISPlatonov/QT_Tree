#include "path.h" 

Path::Path(QWidget* parent)
{
    setPath(parent);
}

void Path::setPath(QWidget* parent)
{
    path = QFileDialog::getOpenFileName(parent, QFileDialog::tr("Open File"), "/", QFileDialog::tr("*.xml"));
}

QString Path::getPath()
{
    return path;
}
