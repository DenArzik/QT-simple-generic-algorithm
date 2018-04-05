#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generic.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , Accuracy_(0.1)
  , generated(false)
  , count_(0)
{
    ui->setupUi(this);

    ui->Graph->addGraph();
    ui->Graph->xAxis->setRange(0,10);
    ui->Graph->yAxis->setRange(-1.5, 1.5);
    ui->Graph->xAxis->setVisible(false);
    ui->Graph->yAxis->setVisible(false);

    QVector<double> x(10/0.1);
    QVector<double> y(x.size());

    QVector<double>::iterator itX = x.begin();
    QVector<double>::iterator itY = y.begin();

    double xPos(0);
    while(itX!=x.end() && itY!=y.end())
    {
        *itX = xPos;
        *itY++ = DesiredFunction(*itX++);
        xPos+=0.1;
    }

    ui->Graph->graph(0)->setData(x,y,true);

    ui->Graph->addGraph();
    ui->Graph->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->Graph->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->Graph->graph(1)->data()->clear();
    ui->Graph->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Accuracy_sliderMoved(int position)
{
    double value = double(position)/double(ui->Accuracy->maximum());
    ui->dBox->setValue(value);
    on_dBox_valueChanged(value);
}

void MainWindow::on_dBox_valueChanged(double arg1)
{
    ui->Accuracy->setValue(arg1*ui->Accuracy->maximum());
    Accuracy_ =arg1;
}

void MainWindow::on_bCycle_clicked()
{
    Generic q(Accuracy_);
    int count(0);
    int check=-1;
    while(check==-1)
    {
        ui->Graph->graph(1)->data()->clear();
        check = q.Cycle();
        ui->LIterations->setText(QString::number(++count));
        Spec s = q.GetSpecie();
        ui->Graph->graph(1)->addData(QVector<double>::fromStdVector(s.x),QVector<double>::fromStdVector(s.y));
        ui->Graph->replot();
        if(count>150)
        {
            QMessageBox::information(NULL, "Error!", "To many iterations! Try to reduce accuracy");
            break;
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!generated)
        q2 = new Generic(Accuracy_), generated = true;

    ui->Graph->graph(1)->data()->clear();

    q2->Cycle();
    ui->LIterations->setText(QString::number(++count_));

    Spec s = q2->GetSpecie();
    ui->Graph->graph(1)->addData(QVector<double>::fromStdVector(s.x),QVector<double>::fromStdVector(s.y));
    ui->Graph->replot();
}

void MainWindow::on_Accuracy_valueChanged(int value)
{
    double val = double(value)/double(ui->Accuracy->maximum());
    Accuracy_ = val;
    ui->dBox->setValue(val);
}
