#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "ui_mainwindow.h"
#include "include/tools/xspf.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupMenuActions();

    void newFile();
    void open();
    void save();
    void saveAs();

    void undo();
    void redo();

    void about();

private:
    Xspf* xspf;

    QString path;
};

#endif // MAINWINDOW_H
