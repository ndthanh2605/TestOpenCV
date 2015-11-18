#ifndef ARTIFICIALNEUTRALNETWORK_H
#define ARTIFICIALNEUTRALNETWORK_H

#include <QObject>
#include <QFile>
#include <stdio.h>
#include <fstream>
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include "FeatureExtraction/featuremanager.h"

#define TRAINING_SAMPLES 99
#define TEST_SAMPLES 33
#define ATTRIBUTES 24
#define CLASSES 6

using namespace cv;
class ArtificialNeutralNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ArtificialNeutralNetwork(QObject *parent = 0);

    void createTestData();
    void createTrainingData();

    void startTraining();
    void startTesting();

signals:

public slots:

private:

    void readFeatureData(char *filename, Mat &data, Mat &classes, int imgCount);

};

#endif // ARTIFICIALNEUTRALNETWORK_H
