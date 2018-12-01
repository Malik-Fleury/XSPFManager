#include "include/widgets/table/playlisttablewidget.h"

PlaylistTableWidget::PlaylistTableWidget(QWidget* parent): QTableWidget(parent)
{
    this->playlist = nullptr;

    configureHeaders();
    configureTable();
    setupFormats();
}

PlaylistTableWidget::~PlaylistTableWidget()
{

}

void PlaylistTableWidget::fill(Playlist* playlist)
{
    this->playlist = playlist;

    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        this->addTrack(track);
    }
}

void PlaylistTableWidget::addTrack(Track* track)
{
    int totalHeaders = this->columnCount();
    int rowNumber = this->rowCount();

    this->insertRow(rowNumber);

    QTableWidgetItem* filenameItem = new QTableWidgetItem(track->getFilename());
    QTableWidgetItem* absolutePathItem = new QTableWidgetItem(track->getAbsoluteFilePath());
    QTableWidgetItem* relativePathItem = new QTableWidgetItem(track->getAbsoluteFilePath());

    this->setItem(rowNumber, 0, filenameItem);
    this->setItem(rowNumber, 1, absolutePathItem);
    this->setItem(rowNumber, 2, relativePathItem);
}

void PlaylistTableWidget::removeTrack()
{
    int totalColumn = this->columnCount();
    QModelIndexList selectionIndexes = this->selectedIndexes();
    int totalItems = selectionIndexes.count();

    for(int index = 0;index < totalItems; index += totalColumn)
    {
        int row = selectionIndexes[index].row();
        qDebug() << row;

        QTableWidget::removeRow(row);
        playlist->removeTrack(row);
    }
}

void PlaylistTableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void PlaylistTableWidget::dragMoveEvent(QDragMoveEvent* event)
{
    event->accept();
}

void PlaylistTableWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QFileInfo fileInfo;

    if(event->source() == this)
    {
        event->setDropAction(Qt::MoveAction);
        this->move(event);
    }
    else
    {

        for(QUrl url: mimeData->urls())
        {
            QString urlStr = url.toString();
            fileInfo.setFile(urlStr);

            if(listFormats.contains(fileInfo.suffix()))
            {
                QString absoluteFilePath = urlStr.replace("file:///", "");

                Track* track = new Track(absoluteFilePath);
                playlist->addTrack(track);
                this->addTrack(track);

                event->acceptProposedAction();
            }
        }
    }
}

void PlaylistTableWidget::move(QDropEvent* event)
{
    QModelIndexList selectionIndexes = this->selectedIndexes();
    int totalColumns = this->columnCount();
    int rowTo = this->rowAt(event->pos().y());

    for(int index = 0;index < totalColumns; index+=3)
    {
        if(rowTo != -1)
        {
            int rowFrom = selectionIndexes[index].row();

            playlist->move(rowFrom, rowTo);
            QList<QTableWidgetItem*> rowItems = this->takeRow(rowFrom);

            this->removeRow(rowFrom);
            this->insertRow(rowTo);
            this->setRow(rowTo, rowItems);
        }
        else
        {
            event->ignore();
        }
    }
}

void PlaylistTableWidget::setRow(int row, const QList<QTableWidgetItem*>& rowItems)
{
    for (int currentColumn = 0; currentColumn < columnCount(); ++currentColumn)
    {
        setItem(row, currentColumn, rowItems.at(currentColumn));
    }
}

QList<QTableWidgetItem*> PlaylistTableWidget::takeRow(int row)
{
    QList<QTableWidgetItem*> rowItems;
    for (int currentColumn = 0; currentColumn < columnCount(); ++currentColumn)
    {
        rowItems << takeItem(row, currentColumn);
    }
    return rowItems;
}

void PlaylistTableWidget::configureHeaders()
{
    QStringList headers;
    headers << "Filename" << "Absolute path" << "Relative path";

    for(int counter = 0;counter < headers.size(); counter++)
    {
        this->insertColumn(counter);
    }

    this->setHorizontalHeaderLabels(headers);
}

void PlaylistTableWidget::configureTable()
{
    this->horizontalHeader()->setSectionsMovable(true);
    this->horizontalHeader()->setDragDropMode(QAbstractItemView::InternalMove);
    this->verticalHeader()->setSectionsMovable(true);
    this->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);

    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setShowGrid(false);
}

void PlaylistTableWidget::setupFormats()
{
    listFormats.append("mp3");
    listFormats.append("flac");
    listFormats.append("wav");
    listFormats.append("m3u8");
}
