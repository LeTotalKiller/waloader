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
    m_languagesList->addItem("English");
    m_languagesList->addItem("Français");
    m_languagesList->setCurrentIndex(currentLanguageIndex);
    QObject::connect(m_languagesList, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));

    m_languageSelecterLayout = new QFormLayout;
    m_languageSelecterLayout->addRow(m_selectAnotherLanguageLabel, m_languagesList);

    m_miscellaneousTabLayout = new QVBoxLayout;
    m_miscellaneousTabLayout->addLayout(m_languageSelecterLayout);

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
