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

class ErrorCodes : public QWidget
{
    Q_OBJECT
public:
    explicit ErrorCodes(QWidget *parent = 0, obd2* myObd = 0);

    #ifndef GUI_TEST
    obd2* obd;
    #endif
    
public slots:
    void StateChangeMainMenu();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_homeButton;
    QPushButton *getButton;
    QPushButton *clearButton;
    QTableWidget *errorTable;
    
    void CreateLayout();

private slots:
    void get_error_codes();
    void clear_error_codes();
};

#endif // ERRORCODES_h