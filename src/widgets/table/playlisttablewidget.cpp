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
        this->addRow(track);
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

    addRow(track, rowNumber);
    playlist->addTrack(track);
}

void PlaylistTableWidget::removeSelectedTracks()
{
    int totalColumn = this->columnCount();
    QModelIndexList selectionIndexes = this->selectedIndexes();
    int totalItems = selectionIndexes.count();
    int numberOfFilesRemoved = totalItems / totalColumn;

    for(int index = totalItems-1;index >= 0; index -= totalColumn)
    {
        int row = selectionIndexes[index].row();
        Track* track = playlist->getTrack(row);

        commandStack.push(new RemoveTrackCommand(this, *track, row));
        commandStack.redo();
    }

    undoNumberOfSteps.push(numberOfFilesRemoved);
    redoNumberOfSteps.clear();
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
        this->move(event);
    }
    else
    {
        QList<QUrl> urls = event->mimeData()->urls();
        this->addTracksFromOutside(event);
    }
}

void PlaylistTableWidget::undo()
{
    if(commandStack.canUndo())
    {
        int undoSteps = undoNumberOfSteps.pop();
        redoNumberOfSteps.push(undoSteps);
        qDebug() << undoSteps;
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
        int redoSteps = redoNumberOfSteps.pop();
        undoNumberOfSteps.push(redoSteps);
        qDebug() << redoSteps;
        for(int counterStep = 0;counterStep < redoSteps; counterStep++)
        {
            commandStack.redo();
        }
    }
}

void PlaylistTableWidget::updateOutputFields(QString playlistOutputFilePath)
{
    int columnOutputAbsFilePath = 2;
    int columnOutputRelFilePath = 3;

    for(int row = 0;row < this->rowCount(); row++)
    {
        Track* track = playlist->getTrack(row);
        QTableWidgetItem* itemOutputAbsFilePath = this->item(row, columnOutputAbsFilePath);
        QTableWidgetItem* itemOutputRelFilePath = this->item(row, columnOutputRelFilePath);

        itemOutputAbsFilePath->setText(playlistOutputFilePath + "/" + track->getOutputRelativeFilePath());
        itemOutputRelFilePath->setText(track->getOutputRelativeFilePath());
    }
}

void PlaylistTableWidget::addRow(Track* track, int rowNumber)
{
    // If -1 and smaller, add the track to the end
    if(rowNumber < 0)
    {
        rowNumber = this->rowCount();
    }

    this->insertRow(rowNumber);

    QTableWidgetItem* filenameItem = new QTableWidgetItem(track->getFilename());
    QTableWidgetItem* absolutePathItem = new QTableWidgetItem(track->getAbsoluteFilePath());
    QTableWidgetItem* outputAbsFilePathItem = new QTableWidgetItem("");
    QTableWidgetItem* outputRelFilePathItem = new QTableWidgetItem("");

    this->setItem(rowNumber, 0, filenameItem);
    this->setItem(rowNumber, 1, absolutePathItem);
    this->setItem(rowNumber, 2, outputAbsFilePathItem);
    this->setItem(rowNumber, 3, outputRelFilePathItem);
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
    headers << "Filename" << "Input absolute path" << "Output absolute path" << "Output relative path";

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
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
        }
        else
        {
            commandStack.push(new MoveTrackCommand(this, rowFrom, this->rowCount()-1));
        }
        commandStack.redo();
    }

    undoNumberOfSteps.push(numberOfFiles);
    redoNumberOfSteps.clear();
    event->accept();
}

void PlaylistTableWidget::addTracksFromOutside(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    QFileInfo fileInfo;
    int rowTo = this->rowAt(event->pos().y());
    int numberOfFilesAdded = 0;

    for(QUrl url: mimeData->urls())
    {
        fileInfo.setFile(url.toLocalFile());

        if(fileInfo.isDir())
        {
            qDebug() << "Is a folder";
            QDir directory = fileInfo.dir();
            QFileInfoList fileInfoList = directory.entryInfoList();

            qDebug() << fileInfoList.length();
            for(QFileInfo fileInfo: fileInfoList)
            {
                qDebug() << "File ADDED";
                this->addTrackDragAndDrop(fileInfo, rowTo++);
                numberOfFilesAdded++;
            }
        }
        else
        {   
            this->addTrackDragAndDrop(fileInfo, rowTo);
            rowTo = rowTo < 0 ? rowTo+2:rowTo+1;

            numberOfFilesAdded++;
        }
    }

    if(numberOfFilesAdded > 0)
    {
        undoNumberOfSteps.push(numberOfFilesAdded);
        redoNumberOfSteps.clear();
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void PlaylistTableWidget::addTrackDragAndDrop(QFileInfo& fileInfo, int rowTo)
{
    if(fileInfo.isFile() && listFormats.contains(fileInfo.suffix()))
    {
        QString absoluteFilePath = fileInfo.absoluteFilePath();
        Track* track = new Track(absoluteFilePath);

        if(rowTo >= 0)
        {
            commandStack.push(new AddTrackCommand(this, *track, rowTo));
        }
        else
        {
            commandStack.push(new AddTrackCommand(this, *track, rowCount()));
        }
        commandStack.redo();
    }
}

/*
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
        redoNumberOfSteps.clear();
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}
*/
