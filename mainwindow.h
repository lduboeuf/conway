#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "gamewidget.h"
#include "generationhistory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectMasterColor();
    void messageHandle(const QString &msg);
    void saveGame();
    void loadGame();
    
private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget* game;
    GenerationHistory* chart;
};

#endif // MAINWINDOW_H
