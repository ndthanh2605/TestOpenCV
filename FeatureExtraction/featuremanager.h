#ifndef FEATUREMANAGER_H
#define FEATUREMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QStringList>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

#include "colorfeatureextractor.h"
#include "texturefeatureextractor.h"
#include "shapefeatureextractor.h"

using namespace cv;

class FeatureManager : public QObject
{
    Q_OBJECT
public:
    static FeatureManager *instance();

    Mat img() const;
    void setImg(const Mat &img);

    QList<double> calcFeatures(QString bgRemovedImgPath, QString binaryImgPath);
    QHash<int, QList<double> > extractFeatures(QString fruit, int imgCount);
    QHash<int, QList<double> > extractFeaturesForTestData(QString fruit, int imgStart, int imgEnd);

signals:

public slots:

private:
    static FeatureManager *mInstance;
    Mat mImg;
    ColorFeatureExtractor *mColorExtr;
    TextureFeatureExtractor *mTextureExtr;
    ShapeFeatureExtractor *mShapeExtr;
    QString mDirBinaryImage;
    QString mDirBgRemovedImage;

    QList<double> mExtractedFeatures;

    explicit FeatureManager(QObject *parent = 0);
    QList<double> extractColorFeatures(QString imgPath);
    QList<double> extractTextureFeatures(QString imgPath);
    QList<double> extractShapeFeatures(QString imgPath);

};

#endif // FEATUREMANAGER_H
