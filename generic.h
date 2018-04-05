#ifndef GENERIC_H
#define GENERIC_H
#include <QVector>
#include <QString>
#include "mainwindow.h"



struct Spec
{
    std::vector<double> x;
    std::vector<double> y;
    Spec()
        :x(100), y(100){}

    double Fitness(double (*yParam)(const double &)) const
    {
        double sum(0);
        for(int i(0);i<100;++i)
        {
            sum+=sqrt( pow(y[i]-yParam(x[i]),2) );
        }
        return sum/=100;
    }

    bool operator<(const Spec &obj)
    {
        return this->Fitness(MainWindow::DesiredFunction) < obj.Fitness(MainWindow::DesiredFunction);
    }
};

class Generic
{
public:

    Generic(const double &);
    int Cycle();
    void Step();
    Spec GetSpecie();
    static double (*DesiredFunction)(const double &x);

private:


    const double xStep;
    int SpeciesCount;
    double Accuracy;
    std::vector<struct Spec> Species;

    void InstantiateSpecies();

    void Breed();
    void Mutate();
    void KillTheWeak();
};



#endif // GENERIC_H
