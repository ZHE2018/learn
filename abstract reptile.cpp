#include "abstract reptile.h"

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

}

void AbstractReptile::load()
{

}



AbstractReptile::AbstractReptile(QObject *parent, QUrl &initUrl, QRegExp &analysisData, QRegExp &analysisNextUrl):QObject(parent)
{
    this->currentUrl=initUrl;
    this->analysisData=analysisData;
    this->analysisNextUrl=analysisNextUrl;
}
