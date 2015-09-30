#ifndef HELPER_HPP
#define HELPER_HPP

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QTextStream>

class Helper : public QObject
{   Q_OBJECT
    public slots:
        void remove(const QString &url)
        {    //qDebug() << "Called the C++ slot and request removal of:" << url;
             QFile(url).remove();
        }
        QString getHome()
        {    //qDebug() << "Called the C++ slot and request removal of:" << url;
             return QDir::homePath();
        }
        QString getRoot()
        {    //qDebug() << "Called the C++ slot and request removal of:" << url;
             return QDir::rootPath();
        }
        bool existsPath(const QString &url)
        {
            return QDir(url).exists();
        }
        bool isFile(const QString &url)
        {
            return QFileInfo(url).isFile();
        }
        int setDefaultBrowser(const QString &execLine)
        {
            /* Search if file exists. If yes remove it */
            if (isFile(getHome() + "/.local/share/applications/open-url.desktop")) remove(getHome() + "/.local/share/applications/open-url.desktop");

            /* Try and open a file for output */
            QString outputFilename = getHome() + "/.local/share/applications/open-url.desktop";
            QFile outputFile(outputFilename);
            outputFile.open(QIODevice::WriteOnly);

            /* Check it opened OK */
            if(!outputFile.isOpen()){
                qDebug() << "Error, unable to open" << outputFilename << "for output";
                return 1;
            }

            /* Point a QTextStream object at the file */
            QTextStream outStream(&outputFile);

            /* Write the line to the file */
            outStream << "[Desktop Entry]\n";
            outStream << "Type=Application\n";
            outStream << "Name=Browser\n";
            outStream << "NoDisplay=true\n";
            outStream << "NotShowIn=X-MeeGo;\n";
            outStream << "MimeType=text/html;x-maemo-urischeme/http;x-maemo-urischeme/https;\n";
            outStream << "Exec=" + execLine + "\n";

            /* Close the file */
            outputFile.close();
        }
        // Default Browser - open-url.desktop

        //[Desktop Entry]
        //Type=Application
        //Name=Browser
        //NotShowIn=X-MeeGo;
        //MimeType=text/html;x-maemo-urischeme/http;x-maemo-urischeme/https;
        //Exec=/usr/bin/harbour-webcat '%U'
};


#endif // HELPER_HPP