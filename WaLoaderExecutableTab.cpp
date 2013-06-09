#include "WaLoaderExecutableTab.h"

WaLoaderExecutableTab::WaLoaderExecutableTab() : QWidget() // General tab's constructor.
{
    QSettings loadGameRepository("HKEY_CURRENT_USER\\Software\\Team17SoftwareLTD\\WormsArmageddon",
                                 QSettings::NativeFormat);

    m_exePath = loadGameRepository.value("PATH", "0").toString();
    m_exeFile = m_exePath + "\\WA.exe";

    m_exeArguments = QStringList();

    // 1. Executable Selection
    m_executableSelectionGroupBox = new QGroupBox(tr("E&xecutable", "Groupbox header."));

    m_fileSelectLabel = new QLabel(tr("Executable", "Executable selecter's label"));

    m_fileNameField = new QLineEdit(m_exeFile);
    QObject::connect(m_fileNameField, SIGNAL(textChanged(QString)), this, SLOT(setTempExeFile(QString)));
    QObject::connect(m_fileNameField, SIGNAL(editingFinished()), this, SLOT(setExeFile()));

    m_fileSelectButton = new QPushButton(tr("Browse...", "Allows selecting the game executable."), this);
    m_fileSelectButton->setCursor(Qt::PointingHandCursor);
    QObject::connect(m_fileSelectButton, SIGNAL(clicked()), this, SLOT(selectGameExecutable()));

    m_executableGroupBoxLayout = new QHBoxLayout;

    m_executableGroupBoxLayout->addWidget(m_fileSelectLabel);
    m_executableGroupBoxLayout->addWidget(m_fileNameField);
    m_executableGroupBoxLayout->addWidget(m_fileSelectButton);

    m_executableSelectionGroupBox->setLayout(m_executableGroupBoxLayout);

    // 2. Game Arguments
    m_regularArgumentsGroupBox = new QGroupBox(tr("&Game Arguments", "Groupbox header."));

    m_skipIntro = new QCheckBox(tr("Skip intro"));
    QObject::connect(m_skipIntro, SIGNAL(stateChanged(int)), this, SLOT(toggleSkipIntro(int)));

    m_noWormKit = new QCheckBox(tr("Disable WormKit"));
    QObject::connect(m_noWormKit, SIGNAL(stateChanged(int)), this, SLOT(toggleNoWormKit(int)));

    m_wormKitArgs = new QCheckBox(tr("WormKit arguments:"));
    QObject::connect(m_wormKitArgs, SIGNAL(stateChanged(int)), this, SLOT(toggleWormKitArgs(int)));

    m_wormKitArgsField = new QLineEdit;
    m_wormKitArgsField->setReadOnly(true);

    m_registerAssociations = new QCheckBox(tr("Register associations"));
    QObject::connect(m_registerAssociations, SIGNAL(stateChanged(int)), this, SLOT(toggleRegisterAssociations(int)));

    m_quietMode = new QCheckBox(tr("Quiet mode"));
    QObject::connect(m_quietMode, SIGNAL(stateChanged(int)), this, SLOT(toggleQuietMode(int)));

    m_hostJoin = new QCheckBox(tr("Host/Join:"));
    QObject::connect(m_hostJoin, SIGNAL(stateChanged(int)), this, SLOT(toggleHostJoin(int)));

    m_hostJoinParameterField = new QLineEdit;
    m_hostJoinParameterField->setReadOnly(true);

    m_customLanguageDirectoriesGroupBox = new QGroupBox(tr("Custom &Language Directories", "Sub-groupbox of the Game Arguments groupbox."));
    m_customLanguageDirectoriesGroupBox->setCheckable(true);
    m_customLanguageDirectoriesGroupBox->setChecked(false);

    m_regularArgumentsLayout = new QGridLayout;

    m_regularArgumentsLayout->addWidget(m_skipIntro, 0, 0);
    m_regularArgumentsLayout->addWidget(m_noWormKit, 1, 0);
    m_regularArgumentsLayout->addWidget(m_registerAssociations, 2, 0);
    m_regularArgumentsLayout->addWidget(m_quietMode, 3, 0);
    m_regularArgumentsLayout->addWidget(m_wormKitArgs, 4, 0);
    m_regularArgumentsLayout->addWidget(m_wormKitArgsField, 5, 0);
    m_regularArgumentsLayout->addWidget(m_hostJoin, 6, 0);
    m_regularArgumentsLayout->addWidget(m_hostJoinParameterField, 7, 0);
    m_regularArgumentsLayout->addWidget(m_customLanguageDirectoriesGroupBox, 0, 1, 8, 1);

    m_regularArgumentsGroupBox->setLayout(m_regularArgumentsLayout);

    // 3. Replay Arguments
    m_replayArgumentsGroupBox = new QGroupBox(tr("&Replay Arguments", "Groupbox header."));
    m_replayArgumentsGroupBox->setCheckable(true);
    m_replayArgumentsGroupBox->setChecked(false);

    m_replayActionGroupBox = new QGroupBox(tr("A&ction", "Sub-groupbox of the Replay Arguments groupbox."));
    m_replayAdditionalParametersGroupBox = new QGroupBox(tr("A&dditional Parameters", "Sub-groupbox of the Replay Arguments groupbox."));

    m_replayArgumentsLayout = new QHBoxLayout;

    m_replayArgumentsLayout->addWidget(m_replayActionGroupBox);
    m_replayArgumentsLayout->addWidget(m_replayAdditionalParametersGroupBox);

    m_replayArgumentsGroupBox->setLayout(m_replayArgumentsLayout);

    // 4. Outputting on the screen
    m_executableTabLayout = new QVBoxLayout;

    m_executableTabLayout->addWidget(m_executableSelectionGroupBox);
    m_executableTabLayout->addWidget(m_regularArgumentsGroupBox);
    m_executableTabLayout->addWidget(m_replayArgumentsGroupBox);

    setLayout(m_executableTabLayout);
}

