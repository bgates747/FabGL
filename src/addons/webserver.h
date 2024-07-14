#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

class WebServer {
public:
    WebServer(const char* ssid, const char* password);
    void begin();
    void handleClient();

private:
    const char* ssid;
    const char* password;
    WiFiServer server;
    String header;
    String output26State;
    String output27State;
    const int output26;
    const int output27;
    unsigned long currentTime;
    unsigned long previousTime;
    const long timeoutTime;

    void handleRequest(WiFiClient client);
};

#endif // WEBSERVER_H
