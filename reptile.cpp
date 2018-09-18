#include "reptile.h"
#include <QDebug>

reptile::reptile()
{
    qDebug()<<"reptile init";
}

reptile::~reptile()
{

}

QUrl reptile::captureToUrl(const QString &line, const QUrl &currenturl)
{
    QUrl url;
    QString s;
    int b=-1,e=-1,i=0;
    for(auto ptr=line.begin();ptr!=line.end();++ptr,++i)
    {
        if(*ptr==QChar('"'))
        {
            if(b==-1)
            {
                b=i;
            }
            else if(e==-1)
            {
                e=i;
            }
            else
            {
                break;
            }
        }
        else
        {
            if(b>=0&&e==-1)
            {
                s+=(*ptr);
            }
        }
    }
    s.replace(QString("\""),QString(""));



    s=currenturl.url().section(QString("/"),0,2)+s;
    url.setUrl(s);
    return url;
}

