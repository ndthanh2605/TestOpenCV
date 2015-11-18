#include "texturefeatureextractor.h"

TextureFeatureExtractor::TextureFeatureExtractor(QObject *parent) : QObject(parent)
{

}

QList<double> TextureFeatureExtractor::calcFeatures(QString imgPath)
{
    QList<double> rs;
    Mat img = imread(imgPath.toStdString());
    if (img.empty()) {
        qDebug() << "ERROR: No image";
        return rs;
    }

    Mat imgGray;
    cvtColor(img, imgGray, CV_BGR2GRAY);
    IplImage iplImg = imgGray;

    CvGLCM *glcm = cvCreateGLCM(&iplImg,1,NULL,4,CV_GLCM_OPTIMIZATION_LUT);
    cvCreateGLCMDescriptors(glcm, CV_GLCMDESC_OPTIMIZATION_ALLOWDOUBLENEST);

    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_ENTROPY));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_ENERGY));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_HOMOGENITY));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CONTRAST));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CLUSTERTENDENCY));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CLUSTERSHADE));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CORRELATION));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CORRELATIONINFO1));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_CORRELATIONINFO2));
    rs.append(cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_MAXIMUMPROBABILITY));

    return rs;
}

void TextureFeatureExtractor::testCalcGLCM()
{
    if (mImg.empty()) {
        qDebug() << "ERROR: No image";
        return;
    }

    Mat imgGray;
    cvtColor(mImg, imgGray, CV_BGR2GRAY);
    IplImage iplImg = imgGray;

    CvGLCM *glcm = cvCreateGLCM(&iplImg,1,NULL,4,CV_GLCM_OPTIMIZATION_LUT);
    cvCreateGLCMDescriptors(glcm, CV_GLCMDESC_OPTIMIZATION_ALLOWDOUBLENEST);
    qDebug() << "TextureFeatureExtractor::calcGLCM done";
    double d = cvGetGLCMDescriptor(glcm, 0, CV_GLCMDESC_HOMOGENITY );
    double a = 1; double *ave = &a;
    double s = 1; double *sd = &s;
    cvGetGLCMDescriptorStatistics(glcm, CV_GLCMDESC_ENERGY, ave, sd);
    qDebug() << "TextureFeatureExtractor::calcGLCM\n"
             << "HOMOGENITY:" << d << "AVERAGE:" << *ave << "STD DEVIATION:"  << *sd;
}

Mat TextureFeatureExtractor::img() const
{
    return mImg;
}

void TextureFeatureExtractor::setImg(const Mat &img)
{
    mImg = img;
}

