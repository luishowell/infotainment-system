/**
 * @file acc_gauge.h
 * @author Luis Howell
 * @brief An accelerometer gauge QWidget
 * @version 0.1
 * @date 2019-03-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ACCGAUGE_H
#define ACCGAUGE_H

#include <QWidget>
#include <QLabel>
#include <glm/glm.hpp>
#include "types.h"

/**
 * @brief An accelerometer gauge QWidget to display g-force
 * 
 */

class AccGauge : public QWidget {

public:

    /**
     * @brief Construct a new Acc Gauge object
     * 
     * @param max_G The maximum G for the gauge
     * @param acc_cal A set of accelerometer readings while the car is still and level
     * @param size Optional, set a constant size for the gauge in pixels
     * @param parent Optional, QWidget parent
     */
    AccGauge(float max_G, int size=0, QWidget *parent = 0);

    int _size;
    float _max_G;

    /**
     * @brief Update accelerometer gauge
     * 
     * @param acc_value An accValues_t type containing a set of acc readings
     */
    void update_gauge(accValues_t* acc_value);

    bool calibrate(accValues_t* acc_cal);

private:
    QLabel *label;

    float _acc_x;
    float _acc_y;
    float _z_rot;
    float _x_rot;
    glm::vec3 x_axis;
    glm::vec3 y_axis;
    glm::vec3 z_axis;
    bool resize_widget = true;

    /**
     * @brief Converts an angle in radians to degrees
     * 
     * @param rad an angle in radians
     * @return float an angle in degrees
     */
    float degrees(float rad);

    /**
     * @brief Converts an angle in degrees to an angle in radians
     * 
     * @param deg an angle in degrees
     * @return float an angle in radians 
     */
    float radians(float deg);

    /**
     * @brief Calculates the clockwise angle of a vector in the xy plane
     * 
     * @param v a glm::vec3 vector
     * @return float the angle in radians
     */
    float xy_angle(const glm::vec3& v);

    /**
     * @brief Calculates the clockwise angle of a vector in the yz plane
     * 
     * @param v a glm::vec3 vector
     * @return float the angle in radians
     */
    float yz_angle(const glm::vec3& v);

    /**
     * @brief Calculates the clockwise angle of a vector in the xz plane
     * 
     * @param v a glm::vec3 vector
     * @return float the angle in radians
     */
    float xz_angle(const glm::vec3& v);

    /**
     * @brief rotates a vector around an axis
     * 
     * @param v a glm::vec3 vector to be rotated
     * @param k a glm::vec3 representing the axis of rotation eg x: (1, 0, 0)
     * @param theta the angle to be rotated in radians
     * @return glm::vec3 The rotated vector
     */
    glm::vec3 rotate(const glm::vec3& v, const glm::vec3& k, float theta);

    /**
     * @brief Converts a G value from the accelerometer into pixels
     * 
     * @param input_G An accelerometer reading in G
     * @return int The G value in pixels
     */
    int G2pix(float input_G);

protected:

    /**
     * @brief Updates the gauge label with a new pixmap conating the viz drawing
     * 
     * @param event QPaintEvent
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Resizes the widget
     * 
     * @param event QResizeEvent
     */
    void resizeEvent(QResizeEvent * event);

    /**
     * @brief Draws accelerometer visulisation
     * 
     * @param qp QPainter object
     */
    void draw_acc_viz(QPainter *qp);
};

#endif //ACCGAUGE_H