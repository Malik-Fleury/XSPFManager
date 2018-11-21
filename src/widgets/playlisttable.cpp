#include "include/widgets/playlisttable.h"

PlaylistTable::PlaylistTable(QWidget* parent): QTableView(parent)
{
    this->setupTable();
}

PlaylistTable::~PlaylistTable()
{

}

void PlaylistTable::addTrack(QString absoluteFilePath)
{
    QAbstractTableModel* tableModel = (QAbstractTableModel*)this->model();
    int row = tableModel->rowCount();
    tableModel->insertRows(row, 1, QModelIndex());

    QModelIndex index = tableModel->index(row, 0);
    tableModel->setData(index, absoluteFilePath, Qt::EditRole);
}

void PlaylistTable::removeTrack()
{
    QAbstractTableModel* tableModel = (QAbstractTableModel*)this->model();
    QModelIndexList indexes = this->selectedIndexes();
    int jump = tableModel->columnCount();

    // Indexes contains each cell
    // The goal is to remove a row, then we have to jump over several indexes to get the right row index
    for(int i = indexes.count() - jump;i >= 0; i -= jump)
    {
        int index = indexes[i].row();
        tableModel->removeRows(index, (indexes.count() % 3) + 1, QModelIndex());
    }
}

void PlaylistTable::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void PlaylistTable::dragMoveEvent(QDragMoveEvent* event)
{
    event->accept();
}

void PlaylistTable::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QFileInfo fileInfo;

    for(QUrl url: mimeData->urls())
    {
        QString absoluteFilePath = url.toString().replace("file:///", "");
        this->addTrack(absoluteFilePath);
    }
}

void PlaylistTable::setupTable()
{
    this->horizontalHeader()->setSectionsMovable(true);
    this->horizontalHeader()->setDragDropMode(QAbstractItemView::InternalMove);
    this->verticalHeader()->setSectionsMovable(true);
    this->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);

    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

