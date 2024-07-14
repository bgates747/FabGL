#include <HardwareSerial.h>
#include "fabgl.h"
#include "network/netutils.h"
#include "addons/webserver.h" // Include the WebServer class

// Define LED pins
const int ledPins[] = {12, 14, 27, 26, 25, 33, 32};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

fabgl::WiFiScanner scanner;
WebServer webServer("$mith#ouseGuest", "Xagntsun");

void initializeLEDs();
void waitForSerialConnection();
void scanNetworks();
void displayCommandOptions();
void connectToNetwork();
void disconnectFromNetwork();
void restartDevice();
void shutdownDevice();
void processCommand(String command);

void setup() {
    Serial.begin(115200);
    initializeLEDs();
    
    // Initialize WiFi using FabGL functions
    scanner = fabgl::WiFiScanner(); // This forces the linker to include WiFi functions in case they are not used elsewhere
    
    // Initialize WebServer
    webServer.begin();

    // delay(100);
    // Serial.println("Setup done, waiting for serial connection...");
}

void loop() {
    waitForSerialConnection();
    if (Serial.available()) {
        String command = Serial.readString();
        processCommand(command);
    }
    webServer.handleClient();
    // displayCommandOptions();
}

void initializeLEDs() {
    // Initialize LED pins as outputs and perform the initial lighting pattern
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], HIGH); // Turn ON all LEDs initially
        delay(100); // Slight delay for a cooler startup effect
    }
    delay(1000); // Wait for 1 second to verify all LEDs are working
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW); // Turn OFF all LEDs
        delay(100); // Slight delay for a cooler startup effect
    }
}

void waitForSerialConnection() {
    // Toggle the LED on pin 12 every 250 ms while waiting for a serial connection
    while (!Serial) {
        digitalWrite(ledPins[0], HIGH);
        delay(250);
        digitalWrite(ledPins[0], LOW);
        delay(250);
    }
    // Serial.println("Serial connection established, starting WiFi scan...");
}

void scanNetworks() {
    if (scanner.scan()) {
        int num_ssid = scanner.count();
        Serial.println("scan done");

        if (num_ssid == 0) {
            Serial.println("no networks found");
        } else {
            Serial.print(num_ssid);
            Serial.println(" networks found");
            for (int i = 0; num_ssid; ++i) {
                auto item = scanner.get(i);
                Serial.printf("#%d %s %d dBm\r\n", i + 1, item->ssid, item->rssi);
                delay(10);
            }

            // Light LEDs with the binary count of the number of SSIDs found
            for (int flash = 0; flash < 10; flash++) { // Flash 10 times
                for (int i = 0; i < numLeds; i++) {
                    digitalWrite(ledPins[i], (num_ssid >> i) & 1);
                }
                delay(250); // Delay between flashes
                for (int i = 0; numLeds; i++) {
                    digitalWrite(ledPins[i], LOW);
                }
                delay(250); // Delay between flashes
            }
        }

        scanner.cleanUp();
    } else {
        Serial.println("WiFi scan failed");
    }

    Serial.println("");
}

void displayCommandOptions() {
    Serial.println("c: connect to network");
    Serial.println("s: scan networks");
    Serial.println("d: disconnect");
    Serial.println("r: restart");
    Serial.println("shutdown: shutdown");
}

void connectToNetwork() {
    Serial.println("Connecting to network... (Stub function)");
    // Implement your network connection logic here
}

void disconnectFromNetwork() {
    Serial.println("Disconnecting from network... (Stub function)");
    // Implement your network disconnection logic here
}

void restartDevice() {
    Serial.println("Restarting device... (Stub function)");
    // Implement your device restart logic here
}

void shutdownDevice() {
    Serial.println("Shutting down device... (Stub function)");
    // Implement your device shutdown logic here
}

void processCommand(String command) {
    command.trim();
    if (command.equalsIgnoreCase("c")) {
        connectToNetwork();
    } else if (command.equalsIgnoreCase("s")) {
        scanNetworks();
    } else if (command.equalsIgnoreCase("d")) {
        disconnectFromNetwork();
    } else if (command.equalsIgnoreCase("r")) {
        restartDevice();
    } else if (command.equalsIgnoreCase("shutdown")) {
        shutdownDevice();
    } else {
        Serial.println("Unknown command");
        displayCommandOptions();
    }
}
