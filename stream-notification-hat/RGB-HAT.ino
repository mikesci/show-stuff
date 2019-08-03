/*
  Listens for UDP broadcast messages on the local network to trigger alerts.

  Components
  ----------
  NodeMCU ESP8266 / ESP-12E
  KY-012 Active Buzzer
  KY-016 RGB LED
  Two 100ohm resistors for the green/blue LED pins
  One 180ohm resistor for the red LED pin
  Lots of tape
*/


#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <WiFiUdp.h>

const char* ssid     = "YOURWIFISSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "YOURWIFIPASS";     // The password of the Wi-Fi network

WiFiUDP Udp;
unsigned int localUdpPort = 4577;
char incomingPacket[256];

int redpin = D0;
int greenpin = D1;
int bluepin = D2;
int buzzerpin = D3;

void setup () {
  pinMode (redpin, OUTPUT);
  pinMode (bluepin, OUTPUT);
  pinMode (greenpin, OUTPUT);
  pinMode (buzzerpin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
  }

  Udp.begin(localUdpPort);
  
  // blank out the LED
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);

  // silence the buzzer
  analogWrite (buzzerpin, 0);
}
 
void loop () {

  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      switch(incomingPacket[0]) {
        case 1: subscribe(); break;
        case 2: bits(); break;
        case 3: donation(); break;
        case 4: raid(); break;
        // case 5: gift(); break;
        case 6: follow(); break;
        case 7: chat(incomingPacket[1], incomingPacket[2], incomingPacket[3]); break;
        default: break;
      }
    }
  }

}

void subscribe() {

  for (int i = 0; i < 3000; i++) {
    // buzzer pattern
    switch (i / 100) {
      case 0: analogWrite (buzzerpin, 400); break;
      case 1: analogWrite (buzzerpin, 0); break;
      case 2: analogWrite (buzzerpin, 250); break;
      case 3: analogWrite (buzzerpin, 0); break;
      case 4: analogWrite (buzzerpin, 200); break;
      default: analogWrite (buzzerpin, 0); break;
    }
    
    // led pattern
    if (i < 500) {
      analogWrite (redpin, 1023);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 1000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 1500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    } else if (i < 2000) {
      analogWrite (redpin, 1023);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 2500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 3000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    }
    
    delay (1);
  }

  // reset all to 0
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);
  analogWrite (buzzerpin, 0);
  
}

void bits() {

  for (int i = 0; i < 3000; i++) {
    // buzzer pattern
    switch (i / 100) {
      case 0: analogWrite (buzzerpin, 200); break;
      case 1: analogWrite (buzzerpin, 0); break;
      case 2: analogWrite (buzzerpin, 150); break;
      case 3: analogWrite (buzzerpin, 0); break;
      case 4: analogWrite (buzzerpin, 50); break;
      default: analogWrite (buzzerpin, 0); break;
    }
    
    // led pattern
    if (i < 500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 1000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 1500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 2000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 2500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    } else if (i < 3000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 1023);
      analogWrite (greenpin, 0);
    }
    
    delay (1);
  }

  // reset all to 0
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);
  analogWrite (buzzerpin, 0);
}


void donation() {
  for (int i = 0; i < 3000; i++) {
    // buzzer pattern
    switch (i / 100) {
      case 0: analogWrite (buzzerpin, 200); break;
      case 1: analogWrite (buzzerpin, 0); break;
      case 2: analogWrite (buzzerpin, 200); break;
      case 3: analogWrite (buzzerpin, 0); break;
      case 4: analogWrite (buzzerpin, 200); break;
      default: analogWrite (buzzerpin, 0); break;
    }
    
    // led pattern
    if (i < 500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    } else if (i < 1000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 1500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    } else if (i < 2000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    } else if (i < 2500) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    } else if (i < 3000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 1023);
    }
    
    delay (1);
  }

  // reset all to 0
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);
  analogWrite (buzzerpin, 0);
}


void raid() {
  for (int i = 0; i < 3000; i++) {
    // buzzer pattern
    analogWrite (buzzerpin, (i * 1023) / 3000);
    
    // led pattern
    if (i < 500) {
      analogWrite (redpin, 1023);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 1000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 1500) {
      analogWrite (redpin, 1023);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 2000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 2500) {
      analogWrite (redpin, 1023);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    } else if (i < 3000) {
      analogWrite (redpin, 0);
      analogWrite (bluepin, 0);
      analogWrite (greenpin, 0);
    }
    
    delay (1);
  }

  // reset all to 0
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);
  analogWrite (buzzerpin, 0);
}

void follow() {
  for (int i = 0; i < 1000; i++) {
    // buzzer pattern
    switch (i / 100) {
      case 0: analogWrite (buzzerpin, 100); break;
      default: analogWrite (buzzerpin, 0); break;
    }
    
    // led pattern
    switch (i / 200) {
      case 0:
        analogWrite (redpin, 0);
        analogWrite (bluepin, 1023);
        analogWrite (greenpin, 0);
        break;
      case 1:
        analogWrite (redpin, 0);
        analogWrite (bluepin, 0);
        analogWrite (greenpin, 0);
        break;
      case 2:
        analogWrite (redpin, 0);
        analogWrite (bluepin, 1023);
        analogWrite (greenpin, 0);
        break;
      case 3:
        analogWrite (redpin, 0);
        analogWrite (bluepin, 0);
        analogWrite (greenpin, 0);
        break;
      case 4:
        analogWrite (redpin, 0);
        analogWrite (bluepin, 1023);
        analogWrite (greenpin, 0);
        break;
      default:
        break;
    }
    delay (1);
  }

  // reset all to 0
  analogWrite (redpin, 0);
  analogWrite (bluepin, 0);
  analogWrite (greenpin, 0);
  analogWrite (buzzerpin, 0);
}

void chat(char r, char g, char bl) {
  analogWrite (redpin, (int)(((float)r / 255) * 1023));
  analogWrite (bluepin, (int)(((float)bl / 255) * 1023));
  analogWrite (greenpin, (int)(((float)g / 255) * 1023));
}





