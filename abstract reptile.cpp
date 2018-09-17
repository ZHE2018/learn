#include "abstract reptile.h"

AbstractReptile::AbstractReptile(QObject *parent) : QObject(parent)
{
    manager= new QNetworkAccessManager(this);
}

AbstractReptile::~AbstractReptile()
{
    delete this->manager;
}

