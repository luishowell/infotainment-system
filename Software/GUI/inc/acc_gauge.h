#include <QWidget>
#include <QLabel>
#include <glm/glm.hpp>
#include "sensorTypes.h"

class AccGauge : public QWidget {

public:
    AccGauge(float max_G, accValues_t acc_cal, int size=0, QWidget *parent = 0);

    int _size;
    float _max_G;

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

    float degrees(float rad);
    float radians(float deg);
    float xy_angle(const glm::vec3& v);
    float yz_angle(const glm::vec3& v);
    float xz_angle(const glm::vec3& v);
    glm::vec3 rotate(const glm::vec3& v, const glm::vec3& k, float theta);
    int G2pix(float input_G);

protected:
    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent * event);

    /**
     * @brief Draws accelerometer visulisation
     * 
     * @param qp QPainter object
     */
    void draw_acc_viz(QPainter *qp);
};