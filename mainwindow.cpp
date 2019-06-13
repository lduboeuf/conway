#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
    game(new GameWidget(this)),
    chart(new GenerationHistory(this))
{
    ui->setupUi(this);
    ui->lbl_message->setVisible(false);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    //ui->colorButton->setIcon( QIcon(icon) );

    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(clear()));
    connect(ui->clearButton, SIGNAL(clicked()), chart,SLOT(clear()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(setCellNumber(int)));
    connect(game,SIGNAL(environmentChanged(bool)),ui->cellsControl,SLOT(setDisabled(bool)));
    connect(game,SIGNAL(gameEnds(bool)),ui->cellsControl,SLOT(setEnabled(bool)));
    connect(game, SIGNAL(generationNumberChanged(QString)), ui->generation_rounds, SLOT(setText(QString)));
    connect(game, SIGNAL(maxCellsNbChanged(QString)), ui->lblmaxCellsNb, SLOT(setText(QString)));
    connect(game, SIGNAL(minCellsNbChanged(QString)), ui->lblminCellsNb, SLOT(setText(QString)));

    //connect(game, SIGNAL(messageChanged(QString)), this, SLOT(messageHandle(QString)));

    connect(game, SIGNAL(nbCellsChanged(int)), chart, SLOT(addCellNb(int)));
    //connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    //connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    //connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);

    QScrollArea *scroll = new QScrollArea;
    //chart->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //chart->setFixedSize(1000,1000);
    //chart->setFixedWidth(1000);
    scroll->setWidget(chart);
    //scroll->ensureVisible(0,2000);

   scroll->setWidgetResizable(true);
    //ui->setLayout->setSizeConstraint(QLayout::SetMinimumSize);
    //scroll->setSizeConstraint(QLayout::SetMinimumSize);
    ui->setLayout->addWidget(scroll);

//    ui->scrollArea->setWidget(chart);
//    ui->scrollArea->setWidgetResizable(true);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString s = QString::number(game->cellNumber())+"\n";
    file.write(s.toUtf8());
    file.write(game->dump().toUtf8());
    QColor color = game->masterColor();
    QString buf = QString::number(color.red())+" "+
                  QString::number(color.green())+" "+
                  QString::number(color.blue())+"\n";
    file.write(buf.toUtf8());
    buf.clear();
    buf = QString::number(ui->iterInterval->value())+"\n";
    file.write(buf.toUtf8());
    file.close();
}

void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sv;
    in >> sv;
    ui->cellsControl->setValue(sv);

    game->setCellNumber(sv);
    QString dump="";
    for(int k=0; k != sv; k++) {
        QString t;
        in >> t;
        dump.append(t+"\n");
    }
    game->setDump(dump);

    int r,g,b; // RGB color
    in >> r >> g >> b;
    currentColor = QColor(r,g,b);
    game->setMasterColor(currentColor); // sets color of the dots
    QPixmap icon(16, 16); // icon on the button
    icon.fill(currentColor); // fill with new color
    //ui->colorButton->setIcon( QIcon(icon) ); // set icon for button
    in >> r; // r will be interval number
    ui->iterInterval->setValue(r);
    game->setInterval(r);
}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    currentColor = color;
    game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    //ui->colorButton->setIcon( QIcon(icon) );
}

void MainWindow::messageHandle(const QString &msg)
{
    ui->lbl_message->setText(msg);
    ui->lbl_message->setVisible(msg.length()>0);

}
