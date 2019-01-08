#ifndef XSPFPLAYLIST_H
#define XSPFPLAYLIST_H

#include <QtWidgets>
#include "lib/pugixml-1.9/src/pugixml.hpp"

#include "include/data/playlist.h"

/**
* Classe permettant de lire et écrire une liste de lecture XSPF
*
* @author	Malik Fleury
* @version	1
*/
class Xspf
{
public:
    Xspf();
    Xspf(QString filePath);
    Xspf(Xspf& xspfSource);
    ~Xspf();

    void open(QString filePath);
    Playlist* readPlaylist();
    void savePlaylist(QString filename, Playlist& playlist, bool absolute = false);

private:
    void removeFileTag(QString& path);
    void addFileTag(QString& path);

    QString getBaseUri();
    void getTracks(QString& filePat, Playlist& playlist);

private:
    QFileInfo fileInfo;
    pugi::xml_document doc;
};

#endif // XSPFPLAYLIST_H
