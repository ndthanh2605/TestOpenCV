#include "artificialneutralnetwork.h"

ArtificialNeutralNetwork::ArtificialNeutralNetwork(QObject *parent) : QObject(parent)
{

}

void ArtificialNeutralNetwork::createTestData()
{
    // features: 12 color + 10 texture + 2 shape
    QHash<int, QList<double> > allFeatures_1 = FeatureManager::instance()->extractFeaturesForTestData("chom chom", 6, 7);
    QHash<int, QList<double> > allFeatures_2 = FeatureManager::instance()->extractFeaturesForTestData("hong", 21, 27);
    QHash<int, QList<double> > allFeatures_3 = FeatureManager::instance()->extractFeaturesForTestData("le", 6, 7);
    QHash<int, QList<double> > allFeatures_4 = FeatureManager::instance()->extractFeaturesForTestData("luu", 7, 8);
    QHash<int, QList<double> > allFeatures_5 = FeatureManager::instance()->extractFeaturesForTestData("tao", 51, 66);
    QHash<int, QList<double> > allFeatures_6 = FeatureManager::instance()->extractFeaturesForTestData("xoai", 14, 17);

    QFile file("test.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        foreach (int key, allFeatures_1.keys()) {
            out << "0,";
            QList<double> features = allFeatures_1.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_2.keys()) {
            out << "1,";
            QList<double> features = allFeatures_2.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_3.keys()) {
            out << "2,";
            QList<double> features = allFeatures_3.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_4.keys()) {
            out << "3,";
            QList<double> features = allFeatures_4.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_5.keys()) {
            out << "4,";
            QList<double> features = allFeatures_5.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_6.keys()) {
            out << "5,";
            QList<double> features = allFeatures_6.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }

        file.close();
    } else {
        qDebug() << "ERROR createTestData";
    }
}

void ArtificialNeutralNetwork::createTrainingData()
{
    // features: 12 color + 10 texture + 2 shape
    QHash<int, QList<double> > allFeatures_1 = FeatureManager::instance()->extractFeatures("chom chom", 5);
    QHash<int, QList<double> > allFeatures_2 = FeatureManager::instance()->extractFeatures("hong", 20);
    QHash<int, QList<double> > allFeatures_3 = FeatureManager::instance()->extractFeatures("le", 5);
    QHash<int, QList<double> > allFeatures_4 = FeatureManager::instance()->extractFeatures("luu", 6);
    QHash<int, QList<double> > allFeatures_5 = FeatureManager::instance()->extractFeatures("tao", 50);
    QHash<int, QList<double> > allFeatures_6 = FeatureManager::instance()->extractFeatures("xoai", 13);

    QFile file("data.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        foreach (int key, allFeatures_1.keys()) {
            out << "0,";
            QList<double> features = allFeatures_1.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_2.keys()) {
            out << "1,";
            QList<double> features = allFeatures_2.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_3.keys()) {
            out << "2,";
            QList<double> features = allFeatures_3.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_4.keys()) {
            out << "3,";
            QList<double> features = allFeatures_4.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_5.keys()) {
            out << "4,";
            QList<double> features = allFeatures_5.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }
        foreach (int key, allFeatures_6.keys()) {
            out << "5,";
            QList<double> features = allFeatures_6.value(key);
            for (int i = 0; i < features.count(); ++i) {
                out << features.at(i) << ",";
            }
            out << "\n";
        }

        file.close();
    } else {
        qDebug() << "ERROR createTestData";
    }
}

void ArtificialNeutralNetwork::startTraining()
{
    cv::Mat training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F);
    cv::Mat training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F);
    cv::Mat classificationResult(1, CLASSES, CV_32F);
    cv::Mat test_set(TEST_SAMPLES,ATTRIBUTES,CV_32F);
    cv::Mat test_set_classifications(TEST_SAMPLES,CLASSES,CV_32F);

    readFeatureData("data.txt", training_set, training_set_classifications, TRAINING_SAMPLES);
    readFeatureData("test.txt", test_set, test_set_classifications, TEST_SAMPLES);

    Mat layers(3,1,CV_32S);
    layers.at<int>(0,0) = ATTRIBUTES;   //input layer
    layers.at<int>(1,0) = 16;             //hidden layer
    layers.at<int>(2,0) = CLASSES;       //output layer

    CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);
    CvANN_MLP_TrainParams params(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),
                                 CvANN_MLP_TrainParams::BACKPROP, 0.1, 0.1);

    qDebug() << "\nUsing training dataset\n";
    int iterations = nnetwork.train(training_set, training_set_classifications,Mat(),Mat(),params);
    qDebug() << "Training iterations:" << iterations << "\n";

    CvFileStorage* storage = cvOpenFileStorage("params.xml", 0, CV_STORAGE_WRITE );
    nnetwork.write(storage,"FruitRecog");
    cvReleaseFileStorage(&storage);

    Mat test_sample;
    int correct_class = 0;
    int wrong_class = 0;
    int classification_matrix[CLASSES][CLASSES] = { { } };
    for (int tsample = 0; tsample < TEST_SAMPLES; tsample++) {
        test_sample = test_set.row(tsample);
        nnetwork.predict(test_sample, classificationResult);
        int maxIndex = 0;
        float value = 0.0f;
        float maxValue = classificationResult.at<float>(0,0);
        qDebug() << "\nchecking Testing Sample" << tsample << "index 0 value" << maxValue;
        for(int index = 1; index < CLASSES; index++) {
            value = classificationResult.at<float>(0,index);
            qDebug() << "checking Testing Sample" << tsample << "index" << index << "value" << value;
            if(value > maxValue) {
                maxValue = value;
                maxIndex = index;
            }
        }
        qDebug() << "Testing Sample" << tsample << "-> class result (type" << maxIndex << ")";

        if (test_set_classifications.at<float>(tsample, maxIndex) != 1.0f)
        {
           wrong_class++;
            for(int class_index = 0; class_index < CLASSES; class_index++) {
                if(test_set_classifications.at<float>(tsample, class_index) == 1.0f) {
                    classification_matrix[class_index][maxIndex]++;// A class_index sample was wrongly classified as maxindex.
                    break;
                }
            }
        } else {
            correct_class++;
            classification_matrix[maxIndex][maxIndex]++;
        }
    }

    qDebug() << "Results on the testing dataset";
    qDebug() << "\tCorrect classification:" << correct_class;
    qDebug() << "\tWrong classifications:" << wrong_class;
}

void ArtificialNeutralNetwork::startTesting()
{

}

void ArtificialNeutralNetwork::readFeatureData(char *filename, Mat &data, Mat &classes, int imgCount)
{
    int label;
    float value;

    FILE* inputfile = fopen(filename, "r" );

    for(int row = 0; row < imgCount; row++) {
        fscanf(inputfile, "%i,", &label);
        classes.at<float>(row,label) = 1.0;

        for(int col = 0; col < ATTRIBUTES; col++) {
            fscanf(inputfile, "%f,", &value);
            data.at<float>(row,col) = value;
//            qDebug() << "readFeatureData row" << row << "col" << col << "- value" << value;
        }
    }

    fclose(inputfile);
}

