#include "schema.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

QJsonDocument load(const QString &path)
{
    QFile config(path);
    QJsonDocument docJsonConfig;

    if (!(config.open(QIODevice::ReadOnly | QIODevice::Text))) {
        qDebug() << "Cannot open file json:" << path;
        return {};
    }

    docJsonConfig = QJsonDocument::fromJson(config.readAll());

    config.close();

    return docJsonConfig;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QJsonDocument jsDoc = load("E:/PROJECT/QT/schema_json/remote-manager.cfg");

    if (jsDoc.isEmpty()) {
        return -1;
    }

    Schema _schema;
    _schema.engine(jsDoc);

    return a.exec();
}