void WaLoaderExecutableTab::selectGameExecutable() // A dialog that lets the user choose the game executable.
{
    QString exeFileName = m_exeFile;

    m_exeFile = QFileDialog::getOpenFileName(this, tr("Select the game executable to run", "Executable choosing window title."), exeFileName, tr("Applications (*.exe)", "Executable choosing window file format."));

    m_tempExeFile = m_exeFile;
    setFileNameFieldContent(m_exeFile);

    QFileInfo *fileInfo = new QFileInfo(m_exeFile);

    QDir exePath = fileInfo->dir();
    m_exePath = exePath.path();
}

void WaLoaderExecutableTab::setExeFile() // Updates m_exeFile and m_exePath upon changing the exe file path manually, if the file exists.
{
    QFileInfo *newFileInfo = new QFileInfo(m_tempExeFile);

    if (newFileInfo->exists())
    {
        m_exeFile = m_tempExeFile;

        QDir newPath = newFileInfo->dir();
        m_exePath = newPath.path();
    }
    else
    {
        setFileNameFieldContent(m_exeFile);
    }
}

void WaLoaderExecutableTab::setTempExeFile(QString newName) // Needed because the editingFinished signal is emitted without any arguments.
{
    m_tempExeFile = newName;
}

void WaLoaderExecutableTab::setFileNameFieldContent(QString newValue)
{
    m_fileNameField->setText(newValue);
}

void WaLoaderExecutableTab::toggleSkipIntro(int newValue)
{
    if (newValue != 0)
    {
        m_exeArguments << "/nointro";
    }
    else
    {
        m_exeArguments.removeDuplicates(); // Safety.
        m_exeArguments.removeOne("/nointro");
    }
}

void WaLoaderExecutableTab::toggleNoWormKit(int newValue)
{
    if (newValue != 0)
    {
        m_exeArguments << "/nowk";

        m_wormKitArgs->setDisabled(true);
        m_wormKitArgs->setChecked(false);
    }
    else
    {
        m_exeArguments.removeDuplicates(); // Safety.
        m_exeArguments.removeOne("/nowk");

        m_wormKitArgs->setDisabled(false);
    }
}

void WaLoaderExecutableTab::toggleWormKitArgs(int newValue)
{
    if (newValue != 0)
    {
        m_wormKitArgsList << "/wkargs";

        m_wormKitArgsField->setReadOnly(false);
    }
    else
    {
        m_wormKitArgsList = QStringList();

        m_wormKitArgsField->setText(QString());
        m_wormKitArgsField->setReadOnly(true);
    }
}

void WaLoaderExecutableTab::toggleRegisterAssociations(int newValue)
{
    if (newValue != 0)
    {
        m_exeArguments << "/register";
    }
    else
    {
        m_exeArguments.removeDuplicates(); // Safety.
        m_exeArguments.removeOne("/register");
    }
}

void WaLoaderExecutableTab::toggleQuietMode(int newValue)
{
    if (newValue != 0)
    {
        m_exeArguments << "/quiet";
    }
    else
    {
        m_exeArguments.removeDuplicates(); // Safety.
        m_exeArguments.removeOne("/quiet");
    }
}

void WaLoaderExecutableTab::toggleHostJoin(int newValue)
{
    if (newValue != 0)
    {
        m_exeArguments << "/host";

        m_hostJoinParameterField->setReadOnly(false);
    }
    else
    {
        m_exeArguments.removeDuplicates(); // Safety.
        m_exeArguments.removeOne("/host");

        m_hostJoinParameterField->setText(QString());
        m_hostJoinParameterField->setReadOnly(true);
    }
}

QString WaLoaderExecutableTab::getExeFile() // Gets m_exeFile.
{
    return m_exeFile;
}

QString WaLoaderExecutableTab::getExePath() // Gets m_exePath.
{
    return m_exePath;
}

QStringList WaLoaderExecutableTab::getExeArguments()
{
    return m_exeArguments;
}

QVBoxLayout* WaLoaderExecutableTab::getTabLayout()
{
    return m_executableTabLayout;
}
