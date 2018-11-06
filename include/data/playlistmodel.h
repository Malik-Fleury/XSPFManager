#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>

class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PlaylistModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:

};

#endif // PLAYLISTMODEL_H
