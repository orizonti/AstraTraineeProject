// TrainerProjectCMake.cpp: определяет точку входа для приложения.
//

#include "TrainerProjectCMake.h"

using namespace std;

#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
