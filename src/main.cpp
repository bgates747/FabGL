#include "fabgl.h"
#include "network/netutils.h"

// Define LED pins
const int ledPins[] = {12, 14, 27, 26, 25, 33, 32};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void initializeLEDs();
void waitForSerialConnection();
void scanNetworks();
void displayCommandOptions();
void connectToNetwork();
void disconnectFromNetwork();
void restartDevice();
void shutdownDevice();

void setup() {
    Serial.begin(115200);
    initializeLEDs();
    
    // Initialize WiFi using FabGL functions
    fabgl::WiFiScanner scanner;  // This forces the linker to include WiFi functions in case they are not used elsewhere

    // If additional WiFi setup is needed, it should be included here

    delay(100);
    Serial.println("Setup done, waiting for serial connection...");
}

void loop() {
    waitForSerialConnection();
    scanNetworks();
    displayCommandOptions();
}

void initializeLEDs() {
    // Initialize LED pins as outputs and perform the initial lighting pattern
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], HIGH); // Turn ON all LEDs initially
        delay(100); // Slight delay for a cooler startup effect
    }
    delay(1000); // Wait for 1 second to verify all LEDs are working
}

void waitForSerialConnection() {
    // Toggle the LED on pin 12 every 250 ms while waiting for a serial connection
    while (!Serial) {
        digitalWrite(ledPins[0], HIGH);
        delay(250);
        digitalWrite(ledPins[0], LOW);
        delay(250);
    }
    Serial.println("Serial connection established, starting WiFi scan...");
}

void scanNetworks() {
    fabgl::WiFiScanner scanner;
    if (scanner.scan()) {
        int num_ssid = scanner.count();
        Serial.println("scan done");

        if (num_ssid == 0) {
            Serial.println("no networks found");
        } else {
            Serial.print(num_ssid);
            Serial.println(" networks found");
            for (int i = 0; i < num_ssid; ++i) {
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
                for (int i = 0; i < numLeds; i++) {
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
    Serial.println("s: shutdown");
}

void connectToNetwork() {
    // Stub function for connecting to a network
}

void disconnectFromNetwork() {
    // Stub function for disconnecting from a network
}

void restartDevice() {
    // Stub function for restarting the device
}

void shutdownDevice() {
    // Stub function for shutting down the device
}
