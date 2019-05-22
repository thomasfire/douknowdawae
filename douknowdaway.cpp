#include "douknowdaway.h"
#include "ui_douknowdaway.h"

DoUKnowDaWay::DoUKnowDaWay(QWidget *parent) :
    ui(new Ui::DoUKnowDaWay)
{
    ui->setupUi(this);
}

DoUKnowDaWay::~DoUKnowDaWay()
{
    delete ui;
}
