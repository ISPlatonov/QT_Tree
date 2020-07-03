#include "dataxml.h"
#include "mainwindow.h"
#include "structdep.h"

void DataXML::ListElements(QDomElement root, QVector<department*>& deps, QString tagname, QString attribute="")
{
    QDomNodeList items = root.elementsByTagName(tagname);

    for (uint16_t i = 0; i < items.count(); ++i)
    {
        QDomNode itemnode = items.at(i);

        //convert to elem
        if (itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            if (attribute.isEmpty())
            {
                QDomNodeList empl = itemele.childNodes();

                struct empl* empl_st = new struct empl;
                for (uint16_t j = 0; j < empl.count(); ++j)
                {
                    QDomElement empl_el = empl.at(j).toElement();
                    if (empl_el.tagName() == "surname")
                        empl_st->surname = empl_el.text();
                    else if (empl_el.tagName() == "name")
                        empl_st->name = empl_el.text();
                    else if (empl_el.tagName() == "middleName")
                        empl_st->midname = empl_el.text();
                    else if (empl_el.tagName() == "salary")
                        empl_st->sal = empl_el.text();
                    else if (empl_el.tagName() == "function")
                        empl_st->func = empl_el.text();
                    else
                        qDebug() << "Unexpected tag";
                }
                deps.back()->empls.push_back(empl_st);
            }
            else
            {
                deps.push_back(new department);
                deps.back()->name = itemele.attribute(attribute);
            }

            if (itemele.elementsByTagName("employment").count())
                ListElements(itemele, deps, "employment");
        }
    }
}

void DataXML::Open(QString path, QVector<department*>& deps)
{
    QDomDocument doc;

    //Load the file
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return;
    }
    else
    {
        if (!doc.setContent(&file))
        {
            qDebug() << "Failed to load the document";
            return;
        }
        file.close();
    }

    deps.clear();

    //get the root element
    QDomElement root = doc.firstChildElement();

    ListElements(root, deps, "department", "name");
}
