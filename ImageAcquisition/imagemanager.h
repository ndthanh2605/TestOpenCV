#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QList>
#include <QDebug>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = 0);


    QList<Mat> listImages() const;

signals:

public slots:

private:
    QList<Mat> mListImages;

};

#endif // IMAGEMANAGER_H
