#include "mapfield.h"
#include "ui_mapfield.h"
#include <QFileDialog>
#include <QDir>

MapField::MapField(QString path, int size_n, int sq_size) :
    ui(new Ui::MapField)
{
    ui->setupUi(this);
    this->sq_size = sq_size;
    matrix = getMatrix(path, size_n);
    this->setMinimumWidth(matrix->get_n() * (sq_size + 2)+20);
    this->setMinimumHeight(matrix->get_n() * (sq_size + 2) + 100);
    this->resize(this->width(), this->height());
    this->setGeometry(0, 0, this->width(), this->height());
}

MapField::~MapField()
{
    delete ui;
}

void MapField::on_pushButton_clicked()
{
    int res = this->matrix->find_way();
    if (res == 0) {
        dukdw = new DoUKnowDaWay(this);
        dukdw->show();
    }
    update();
}

void MapField::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i=0; i < matrix->get_n(); i++) {
        for (int j=0; j < matrix->get_n(); j++) {
            switch (matrix->get_value(i, j)) {
            case 0:
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                break;
            case -1:
                painter.setBrush(QBrush(Qt::darkMagenta, Qt::SolidPattern));
                break;
            case 1:
                painter.setBrush(QBrush(Qt::darkGray, Qt::SolidPattern));
                break;
            case 2:
                painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
                break;
            case 3:
                painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
                break;
            case 5:
                painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
                break;
            default:
                painter.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));
                break;
            }
            int x = i * (sq_size + 2) + 10;
            int y = j * (sq_size + 2) + 50;
            QPen pen;
            pen.setColor(Qt::lightGray);
            pen.setWidth(0);
            painter.setPen(pen);
            painter.drawRoundedRect(QRect(QPoint(x, y), QSize(sq_size, sq_size)), 3, 3);
            //painter.drawRect(QRect(QPoint(x, y), QSize(sq_size, sq_size)));

        }
    }
    painter.end();
}

void MapField::mouseMoveEvent(QMouseEvent *event) {
    m_x = event->x();
    m_y = event->y();
}

void MapField::mousePressEvent(QMouseEvent *event) {
    m_x = event->x();
    m_y = event->y();
    if (m_x > (matrix->get_n() * (sq_size + 2)+ 10) || m_x < 10 || m_y < 50 || m_y > (matrix->get_n() * (sq_size + 2)+ 50) ) return;
    int i = (m_x - 10) / (sq_size + 2);
    int j = (m_y - 50) / (sq_size + 2);
    int curr_value = this->matrix->get_value(i, j);
    int x;
    if (curr_value == 0 && event->button() == Qt::LeftButton) {
        x = 1;
    } else if (curr_value == 1 && event->button() == Qt::LeftButton) {
        x = -1;
    } else if (event->button() == Qt::RightButton) {
        x = 2;
    } else if (event->button() == Qt::MiddleButton) {
        x = 3;
    } else {
        x = 0;
    }

    this->matrix->set_value(i, j, x);
    update();
}


SquareMatrix *getMatrix(QString path, int n) {
    SquareMatrix *matrix = new SquareMatrix();
    matrix->input_matrix(path, n);
    return matrix;
}

void MapField::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save a Matrix", QDir::homePath());
    this->matrix->output_matrix(filename);

}
