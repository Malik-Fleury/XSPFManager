#include "include/data/track.h"

Track::Track(QString absoluteFilePath): fileInfo(absoluteFilePath)
{
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
