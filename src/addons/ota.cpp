#include "ota.h"

OTA::OTA() {
}

void OTA::handleOTAUpdate(WiFiClient& client) {
    sendOTAUpdateForm(client);
}

void OTA::handleOTAUpload(WiFiClient& client) {
    bool isUpdating = false;
    String header = "";
    if (Update.hasError()) {
        Update.end();
    }

    while (client.connected()) {
        if (client.available()) {
            char c = client.read();
            header += c;
            if (header.endsWith("\r\n\r\n")) {
                break;
            }
        }
    }

    if (header.indexOf("Content-Type: multipart/form-data") == -1) {
        client.println("HTTP/1.1 500 Internal Server Error");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Invalid content type. Expected multipart/form-data.");
        return;
    }

    int contentLength = -1;
    if (header.indexOf("Content-Length: ") >= 0) {
        String contentLengthStr = header.substring(header.indexOf("Content-Length: ") + 16);
        contentLengthStr = contentLengthStr.substring(0, contentLengthStr.indexOf("\r\n"));
        contentLength = contentLengthStr.toInt();
    }

    if (contentLength <= 0) {
        client.println("HTTP/1.1 500 Internal Server Error");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Invalid content length.");
        return;
    }

    if (!Update.begin(contentLength)) {
        client.println("HTTP/1.1 500 Internal Server Error");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Failed to start update. Reason: " + String(Update.errorString()));
        return;
    }

    processOTAUpload(client, contentLength);

    if (Update.end(true)) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Update successful. Rebooting...");
        delay(100);
        ESP.restart();
    } else {
        client.println("HTTP/1.1 500 Internal Server Error");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Update failed. Reason: " + String(Update.errorString()));
    }
}

void OTA::sendOTAUpdateForm(WiFiClient& client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<title>OTA Update</title></head>");
    client.println("<body><h1>ESP32 OTA Update</h1>");
    client.println("<form method='POST' action='/update' enctype='multipart/form-data'>");
    client.println("<input type='file' name='firmware'>");
    client.println("<input type='submit' value='Update Firmware'>");
    client.println("</form></body></html>");
}

void OTA::processOTAUpload(WiFiClient& client, int contentLength) {
    uint8_t buffer[1024];
    while (client.connected() && contentLength > 0) {
        if (client.available()) {
            size_t bytesRead = client.readBytes(buffer, min((size_t)client.available(), sizeof(buffer)));
            Update.write(buffer, bytesRead);
            contentLength -= bytesRead;
        }
    }
}
