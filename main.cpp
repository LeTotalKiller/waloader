#include <QApplication>
#include <QFile>
#include <QLocale>
#include <QLibraryInfo>
#include <QSettings>
#include <QString>
#include <QTranslator>
#include <QVariant>

#include "WaLoaderWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qint64 xSize(400), ySize(440);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QString programLanguage = locale;

    QFileInfo configurationFile("WALoader.ini");
    QSettings programGenericSettings("WALoader.ini", QSettings::IniFormat);

    if (!configurationFile.exists())
    {
        // Let's create the file
        programGenericSettings.beginGroup("Program");
        programGenericSettings.setValue("Language", locale);
        programGenericSettings.setValue("XSize", 400);
        programGenericSettings.setValue("YSize", 440);
        programGenericSettings.endGroup();
    }
    else
    {
        programGenericSettings.beginGroup("Program");

        if (programGenericSettings.contains("Language"))
        {
            programLanguage = programGenericSettings.value("Language").toString();
        }
        else
        {
            programGenericSettings.setValue("Language", QVariant(locale));
        }

        if (programGenericSettings.contains("XSize"))
        {
            xSize = programGenericSettings.value("XSize").toInt();
        }
        else
        {
            programGenericSettings.setValue("XSize", QVariant(xSize));
        }

        if (programGenericSettings.contains("YSize"))
        {
            ySize = programGenericSettings.value("YSize").toInt();
        }
        else
        {
            programGenericSettings.setValue("YSize", QVariant(ySize));
        }

        programGenericSettings.endGroup();
    }

    QTranslator customTranslationFile;
    customTranslationFile.load(QString("WALoader_") + programLanguage);
    app.installTranslator(&customTranslationFile);

    QTranslator qtTranslationFile;
    qtTranslationFile.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslationFile);

    WaLoaderWindow appWindow(xSize, ySize);
    appWindow.show();

    return app.exec();
}
