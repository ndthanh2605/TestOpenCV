#include "colorfeatureextractor.h"

ColorFeatureExtractor::ColorFeatureExtractor(QObject *parent) : QObject(parent)
{

}

QList<double> ColorFeatureExtractor::calcFeatures(QString imgPath)
{
    QList<double> rs;
    Mat img = imread(imgPath.toStdString());
    if (img.empty()) {
        qDebug() << "ERROR: HSV image null";
        return rs;
    }

    Mat imgHsv = imgHSVfromRGB(img);
    std::vector<Mat> rgbComponents;
    split(img, rgbComponents);
    std::vector<Mat> hsvComponents;
    split(imgHsv, hsvComponents);

    Scalar meanR, meanG, meanB, stdvR, stdvG, stdvB;
    Scalar meanH, meanS, meanV, stdvH, stdvS, stdvV;

    meanStdDev(rgbComponents[0], meanR, stdvR);
    meanStdDev(rgbComponents[1], meanG, stdvG);
    meanStdDev(rgbComponents[2], meanB, stdvB);
    meanStdDev(hsvComponents[0], meanH, stdvH);
    meanStdDev(hsvComponents[1], meanS, stdvS);
    meanStdDev(hsvComponents[2], meanV, stdvV);

    rs.append(meanR[0]); rs.append(meanG[0]); rs.append(meanB[0]);
    rs.append(stdvR[0]); rs.append(stdvG[0]); rs.append(stdvB[0]);
    rs.append(meanH[0]); rs.append(meanS[0]); rs.append(meanV[0]);
    rs.append(stdvH[0]); rs.append(stdvS[0]); rs.append(stdvV[0]);

    return rs;
}

void ColorFeatureExtractor::testCalcColorFeatures()
{
    mImgHSV = imgHSVfromRGB(mImg);
    if (mImgHSV.empty()) {
        qDebug() << "ERROR: HSV image null";
        return;
    }
    std::vector<Mat> hsvComponents;
    split(mImgHSV, hsvComponents);

    Scalar mean, stdv;
    meanStdDev(hsvComponents[0], mean, stdv);

    qDebug() << "ColorFeatureExtractor::calcColorFeatures\n"
             << "mean H:" << mean[0] << "- stdv H:" << stdv[0];
}

Mat ColorFeatureExtractor::img() const
{
    return mImg;
}

void ColorFeatureExtractor::setImg(const Mat &img)
{
    mImg = img;
}

Mat ColorFeatureExtractor::imgHSVfromRGB(Mat img)
{
    if (img.empty()) {
        qDebug() << "ERROR: No image";
        return Mat::zeros(img.rows, img.cols, CV_64F);
    }
    Mat imgHSV;
    cvtColor(img, imgHSV, CV_BGR2HSV);
    return imgHSV;
}

