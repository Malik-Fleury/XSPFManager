#ifndef PANELEXPORT_H
#define PANELEXPORT_H

#include <QtWidgets>
#include "include/data/playlistmodel.h"
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

     PlaylistModel* getPlaylistModel();
     void setPlaylistModel(PlaylistModel* playlistModel);

private:
    void setupActions();

private slots:
    void chooseOutputFile();
    void exportFiles();

private:
    PlaylistModel* model;
};

#endif // PANELEXPORT_H
