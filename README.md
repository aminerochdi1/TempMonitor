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

# Here's a summary of the key features:

- It connects to a WiFi network using the provided SSID and password.
- It initializes a DHT sensor for measuring temperature.
- It connects to an MQTT broker (server) with the specified IP address and port.
- It defines a callback function (callback) to handle incoming MQTT messages. In this case, it listens for messages on the topic "device/led" and controls the built-in LED based on the payload.
- The reconnect function attempts to reconnect to the MQTT broker if the connection is lost.
- The setup function sets up the initial configurations, such as pin modes and the MQTT server.
- The loop function is the main execution loop. It checks for MQTT connectivity, publishes temperature data from the DHT sensor, publishes analog temperature data, and prints debugging information to the serial monitor.
Make sure that you have the required libraries (ESP8266WiFi, PubSubClient, ArduinoJson, DHT) installed in your Arduino IDE.

# useful-links
telegram bot [here](https://t.me/TempNoitifierBot)
source code [here](https://github.com/aminerochdi1/TempMonitor/blob/master/build.html)
