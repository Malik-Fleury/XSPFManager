#ifndef XSPFPLAYLIST_H
#define XSPFPLAYLIST_H

#include <QtWidgets>
#include "lib/pugixml-1.9/src/pugixml.hpp"

#include "include/data/playlist.h"

class Xspf
{
public:
    Xspf();
    Xspf(QString filePath);
    Xspf(Xspf& xspfSource);
    ~Xspf();

    void open(QString filePath);
    Playlist* readPlaylist();
    void savePlaylist(QString filename, Playlist& playlist);

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
