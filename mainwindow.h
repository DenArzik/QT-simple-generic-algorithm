#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline static double DesiredFunction(const double &x){ return cos(2*x); }

private slots:
    void on_Accuracy_sliderMoved(int position);

    void on_dBox_valueChanged(double arg1);

    void on_bCycle_clicked();

    void on_pushButton_2_clicked();

    void on_Accuracy_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    double Accuracy_;
    class Generic *q2;
    bool generated;
    int count_;

};

#endif // MAINWINDOW_H
