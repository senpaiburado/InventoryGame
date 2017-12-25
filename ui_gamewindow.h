/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vLay;
    QLabel *gameTitle;
    QPushButton *playButton;
    QPushButton *exitButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(479, 376);
        centralWidget = new QWidget(GameWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 210, 381, 141));
        vLay = new QVBoxLayout(verticalLayoutWidget);
        vLay->setSpacing(6);
        vLay->setContentsMargins(11, 11, 11, 11);
        vLay->setObjectName(QStringLiteral("vLay"));
        vLay->setContentsMargins(0, 0, 0, 0);
        gameTitle = new QLabel(verticalLayoutWidget);
        gameTitle->setObjectName(QStringLiteral("gameTitle"));
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        gameTitle->setFont(font);

        vLay->addWidget(gameTitle);

        playButton = new QPushButton(verticalLayoutWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setCursor(QCursor(Qt::UpArrowCursor));

        vLay->addWidget(playButton);

        exitButton = new QPushButton(verticalLayoutWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setCursor(QCursor(Qt::UpArrowCursor));

        vLay->addWidget(exitButton);

        GameWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GameWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameWindow->setStatusBar(statusBar);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "GameWindow", Q_NULLPTR));
        gameTitle->setText(QApplication::translate("GameWindow", "             Inventory Game", Q_NULLPTR));
        playButton->setText(QApplication::translate("GameWindow", "Play", Q_NULLPTR));
        exitButton->setText(QApplication::translate("GameWindow", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
