#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Lupis_wifi_1";
const char *password = "LupisOpen24h";
const char *mqttServer = "192.168.89.199";
const int mqttPort = 1883;
const char *mqttTopic = "braille";

const int motorPins[] = {16, 17, 18, 19, 21, 22};

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.println("Message arrived in topic: " + String(topic));

  char receivedMessage[length + 1];
  for (int i = 0; i < length; i++) {
    receivedMessage[i] = (char)payload[i];
  }
  receivedMessage[length] = '\0';
  convertAndControlVibration(receivedMessage);
}

void convertAndControlVibration(char *message) {  
  for (int i = 0; i < strlen(message); i++) {
    char currentChar = toupper(message[i]);   
    switch (currentChar) {
      case 'A':
        activateVibration(0);
        break;
      case 'B':
        activateVibration(1);
        break;
      case 'C':
        activateVibration(2);
        break;
      case 'D':
        activateVibration(3);
        break;
      case 'E':
        activateVibration(4);
        break;
      case 'F':
        activateVibration(5);
        break;
      case 'G':
        activateVibration(6);
        break;
      case 'H':
        activateVibration(7);
        break;
      case 'I':
        activateVibration(8);
        break;
      case 'J':
        activateVibration(9);
        break;
      case 'K':
        activateVibration(10);
        break;
      case 'L':
        activateVibration(11);
        break;
      case 'M':
        activateVibration(12);
        break;
      case 'N':
        activateVibration(13);
        break;
      case 'O':
        activateVibration(14);
        break;
      case 'P':
        activateVibration(15);
        break;
      case 'Q':
        activateVibration(16);
        break;
      case 'R':
        activateVibration(17);
        break;
      case 'S':
        activateVibration(18);
        break;
      case 'T':
        activateVibration(19);
        break;
      case 'U':
        activateVibration(20);
        break;
      case 'V':
        activateVibration(21);
        break;
      case 'W':
        activateVibration(22);
        break;
      case 'X':
        activateVibration(23);
        break;
      case 'Y':
        activateVibration(24);
        break;
      case 'Z':
        activateVibration(25);
        break;
      default:
        break;
    }

    // Chờ 2s giữa các chữ cái trong một từ
    delay(2000);
    deactivateAllVibrations();
  }

  // Chờ 4s giữa các từ (dấu cách)
  delay(4000);
}

void activateVibration(int index) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(motorPins[i], HIGH);
  }
  delay(2000);  // Thời gian chạy đồng thời tất cả các chấm (2s)
  for (int i = 0; i < 6; i++) {
    digitalWrite(motorPins[i], LOW);
  }
  delay(1000);  // Chờ 1s giữa các ký tự
}



void deactivateAllVibrations() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(motorPins[i], LOW);
  }
}

void setup() {
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Kết nối đầu rung với chân
  for (int i = 0; i < 6; i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

