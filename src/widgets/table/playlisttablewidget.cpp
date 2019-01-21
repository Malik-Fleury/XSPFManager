#include "include/widgets/table/playlisttablewidget.h"

/**
* PlaylistTableWidget
* Constructeur par défaut
*
* @param QWidget* parent : Parent
*/
PlaylistTableWidget::PlaylistTableWidget(QWidget* parent): QTableWidget(parent)
{
    this->playlist = nullptr;

    configureHeaders();
    configureTable();
    setupFormats();
}

/**
* ~PlaylistTableWidget
* Destructeur par défaut
*/
PlaylistTableWidget::~PlaylistTableWidget()
{

}

/**
* fill
* Permet de remplir la table avec la liste de lecture passé en paramètre
*
* @param Playlist* playlist : liste de lecture à afficher
*/
void PlaylistTableWidget::fill(Playlist* playlist)
{
    this->playlist = playlist;

    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        this->addRow(track);
    }
}

/**
* addTrack
* Permet d'ajouter un média dans la table et dans les données à une certaine position (par défaut : à la suite)
*
* @param Track* track : média à ajouter
* @param int position : position où ajouter le média
*/
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

/**
* removeSelectedTracks
* Permet de supprimer les fichiers sélectionnés dans la table
*/
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

/**
* removeTrack
* Permet de supprimer un média à la ligne spécifiée
*
* @param int row : Ligne du média a supprimer dans la table
*/
void PlaylistTableWidget::removeTrack(int row)
{
    this->removeRow(row);
    playlist->removeTrack(row);
}

/**
* moveTrack
* Permet de déplacer un média à une autre position
*
* @param int rowFrom : Ligne du média avant déplacement
* @param int rowTo : Ligne du média après déplacement
*/
void PlaylistTableWidget::moveTrack(int rowFrom, int rowTo)
{
    playlist->move(rowFrom, rowTo);
    QList<QTableWidgetItem*> rowItems = this->takeRow(rowFrom);

    this->removeRow(rowFrom);
    this->insertRow(rowTo);
    this->setRow(rowTo, rowItems);
}

/**
* dragEnterEvent
* Event
*
* @param QDragEnterEvent* event :
*/
void PlaylistTableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

/**
* dragMoveEvent
* Event
*
* @param QDragMoveEvent* event :
*/
void PlaylistTableWidget::dragMoveEvent(QDragMoveEvent* event)
{
    event->accept();
}

/**
* dropEvent
* Permet d'ajouter des fichiers ou de déplacer des fichiers existants déjà dans la table
*
* @param QDropEvent* event :
*/
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

/**
* undo
* Permet de revenir en arrière
*/
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

/**
* redo
* Permet de revenir en avant
*/
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

/**
* updateOutputFields
* Permet d'ajouter des informations complémentaires dans la table lorsque le fichier de sortie est définit
*
* @param QString playlistOutputFilePath : chemin de sortie du fichier XSPF
*/
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

void PlaylistTableWidget::sortColumn(int logicalIndex)
{
    qDebug() << "OK";
}

void PlaylistTableWidget::sortChanged(int logicalIndex, Qt::SortOrder order)
{
    switch(logicalIndex)
    {
        case Sorting::FILENAME:
            if(order == Qt::AscendingOrder)
            {
                playlist->sort(Sorting::FILENAME);
            }
            else
            {
                playlist->sort(Sorting::FILENAME, true);
            }
            break;
        case Sorting::ABSOLUTE_FILE_PATH:
            if(order == Qt::AscendingOrder)
            {
                playlist->sort(Sorting::ABSOLUTE_FILE_PATH);
            }
            else
            {
                playlist->sort(Sorting::ABSOLUTE_FILE_PATH, true);
            }
            break;
        case Sorting::OUTPUT_ABSOLUTE_FILE_PATH:
            if(order == Qt::AscendingOrder)
            {
                playlist->sort(Sorting::OUTPUT_ABSOLUTE_FILE_PATH);
            }
            else
            {
                playlist->sort(Sorting::OUTPUT_ABSOLUTE_FILE_PATH, true);
            }
            break;
        case Sorting::OUTPUT_RELATIVE_FILE_PATH:
            if(order == Qt::AscendingOrder)
            {
                playlist->sort(Sorting::OUTPUT_RELATIVE_FILE_PATH);
            }
            else
            {
                playlist->sort(Sorting::OUTPUT_RELATIVE_FILE_PATH, true);
            }
            break;
    }

    this->setRowCount(0);
    this->fill(this->playlist);
}

/**
* addRow
* Permet d'ajouter une nouvelle ligne dans la table
*
* @param Track* track : Média à afficher
* @param int rowNumber : Ligne à laquelle positionner le média
*/
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

/**
* setRow
* .
*
* @param int row : Ligne
* @param const QList<QTableWidgetItem*>& rowItems : Cellules de la table
*/
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

/**
* configureHeaders
* Permet de configurer les entêtes de la table
*/
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

/**
* configureTable
* Permet de configurer les différents options de la table
*/
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
    this->horizontalHeader()->setSortIndicatorShown(true);

    //connect(this->horizontalHeader(), &QHeaderView::sectionClicked, this, &PlaylistTableWidget::sortColumn);
    connect(this->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &PlaylistTableWidget::sortChanged);
}

/**
* setupFormats
* Permet de définir les formats acceptés
*/
void PlaylistTableWidget::setupFormats()
{
    listFormats.append("mp3");
    listFormats.append("flac");
    listFormats.append("wav");
    listFormats.append("m3u8");
}

/**
* move
* Permet de déplacer un média dans la table (maj graphique et données)
*
* @param QDropEvent* event : Evénement lié à une action DROP
*/
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

/**
* addTracksFromOutside
* Permet d'ajouter des fichiers depuis l'extérieur du logiciel (glisser/déposer depuis le bureau par exemple)
*
* @param QDropEvent* event : Evénement lié à une action DROP
*/
void PlaylistTableWidget::addTracksFromOutside(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    QFileInfo fileInfo;
    int rowTo = this->rowAt(event->pos().y());
    int numberOfFilesAdded = 0;

    for(QUrl url: mimeData->urls())
    {
        fileInfo.setFile(url.toLocalFile());

        // If the url is a folder, use QDirIterator to look for files recursively
        if(fileInfo.isDir())
        {
            QDirIterator it(fileInfo.filePath(), QStringList() << "*.flac", QDir::Files, QDirIterator::Subdirectories);
            QFileInfo currentFileInfo;

            while(it.hasNext())
            {
                currentFileInfo.setFile(it.next());
                this->addTrackDragAndDrop(currentFileInfo, rowTo);
                rowTo = rowTo < 0 ? rowTo+2:rowTo+1;

                numberOfFilesAdded++;
            }
        }
        // If the url is a file, add it to the table directly
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

/**
* addTrackDragAndDrop
* Permet d'ajouter des fichiers via drag'n'drop
*
* @param QFileInfo& fileInfo : Information concernant le fichier à ajouter dans la table et dans les données
* @param int rowTo : Ligne où ajouter le média
*/
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
