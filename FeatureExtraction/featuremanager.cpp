#include "featuremanager.h"

FeatureManager* FeatureManager::mInstance = NULL;

FeatureManager::FeatureManager(QObject *parent) : QObject(parent)
{
    mColorExtr = new ColorFeatureExtractor;
    mTextureExtr = new TextureFeatureExtractor;
    mShapeExtr = new ShapeFeatureExtractor;

    mDirBinaryImage = "D:\\GoogleDrive\\Master\ Thesis\\images\\Binary\ image\\";
    mDirBgRemovedImage = "D:\\GoogleDrive\\Master\ Thesis\\images\\Remove\ Background\ Image\\";
}

Mat FeatureManager::img() const
{
    return mImg;
}

void FeatureManager::setImg(const Mat &img)
{
    mImg = img;
    mColorExtr->setImg(mImg);
    mTextureExtr->setImg(mImg);
    mShapeExtr->setImg(mImg);
}

QList<double> FeatureManager::calcFeatures(QString bgRemovedImgPath, QString binaryImgPath)
{
    QList<double> rs;

    rs.append(extractColorFeatures(bgRemovedImgPath));
    rs.append(extractTextureFeatures(bgRemovedImgPath));
    rs.append(extractShapeFeatures(binaryImgPath));

    return rs;
}

QHash<int, QList<double> > FeatureManager::extractFeatures(QString fruit, int imgCount)
{
    QHash<int, QList<double> > rs;
    for (int i = 1; i <= imgCount; ++i) {
        QList<double> features;
        QString binaryImgPath = QString("%1%2-bg\\%3.png").arg(mDirBinaryImage).arg(fruit).arg(i);
        QString bgRemovedImgPath = QString("%1%2\\%3.jpg").arg(mDirBgRemovedImage).arg(fruit).arg(i);
        features.append(extractColorFeatures(bgRemovedImgPath));
        features.append(extractTextureFeatures(bgRemovedImgPath));
        features.append(extractShapeFeatures(binaryImgPath));

        rs.insert(i, features);
    }
    return rs;
}

QHash<int, QList<double> > FeatureManager::extractFeaturesForTestData(QString fruit, int imgStart, int imgEnd)
{
    QHash<int, QList<double> > rs;
    for (int i = imgStart; i <= imgEnd; ++i) {
        QList<double> features;
        QString binaryImgPath = QString("%1%2-bg\\%3.png").arg(mDirBinaryImage).arg(fruit).arg(i);
        QString bgRemovedImgPath = QString("%1%2\\%3.jpg").arg(mDirBgRemovedImage).arg(fruit).arg(i);
        features.append(extractColorFeatures(bgRemovedImgPath));
        features.append(extractTextureFeatures(bgRemovedImgPath));
        features.append(extractShapeFeatures(binaryImgPath));

        rs.insert(i, features);
    }
    return rs;
}

QList<double> FeatureManager::extractColorFeatures(QString imgPath)
{
    qDebug() << "extractColorFeatures imgPath:" << imgPath;
    return mColorExtr->calcFeatures(imgPath);
}

QList<double> FeatureManager::extractTextureFeatures(QString imgPath)
{
    qDebug() << "extractTextureFeatures imgPath:" << imgPath;
    return mTextureExtr->calcFeatures(imgPath);
}

QList<double> FeatureManager::extractShapeFeatures(QString imgPath)
{
    qDebug() << "extractShapeFeatures imgPath:" << imgPath;
    return mShapeExtr->calcFeatures(imgPath);
}

FeatureManager *FeatureManager::instance()
{
    if (mInstance == NULL) {
        mInstance = new FeatureManager;
    }
    return mInstance;
}
