#include "generationhistory.h"

#include <QPainter>
#include <QDebug>

GenerationHistory::GenerationHistory(QWidget *parent) : QWidget(parent)
{

}

GenerationHistory::~GenerationHistory()
{
    points.clear();
}

void GenerationHistory::addCellNb(int nb)
{
    if (points.size()>500){
        points.remove(0,100);
    }
    points << nb;
    update();
}

void GenerationHistory::clear()
{
    points.clear();
    update();
}

void GenerationHistory::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(this->rect().bottomLeft());
    painter.scale(1.0, -1.0);
    //QRect size(10, 10, width()-10, height()-10);
    painter.setBrush(Qt::cyan);
    for (int i = 0; i < points.size(); ++i) {
        painter.drawLine(i, 0, i, points.at(i));
    }

    //painter.drawLine(0, 5, 20, 5);
    //painter.drawRect(size);

}
