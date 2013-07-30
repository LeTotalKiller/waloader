#ifndef WALOADERMISCELLANEOUSTAB_H
#define WALOADERMISCELLANEOUSTAB_H

#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSettings>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class WaLoaderMiscellaneousTab : public QWidget
{
    Q_OBJECT

    public:
    WaLoaderMiscellaneousTab();
    QVBoxLayout* getTabLayout();

    public slots:
    void changeLanguage(int);

    private:
    QComboBox *m_languagesList;
    QFormLayout *m_languageSelecterLayout;
    QLabel *m_selectAnotherLanguageLabel;
    QSettings *m_programGenericSettings;
    QTextEdit *m_aboutProgram;
    QVBoxLayout *m_miscellaneousTabLayout;
};

#endif // WALOADERMISCELLANEOUSTAB_H
