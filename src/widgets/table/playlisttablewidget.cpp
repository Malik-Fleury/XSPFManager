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
    this->clearContents();

    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        this->addTrack(track);
    }
}

void PlaylistTableWidget::addTrack(Track* track, int position)
{
    int totalHeaders = this->columnCount();
    int rowNumber = position;

    // If -1 and smaller, add the track to the end
    if(rowNumber < 0)
    {
        rowNumber = this->rowCount();
    }
    this->insertRow(rowNumber);

    QTableWidgetItem* filenameItem = new QTableWidgetItem(track->getFilename());
    QTableWidgetItem* absolutePathItem = new QTableWidgetItem(track->getAbsoluteFilePath());
    QTableWidgetItem* relativePathItem = new QTableWidgetItem(track->getAbsoluteFilePath());

    this->setItem(rowNumber, 0, filenameItem);
    this->setItem(rowNumber, 1, absolutePathItem);
    this->setItem(rowNumber, 2, relativePathItem);
}

void PlaylistTableWidget::removeSelectedTracks()
{
    int totalColumn = this->columnCount();
    QModelIndexList selectionIndexes = this->selectedIndexes();
    int totalItems = selectionIndexes.count();

    for(int index = 0;index < totalItems; index += totalColumn)
    {
        int row = selectionIndexes[index].row();
        this->removeTrack(row);
    }
}

void PlaylistTableWidget::removeTrack(int row)
{
    this->removeRow(row);
    playlist->removeTrack(row);
}

void PlaylistTableWidget::moveTrack(int rowFrom, int rowTo)
{
    playlist->move(rowFrom, rowTo);
    QList<QTableWidgetItem*> rowItems = this->takeRow(rowFrom);

    this->removeRow(rowFrom);
    this->insertRow(rowTo);
    this->setRow(rowTo, rowItems);
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
    if(event->source() == this)
    {
        event->setDropAction(Qt::MoveAction);
        this->move(event);
    }
    else
    {
        this->addTracksFromOutside(event);
    }
}

void PlaylistTableWidget::undo()
{
    if(commandStack.canUndo())
    {
        int undoSteps = undoNumberOfSteps.pop();
        redoNumberOfSteps.enqueue(undoSteps);

        for(int counterStep = 0;counterStep < undoSteps; counterStep++)
        {
            commandStack.undo();
        }
    }
}

void PlaylistTableWidget::redo()
{
    if(commandStack.canRedo())
    {
        int redoSteps = redoNumberOfSteps.dequeue();
        undoNumberOfSteps.push(redoStep);

        for(int counterStep = 0;counterStep < redoSteps; counterStep++)
        {
            commandStack.redo();
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

void PlaylistTableWidget::move(QDropEvent* event)
{
    QModelIndexList selectionIndexes = this->selectedIndexes();
    int totalItems = selectionIndexes.count();
    int rowTo = this->rowAt(event->pos().y());
    int numberOfFiles = totalItems / columnCount();

    for(int index = 0;index < totalItems; index += this->columnCount())
    {
        int rowFrom = selectionIndexes[index].row();

        if(rowTo >= 0)
        {
            commandStack.push(new MoveTrackCommand(this, rowFrom, rowTo++));
            commandStack.redo();
        }
        else
        {
            commandStack.push(new MoveTrackCommand(this, rowFrom, this->rowCount()-1));
            commandStack.redo();
        }
    }

    undoNumberOfSteps.push(numberOfFiles);
    event->accept();
}

void PlaylistTableWidget::addTracksFromOutside(QDropEvent* event)
{
    QFileInfo fileInfo;
    const QMimeData* mimeData = event->mimeData();
    int rowTo = this->rowAt(event->pos().y());
    int numberOfFilesAdded = 0;

    for(QUrl url: mimeData->urls())
    {
        QString urlStr = url.toString();
        fileInfo.setFile(urlStr);

        if(listFormats.contains(fileInfo.suffix()))
        {
            QString absoluteFilePath = urlStr.replace("file:///", "");

            Track* track = new Track(absoluteFilePath);
            playlist->addTrack(track);

            if(rowTo >= 0)
            {
                commandStack.push(new AddTrackCommand(this, *track, rowTo++));
            }
            else
            {
                int row = rowCount();
                commandStack.push(new AddTrackCommand(this, *track, row));
            }
            commandStack.redo();

            numberOfFilesAdded++;
        }
    }

    if(numberOfFilesAdded > 0)
    {
        undoNumberOfSteps.push(numberOfFilesAdded);
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}
