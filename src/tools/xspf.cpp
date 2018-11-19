#include "include/tools/xspf.h"

using namespace pugi;

Xspf::Xspf(): doc(nullptr)
{
}

Xspf::Xspf(QString filePath): fileInfo(filePath)
{
    open(filePath);
}

Xspf::~Xspf()
{
    close();
}

void Xspf::open(QString filePath)
{
    doc = new xml_document();
    xml_parse_result result = doc->load_file(filePath.toStdString().c_str());

    if(!result)
    {
        qDebug() << result.description();
    }
}

void Xspf::close()
{
    if(doc != nullptr)
    {
        delete doc;
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

Playlist Xspf::readPlaylist()
{
    QString baseUri = this->getBaseUri();
    QString filePath = fileInfo.absolutePath();
    QList<Track*>* tracksList = this->getTracks(filePath);

    return Playlist(baseUri, tracksList);
}

QString Xspf::getBaseUri()
{
    QString baseUri = doc->select_node("/playlist").node().attribute("xml:base").as_string();
    removeFileTag(baseUri);     // Remove the tag "File:///"
    return baseUri;
}

QList<Track*>* Xspf::getTracks(QString& baseUri)
{
    QList<Track*>* tracksList = new QList<Track*>();
    xpath_node_set trackXPathNodesSet= doc->select_nodes("/playlist/trackList/track");

    // Iterate over the set of tracks
    for(xpath_node trackXPathNode : trackXPathNodesSet)
    {
        xml_node trackNode = trackXPathNode.node();
        QString location = trackNode.child("location").text().as_string();
        Track* track = nullptr;

        // Remove the tag "File:///"
        removeFileTag(location);

        if(!baseUri.isEmpty())
            track = new Track(baseUri, location);
        else
            track = new Track(location);

        /*
        for(xml_node childNode : trackNode.children())
        {
            QString key = childNode.name();
            QString data = childNode.text().as_string();
            track->addData(key, data);
        }
        */

        tracksList->append(track);
    }

    return tracksList;
}

void Xspf::savePlaylist(QString filePath, Playlist& playlist)
{
    xml_document newDoc;

    xml_node declaration = newDoc.prepend_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";
    declaration.append_attribute("encoding") = "UTF-8";

    xml_node playlistNode = newDoc.append_child("playlist");
    if(!playlist.getBaseUri().isEmpty())
    {
        QString uriBase = playlist.getBaseUri();
        addFileTag(uriBase);
        playlistNode.append_attribute("xml:base").set_value(uriBase.toStdString().c_str());
    }
    playlistNode.append_attribute("version").set_value("1");
    playlistNode.append_attribute("xmlns").set_value("http://xspf.org/ns/0/");

    xml_node tracklistNode = playlistNode.append_child("trackList");

    for(auto itrTrack = playlist.getConstBegin(); itrTrack != playlist.getConstEnd(); itrTrack++)
    {
        Track* track = (Track*)*itrTrack;
        xml_node trackNode = tracklistNode.append_child("track");

        xml_node dataNode = trackNode.append_child("location");
        if(!playlist.getBaseUri().isEmpty())
        {
            QDir baseUriDir = playlist.getBaseUriDir();
            dataNode.text().set(track->getRelativePath(baseUriDir).toStdString().c_str());
        }
        else
        {
            QString absolutePath = track->getAbsolutePath();
            addFileTag(absolutePath);
            dataNode.text().set(absolutePath.toStdString().c_str());
        }

        /*
        for(auto itrTrackData = track->getConstBegin(); itrTrackData != track->getConstEnd(); itrTrackData++)
        {
            QString key(*itrTrackData);
            QString dataTrack = track->getDataFromKey(key);

            xml_node dataNode = trackNode.append_child(key.toStdString().c_str());
            dataNode.text().set(dataTrack.toStdString().c_str());
        }
        */
    }

    newDoc.save_file(filePath.toStdString().c_str());
}
