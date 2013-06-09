#ifndef WALOADERMISCELLANEOUSTAB_H
#define WALOADERMISCELLANEOUSTAB_H

#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class WaLoaderMiscellaneousTab : public QWidget
{
    Q_OBJECT

    public:
    WaLoaderMiscellaneousTab();
    QVBoxLayout* getTabLayout();

    private:
    QComboBox *m_languagesList;

    QFormLayout *m_languageSelecterLayout;

    QLabel *m_selectAnotherLanguageLabel;
    QLabel *m_programVersionLabel;
    QLabel *m_poweredByLabel;
    QLabel *m_authorAndSpecialThanksLabel;
    QLabel *m_translationsLabel;
    QLabel *m_englishTranslationLabel;
    QLabel *m_englishTranslatorLabel;
    QLabel *m_frenchTranslationLabel;
    QLabel *m_frenchTranslatorLabel;

    QVBoxLayout *m_miscellaneousTabLayout;
};

#endif // WALOADERMISCELLANEOUSTAB_H
