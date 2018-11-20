#include "include/data/track.h"

Track::Track(QString absolutePath): fileInfo(absolutePath)
{
    //this->dataMap = new QMap<QString, QString>();
}

Track::Track(QString uriBase, QString relativePath):
    fileInfo(Track::generateAbsolutePath(uriBase, relativePath))
{
}

Track::~Track()
{
    //delete dataMap;
}

QString Track::getFilename()
{
    return this->fileInfo.fileName();
}

QString Track::getAbsolutePath()
{
    return this->fileInfo.absoluteFilePath();
}

QString Track::getRelativePath(QDir& baseUriDir)
{
    return baseUriDir.relativeFilePath(this->getAbsolutePath());
}

QString Track::generateAbsolutePath(QString baseUri, QString relativePath)
{
    return baseUri + "/" + relativePath;
}

/*
void Track::addData(QString key, QString data)
{
    dataMap->insert(key, data);
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
*/
