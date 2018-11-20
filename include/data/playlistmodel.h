#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QtWidgets>
#include <QAbstractTableModel>

const int COLS= 3;
const int ROWS= 10;

class PlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PlaylistModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // Headers
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Editing
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

public slots:
    void timerHit();

private:
    QString m_gridData[ROWS][COLS];
};

#endif // PLAYLISTMODEL_H
