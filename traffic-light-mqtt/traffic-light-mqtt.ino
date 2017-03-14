#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define PIN            15
#define NUMPIXELS      1 

const char* ssid = "procodecg";
const char* password = "12345678";
//const char* mqtt_server = "broker.mqtt-dashboard.com";
//const char* mqtt_server = "192.168.1.118";
const char* mqtt_server = "192.168.1.101";

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 1000;
int i=0;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("x");
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

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
//      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("led1");
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
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  
    // red
    client.publish("led1", "red");
    pixels.setPixelColor(0, pixels.Color(63,0,0));
    pixels.show(); 
    delay(3000);


    client.publish("led1", "yellow");
    for (i=0; i<5; i++) {
      // yellow
      pixels.setPixelColor(0, pixels.Color(63,63,0)); pixels.show(); delay(500);
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
    }
    
    // green
    client.publish("led1", "green");
    pixels.setPixelColor(0, pixels.Color(0,63,0));
    pixels.show(); 
    delay(3000);


    client.publish("led1", "yellow");
    for (i=0; i<3; i++) {
      // orange
      pixels.setPixelColor(0, pixels.Color(63,40,0)); pixels.show(); delay(500);
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
    }
}
