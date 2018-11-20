#include "include/tools/xspf.h"

using namespace pugi;

Xspf::Xspf()
{
}

Xspf::Xspf(QString filePath): fileInfo(filePath)
{
    open(filePath);
}

Xspf::Xspf(Xspf& xspfSource)
{
    this->fileInfo = xspfSource.fileInfo;
}

Xspf::~Xspf()
{
}

void Xspf::open(QString filePath)
{
    xml_parse_result result = doc.load_file(filePath.toStdString().c_str());

    if(!result)
    {
        qDebug() << result.description();
    }
}

void Xspf::removeFileTag(QString& path)
{
    if(path.contains("file:///"))
    {
        path.replace("file:///", "");
    }
}

void Xspf::addFileTag(QString& path)
{
    path = "file:///" + path;
}

Playlist* Xspf::readPlaylist()
{
    Playlist* playlist = new Playlist(this->getBaseUri());

    QString filePath = fileInfo.absolutePath();
    this->getTracks(filePath, *playlist);

    return playlist;
}

QString Xspf::getBaseUri()
{
    xml_attribute baseUriAttribute = doc.select_node("/playlist").node().attribute("xml:base");
    QString baseUri = baseUriAttribute.as_string();
    removeFileTag(baseUri);     // Remove the tag "File:///"
    return baseUri;
}

void Xspf::getTracks(QString& filePath, Playlist& playlist)
{
    xpath_node_set trackXPathNodesSet= doc.select_nodes("/playlist/trackList/track");

    // Iterate over the set of tracks
    for(xpath_node trackXPathNode : trackXPathNodesSet)
    {
        xml_node trackNode = trackXPathNode.node();
        QString location = trackNode.child("location").text().as_string();
        Track* track = nullptr;

        // Remove the tag "File:///"
        removeFileTag(location);

        if(!filePath.isEmpty())
            track = new Track(filePath, location);
        else
            track = new Track(location);

        playlist.addTrack(track);
    }
}

void Xspf::savePlaylist(QString filePath, Playlist& playlist)
{
    QFileInfo fileDestInfo(filePath);
    xml_document newDoc;

    // Declare the root node with the version and the encoding of the XML file
    xml_node declaration = newDoc.prepend_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";
    declaration.append_attribute("encoding") = "UTF-8";

    // Add the playlist node and add the XML BASE attribute if the playlist contains an URI
    xml_node playlistNode = newDoc.append_child("playlist");
    if(playlist.existsBaseUri())
    {
        QString uriBase = playlist.getBaseUri();
        addFileTag(uriBase);
        playlistNode.append_attribute("xml:base").set_value(uriBase.toStdString().c_str());
    }
    // Add attributes concerning the version of XSPF
    playlistNode.append_attribute("version").set_value("1");
    playlistNode.append_attribute("xmlns").set_value("http://xspf.org/ns/0/");

    // Create nodes for each tracks
    xml_node tracklistNode = playlistNode.append_child("trackList");
    for(auto itrTrack = playlist.getConstBegin(); itrTrack != playlist.getConstEnd(); itrTrack++)
    {
        Track* track = (Track*)*itrTrack;
        xml_node trackNode = tracklistNode.append_child("track");
        xml_node dataNode = trackNode.append_child("location");

        // If we have an URI, the location is relative with base URI
        if(playlist.existsBaseUri())
        {
            QDir absolutePathDir = fileDestInfo.absoluteDir().absolutePath();
            QString relativePathToTrack = track->getRelativeFilePath(absolutePathDir);
            dataNode.text().set(relativePathToTrack.toStdString().c_str());
        }
        // Else we set the absolute path to the file
        else
        {
            QString absolutePath = track->getAbsolutePath();
            addFileTag(absolutePath);
            dataNode.text().set(absolutePath.toStdString().c_str());
        }
    }

    newDoc.save_file(filePath.toStdString().c_str());
}
