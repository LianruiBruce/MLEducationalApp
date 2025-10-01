#ifndef LINEARREGRESSIONMODEL_H
#define LINEARREGRESSIONMODEL_H

//Author: Matthew Williams

#include <vector>
#include <QPoint>
using std::vector;

///
/// \brief The LinearRegressionModel class acts as the Machine Learning
///        Model for the program.  It can be incremented, and the current
///        Error and Predictions can be accessed for given points.
///
class LinearRegressionModel {

public:
    ///
    /// \brief Instantiates the model with parameters
    /// \param _weight Slope of prediction line
    /// \param _bias Y-intercept of prediction line
    /// \param _learn_rate Learn rate parameter of simple gradient descent
    ///
    LinearRegressionModel(double _weight, double _bias, double _learn_rate=0.001, double bias_lr_modifier=1.7);

    ///
    /// \brief Applies one step of simple gradient descent to the model's
    ///        weight and bias, given the points passed in.
    /// \param points The vector of points that exist in the scatter-plot
    ///
    vector<double> iterateDescent(vector<QPoint>& points);

    ///
    /// \brief Returns the current model's prediction, given the input
    ///        point x.
    /// \param x The point at which the model should predict a "y" value for
    /// \return The predicted "y" value associated with the given "x" value
    ///
    double predict(double x);

    ///
    /// \brief Returns the model's Least Squared Error value on the given
    ///        dataset.
    /// \param points The vector representing the scatter-plot dataset
    /// \return The error of the model (Least Squared Error)
    ///
    double getError(vector<QPoint>& points);


private:
    // The slope of the prediction line
    double weight;
    // The y-intercept of the prediction line
    double bias;
    // The rate of learning (Gradient Descent parameter)
    double learn_rate;
    // Multiplies the learn rate for the bias (more visually appealing)
    double bias_learn_rate_modifier;
    // When the gradients' sum multiplied by the learn rate is less than this, we stop
    double quit_threshold = 0.0001;

    // Returns a vector containing the weight's gradient in the "0" index position,
    //  and the bias's gradient in the "1" index position.
    vector<double> findGradients(vector<QPoint>& points, vector<double>& predictions);

    // Returns a vector containing the predictions from the model for
    //  each given x value.
    vector<double> predictAll(vector<QPoint>& points);

};

#endif // LINEARREGRESSIONMODEL_H
