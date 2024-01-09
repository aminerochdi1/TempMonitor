#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Update these with values suitable for your network.
const char* ssid = ""; // YOUR WIFI SSID
const char* password = ""; // YOUR WIFI PASSWORD
const char* mqtt_server = "";  //YOUR ADRESS ( execute this command 'ping test.mosquitto.org' ) 

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (200)  // Increased buffer size to accommodate larger JSON data
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Check the topic and control the LED accordingly

  if (strcmp(topic, "device/led") == 0) {
    // Switch on the LED if the payload is '1'
    if ((char)payload[0] == '1') {
      digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on
    } else {
      digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off
    }
  }
}
          // CONNECTION TO MQTT CLIENT
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("device/temp", "MQTT Server is Connected");
      client.subscribe("device/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    // Read temperature from DHT sensor
    //delay(10000);
    float temperature = dht.readTemperature();

    // Create a JSON object for DHT data
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["temperature"] = temperature;

    // Convert the JSON object to a string
    String jsonString;
    serializeJson(jsonDocument, jsonString);

    // Publish the JSON string for DHT data
    client.publish("device/temp", jsonString.c_str());

    // Read additional temperature from analog sensor
    int analogValue = analogRead(A0);

    // Create a JSON object for analog data
    jsonDocument.clear();
    jsonDocument["analogTemperature"] = analogValue;

    // Convert the JSON object to a string
    jsonString = "";
    serializeJson(jsonDocument, jsonString);

    // Publish the JSON string for analog data
    client.publish("device/analog", jsonString.c_str());

    // Print messages to serial for debugging
    Serial.print("DHT Data: ");
    Serial.println(jsonString);

    Serial.print("Analog Temperature: ");
    Serial.println(analogValue);
  }
}
