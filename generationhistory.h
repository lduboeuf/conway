#ifndef GENERATIONHISTORY_H
#define GENERATIONHISTORY_H

#include <QWidget>
#include <QVector>

class GenerationHistory : public QWidget
{
    Q_OBJECT
private:
    int step =0;
    QVector<int> points;
protected:
    void paintEvent(QPaintEvent *);
public:
    explicit GenerationHistory(QWidget *parent = nullptr);
    ~GenerationHistory();

signals:

public slots:
    void addCellNb(int nb);
    void clear();
};


#endif // GENERATIONHISTORY_H
