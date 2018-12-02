#ifndef PANELEXPORT_H
#define PANELEXPORT_H

#include <QtWidgets>
#include "include/data/playlist.h"
#include "include/data/track.h"
#include "include/tools/xspf.h"
#include "ui_panelexport.h"

class PanelExport : public QWidget, public Ui::panelExport
{
    Q_OBJECT

public:
    explicit PanelExport(QWidget *parent = 0);
    ~PanelExport();

    Playlist* getPlaylist();
    void setPlaylist(Playlist* playlist);

private:
    void setupActions();

private slots:
    void chooseOutputFile();
    void exportFiles();

private:
    Playlist* playlist;
};

#endif // PANELEXPORT_H
