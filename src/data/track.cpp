#include "include/data/track.h"

Track::Track(QString absoluteFilePath): fileInfo(absoluteFilePath)
{
    //this->dataMap = new QMap<QString, QString>();
}

Track::Track(QString uriBase, QString relativePath):
    fileInfo(Track::generateAbsolutePath(uriBase, relativePath))
{
}

Track::Track(Track& trackSource)
{
    this->fileInfo = trackSource.fileInfo;
}

Track::~Track()
{
    //delete dataMap;
}

void Track::setAbsoluteFilePath(QString absoluteFilePath)
{
    this->fileInfo.setFile(absoluteFilePath);
}

QString Track::getFilename()
{
    return this->fileInfo.fileName();
}

QString Track::getAbsoluteFilePath()
{
    return this->fileInfo.absoluteFilePath();
}

QString Track::getAbsolutePath()
{
    return this->fileInfo.absolutePath();
}

QString Track::getRelativeFilePath(QDir& absolutePathDir)
{
    return absolutePathDir.relativeFilePath(this->getFilename());
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
