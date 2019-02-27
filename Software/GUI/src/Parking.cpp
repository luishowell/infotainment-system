 /**
 * @file Parking.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
 
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QPainter>
#include <iostream>
#include <vector>
#include <math.h>
#include "Parking.h"
#include "config.h"

using namespace std;


int Parking::round_float(float input)
{
  if (input>0)
  {
    return int(input+0.5);
  }
  else
  {
    return int(input-0.5);
  }
}


int Parking::dist2pix(float input_dist)
{
  float input_start = 0.0;
  float input_end = 2.0;
  int output_start = 0;
  int output_end = 80;

  if (input_dist>input_end)
  {
    input_dist = input_end;
  }
  else if (input_dist<input_start)
  {
    input_dist = input_start;
  }

  return int(output_start + ((output_end - output_start) / (input_end - input_start)) * (input_dist - input_start));
}


float Parking::deg2rad(float deg)
{
  return (3.14*deg)/180.0;
}


vector<int> Parking::calc_line_coor(int centre_x, int centre_y, int bar_width, int angle)
{
  vector<int> coords;
  float x1, x2, y1, y2;

  float rad = deg2rad(angle);
 
  x1 = cos(rad)*(bar_width/2.0);
  y1 = sin(rad)*(bar_width/2.0);
  y1 = -y1; //flipped as y pixel axis is opposite

  x2 = -x1;
  y2 = -y1;

  x1=x1+centre_x;
  y1=y1+centre_y;

  x2=x2+centre_x;
  y2=y2+centre_y;

  coords.push_back(round_float(x1));
  coords.push_back(round_float(y1));
  coords.push_back(round_float(x2));
  coords.push_back(round_float(y2));

  return coords;
}

/**
 * @brief Construct a new Parking:: Parking object
 * 
 * @param parent 
 */
Parking::Parking(QWidget *parent) : QWidget(parent) 
{
     
  setFixedSize(widgetSize);

  CreateLayout();    

  connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));
    
}

/**
 * @brief 
 * 
 */
void Parking::StateChangeMainMenu()
{
  emit DisplayChange(MAIN_MENU, this);
}

/**
 * @brief 
 * 
 */
void Parking::CreateLayout()
{
  QVBoxLayout* vLayout = new QVBoxLayout(this);
  vLayout->setSpacing(25);

  QGroupBox* titleBox = new QGroupBox("Parking Mode", this);
  titleBox->setAlignment(Qt::AlignHCenter);

  QGridLayout* boxLayout = new QGridLayout(titleBox);
  boxLayout->setVerticalSpacing(10);

  m_homeButton = new QPushButton("Home");
  m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);

  titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
  vLayout->addWidget(titleBox);
  vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}

void Parking::SensorRx(sensorDist_t* msg)
{
  //std::cout << "SENSOR DATA: " << msg->rearLeft << std::endl;
  frontCentre = msg->frontCentre;
  frontRight = msg->frontRight;
  frontLeft = msg->frontLeft;
  rearCentre = msg->rearCentre;
  rearRight = msg->rearRight;
  rearLeft = msg->rearLeft;
  update();
}


void Parking::paintEvent(QPaintEvent *e) 
{    
  Q_UNUSED(e);
  
  QPainter qp(this);
  draw_sensor_lines(&qp);
}


void Parking::draw_sensor_lines(QPainter *qp) 
{
  int centre_offset = -40;
  int centre_x = 800/4;
  int centre_y = 480/2+centre_offset;
  int car_width = 50;
  int car_length = int(car_width*1.5);
  int bar_width = int(car_width*0.5);

  QPen pen(Qt::black, 2, Qt::SolidLine);  
  qp->setPen(pen);
  qp->drawRect(centre_x-(car_width/2), centre_y-(car_length/2), car_width, car_length);

  vector<int> line_coords;
  int x, y;

  // front centre
  x = centre_x;
  y = centre_y-(car_length/2)-dist2pix(frontCentre);
  line_coords = calc_line_coor(x, y, bar_width, 0);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);

  //front right
  x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(frontRight);
  y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(frontRight);
  line_coords = calc_line_coor(x, y, bar_width, -45);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);

  //front left
  x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(frontLeft);
  y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(frontLeft);
  line_coords = calc_line_coor(x, y, bar_width, 45);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);


  //rear centre
  x = centre_x;
  y = centre_y+(car_length/2)+dist2pix(rearCentre);
  line_coords = calc_line_coor(x, y, bar_width, 0);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);

  //rear right
  x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(rearRight);
  y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(rearRight);
  line_coords = calc_line_coor(x, y, bar_width, 45);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);

  //rear left
  x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(rearLeft);
  y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(rearLeft);
  line_coords = calc_line_coor(x, y, bar_width, -45);
  qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
}

