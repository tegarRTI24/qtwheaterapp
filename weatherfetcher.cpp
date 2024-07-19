#include "weatherfetcher.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkRequest>
#include <QDebug>

WeatherFetcher::WeatherFetcher(QObject *parent) : QObject(parent) {
    connect(&manager, &QNetworkAccessManager::finished, this, &WeatherFetcher::onResult);
}

void WeatherFetcher::fetchWeather(const QString &location) {
    QString apiKey = "9538d76eb6ff4a628ae75956242805";  // Ganti dengan API key Anda
    QString url = QString("http://api.weatherapi.com/v1/current.json?key=%1&q=%2").arg(apiKey, location);
    manager.get(QNetworkRequest(QUrl(url)));
}

void WeatherFetcher::fetchWeather(double latitude, double longitude) {
    QString apiKey = "9538d76eb6ff4a628ae75956242805";  // Ganti dengan API key Anda
    QString location = QString("%1,%2").arg(latitude).arg(longitude);
    QString url = QString("http://api.weatherapi.com/v1/current.json?key=%1&q=%2").arg(apiKey, location);
    manager.get(QNetworkRequest(QUrl(url)));
}

void WeatherFetcher::onResult(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonObject current = jsonObject["current"].toObject();
        double tempC = current["temp_c"].toDouble();
        QString condition = current["condition"].toObject()["text"].toString();
        QString iconUrl = "http:" + current["condition"].toObject()["icon"].toString();

        emit weatherFetched(tempC, condition, iconUrl);
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}
