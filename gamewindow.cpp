#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QRect screen = QApplication::desktop()->screenGeometry();
    setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    move(QPoint(screen.width() / 2 - WINDOW_WIDTH / 2, screen.height() / 2 - WINDOW_HEIGHT / 2));

    layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);

    title = new QLabel("Inventory Game!");

    playButton = new QPushButton("New Game");
    exitButton = new QPushButton("Exit");

    connect(playButton, &QPushButton::clicked, this, &GameWindow::playGame);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::exitGame);

    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addWidget(playButton);
    layout->addWidget(exitButton);

    central = new QWidget();
    central->setLayout(layout);
    setCentralWidget(central);
}

GameWindow::~GameWindow()
{
    delete title;
    delete playButton;
    delete exitButton;
    delete layout;
    delete central;
}

void GameWindow::playGame()
{
    playground = new Playground(this);
    playground->show();
    hide();
}

void GameWindow::exitGame()
{
    int answer = QMessageBox::question(this, tr("Confirm"), tr("Do you really want to leave?"), QMessageBox::Yes,
                                           QMessageBox::No);
    if (answer == QMessageBox::Yes)
        QApplication::exit(0);
}
