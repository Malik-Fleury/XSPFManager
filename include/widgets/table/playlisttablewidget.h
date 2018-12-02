#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QtWidgets>
#include "include/data/playlist.h"

class PlaylistTableWidget : public QTableWidget
{
public:
    PlaylistTableWidget(QWidget* parent = 0);
    virtual ~PlaylistTableWidget();

    void fill(Playlist* playlist);

    void addTrack(Track* track, int position = -1);
    void removeSelectedTracks();
    void removeTrack(int row);
    void moveTrack(int rowFrom, int rowTo);

    QList<QTableWidgetItem*> takeRow(int row);
    void setRow(int row, const QList<QTableWidgetItem*>& rowItems);

public slots:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void configureHeaders();
    void configureTable();
    void setupFormats();
    void move(QDropEvent* event);
    void addTracksFromOutside(QDropEvent* event);

private:
    Playlist* playlist;
    QStringList listFormats;
};

#endif // PLAYLISTWIDGET_H
