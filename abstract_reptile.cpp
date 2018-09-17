#include "abstract_reptile.h"
#include <QFile>
#include <QTextStream>


AbstractReptile::AbstractReptile(QObject *parent) : QObject(parent)
{
    manager= new QNetworkAccessManager(this);
}

AbstractReptile::~AbstractReptile()
{
    delete this->manager;
}

void AbstractReptile::save()
{
    QFile file("temp.data");
    if(file.open(QFile::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        out<<this->currentUrl.toString()<<"\r\n";
    }
    else
    {
        emit IOError(QString("Write file error: open fall."));
    }
}

void AbstractReptile::load()
{

}

void AbstractReptile::work()
{

}

AbstractReptile::AbstractReptile(QObject *parent, QUrl &initUrl, QRegExp &analysisData, QRegExp &analysisNextUrl):QObject(parent)
{
    this->currentUrl=initUrl;
    this->analysisData=analysisData;
    this->analysisNextUrl=analysisNextUrl;
}
