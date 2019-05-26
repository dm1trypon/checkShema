#ifndef SCHEMA_H
#define SCHEMA_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMap>

class Schema : public QObject
{
    Q_OBJECT
    QJsonDocument array(const QJsonArray jsArr);
    QJsonDocument object(const QJsonObject jsObj);

    void show(const QJsonDocument shemaDoc);
    void write(const QJsonDocument shemaDoc);
public:
    Schema();
    void engine(const QJsonDocument jsDoc);
};

#endif // SCHEMA_H
