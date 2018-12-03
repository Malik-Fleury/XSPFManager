#include "include/window/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    path = "";
    playlist = nullptr;

    setupUi(this);
    setupPlaylistTable();
    setupPanelExport();
    setupMenuActions();

    enableWidgets(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupMenuActions()
{
    // File
    connect(menuFileNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(menuFileOpen, &QAction::triggered, this, &MainWindow::open);
    connect(menuFileSave, &QAction::triggered, this, &MainWindow::save);
    connect(menuFileSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(menuFileQuit, &QAction::triggered, this, &QApplication::quit);

    // Edit
    connect(menuEditUndo, &QAction::triggered, playlistTable, &PlaylistTableWidget::undo);
    connect(menuEditRedo, &QAction::triggered, playlistTable, &PlaylistTableWidget::redo);
    connect(menuEditRemoveSel, &QAction::triggered, playlistTable, &PlaylistTableWidget::removeSelectedTracks);

    // Language
    languagesActGroup = new QActionGroup(this);
    languagesActGroup->addAction(this->actionEnglish);
    languagesActGroup->addAction(this->actionFrench);
    connect(languagesActGroup, &QActionGroup::triggered, this, &MainWindow::changeLanguage);

    // Help
    connect(menuHelpAbout, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::setupOtherEvents()
{
    //connect(this->playlistTableView, &QTableView::)
}

void MainWindow::setupPlaylistTable()
{
    this->playlistTable = new PlaylistTableWidget(this);
    this->centralWidget()->layout()->addWidget(playlistTable);
}

void MainWindow::setupPanelExport()
{
    this->panelExport = new PanelExport(this);
    this->centralWidget()->layout()->addWidget(panelExport);
}

void MainWindow::enableWidgets(bool enable)
{
    this->playlistTable->setEnabled(enable);
    this->panelExport->setEnabled(enable);
}

void MainWindow::newFile()
{
    this->freeMemoryPlaylist();
    this->playlist = new Playlist();
    this->playlistTable->fill(playlist);
    this->panelExport->setPlaylist(playlist);
    this->enableWidgets(true);
}

void MainWindow::open()
{
    QString fileToOpen = QFileDialog::getOpenFileName(this, "Open xspf playlist", QString(), "*.xspf");

    if(!fileToOpen.isEmpty())
    {
        xspf.open(fileToOpen);

        this->freeMemoryPlaylist();
        this->playlist = xspf.readPlaylist();

        // Add the data of the playlist to the table
        playlistTable->fill(playlist);
        panelExport->setPlaylist(playlist);
    }

    this->enableWidgets(true);
}

void MainWindow::save()
{
    // If the path is not already set, we ask to the user where to save
    if(this->path.isEmpty())
    {
        this->saveAs();
    }
    else
    {
        xspf.savePlaylist(this->path, *playlist, true);
    }
}

void MainWindow::saveAs()
{
    QString fileToSave = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!fileToSave.isEmpty())
    {
        this->path = fileToSave;
        this->save();
    }
}

void MainWindow::loadLanguage(const QString& languageFile)
{
    QApplication* app = (QApplication*)QApplication::instance();
    QTranslator translator;
    translator.load(languageFile);
    app->installTranslator(&translator);

    this->retranslateUi(this);
    this->panelExport->retranslateUi(panelExport);
}

void MainWindow::changeLanguage(QAction* action)
{
    if(action == actionFrench)
    {
        this->loadLanguage(FRENCH_FILE);
    }
    else if(action == actionEnglish)
    {
        this->loadLanguage(ENGLISH_FILE);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, "XSPF-Manager", "Auteur: Malik Fleury \nVersion: 1");
}

void MainWindow::freeMemoryPlaylist()
{
    if(this->playlist != nullptr)
    {
        delete playlist;
        playlist = nullptr;
    }
}

void MainWindow::dropEventHandler(QDropEvent* event)
{

}
