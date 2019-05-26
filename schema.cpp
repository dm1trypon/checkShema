#include "schema.h"

#include <QDebug>
#include <QFile>

Schema::Schema()
{

}

void Schema::engine(const QJsonDocument jsDoc)
{
    QJsonDocument shemaDoc;

    if (jsDoc.isObject()) {
        shemaDoc.setObject(object(jsDoc.object()).object());
        show(shemaDoc);
        write(shemaDoc);

        return;
    }

    array(jsDoc.array());
    show(shemaDoc);
    write(shemaDoc);
}

QJsonDocument Schema::object(const QJsonObject jsObj)
{
    QJsonObject rootObj;
    QJsonObject keyObj;
    QJsonArray requireArr;

    foreach(const QString key, jsObj.keys()) {
        requireArr.append(key);
    }

    rootObj.insert("require", requireArr);

    foreach(const QString key, jsObj.keys()) {
        if (jsObj[key].isObject()) {
            keyObj.insert(key, object(jsObj[key].toObject()).object());
            continue;
        }

        if (jsObj[key].isArray()) {
            keyObj.insert(key, array(jsObj[key].toArray()).object());
            continue;
        }

        if (jsObj[key].isString()) {
            keyObj.insert(key, QJsonObject{{"type", "string"}});
            continue;
        }

        if (jsObj[key].isBool()) {
            keyObj.insert(key, QJsonObject{{"type", "bool"}});
            continue;
        }

        if (jsObj[key].isDouble()) {
            keyObj.insert(key, QJsonObject{{"type", "number"}});
            continue;
        }

        if (jsObj[key].isUndefined()) {
            keyObj.insert(key, QJsonObject{{"type", "underfined"}});
            continue;
        }

        if (jsObj[key].isNull()) {
            keyObj.insert(key, QJsonObject{{"type", "null"}});
            continue;
        }
    }

    rootObj.insert("properties", keyObj);
    rootObj.insert("type", QJsonObject{{"type", "object"}});

    return QJsonDocument(rootObj);
}

QJsonDocument Schema::array(const QJsonArray jsArr)
{
    QJsonObject rootObj;
    QJsonArray keyArr;

    foreach(const QJsonValue value, jsArr) {
        if (value.isObject()) {
            keyArr.append(object(value.toObject()).object());
            continue;
        }

        if (value.isArray()) {
            keyArr.append(array(value.toArray()).object());
            continue;
        }

        if (value.isString()) {
            keyArr.append(QJsonObject{{"type", "string"}});
            continue;
        }

        if (value.isBool()) {
            keyArr.append(QJsonObject{{"type", "bool"}});
            continue;
        }

        if (value.isDouble()) {
            keyArr.append(QJsonObject{{"type", "number"}});
            continue;
        }

        if (value.isUndefined()) {
            keyArr.append(QJsonObject{{"type", "underfined"}});
            continue;
        }

        if (value.isNull()) {
            keyArr.append(QJsonObject{{"type", "null"}});
            continue;
        }
    }

    rootObj.insert("type", "array");
    rootObj.insert("properties", keyArr);
    return QJsonDocument(rootObj);
}

void Schema::write(const QJsonDocument shemaDoc)
{
    QFile jsonFile("E:/PROJECT/QT/schema_json/schema.json");
    jsonFile.open(QIODevice::WriteOnly);
    jsonFile.write(shemaDoc.toJson());
    jsonFile.close();
}

void Schema::show(const QJsonDocument shemaDoc)
{
    qDebug() << shemaDoc.toJson(QJsonDocument::Compact);
}
