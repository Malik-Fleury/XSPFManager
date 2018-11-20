#include "include/data/playlistmodel.h"

PlaylistModel::PlaylistModel(QObject* parent)
    :QAbstractTableModel(parent)
{
    //    selectedCell = 0;
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
    timer->start();

    for(int i = 0;i < ROWS; i++)
        for(int j = 0;j < COLS; j++)
            m_gridData[i][j] = "Test";
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
    return ROWS;
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
            if(index.column() == 0 && index.row() == 0)
            {
                return QTime::currentTime().toString();
            }
            else
            {
                qDebug() << m_gridData[index.row()][index.column()];
                return m_gridData[index.row()][index.column()];
            }
            break;
        case Qt::FontRole:
            if(index.column() == 0)
            {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }
            break;
        case Qt::TextAlignmentRole:

            if (index.column() == 0)
            {
                return Qt::AlignHCenter;
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
                case 0:
                    return QString("Filename");
                case 1:
                    return QString("Absolute");
                case 2:
                    return QString("Relative");
            }
        }
    }

    return QVariant();
}

bool PlaylistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
    }

    return true;
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void PlaylistModel::timerHit()
{
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft);
}
