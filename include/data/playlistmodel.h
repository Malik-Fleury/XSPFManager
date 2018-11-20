#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QtWidgets>
#include <QAbstractTableModel>
#include "include/data/playlist.h"

const int COLS= 3;
const int ROWS= 10;

const int FILENAME_COL = 0;
const int ABSOLUTE_PATH_COL = 1;
const int RELATIVE_PATH_COL = 2;

class PlaylistModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    PlaylistModel(Playlist* playlist, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // Headers
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Editing
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

private:
    Playlist* playlist;
};

#endif // PLAYLISTMODEL_H
