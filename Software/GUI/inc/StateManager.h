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
    Diagnostics *m_diags;

public slots:
    void ChangeRequested(state_t req_state, QWidget* self);
    void CANPublishDiagRx(diagMsg_t* msg);
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);
    void DiagDataTx(diagMsg_t* msg);
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

private:
    MainMenu *m_mainMenu;
    
    Parking *m_parking;
    ErrorCodes *m_errorCodes;
    Media *m_media;
    
};

#endif // STATEMANAGER_H