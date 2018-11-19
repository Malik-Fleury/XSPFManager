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
    ~Xspf();

    Playlist readPlaylist();
    void savePlaylist(QString filename, Playlist& playlist);

private:
    void open(QString filePath);
    void close();
    void removeFileTag(QString& path);
    void addFileTag(QString& path);

    QString getBaseUri();
    QList<Track*>* getTracks(QString& filePat);

private:
    QFileInfo fileInfo;
    pugi::xml_document* doc;
};

#endif // XSPFPLAYLIST_H
