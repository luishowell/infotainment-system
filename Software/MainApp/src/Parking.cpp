 /**
 * @file Parking.cpp
 * @author Jamie Brown/Luis Howell
 * @brief Implementation of Parking.
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
#include <QtMultimedia/QCamera>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QPixmap>
#include <QLabel>

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

Parking::Parking(QWidget *parent) : QWidget(parent) 
{
     
  setFixedSize(widgetSize);

  beep_effect = new QSoundEffect;
  beep_effect->setSource(QUrl::fromLocalFile("./MainApp/src/beep.wav"));
  beep_effect->setLoopCount(1);
  beep_effect->setVolume(1.0f); 

  m_timer = new QTimer;
  beep_timer = new QElapsedTimer;
  connect(m_timer, SIGNAL(timeout()), this, SLOT(parking_beep()));

  CreateLayout();   

  m_timer->start(1);
  beep_timer->start();

  connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));    
}

void Parking::parking_beep()
{
  if (!beep_effect->isPlaying())
  {
    if ((int(beep_timer->elapsed())>=beep_delay)&&(viz_label->isVisible())&&(beep_delay>0)&&(smallest_dist<1.5))
    {
      beep_effect->play();
      beep_timer->start();
    }   
  }
}

void Parking::calc_beep_delay()
{
  float input_start = 0.0;
  float input_end = 2.0;
  int output_start = 100;
  int output_end = 2000;

  if (smallest_dist>input_end)
  {
    smallest_dist = input_end;
  }
  else if (smallest_dist<input_start)
  {
    smallest_dist = input_start;
  }

  beep_delay = int(output_start + ((output_end - output_start) / (input_end - input_start)) * (smallest_dist - input_start)); 
}

void Parking::calc_smallest_dist()
{
  double dist_array[6] = {rearLeft, rearRight, rearCentre, frontLeft, frontRight, frontCentre};
  bool connected_array[6] = {rearLeftConnected, rearRightConnected, rearCentreConnected, frontLeftConnected, frontRightConnected, frontCentreConnected};
  double min_dist = 10.0;

  for (int i=0; i<6; i++)
  {
    if ((dist_array[i]<min_dist)&&connected_array[i])
    {
      min_dist = dist_array[i];
    }
  }

  smallest_dist = min_dist;  
}

void Parking::StateChangeMainMenu()
{
  emit DisplayChange(MAIN_MENU, this);
}

void Parking::CreateLayout()
{
  QVBoxLayout* vLayout = new QVBoxLayout(this);
  vLayout->setSpacing(25);

  QGroupBox* titleBox = new QGroupBox("Parking Mode", this);
  titleBox->setAlignment(Qt::AlignHCenter);

  QHBoxLayout* hbox = new QHBoxLayout;

  cout<<"Cameras: "<<QCameraInfo::availableCameras().count()<<endl;

  QCamera* cam = new QCamera();  
  QCameraViewfinder* viewf = new QCameraViewfinder;
  //QCameraViewfinder* viewf = new QCameraViewfinder(titleBox);
  //viewf->setGeometry(400, 30, 360, 260);

  cam->setViewfinder(viewf);
 
  viz_label = new QLabel;

  hbox->addWidget(viz_label);
  hbox->addWidget(viewf);  
  titleBox->setLayout(hbox);

  cam->start();  

  m_homeButton = new QPushButton("Home");
  m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);

  titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
  vLayout->addWidget(titleBox);
  vLayout->addWidget(m_homeButton, Qt::AlignBottom);  
}

void Parking::SensorRx(sensorDist_t* msg)
{
  rearLeftConnected = msg->rearLeftConnected;
  rearRightConnected = msg->rearRightConnected;
  rearCentreConnected = msg->rearCentreConnected;
  frontLeftConnected = msg->frontLeftConnected;
  frontRightConnected = msg->frontRightConnected;
  frontCentreConnected = msg->frontCentreConnected;
  frontCentre = msg->frontCentre;
  frontRight = msg->frontRight;
  frontLeft = msg->frontLeft;
  rearCentre = msg->rearCentre;
  rearRight = msg->rearRight;
  rearLeft = msg->rearLeft;
  calc_smallest_dist();
  calc_beep_delay();
  update();
}


void Parking::paintEvent(QPaintEvent *e) 
{    
  Q_UNUSED(e);
  QPixmap drawing(240, 300);
  drawing.fill(QWidget::palette().color(QWidget::backgroundRole()));
  QPainter qp(&drawing);
  draw_sensor_lines(&qp);
  viz_label->setPixmap(drawing);
}


void Parking::draw_sensor_lines(QPainter *qp) 
{
  int centre_x = 800/4-80;
  int centre_y = 150;
  int car_width = 50;
  int car_length = int(car_width*1.5);
  int bar_width = int(car_width*0.5);
  int marker_width = int(bar_width/4);

  QPen pen2(Qt::black, 2, Qt::SolidLine);  
  QPen pen1(Qt::black, 1, Qt::SolidLine);  
  qp->setPen(pen2);
  //qp->drawRect(centre_x-(car_width/2), centre_y-(car_length/2), car_width, car_length); //drawing car
  qp->drawRoundedRect(centre_x-(car_width/2), centre_y-(car_length/2), car_width, car_length, 40.0, 20.0, Qt::RelativeSize);

  vector<int> line_coords;
  int x, y;

  // front centre
  if (frontCentreConnected)
  {    
    x = centre_x;
    y = centre_y-(car_length/2)-dist2pix(frontCentre);
    line_coords = calc_line_coor(x, y, bar_width, 0);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = centre_x;
    y = centre_y-(car_length/2)-dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, 0);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->drawText(centre_x+marker_width, centre_y-(car_length/2)-dist2pix(2.0)+4, "2.0m");
  qp->setPen(pen2);

  //front right
  if (frontRightConnected)
  {
    x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(frontRight);
    y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(frontRight);
    line_coords = calc_line_coor(x, y, bar_width, -45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(marker_dist);
    y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, -45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen2);

  //front left
  if (frontLeftConnected)
  {
    x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(frontLeft);
    y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(frontLeft);
    line_coords = calc_line_coor(x, y, bar_width, 45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(marker_dist);
    y = (centre_y-(car_length/2))-sin(deg2rad(45))*dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, 45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen2);


  //rear centre
  if (rearCentreConnected)
  {
    x = centre_x;
    y = centre_y+(car_length/2)+dist2pix(rearCentre);
    line_coords = calc_line_coor(x, y, bar_width, 0);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = centre_x;
    y = centre_y+(car_length/2)+dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, 0);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen2);

  //rear right
  if (rearRightConnected)
  {
    x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(rearRight);
    y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(rearRight);
    line_coords = calc_line_coor(x, y, bar_width, 45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = (centre_x+(car_width/2))+cos(deg2rad(45))*dist2pix(marker_dist);
    y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, 45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen2);

  //rear left
  if (rearLeftConnected)
  {
    x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(rearLeft);
    y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(rearLeft);
    line_coords = calc_line_coor(x, y, bar_width, -45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen1); 
  for (float marker_dist=0.5; marker_dist<2.1; marker_dist=marker_dist+0.5)
  {
    if (marker_dist==2.0)
    {
      marker_width=int(bar_width*0.75);
    }
    else{
      marker_width=int(bar_width/4);
    }
    x = (centre_x-(car_width/2))-cos(deg2rad(45))*dist2pix(marker_dist);
    y = (centre_y+(car_length/2))+sin(deg2rad(45))*dist2pix(marker_dist);
    line_coords = calc_line_coor(x, y, marker_width, -45);
    qp->drawLine(line_coords[0], line_coords[1], line_coords[2], line_coords[3]);
  }
  qp->setPen(pen2);
}

