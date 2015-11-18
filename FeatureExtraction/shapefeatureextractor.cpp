#include "shapefeatureextractor.h"

ShapeFeatureExtractor::ShapeFeatureExtractor(QObject *parent) : QObject(parent)
{

}

Mat ShapeFeatureExtractor::img() const
{
    return mImg;
}

void ShapeFeatureExtractor::setImg(const Mat &img)
{
    mImg = img;
}

QList<double> ShapeFeatureExtractor::calcFeatures(Mat img)
{
    QList<double> rs;
    if (img.empty()) {
        qDebug() << "ERROR: No image";
        return rs;
    }

    // area
    int area = countNonZero(img);
    qDebug() << "test cvCountNonZero" << area;

    // perimeter

    // minor axis length

    // major axis length

    return rs;
}

QList<double> ShapeFeatureExtractor::calcFeatures(QString imgPath)
{
    QList<double> rs;
    Mat img = imread(imgPath.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    if (img.empty()) {
        qDebug() << "ERROR: No image";
        return rs;
    }

    // area
    int area = countNonZero(img);
    rs.append(area);

    // perimeter
    int perimeter = calcPerimeter(img);
    rs.append(perimeter);

    // minor axis length

    // major axis length

    return rs;
}

int ShapeFeatureExtractor::calcPerimeter(Mat img)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    int largest_area = 0;
    int largest_contour_index = 0;
    vector<Point> hull;
    for( int i = 0; i < contours.size(); i++ ) {
        double a = contourArea( contours[i], false);
        if(a > largest_area){
            largest_area = a;
            largest_contour_index = i;
        }
    }

    convexHull( Mat(contours[largest_contour_index]), hull, false );
    return hull.size();
}

