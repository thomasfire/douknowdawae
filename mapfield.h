#ifndef MAPFIELD_H
#define MAPFIELD_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <douknowdaway.h>
#include <matrix.h>

namespace Ui {
class MapField;
}

class MapField : public QWidget
{
    Q_OBJECT

public:
    explicit MapField(QString path, int size_n, int sq_size);
    virtual void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void leaveEvent(QEvent *event);

    ~MapField();

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MapField *ui;
    DoUKnowDaWay *dukdw;
    SquareMatrix *matrix;
    int sq_size;
    int m_x, m_y;
};

SquareMatrix *getMatrix(QString path, int n=0);

#endif // MAPFIELD_H
