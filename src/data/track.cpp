#include "include/data/track.h"

Track::Track()
{
    this->dataMap = new QMap<QString, QString>();
}

Track::~Track()
{
    delete dataMap;
}

void Track::addData(QString key, QString data)
{
    dataMap->insert(key, data);
}

void Track::showDebugData()
{
    qDebug() << dataMap->value("title");
}

QString Track::getDataFromKey(QString& key)
{
    return dataMap->value(key);
}

QMap<QString, QString>::key_iterator Track::getConstBegin()
{
    return dataMap->keyBegin();
}

QMap<QString, QString>::key_iterator Track::getConstEnd()
{
    return dataMap->keyEnd();
}

