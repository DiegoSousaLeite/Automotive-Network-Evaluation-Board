#ifndef SYSTEMDEFINITION_H
#define SYSTEMDEFINITION_H

#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QDir>

class SystemDefinition  {
private:
    QString mFilePath;
    QString rFilePath;
    QSettings *mfProperty;
    QSettings *rfProperty;

public:
    SystemDefinition() {
        // Caminhos relativos baseados no diretório do executável
        QString appDirPath = QCoreApplication::applicationDirPath();
        mFilePath = appDirPath + "/system/JigaAppCmd.properties";
        rFilePath = appDirPath + "/system/ErrorReport.properties";

    qDebug() << "SystemDefinition: mFilePath =" << mFilePath;
    qDebug() << "SystemDefinition: rFilePath =" << rFilePath;
    qDebug() << "VER ESSA CLASSE NO FUTURO";
//    // Carregando as propriedades do aplicativo
//    if (!QFile::exists(mFilePath)) {
//        qFatal("Arquivo de configuração não encontrado em %s", qPrintable(mFilePath));
//        return; // Adicionado para evitar o abort()
//    }
    mfProperty = new QSettings(mFilePath, QSettings::IniFormat);

//    // Carregando as propriedades de relatório de erro
//    if (!QFile::exists(rFilePath)) {
//        qFatal("Arquivo de relatório de erro não encontrado em %s", qPrintable(rFilePath));
//        return; // Adicionado para evitar o abort()
//    }
    rfProperty = new QSettings(rFilePath, QSettings::IniFormat);
    }

    ~SystemDefinition() {
        delete mfProperty;
        delete rfProperty;
    }

    void printSystemProperties() {
        foreach (const QString &key, mfProperty->allKeys()) {
            qDebug() << key << ": " << mfProperty->value(key).toString();
        }
    }

    QSettings* getReportProperty() {
        return rfProperty;
    }
};

#endif // SYSTEMDEFINITION_H
