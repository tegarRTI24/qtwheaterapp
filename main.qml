import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: latitudeInput
            placeholderText: "Enter latitude"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        TextField {
            id: longitudeInput
            placeholderText: "Enter longitude"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        Button {
            text: "Get Weather by Coordinates"
            onClicked: {
                var latitude = parseFloat(latitudeInput.text)
                var longitude = parseFloat(longitudeInput.text)
                weatherFetcher.fetchWeather(latitude, longitude)
            }
        }

        TextField {
            id: locationInput
            placeholderText: "Enter location"
        }

        Button {
            text: "Get Weather by Location"
            onClicked: weatherFetcher.fetchWeather(locationInput.text)
        }

        Text {
            id: tempText
            text: qsTr("Temperature: ")
        }

        Text {
            id: conditionText
            text: qsTr("Condition: ")
        }

        Image {
            id: weatherIcon
            width: 100
            height: 100
            source: ""
            visible: false
        }
    }

    Connections {
        target: weatherFetcher
        onWeatherFetched: function(tempC, condition, iconUrl) {
            tempText.text = "Temperature: " + tempC + " °C";
            conditionText.text = "Condition: " + condition;
            weatherIcon.source = iconUrl;
            weatherIcon.visible = true;
        }
    }
}
