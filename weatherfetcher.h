#ifndef WEATHERFETCHER_H
#define WEATHERFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherFetcher : public QObject {
    Q_OBJECT
public:
    explicit WeatherFetcher(QObject *parent = nullptr);
    Q_INVOKABLE void fetchWeather(const QString &location);
    Q_INVOKABLE void fetchWeather(double latitude, double longitude);

signals:
    void weatherFetched(double tempC, const QString &condition, const QString &iconUrl);

private slots:
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
};

#endif // WEATHERFETCHER_H
