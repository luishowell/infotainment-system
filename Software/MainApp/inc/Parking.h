/**
 * @file Parking.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PARKING_H
#define PARKING_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include "types.h"
#include <vector>

class Parking : public QWidget
{
    Q_OBJECT
public:
    explicit Parking(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();

    /**
     * @brief recieves the sensor distance signals and updates the sensor visualisation
     * 
     * @param msg Struct of sensor distances
     */
    void SensorRx(sensorDist_t* msg);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_homeButton;
    QLabel *viz_label;
    void CreateLayout ();
    double rearLeft=0;
    double rearRight=0;
    double rearCentre=0;
    double frontLeft=0;
    double frontRight=0;
    double frontCentre=0;

    /**
     * @brief Round a float up or down to the nearest integer
     * 
     * @param input Float value to round
     * @return int Rounded integer value
     */
    int round_float(float input);

    /**
     * @brief Maps an ultrasonic distance to a pixel value
     * 
     * @param input_dist A float containing a sensor distance between 0-2.0m
     * @return int A value between 0-80 pixels
     */
    int dist2pix(float input_dist);

    /**
     * @brief Converts degrees to radians
     * 
     * @param deg A float value in degrees
     * @return float The value in radians
     */
    float deg2rad(float deg);

    /**
     * @brief Calculates the pixel coordinates of a line
     * 
     * @param centre_x X pixel coordinate of centre of line
     * @param centre_y Y pixel coordinate of centre of line
     * @param bar_width Length of the line in pixels 
     * @param angle Angle of line
     * @return vector<int> Four element vector of line points in order: x1, y1, x2, y2
     */
    std::vector<int> calc_line_coor(int centre_x, int centre_y, int bar_width, int angle);

protected:
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Draws ultrasonic sensor visulisation
     * 
     * @param qp QPainter object
     */
    void draw_sensor_lines(QPainter *qp);
};

#endif // PARKING_H