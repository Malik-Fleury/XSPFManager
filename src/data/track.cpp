#include "include/data/track.h"

Track::Track(QString absoluteFilePath): fileInfo(absoluteFilePath), fileOutput(fileInfo.fileName())
{
}

Track::Track(QString uriBase, QString relativePath):
    Track(Track::generateAbsolutePath(uriBase, relativePath))
{
}

Track::Track(Track& trackSource)
{
    this->fileInfo = trackSource.fileInfo;
    this->fileOutput = trackSource.fileOutput;
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

QString Track::getOutputRelativeFilePath()
{
    return this->fileOutput.filePath();
}

void Track::setOutputRelativeFilePath(QString outputRelFilePath)
{
    this->fileOutput.setFile(outputRelFilePath);
}

QString Track::generateAbsolutePath(QString baseUri, QString relativePath)
{
    return baseUri + "/" + relativePath;
}
