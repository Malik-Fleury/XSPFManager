#include "include/data/playlistmodel.h"

PlaylistModel::PlaylistModel(Playlist* playlist, QObject* parent)
    :QAbstractTableModel(parent)
{
    this->playlist = playlist;
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
    return playlist->getNumberOfTracks();
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
    return COLS;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
            {
                int column = index.column();
                int trackId = index.row();
                Track* track = playlist->getTrack(trackId);

                switch(column)
                {
                    case FILENAME_COL:
                        return track->getFilename();
                        break;
                    case ABSOLUTE_PATH_COL:
                        return track->getAbsoluteFilePath();
                        break;
                    case RELATIVE_PATH_COL:
                        return track->getAbsoluteFilePath();
                        break;
                }
            }
            break;
    }

    return QVariant();
}

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case FILENAME_COL:
                    return QString("Filename");
                case ABSOLUTE_PATH_COL:
                    return QString("Absolute");
                case RELATIVE_PATH_COL:
                    return QString("Relative");
            }
        }
    }

    return QVariant();
}

bool PlaylistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    switch(role)
    {
        case Qt::EditRole:
            {
                Track* track = playlist->getTrack(index.row());
                track->setAbsoluteFilePath(value.toString());
            }
            break;
    }

    return true;
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable /*|  Qt::ItemIsEditable*/ | Qt::ItemIsEnabled;
}


bool PlaylistModel::insertRows(int position, int rows, const QModelIndex& index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row)
    {
        Track* track = new Track();
        playlist->addTrack(track);
    }

    endInsertRows();
    return true;
}

bool PlaylistModel::removeRows(int position, int rows, const QModelIndex& index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for(int row = 0;row < rows; ++row)
    {
         playlist->removeTrack(position);
    }

    endRemoveRows();
    return true;
}
