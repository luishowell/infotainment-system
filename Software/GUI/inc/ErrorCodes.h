/**
 * @file ErrorCodes.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ERRORCODES_h
#define ERRORCODES_h

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QObject>

#ifndef GUI_TEST
#include "obd2.hpp"
#endif

#include "types.h"

/**
 * @brief 
 * 
 */
class ErrorCodes : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief Construct a new Error Codes object
     * 
     * @param parent 
     * @param myObd 
     */
    explicit ErrorCodes(QWidget *parent = 0, obd2* myObd = 0);

    /**
     * @brief 
     * 
     */
    obd2* obd;

    
public slots:

    /**
     * @brief 
     * 
     */
    void StateChangeMainMenu();

signals:

    /**
     * @brief 
     * 
     * @param req_state 
     * @param currentView 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private:

    QPushButton *m_homeButton;
    QPushButton *getButton;
    QPushButton *clearButton;
    QTableWidget *errorTable;
    
    /**
     * @brief 
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