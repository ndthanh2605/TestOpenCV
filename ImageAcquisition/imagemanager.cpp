#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    Mat image= imread("C:\\a.jpg");
    mListImages.append(image);
}

QList<Mat> ImageManager::listImages() const
{
    return mListImages;
}

