//Author: Matthew Williams

#include "linearregressionmodel.h"
#include <cmath>
#include <QObject>
#include <QDebug>
using std::pow;

//Constructor does nothing
LinearRegressionModel::LinearRegressionModel(double _weight, double _bias, double _learn_rate, double bias_lr_modifier) {
    //Instantiate Member Variables
    weight = _weight;
    bias = _bias;
    learn_rate = _learn_rate;
    bias_learn_rate_modifier = bias_lr_modifier;
}


vector<double> LinearRegressionModel::iterateDescent(vector<QPoint>& points) {
    vector<double> predictions = predictAll(points);
    vector<double> gradients = findGradients(points, predictions);
    bias += gradients[0] * learn_rate * bias_learn_rate_modifier;
    weight -= gradients[1] * learn_rate;

    double gradient_approx = (gradients[0] + gradients[1]) * learn_rate;

    if (gradient_approx > -quit_threshold && gradient_approx < quit_threshold) {
        vector<double> returnVals;
        returnVals.push_back(0);
        return returnVals;
    }

    vector<double> returnLine;
    returnLine.push_back(weight);
    returnLine.push_back(bias);
    return returnLine;
}

double LinearRegressionModel::predict(double x) {
    return (weight * x) + bias;
}

double LinearRegressionModel::getError(vector<QPoint>& points) {
    vector<double> predictions = predictAll(points);
    double error = 0;

    for (vector<QPoint>::size_type i = 0; i < points.size(); i++) {
        error += pow(predictions[i] - points[i].ry(), 2);
    }

    error /= points.size();
    return error;
}

vector<double> LinearRegressionModel::findGradients(vector<QPoint>& points, vector<double>& predictions) {
    int len = predictions.size();
    double diffSum = 0;
    double weightedDiffSum = 0;

    for (int i = 0; i < len; i++) {
        double current_temp = points[i].ry() - predictions[i];
        // \sum (y - y_hat)
        diffSum += current_temp;
        // \sum (y - y_hat) x
        weightedDiffSum += current_temp * points[i].rx();
    }
    vector<double> gradient;
    gradient.push_back(weightedDiffSum / len);
    gradient.push_back(diffSum / len);

    return gradient;
}

vector<double> LinearRegressionModel::predictAll(vector<QPoint>& points) {
    vector<double> predictions;
    for (int i = 0; i < points.size(); i++) {
        predictions.push_back(predict(points[i].rx()));
    }
    return predictions;
}
