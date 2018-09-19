#ifndef REPTILE_H
#define REPTILE_H

#include "abstract_reptile.h"

class reptile : public AbstractReptile
{
public:
    reptile();
    ~reptile();
private:
    QUrl captureToUrl(const QString & line, const QUrl & currenturl);
};

#endif // REPTILE_H
