#include "WaLoaderMiscellaneousTab.h"

WaLoaderMiscellaneousTab::WaLoaderMiscellaneousTab() : QWidget()
{
    m_programGenericSettings = new QSettings("WALoader.ini", QSettings::IniFormat);
    m_programGenericSettings->beginGroup("Program");
    QString currentLanguageStr = m_programGenericSettings->value("Language").toString();
    qint64 currentLanguageIndex;

    if (currentLanguageStr == "fr")
    {
        currentLanguageIndex = 1;
    }
    else
    {
        currentLanguageIndex = 0;
    }

    m_selectAnotherLanguageLabel = new QLabel(tr("Select another language"));

    m_languagesList = new QComboBox;
    m_languagesList->addItem("English (LeTotalKiller)");
    m_languagesList->addItem("Français (LeTotalKiller)");
    m_languagesList->setCurrentIndex(currentLanguageIndex);
    QObject::connect(m_languagesList, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));

    m_languageSelecterLayout = new QFormLayout;
    m_languageSelecterLayout->addRow(m_selectAnotherLanguageLabel, m_languagesList);

    m_aboutProgram = new QTextEdit("WA Loader - v0.1.1.8 (30/07/2013).<br /><br />" + tr("Powered by Qt 5.1.0.") + "<br /><br />" + tr("Made by LeTotalKiller.") + "<br /><br />" + tr("Special thanks to (sorted in alphabetical order):") + "<br />Muzer<br />Piki1802<br />ZexorZ");
    m_aboutProgram->setReadOnly(true);

    m_miscellaneousTabLayout = new QVBoxLayout;
    m_miscellaneousTabLayout->addLayout(m_languageSelecterLayout);
    m_miscellaneousTabLayout->addWidget(m_aboutProgram);

    setLayout(m_miscellaneousTabLayout);
}

void WaLoaderMiscellaneousTab::changeLanguage(int newLanguageId)
{
    switch (newLanguageId)
    {
        case 0:
        m_programGenericSettings->setValue("Language", "en");
        break;

        case 1:
        m_programGenericSettings->setValue("Language", "fr");
        break;

        default:
        m_programGenericSettings->setValue("Language", "en");
        break;
    }

    QMessageBox::information(this, tr("Note"), tr("This change will apply next time you start this program."));
}

QVBoxLayout* WaLoaderMiscellaneousTab::getTabLayout()
{
    return m_miscellaneousTabLayout;
}
