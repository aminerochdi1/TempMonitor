# TempMonitor

The Temperature Monitor is a simple yet effective project that allows you to remotely monitor and display temperature data in real-time. The project uses an ESP8266 microcontroller connected to a DHT11 sensor for measuring ambient temperature. The collected data is then sent to a web interface using MQTT (Message Queuing Telemetry Transport) protocol.

Features:

Real-time temperature monitoring.
MQTT communication for data transmission.
Web-based interface for displaying temperature information.
Dynamic updating of temperature values.
Visual indication of temperature status through color-coded icons.
Implementation:
The project utilizes HTML, CSS, and JavaScript for the web interface, and the Paho MQTT JavaScript library for MQTT communication. Temperature data is acquired from the DHT11 sensor and transmitted to the web interface through MQTT. The web page dynamically updates the displayed temperature and includes visual indicators based on predefined temperature thresholds.

Usage:

Open the web page to view real-time temperature data.
The temperature value is dynamically updated as new data arrives.
Color-coded icons indicate the temperature status (e.g., green for normal, yellow for elevated, and red for high temperatures).
This project is not only educational but also practical, offering a convenient way to monitor temperature remotely.

source code https://github.com/aminerochdi1/TempMonitor/blob/master/build.html:[here]