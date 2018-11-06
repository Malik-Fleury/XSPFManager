#include "include/data/playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
   return 10;
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }

    return QVariant();
}
