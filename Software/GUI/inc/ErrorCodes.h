#ifndef ERRORCODES_h
#define ERRORCODES_h

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include "types.h"

class ErrorCodes : public QWidget
{
    Q_OBJECT
public:
    explicit ErrorCodes(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_homeButton;
    void CreateLayout();
};

#endif // ERRORCODES_h