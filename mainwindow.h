#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QList>
#include <QDebug>

#include "FeatureExtraction/featuremanager.h"
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#define ATTRIBUTES 24
#define CLASSES 6

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbBrowseColorImg_clicked();

    void on_pbBrowseBinaryImg_clicked();

    void on_pbRecognize_clicked();

private:
    Ui::MainWindow *ui;
    Mat mFeatureMat;
    CvANN_MLP mAnnClassifier;

    loadTrainingData();
    predictResult();

};

#endif // MAINWINDOW_H
