#include "include/data/track.h"

/**
* Track
* Constructeur surchargé: chemin absolu du fichier
*
* @param QString absoluteFilePath : chemin absolu du fichier média
*/
Track::Track(QString absoluteFilePath): fileInfo(absoluteFilePath), fileOutput(fileInfo.fileName())
{
}

/**
* Track
* Constructeur surchargé: URI de base et chemin relatif au fichier
*
* @param QString baseURI : Uri de base
* @param QString relativePath : chemin relatif du fichier
*/
Track::Track(QString uriBase, QString relativePath):
    Track(Track::generateAbsolutePath(uriBase, relativePath))
{
}

/**
* Track
* Constructeur de copie
*
* @param Track& trackSource : Média à copier
*/
Track::Track(Track& trackSource)
{
    this->fileInfo = trackSource.fileInfo;
    this->fileOutput = trackSource.fileOutput;
}

/**
* ~Track
* Destructeur par défaut
*/
Track::~Track()
{
}

/**
* setAbsoluteFilePath
* Permet de modifier le chemin absolu du fichier (en entrée)
*
* @param QString absoluteFilePath : nouveau chemin absolu du fichier
*/
void Track::setAbsoluteFilePath(QString absoluteFilePath)
{
    this->fileInfo.setFile(absoluteFilePath);
}

/**
* getFilename
* Permet d'obtenir le nom du fichier
*
* @return description of the returned value
*/
QString Track::getFilename()
{
    return this->fileInfo.fileName();
}

/**
* getAbsoluteFilePath
* Permet d'obtenir le chemin absolu du fichier en entrée
*
* @return Une string comportant le chemin absolu (avec nom du fichier inclus) d'entrée
*/
QString Track::getAbsoluteFilePath()
{
    return this->fileInfo.absoluteFilePath();
}

/**
* getAbsolutePath
* Permet d'obtenir le chemin absolu du fichier en entrée (sans le nom de fichier)
*
* @return Une string comportant le chemin absolu (sans le nom de fichier)
*/
QString Track::getAbsolutePath()
{
    return this->fileInfo.absolutePath();
}

/**
* getRelativeFilePath
* Permet d'obtenir le chemin relatif (avec le nom de fichier)
*
* @param QDir& absolutePathDir : chemin absolu à partir du quel on définit le chemin relatif
* @return Une string comportant le chemin relatif
*/
QString Track::getRelativeFilePath(QDir& absolutePathDir)
{
    return absolutePathDir.relativeFilePath(this->getFilename());
}

/**
* getOutputRelativeFilePath
* Permet d'obtenir le chemin relatif du fichier de sortie
*
* @return String comportant le chemin relatif du fichier de sortie
*/
QString Track::getOutputRelativeFilePath()
{
    return this->fileOutput.filePath();
}

/**
* setOutputRelativeFilePath
* Permet de définir le chemin relatif du fichier en sortie
*
* @param QString outputRelFilePath : String comportant le chemin relatif
*/
void Track::setOutputRelativeFilePath(QString outputRelFilePath)
{
    this->fileOutput.setFile(outputRelFilePath);
}

/**
* Name of the function
* Description of the function
*
* @param type param1 : Description of the parameter "param1"
* @param type param2 : Description of the parameter "param2"
* @return description of the returned value
*/
QString Track::generateAbsolutePath(QString baseUri, QString relativePath)
{
    return baseUri + "/" + relativePath;
}
