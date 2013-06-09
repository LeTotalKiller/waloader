#include "WaLoaderMiscellaneousTab.h"

WaLoaderMiscellaneousTab::WaLoaderMiscellaneousTab() : QWidget()
{
    m_selectAnotherLanguageLabel = new QLabel(tr("Select another language"));
    m_languagesList = new QComboBox;

    m_languageSelecterLayout = new QFormLayout;
    m_languageSelecterLayout->addRow(m_selectAnotherLanguageLabel, m_languagesList);

    m_miscellaneousTabLayout = new QVBoxLayout;
    m_miscellaneousTabLayout->addLayout(m_languageSelecterLayout);
}

QVBoxLayout* WaLoaderMiscellaneousTab::getTabLayout()
{
    return m_miscellaneousTabLayout;
}
