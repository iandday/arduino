/*
  Westinghouse Indoor Wireless Remote System 
  Model TK301
  Item T28064
  UPC 686140280641
  
  Adapted from: https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// Set 1
#define r1p1On 3818455479
#define r1p2On 3818455735
#define r1p3On 3818455991
#define r1pAllOn 3818456247
#define r1p1Off 3818455447
#define r1p2Off 3818455703
#define r1p3Off 3818455959
#define r1AllOff 3818456215

// Set 2
#define r2p1On 3530424759
#define r2p2On 3530425015
#define r2p3On 3530425271
#define r2pAllOn 3530425527
#define r2p1Off 3530424727
#define r2p3Off 3530425239
#define r2p2Off 3530424983
#define r2AllOff 3530425495


void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {

  Serial.print("Switching ON");
  mySwitch.send(r1p3On, 32);
  delay(1000);  
  Serial.print("Switching OFF");
  mySwitch.send(r1p3Off, 32);
  delay(1000);  


}
