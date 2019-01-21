#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include "types.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    
public slots:
    void StateChangeDiag();
    void StateChangeMedia();
    void StateChangeParking();
    void StateChangeErrorCodes();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_mediaButton;
    QPushButton *m_diagButton;
    QPushButton *m_errorButton;
    QPushButton *m_parkButton;
    void CreateLayout();
};

#endif // MAINMENU_H