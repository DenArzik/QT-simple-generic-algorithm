#include "generic.h"
#include <ctime>
#include<vector>

using namespace std;


Generic::Generic(const double &a)
    : xStep(0.1)
    , SpeciesCount(20)
    , Accuracy(a)
    , Species(SpeciesCount)
{
    InstantiateSpecies();
}

void Generic::InstantiateSpecies()
{
    /*for(int i(0);i<SpeciesCount;++i)
        Species[i].DesiredFunction = DesiredFunction;*/


    srand(time(0));
    for(int i(0);i<SpeciesCount;++i)
    {
        double xPos(0);
        for(int j(0);j<100;++j)
        {
            Species[i].x[j]=xPos;
            Species[i].y[j]=(rand()%20-10)/10.0;
            xPos+=xStep;
        }
    }
}

int Generic::Cycle()
{
    Breed();
    Mutate();
    KillTheWeak();

    sort(Species.begin(),Species.end());
    if(Species[0].Fitness(MainWindow::DesiredFunction)<Accuracy)
        return 0;
    return -1;
}

void Generic::Breed()
{
    vector<double> tempY;
    for(int i(0);i<SpeciesCount-1;i++)
    {
        for(int j(0);j<100;j++)
            tempY.push_back(rand()%2==0?Species[i].y[j]:Species[i+1].y[j]);

        Spec child;
        child.x=Species[i].x;
        child.y=tempY;

        Species.push_back(child);
        tempY.clear();
    }

    for(int j(0);j<100;j++)
        tempY.push_back(rand()%2==0?Species[0].y[j]:Species[SpeciesCount-1].y[j]);
    Spec child;
    child.x=Species[0].x;
    child.y=tempY;
    Species.push_back(child);
}

void Generic::Mutate()
{
    for(int i(0);i<5;++i)
    {
        int index = rand()%20;
        for(int j(0);j<100;j++)
        {
            if(sqrt(pow(Species[index].y[j]-MainWindow::DesiredFunction(0.1*j),2))>Accuracy)
                Species[index].y[j] = (rand()%20-10)/10.0;
        }
    }
}

void Generic::KillTheWeak()
{
    sort(Species.begin(), Species.end());
    Species.erase(Species.begin()+SpeciesCount-1, Species.begin()+SpeciesCount*2-1);
}

void Generic::Step()
{

}

Spec Generic::GetSpecie()
{
    sort(Species.begin(), Species.end());
    return Species[0];
}
