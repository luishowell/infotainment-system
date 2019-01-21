#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QWidget>
#include "types.h"
#include "MainMenu.h"
#include "Diagnostics.h"
#include "Parking.h"
#include "ErrorCodes.h"
#include "Media.h"



class StateManager : public QWidget
{
    Q_OBJECT

public:
    explicit StateManager(QWidget *parent = 0);

public slots:
    void ChangeRequested(state_t req_state, QWidget* self);
    void CANPublishDiagRx(diagMsg_t* msg);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    MainMenu *m_mainMenu;
    Diagnostics *m_diags;
    Parking *m_parking;
    ErrorCodes *m_errorCodes;
    Media *m_media;
    
};

#endif // STATEMANAGER_H