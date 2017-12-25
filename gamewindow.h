#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QDebug>

#include "playground.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void playGame();
    void exitGame();

private:
    const int WINDOW_WIDTH = 480;
    const int WINDOW_HEIGHT = 600;

    QLabel *title;

    QPushButton *playButton;
    QPushButton *exitButton;

    QVBoxLayout *layout;
    QWidget *central;

    Playground *playground;
};

#endif // GAMEWINDOW_H
