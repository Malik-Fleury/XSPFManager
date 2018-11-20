#include "include/widgets/playlisttable.h"

PlaylistTable::PlaylistTable(QWidget* parent): QTableView(parent)
{
    this->setupTable();
}

PlaylistTable::~PlaylistTable()
{

}

void PlaylistTable::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QFileInfo fileInfo;

    for(QUrl url: mimeData->urls())
    {
        fileInfo.setFile(url.toString());
        qDebug() << fileInfo.suffix();
    }
}

void PlaylistTable::dragMoveEvent(QDragMoveEvent* event)
{
    qDebug() << "DRAAGGGGG";
    event->accept();
}

void PlaylistTable::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    qDebug() << mimeData->urls().at(0);
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

