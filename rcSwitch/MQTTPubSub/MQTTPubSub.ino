/*
Control wireless power outets over MQTT using an ESP8266

Power outlets used:
  Westinghouse Indoor Wireless Remote System 
  Model TK301
  Item T28064
  UPC 686140280641

Commands should be sent to the topic named 'rfPlug'
Command payload should be in the form of DEVICE/FUNCTION/COMMAND
  Example: r1p1/power/on

Once connected to the MQTT server a message containg the gateway's IP address 
  will be published to the topic 'rfPlug/ipAddress'

Remote RF codes were captured utilizing the receive example 
  from: https://github.com/sui77/rc-switch/
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <RCSwitch.h>

//Update these with values suitable for your network
const char* ssid = "NachoWifi";
const char* password = "Daynet236";
const char* mqtt_server = "openhab.home.ianday.me";

//Remote RF Codes
#define r1p1On 3818455479
#define r1p1Off 3818455447
#define r1p2On 3818455735
#define r1p2Off 3818455703
#define r1p3On 3818455991
#define r1p3Off 3818455959
#define r1AllOn 3818456247
#define r1AllOff 3818456215
#define r2p1On 3530424759
#define r2p1Off 3530424727
#define r2p2On 3530425015
#define r2p2Off 3530424983
#define r2p3On 3530425271
#define r2p3Off 3530425239
#define r2AllOn 3530425527
#define r2AllOff 3530425495

RCSwitch mySwitch = RCSwitch();
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  mySwitch.enableTransmit(16);  // Transmitter is connected to Arduino Pin #16  
  /*
  Optional RCSwitch Settings, default values worked for me
    mySwitch.setPulseLength(320); // Optional set pulse length.
    mySwitch.setProtocol(2); // Optional set protocol (default is 1, will work for most outlets)
    mySwitch.setRepeatTransmit(15);  // Optional set number of transmission repetitions.
  */
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Expected payload to be in form of DEVICE/FUNCTION/COMMAND
  //Example:  plug1/power/on
  
  String msgString; 
  String msgDevice;
  String msgFunction;
  String msgCommand;
  
  Serial.print("Message arrived ["); Serial.print(topic);  Serial.print("] ");
   {                                                     
    char message_buff[length + 1];                  //copy over the payload so that we can add a /0 terminator, this can then be wrapped inside a string for easy manipulation.
    strncpy(message_buff, (char*)payload, length);  //copy over the data
    message_buff[length] = '\0';                    //make certain that it ends with a null         
    msgString = String(message_buff);
    msgString.toLowerCase();                        

    for (int i = 0; i < length; i++) {
      if (msgString.substring(i, i+1) == "/") {
        msgDevice = msgString.substring(0, i);
        break;
        }
    }
    
    for (int i = msgDevice.length()+1; i < length; i++) {
      if (msgString.substring(i, i+1) == "/") {
        msgFunction = msgString.substring(msgDevice.length()+1, i);
        msgCommand = msgString.substring(i+1, length);
        break;
        }
    }
   }

  Serial.println();
  Serial.print("Device: ");
  Serial.print(msgDevice);
  Serial.println();
  Serial.print("Function: ");
  Serial.print(msgFunction);
  Serial.println();
  Serial.print("Command: ");
  Serial.print(msgCommand);

  //Trim strings before comparing
  msgDevice.trim();
  msgFunction.trim();
  msgCommand.trim();
 
  if (msgDevice == "r1p1") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r1p1On, 32);
        Serial.print("Powered on r1p1");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r1p1Off, 32);
        Serial.print("Powered off r1p1");
        }
    }
  }

  //Evaluate input received and send proper command  
  if (msgDevice == "r1p2") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r1p2On, 32);
        Serial.print("Powered on r1p2");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r1p2Off, 32);
        Serial.print("Powered off r1p2");
        }
    }
  }  

  if (msgDevice == "r1p3") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r1p3On, 32);
        Serial.print("Powered on r1p3");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r1p3Off, 32);
        Serial.print("Powered off r1p3");
        }
    }
  }

  if (msgDevice == "r2p1") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r2p1On, 32);
        Serial.print("Powered on r2p1");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r2p1Off, 32);
        Serial.print("Powered off r2p1");
        }
    }
  }

  if (msgDevice == "r2p2") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r2p2On, 32);
        Serial.print("Powered on r2p2");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r2p2Off, 32);
        Serial.print("Powered off r2p2");
        }
    }
  }  

  if (msgDevice == "r2p3") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r2p3On, 32);
        Serial.print("Powered on r2p3");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r2p3Off, 32);
        Serial.print("Powered off r2p3");
        }
    }
  }

  if (msgDevice == "r1AllOff") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r1AllOn, 32);
        Serial.print("Powered on r1All");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r1AllOff, 32);
        Serial.print("Powered off r1All");
        }
    }
  }

  if (msgDevice == "r2AllOff") {
    if (msgFunction == "power") {
      if (msgCommand == "on"){
        mySwitch.send(r2AllOn, 32);
        Serial.print("Powered on r1All");
        }
      else if (msgCommand == "off") {
        mySwitch.send(r2AllOff, 32);
        Serial.print("Powered off r1All");
        }
    }
  }


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      IPAddress       ip = WiFi.localIP();
      String  DisplayAddress = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
      char charIP[DisplayAddress.length()+1];
      DisplayAddress.toCharArray(charIP, DisplayAddress.length()+1);
      client.publish("rfPlug/ipAddress", charIP );
      
      // ... and resubscribe
      client.subscribe("rfPlug");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
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

