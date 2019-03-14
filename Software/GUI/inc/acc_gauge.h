#include <QWidget>
#include <QLabel>
#include <glm/glm.hpp>

class AccGauge : public QWidget {

public:
    AccGauge(float max_G, int size=0, QWidget *parent = 0);

    int _size;
    float _max_G;

private:
    QLabel *label;

    float _acc_x;
    float _acc_y;
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