#include <QVBoxLayout>
#include <QFont>
#include <QPixmap>
#include <QPainter>

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include "AccGauge.h"


AccGauge::AccGauge(float max_G, accValues_t* acc_cal, int size, QWidget *parent)
: QWidget(parent), _max_G(max_G), x_axis(1.0, 0.0, 0.0), y_axis(0.0, 1.0, 0.0), z_axis(0.0, 0.0, 1.0)
{
  if (size!=0)
  {
    _size=size;
    resize_widget = false;
  }    

  glm::vec3 acc_down(acc_cal->xAxis, acc_cal->yAxis, acc_cal->zAxis);
  _z_rot = radians(270)-xy_angle(acc_down);   
  glm::vec3 rotated = rotate(acc_down, z_axis, _z_rot);
  _x_rot = radians(270)-yz_angle(rotated);

    label = new QLabel();
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(label);
    setLayout(vbox);
}


float AccGauge::degrees(float rad)
{
    float degree = rad * 180.0/M_PI;
    return degree;
}
float AccGauge::radians(float deg)
{
    float radian = deg * M_PI/180.0;
    return radian;
}


float AccGauge::xy_angle(const glm::vec3& v)
{
    float x1 = 1;
    float y1 = 0;
    float x2 = v.x;
    float y2 = v.y;

    float dot = x1*x2 + y1*y2;      
    float det = x1*y2 - y1*x2;     
    float rad = atan2(det, dot);

    if (rad<0)
    {
        rad = radians(360)+rad;
    }
    
    return rad;
}
float AccGauge::yz_angle(const glm::vec3& v)
{
    float x1 = 1;
    float y1 = 0;
    float x2 = v.y;
    float y2 = v.z;

    float dot = x1*x2 + y1*y2;      
    float det = x1*y2 - y1*x2;     
    float rad = atan2(det, dot);

    if (rad<0)
    {
        rad = radians(360)+rad;
    }
    
    return rad;
}
float AccGauge::xz_angle(const glm::vec3& v)
{
    float x1 = 1;
    float y1 = 0;
    float x2 = v.x;
    float y2 = v.z;

    float dot = x1*x2 + y1*y2;      
    float det = x1*y2 - y1*x2;     
    float rad = atan2(det, dot);

    if (rad<0)
    {
        rad = radians(360)+rad;
    }
    
    return rad;
}


glm::vec3 AccGauge::rotate(const glm::vec3& v, const glm::vec3& k, float theta)
{
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);

    glm::vec3 rotated = (v * cos_theta) + (glm::cross(k, v) * sin_theta) + (k * glm::dot(k, v)) * (1 - cos_theta);

    return rotated;
}

void AccGauge::update_gauge(accValues_t* acc_value)
{
  glm::vec3 v(acc_value->xAxis, acc_value->yAxis, acc_value->zAxis);

  glm::vec3 rotated = rotate(v, z_axis, _z_rot);
  rotated = rotate(rotated, x_axis, _x_rot);

  _acc_x = -rotated.x;
  _acc_y = rotated.y;
  update();
}


void AccGauge::paintEvent(QPaintEvent *e) 
{    
  Q_UNUSED(e);
  QPixmap drawing(_size, _size);
  drawing.fill(QWidget::palette().color(QWidget::backgroundRole()));
  QPainter qp(&drawing);
  draw_acc_viz(&qp);
  label->setPixmap(drawing);
}


void AccGauge::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    if (resize_widget)
    {
      int width = this->width()-25;
      int height = this->height()-25;
      // std::cout<<"Width: "<<this->width()<<std::endl;
      // std::cout<<"Height: "<<this->height()<<std::endl;
      if (width<height)
      {
          _size = width;
      }
      else
      {
          _size = height;
      }
    }
}


void AccGauge::draw_acc_viz(QPainter *qp)
{

  //placeholder
  //_acc_x = 1;
  //_acc_y = -1;

  int dot_radius = int(_size*0.05);
  
    int centre_x = int(_size/2);
    int centre_y = int(_size/2);

    QPen pen1(Qt::black, 1, Qt::SolidLine);    
  
    qp->setPen(pen1);
    float G_inc = _max_G/3.0;
    for (float g_marker=G_inc;g_marker<=_max_G;g_marker=g_marker+G_inc)
    {
        qp->drawEllipse(QPointF(centre_x,centre_y), G2pix(g_marker), G2pix(g_marker));
    }    
    QString max_G_string = QString::number(_max_G)+"G";
    qp->drawText(centre_x-13, centre_y-G2pix(_max_G)+15, max_G_string); 
    
    //qp->setPen(solid);
    qp->setBrush(Qt::black);
    qp->drawEllipse(QPointF(centre_x+G2pix(_acc_x),centre_y-G2pix(_acc_y)), dot_radius, dot_radius);   
}


int AccGauge::G2pix(float input_G)
{
  float input_start = -_max_G;
  float input_end = _max_G;
  int output_start = int(-0.9*_size/2.0);
  int output_end = int(0.9*_size/2.0);

  if (input_G>input_end)
  {
    input_G = input_end;
  }
  else if (input_G<input_start)
  {
    input_G = input_start;
  }

  return int(output_start + ((output_end - output_start) / (input_end - input_start)) * (input_G - input_start));
}