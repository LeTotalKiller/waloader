#include <sys/types.h>
#include "WaLoaderWindow.h"

WaLoaderWindow::WaLoaderWindow() : QTabWidget() // Program's window.
{
    resize(400, 400);

    m_executableTab = new WaLoaderExecutableTab;
    m_miscellaneousTab = new WaLoaderMiscellaneousTab;

    setTabShape(QTabWidget::Rounded);

    // Executable tab.
    addTab(m_executableTab, tr("&Executable", "Executable settings."));

    if (currentIndex() == 0)
    {
        m_executableTabStartGameButton = new QPushButton(tr("Start the game", "Quits the loader and starts the game."), this);
        m_executableTabStartGameButton->setCursor(Qt::PointingHandCursor);
        QObject::connect(m_executableTabStartGameButton, SIGNAL(clicked()), this, SLOT(loadGame()));

        m_executableTabQuitAppButton = new QPushButton(tr("Quit", "Quits the loader."), this);
        m_executableTabQuitAppButton->setCursor(Qt::PointingHandCursor);
        QObject::connect(m_executableTabQuitAppButton, SIGNAL(clicked()), qApp, SLOT(quit()));

        m_executableTabQuitButtonsLayout = new QGridLayout;
        m_executableTabQuitButtonsLayout->addWidget(m_executableTabStartGameButton, 0, 1);
        m_executableTabQuitButtonsLayout->addWidget(m_executableTabQuitAppButton, 0, 2);
        m_executableTabQuitButtonsLayout->setColumnMinimumWidth(0, 190);

        m_executableTab->getTabLayout()->addLayout(m_executableTabQuitButtonsLayout);
    }

    addTab(m_miscellaneousTab, tr("&Miscellaneous", "Program language selection and about the program."));

    if (currentIndex() == 1)
    {
        m_miscellaneousTabStartGameButton = new QPushButton(tr("Start the game", "Quits the loader and starts the game."), this);
        m_miscellaneousTabStartGameButton->setCursor(Qt::PointingHandCursor);
        QObject::connect(m_miscellaneousTabStartGameButton, SIGNAL(clicked()), this, SLOT(loadGame()));

        m_miscellaneousTabQuitAppButton = new QPushButton(tr("Quit", "Quits the loader."), this);
        m_miscellaneousTabQuitAppButton->setCursor(Qt::PointingHandCursor);
        QObject::connect(m_miscellaneousTabQuitAppButton, SIGNAL(clicked()), qApp, SLOT(quit()));

        m_miscellaneousTabQuitButtonsLayout = new QGridLayout;
        m_miscellaneousTabQuitButtonsLayout->addWidget(m_miscellaneousTabStartGameButton, 0, 1);
        m_miscellaneousTabQuitButtonsLayout->addWidget(m_miscellaneousTabQuitAppButton, 0, 2);
        m_miscellaneousTabQuitButtonsLayout->setColumnMinimumWidth(0, 190);

        m_miscellaneousTab->getTabLayout()->addLayout(m_miscellaneousTabQuitButtonsLayout);
    }

    QObject::connect(this, SIGNAL(currentChanged(int)), this, SLOT(setCurrentIndex(int)));
}

void WaLoaderWindow::loadGame() // Launches the game with all the collected information.
{
    QProcess *gameProcess = new QProcess();
    gameProcess->startDetached(m_executableTab->getExeFile(), m_executableTab->getExeArguments(), m_executableTab->getExePath());

    qApp->quit();
}
