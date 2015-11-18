#include <QApplication>

#include "Training/artificialneutralnetwork.h"
#include "mainwindow.h"

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ArtificialNeutralNetwork *ann = new ArtificialNeutralNetwork;
//    ann->createTrainingData();
//    ann->createTestData();
//    ann->startTraining();

    MainWindow w;
    w.show();

    return a.exec();
}
