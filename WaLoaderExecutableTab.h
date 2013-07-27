#ifndef WALOADEREXECUTABLETAB_H
#define WALOADEREXECUTABLETAB_H

#include <QApplication>
#include <QCheckBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>

class WaLoaderExecutableTab : public QWidget
{
    Q_OBJECT

    public:
    WaLoaderExecutableTab();
    QVBoxLayout* getTabLayout();

    public slots:
    QString getExeFile();
    QString getExePath();
    QStringList getExeArguments();

    void selectGameExecutable();
    void setExeFile();
    void setFileNameFieldContent(QString);
    void setTempExeFile(QString);

    void toggleSkipIntro(int);
    void toggleNoWormKit(int);
    void toggleWormKitArgs(int);
    void toggleRegisterAssociations(int);
    void toggleQuietMode(int);
    void toggleHostJoin(int);

    private:
    QCheckBox *m_skipIntro;
    QCheckBox *m_noWormKit;
    QCheckBox *m_wormKitArgs;
    QCheckBox *m_registerAssociations;
    QCheckBox *m_quietMode;
    QCheckBox *m_hostJoin;

    QCheckBox *m_replayPlay;
    QCheckBox *m_replayPlayAt;
    QCheckBox *m_replayGetMap;
    QCheckBox *m_replayGetScheme;
    QCheckBox *m_replayGetVideo;
    QCheckBox *m_replayGetLog;
    QCheckBox *m_replaySanitize;
    QCheckBox *m_replayRepair;

    QFormLayout *m_wormKitArgsLineLayout;

    QGridLayout *m_regularArgumentsLayout;

    QGroupBox *m_executableSelectionGroupBox;

    QGroupBox *m_regularArgumentsGroupBox;
    QGroupBox *m_customLanguageDirectoriesGroupBox;

    QGroupBox *m_replayArgumentsGroupBox;
    QGroupBox *m_replayActionGroupBox;
    QGroupBox *m_replayAdditionalParametersGroupBox;
    QGroupBox *m_replayPlayAtAdditionalParametersGroupBox;
    QGroupBox *m_replayExportVideoAdditionalParametersGroupBox;

    QHBoxLayout *m_executableGroupBoxLayout;
    QHBoxLayout *m_replayArgumentsLayout;

    QLabel *m_fileSelectLabel;

    QLineEdit *m_fileNameField;
    QLineEdit *m_wormKitArgsField;
    QLineEdit *m_hostJoinParameterField;

    QPushButton *m_fileSelectButton;

    QString m_exeFile;
    QString m_exePath;
    QString m_tempExeFile;

    QStringList m_exeArguments;
    QStringList m_wormKitArgsList;

    QVBoxLayout *m_executableTabLayout;
    QVBoxLayout *m_replayActionsLayout;
};

#endif // WALOADEREXECUTABLETAB_H
