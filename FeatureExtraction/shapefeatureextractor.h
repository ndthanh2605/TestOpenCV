#ifndef SHAPEFEATUREEXTRACTOR_H
#define SHAPEFEATUREEXTRACTOR_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class ShapeFeatureExtractor : public QObject
{
    Q_OBJECT
public:
    explicit ShapeFeatureExtractor(QObject *parent = 0);

    Mat img() const;
    void setImg(const Mat &img);

    QList<double> calcFeatures(Mat img);
    QList<double> calcFeatures(QString imgPath);

signals:

public slots:

private:
    Mat mImg;

    int calcPerimeter(Mat img);

};

#endif // SHAPEFEATUREEXTRACTOR_H
