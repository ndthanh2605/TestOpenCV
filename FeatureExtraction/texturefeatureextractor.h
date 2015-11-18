#ifndef TEXTUREFEATUREEXTRACTOR_H
#define TEXTUREFEATUREEXTRACTOR_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/legacy/legacy.hpp>
using namespace cv;

class TextureFeatureExtractor : public QObject
{
    Q_OBJECT
public:
    explicit TextureFeatureExtractor(QObject *parent = 0);

    QList<double> calcFeatures(QString imgPath);
    void testCalcGLCM();

    Mat img() const;
    void setImg(const Mat &img);

signals:

public slots:

private:
    Mat mImg;

};

#endif // TEXTUREFEATUREEXTRACTOR_H
