#ifndef PANELEXPORT_H
#define PANELEXPORT_H

#include <QtWidgets>
#include "include/data/playlist.h"
#include "include/data/track.h"
#include "include/tools/xspf.h"
#include "ui_panelexport.h"


/**
* Classe représentant le panneau d'exportation. Il permet de définir où le fichiers XSPF et médias seront copiés
*
* @author	Malik Fleury
* @version	1
*/
class PanelExport : public QWidget, public Ui::panelExport
{
    Q_OBJECT

public:
    explicit PanelExport(QWidget *parent = 0);
    ~PanelExport();

    Playlist* getPlaylist();
    void setPlaylist(Playlist* playlist);

signals:
    void playlistOutputUpdated(QString playlistOutputFilePath);

private:
    void setupActions();

private slots:
    void chooseOutputFile();
    void exportFiles();

private:
    Playlist* playlist;
};

#endif // PANELEXPORT_H
