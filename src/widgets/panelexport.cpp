#include "include/widgets/panelexport.h"
#include "ui_panelexport.h"

/**
* PanelExport
* Constructeur par défaut
*
* @param QWidget* parent : parent du composant
*/
PanelExport::PanelExport(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    this->setupActions();
}


/**
* ~PanelExport
* Destructeur par défaut
*/
PanelExport::~PanelExport()
{
}

Playlist* PanelExport::getPlaylist()
{
    return this->playlist;
}

/**
* setPlaylist
* Permet de définir de passer une liste de lecture
*
* @param Playlist* playlist : liste de lecture devant être exportée
*/
void PanelExport::setPlaylist(Playlist* playlist)
{
    this->playlist = playlist;
}

/**
* setupActions
* Permet de définir les connexions entres les différentes éléments du composant
*/
void PanelExport::setupActions()
{
    connect(buttonChooseOutputFile, &QPushButton::pressed, this, &PanelExport::chooseOutputFile);
    connect(buttonExport, &QPushButton::pressed, this, &PanelExport::exportFiles);
}

/**
* chooseOutputFile
* Permet d'ouvrir une fenêtre afin de choisir le dossir de destination
*/
void PanelExport::chooseOutputFile()
{
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!outputFilePath.isEmpty())
    {
        this->lineEditOutputFile->setText(outputFilePath);

        emit playlistOutputUpdated(outputFilePath);
    }
}

/**
* Export files
* Permet d'effectuer l'exportation des fichiers
*/
void PanelExport::exportFiles()
{
    int count = playlist->getNumberOfTracks();
    QFileInfo outputFileInfo(lineEditOutputFile->text());
    QProgressDialog progressBarDialog("Copying files...", "Cancel",0, count-1, this);
    progressBarDialog.setWindowModality(Qt::WindowModal);

    progressBarDialog.show();

    if(this->checkBoxUri->isChecked())
    {
        QString newUri = this->lineEditUri->text();
        playlist->setBaseUri(newUri);
    }
    else
    {
        playlist->setBaseUri("");
    }

    int i = 0;
    for(auto itr = playlist->getConstBegin(); itr != playlist->getConstEnd(); itr++)
    {
        Track* track = (Track*)*itr;
        QString newAbsoluteFilePath = outputFileInfo.absolutePath() + "/" + track->getFilename();
        QFile::copy(track->getAbsoluteFilePath(), newAbsoluteFilePath);
        progressBarDialog.setValue(i++);
    }

    Xspf xspf;
    xspf.savePlaylist(outputFileInfo.absoluteFilePath(), *playlist);

    QMessageBox::information(this, "Copy", "Copy process is done.",
                             QMessageBox::Ok);
}
