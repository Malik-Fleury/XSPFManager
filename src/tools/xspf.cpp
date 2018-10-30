#include "include/tools/xspf.h"

using namespace pugi;

Xspf::Xspf()
{
    doc = nullptr;
}

Xspf::Xspf(QString& filePath)
{
    Xspf();
    open(filePath);
}

Xspf::~Xspf()
{
    close();
}

void Xspf::open(QString& filePath)
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

Playlist Xspf::readPlaylist()
{
    QString baseUri = this->getBaseUri();
    QList<Track*>* tracksList = this->getTracks();

    return Playlist(baseUri, tracksList);
}

QString Xspf::getBaseUri()
{
    return doc->select_node("/playlist").node().attribute("xml:base").as_string();
}

QList<Track*>* Xspf::getTracks()
{
    QList<Track*>* tracksList = new QList<Track*>();
    xpath_node_set trackXPathNodesSet= doc->select_nodes("/playlist/trackList/track");

    for(xpath_node trackXPathNode : trackXPathNodesSet)
    {
        Track* track = new Track();
        xml_node trackNode = trackXPathNode.node();

        for(xml_node childNode : trackNode.children())
        {
            QString key = childNode.name();
            QString data = childNode.text().as_string();
            track->addData(key, data);
        }

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
    playlistNode.append_attribute("xml:base").set_value("test");
    playlistNode.append_attribute("version").set_value("1");
    playlistNode.append_attribute("xmlns").set_value("http://xspf.org/ns/0/");

    xml_node tracklistNode = playlistNode.append_child("trackList");

    for(auto itrTrack = playlist.getConstBegin(); itrTrack != playlist.getConstEnd(); itrTrack++)
    {
        Track* track = (Track*)*itrTrack;
        xml_node trackNode = tracklistNode.append_child("track");

        for(auto itrTrackData = track->getConstBegin(); itrTrackData != track->getConstEnd(); itrTrackData++)
        {
            QString key(*itrTrackData);
            QString dataTrack = track->getDataFromKey(key);

            xml_node dataNode = trackNode.append_child(key.toStdString().c_str());
            dataNode.text().set(dataTrack.toStdString().c_str());
        }
    }

    newDoc.save_file(filePath.toStdString().c_str());
}

//    if(result)
//    {
//        pugi::xpath_node xNode = doc.select_node("/playlist/trackList/track[1]/title");
//        pugi::xpath_node_set xSet = doc.select_nodes("/playlist/trackList/track[1]/title");
//        qDebug() << xSet.size();
//        qDebug() << xSet.first().node().text().as_string();
//        qDebug() << xNode.node().text().as_string();
//    }
//    else
//    {
//        qDebug() << result.description();
//    }
