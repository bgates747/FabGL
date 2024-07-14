#ifndef OTA_H
#define OTA_H

#include <WiFiClient.h>
#include <Update.h>

class OTA {
public:
    OTA();
    void handleOTAUpdate(WiFiClient& client);
    void handleOTAUpload(WiFiClient& client);

private:
    void sendOTAUpdateForm(WiFiClient& client);
    void processOTAUpload(WiFiClient& client, int contentLength);
};

#endif // OTA_H
