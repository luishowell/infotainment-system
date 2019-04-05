/**
 * @file ErrorCodes.h
 * @author Luis Howell
 * @brief The main widget class for the fault codes screen.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ERRORCODES_h
#define ERRORCODES_h

#include "obd2.hpp"
#include "types.h"

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QObject>

class ErrorCodes : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief Construct a new Error Codes object
     * 
     * @param parent Pointer to ErrorCodes parent QWidget if exists. 
     * @param myObd Pointer to an OBD2 object. 
     */
    explicit ErrorCodes(QWidget *parent = 0, obd2* myObd = 0);

    obd2* obd;

    
public slots:

    /**
     * @brief Sends request to change to the MainMenu. 
     * 
     */
    void StateChangeMainMenu();

signals:

    /**
     * @brief Request to change to a different view. 
     * 
     * @param req_state The requested view. 
     * @param currentView A pointer to this ErrorCodes object. 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private:

    QPushButton *m_homeButton;
    QPushButton *getButton;
    QPushButton *clearButton;
    QTableWidget *errorTable;
    
    /**
     * @brief Creates child Qt widgets and lays them out. 
     * 
     */
    void CreateLayout();

private slots:

    /**
     * @brief Gets the currently stored diagnostic trouble codes (DTCs) and updates the table
     * 
     */
    void GetErrorCodes();

    /**
     * @brief Sends a clear error codes command to the OBD2 module, if successful clears the table
     * 
     */
    void ClearErrorCodes();
};

#endif // ERRORCODES_h