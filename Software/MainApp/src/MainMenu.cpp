/**
 * @file MainMenu.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "MainMenu.h" 
#include "config.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <Qt>
#include <QString>
#include <QSize>
#include <QIcon>

/**
 * @brief Construct a new Main Menu:: Main Menu object
 * 
 * @param parent 
 */
MainMenu::MainMenu(QWidget *parent) : QWidget(parent) 
 {
   setFixedSize(widgetSize);

   CreateLayout();    

   /* connect buttons to state request signal emits  */
   connect(m_diagButton, SIGNAL (clicked()), this, SLOT (StateChangeDiag()));
   connect(m_mediaButton, SIGNAL (clicked()), this, SLOT (StateChangeMedia()));
   connect(m_parkButton, SIGNAL (clicked()), this, SLOT (StateChangeParking()));
   connect(m_errorButton, SIGNAL (clicked()), this, SLOT (StateChangeErrorCodes()));
 }

/**
 * @brief 
 * 
 */
void MainMenu::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   QGroupBox* titleBox = new QGroupBox("Main Menu", this);

   /* create buttons */
   m_diagButton = new QToolButton;
   m_mediaButton = new QToolButton;
   m_parkButton = new QToolButton;
   m_errorButton = new QToolButton;

   /* create icons */
   QIcon diagIcon;
   diagIcon.addFile(QString::fromUtf8("./MainApp/images/wrench.png"), QSize(), QIcon::Normal, QIcon::Off);
   QIcon errorIcon;
   errorIcon.addFile(QString::fromUtf8("./MainApp/images/hazard.png"), QSize(), QIcon::Normal, QIcon::Off);
   QIcon mediaIcon;
   mediaIcon.addFile(QString::fromUtf8("./MainApp/images/speaker.png"), QSize(), QIcon::Normal, QIcon::Off);
   QIcon parkingIcon;
   parkingIcon.addFile(QString::fromUtf8("./MainApp/images/hatchback.png"), QSize(), QIcon::Normal, QIcon::Off);

   const QSize btnSize = QSize(300, 140);
   m_diagButton->setFixedSize(btnSize);
   m_mediaButton->setFixedSize(btnSize);
   m_parkButton->setFixedSize(btnSize);
   m_errorButton->setFixedSize(btnSize);

   /* add icons */
   m_diagButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_diagButton->setIcon(diagIcon);
   m_diagButton->setIconSize(QSize(125, 125));
   m_diagButton->setText("Diagnostics");
   m_errorButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_errorButton->setIcon(errorIcon);
   m_errorButton->setIconSize(QSize(100, 100));
   m_errorButton->setText("Fault Codes");
   m_mediaButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_mediaButton->setIcon(mediaIcon);
   m_mediaButton->setIconSize(QSize(90, 90));
   m_mediaButton->setText("Media");
   m_parkButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_parkButton->setIcon(parkingIcon);
   m_parkButton->setIconSize(QSize(125, 125));
   m_parkButton->setText("Parking Mode");

   /* set layout */
   QGridLayout* layout = new QGridLayout(titleBox);
   layout->addWidget(m_diagButton, 0, 0, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_mediaButton, 0, 20, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_parkButton, 4, 0, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_errorButton, 4, 20, 5, 2, Qt::AlignHCenter);
   layout->setAlignment(Qt::AlignHCenter);

   
   titleBox->setFixedSize(WIDGET_SIZE_X-30, 380);
   
   titleBox->setLayout(layout);
   
   vLayout->addWidget(titleBox);
   titleBox->setAlignment(Qt::AlignHCenter);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeDiag()
{
   emit DisplayChange(DIAGNOSTICS, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeParking()
{
   emit DisplayChange(PARKING, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeErrorCodes()
{
   emit DisplayChange(ERROR_CODES, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeMedia()
{
   emit DisplayChange(MEDIA, this);
}