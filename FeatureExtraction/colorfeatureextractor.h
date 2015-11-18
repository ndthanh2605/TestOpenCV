#ifndef COLORFEATUREEXTRACTOR_H
#define COLORFEATUREEXTRACTOR_H

#include <QObject>
#include <QList>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class ColorFeatureExtractor : public QObject
{
    Q_OBJECT
public:
    explicit ColorFeatureExtractor(QObject *parent = 0);

    QList<double> calcFeatures(QString imgPath);
    void testCalcColorFeatures();

    Mat img() const;
    void setImg(const Mat &img);

signals:

public slots:

private:
    Mat mImg;
    Mat mImgHSV;

    Mat imgHSVfromRGB(Mat img);

};

#endif // COLORFEATUREEXTRACTOR_H
