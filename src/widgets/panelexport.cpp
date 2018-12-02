#include "include/widgets/panelexport.h"
#include "ui_panelexport.h"

PanelExport::PanelExport(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
    this->setupActions();
}

PanelExport::~PanelExport()
{
}

Playlist* PanelExport::getPlaylist()
{
    return this->playlist;
}

void PanelExport::setPlaylist(Playlist* playlist)
{
    this->playlist = playlist;
}

void PanelExport::setupActions()
{
    connect(buttonChooseOutputFile, &QPushButton::pressed, this, &PanelExport::chooseOutputFile);
    connect(buttonExport, &QPushButton::pressed, this, &PanelExport::exportFiles);
}

void PanelExport::chooseOutputFile()
{
    QString outputFilePath = QFileDialog::getSaveFileName(this, "Save the xspf playlist", QString(), "*.xspf");

    if(!outputFilePath.isEmpty())
    {
        this->lineEditOutputFile->setText(outputFilePath);
    }
}

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
