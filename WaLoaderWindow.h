#ifndef WALOADERWINDOW_H
#define WALOADERWINDOW_H

#include <QApplication>
#include <QFileInfo>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTabWidget>
#include <QWidget>

#include "WaLoaderExecutableTab.h"
#include "WaLoaderMiscellaneousTab.h"

class WaLoaderWindow : public QTabWidget
{
    Q_OBJECT

    public:
    WaLoaderWindow(qint64, qint64);

    public slots:
    void loadGame();

    private:
    QGridLayout *m_executableTabQuitButtonsLayout;
    QGridLayout *m_miscellaneousTabQuitButtonsLayout;

    qint64 m_xSize;
    qint64 m_ySize;

    QPushButton *m_miscellaneousTabStartGameButton;
    QPushButton *m_executableTabStartGameButton;
    QPushButton *m_miscellaneousTabQuitAppButton;
    QPushButton *m_executableTabQuitAppButton;

    WaLoaderExecutableTab *m_executableTab;
    WaLoaderMiscellaneousTab *m_miscellaneousTab;
};

#endif // WALOADERWINDOW_H
