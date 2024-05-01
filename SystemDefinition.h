#ifndef SYSTEMDEFINITION_H
#define SYSTEMDEFINITION_H

#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QDir>

class SystemDefinition {
private:
    QString mFilePath;
    QString rFilePath;
    QSettings *mfProperty;
    QSettings *rfProperty;

public:
    SystemDefinition() {
        mFilePath = QDir::currentPath() + "/system/resources/Application.properties";
        rFilePath = QDir::currentPath() + "/system/resources/ErrorReport.properties";

        // Carregando as propriedades do aplicativo
        if (!QFile::exists(mFilePath)) {
            qFatal("Arquivo de configuração não encontrado.");
            exit(1);
        }
        mfProperty = new QSettings(mFilePath, QSettings::IniFormat);

        // Carregando as propriedades de relatório de erro
        if (!QFile::exists(rFilePath)) {
            qFatal("Arquivo de relatório de erro não encontrado.");
            exit(1);
        }
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
