#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblImage->setScaledContents(true);

    mFeatureMat = Mat::zeros(1,ATTRIBUTES,CV_32F);
    loadTrainingData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbBrowseColorImg_clicked()
{
    QString colorImgPath = QFileDialog::getOpenFileName(this, "Open color image", "D:/GoogleDrive/Master Thesis/images/test/Remove Background Images");
    ui->leColorImgPath->setText(colorImgPath);
    ui->lblImage->setPixmap(QPixmap(colorImgPath));
}

void MainWindow::on_pbBrowseBinaryImg_clicked()
{
    QString binImgPath = QFileDialog::getOpenFileName(this, "Open binary image", "D:/GoogleDrive/Master Thesis/images/test/Binary Images");
    ui->leBinaryImgPath->setText(binImgPath);
}

void MainWindow::on_pbRecognize_clicked()
{
    if (ui->leColorImgPath->text().isEmpty()
            || ui->leBinaryImgPath->text().isEmpty()) {
        QMessageBox::warning(this, "ERROR", "Both color & binary image must be selected", QMessageBox::Ok);
    }

    QList<double> features = FeatureManager::instance()->calcFeatures(ui->leColorImgPath->text(), ui->leBinaryImgPath->text());
    float tmp;
    for (int i=0; i< features.size(); i++) {
        tmp = features.at(i);
        mFeatureMat.at<float>(0, i) = tmp;
    }
    predictResult();
}

MainWindow::loadTrainingData()
{
    CvFileStorage* storage = cvOpenFileStorage( "params.xml", 0, CV_STORAGE_READ );
    CvFileNode *n = cvGetFileNodeByName(storage,0,"FruitRecog");
    mAnnClassifier.read(storage,n);
    cvReleaseFileStorage(&storage);

    qDebug() << "Finish load training data";
}

MainWindow::predictResult()
{
    int maxIndex = 0;
    Mat classOut(1,CLASSES,CV_32F);
    mAnnClassifier.predict(mFeatureMat, classOut);
    float value;
    float maxValue = classOut.at<float>(0,0);
    qDebug() << "\nrecognition index 0, value" << maxValue;
    for(int index = 1; index < CLASSES; index++) {
        value = classOut.at<float>(0,index);
        qDebug() << "recognition index" << index << ", value" << value;
        if(value > maxValue) {
            maxValue = value;
            maxIndex=index;
        }
    }

    // show result
    QString rs;
    switch (maxIndex) {
    case 0:
        rs = "Chôm chôm";
        break;
    case 1:
        rs = "Hồng";
        break;
    case 2:
        rs = "Lê";
        break;
    case 3:
        rs = "Lựu";
        break;
    case 4:
        rs = "Táo";
        break;
    case 5:
        rs = "Xoài";
        break;
    default:
        break;
    }

    QMessageBox::information(this, "DONE", "Fruit Detected: " + rs, QMessageBox::Ok);
}
