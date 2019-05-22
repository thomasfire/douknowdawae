#ifndef DOUKNOWDAWAY_H
#define DOUKNOWDAWAY_H

#include <QDialog>

namespace Ui {
class DoUKnowDaWay;
}

class DoUKnowDaWay : public QDialog
{
    Q_OBJECT

public:
    explicit DoUKnowDaWay(QWidget *parent = 0);
    ~DoUKnowDaWay();

private:
    Ui::DoUKnowDaWay *ui;
};

#endif // DOUKNOWDAWAY_H
