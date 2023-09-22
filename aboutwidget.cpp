#include "aboutwidget.h"
#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setWindowIcon(QIcon(":/imgs/blue-about-60.png"));
    setWindowTitle(QString("半导体激光器芯片设计软件 SemiCL V1.0"));

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(QString(":/imgs/logoPic.png")));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->textBrowser_2->setText(QString("<font color='red'>This wizard </font>will help you register your copy of "
                                       "<i>Super Product One</i>&trade; or start "
                                       "evaluating the product.<br>重庆国家应用数学中心"));
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::on_pushButton_clicked()
{
    this->close();
}

