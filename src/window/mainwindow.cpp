#include "include/window/mainwindow.h"

/**
* MainWindow
* Constructeur par défaut de la fenêtre
*
* @param QWidget* parent: parent
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    path = "";
    playlist = nullptr;

    setupUi(this);
    setupPlaylistTable();
    setupPanelExport();
    setupMenuActions();
    setupOtherEvents();

    enableWidgets(false);
}

/**
* ~MainWindow
* Destructeur par défaut
*/
MainWindow::~MainWindow()
{
}

/**
* setupMenuAction
* Permet de mettre en place les menus
*/
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

/**
* setupOtherEvents
* Permet de mettre en place les connexions d'autres composants
*/
void MainWindow::setupOtherEvents()
{
    connect(panelExport, &PanelExport::playlistOutputUpdated, playlistTable, &PlaylistTableWidget::updateOutputFields);
}

/**
* setupPlaylistTable
* Permet de mettre en place la table comportant la liste de lecture
*/
void MainWindow::setupPlaylistTable()
{
    this->playlistTable = new PlaylistTableWidget(this);
    this->centralWidget()->layout()->addWidget(playlistTable);
}

/**
* setupPanelExport
* Permet de mettre en place le panneau d'exportation
*/
void MainWindow::setupPanelExport()
{
    this->panelExport = new PanelExport(this);
    this->centralWidget()->layout()->addWidget(panelExport);
}

/**
* enableWidgets
* Permet d'activer ou désactiver la table et le panneau d'exportation
*
* @param enable : activer/désactiver les widgets
*/
void MainWindow::enableWidgets(bool enable)
{
    this->playlistTable->setEnabled(enable);
    this->panelExport->setEnabled(enable);
}

/**
* newFile
* Permet de créer un nouveau fichier
*/
void MainWindow::newFile()
{
    this->freeMemoryPlaylist();
    this->playlist = new Playlist();
    this->playlistTable->fill(playlist);
    this->panelExport->setPlaylist(playlist);
    this->enableWidgets(true);
}

/**
* open
* Permet d'ouvrir un fichier
*/
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

        // Enable widgets
        this->enableWidgets(true);
    }
}

/**
* save
* Permet de sauvegarder un fichier, si aucune sauvegarde n'a été faite, une fenêtre s'ouvre afin de demander la destination
*/
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

/**
* saveAs
* Permet de sauvegarder le fichier à un emplacement bien définit
*/
void MainWindow::saveAs()
{
    QString fileToSave = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!fileToSave.isEmpty())
    {
        this->path = fileToSave;
        this->save();
    }
}

/**
* loadLanguage
* Permet de charger un fichier de langue
*
* @param QString languageFile : nom du fichier de langue
*/
void MainWindow::loadLanguage(const QString& languageFile)
{
    QApplication* app = (QApplication*)QApplication::instance();
    QTranslator translator;
    translator.load(languageFile);
    app->installTranslator(&translator);

    this->retranslateUi(this);
    this->panelExport->retranslateUi(panelExport);
}

/**
* changeLanguage
* Permet de changer la langue de l'application
*
* @param QAction* action : action qui a été pressée
*/
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

/**
* about
* Permet d'afficher une fenêtre d'information sur le programme
*/
void MainWindow::about()
{
    QMessageBox::about(this, "XSPF-Manager", "Auteur: Malik Fleury \nVersion: 1");
}

/**
* freeMemoryPlaylist
* Permet de libérer la mémoie de la liste de lecture
*/
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
