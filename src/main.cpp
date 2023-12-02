#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>

// SSID & Password
const char *ssid = "HomeAWiFi";                // Enter your SSID here
const char *password = "gabriel99GlobeAtHome"; // Enter your Password here

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

void handle_root();

void setup()
{
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); // Show ESP32 IP on serial

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop()
{
  server.handleClient();
}

// Handle root url (/)
void handle_root()
{
  // Open the HTML file
  File file = SPIFFS.open("/index.html", "r");

  if (file)
  {
    // Read the content of the file
    String htmlContent = "";
    while (file.available())
    {
      htmlContent += (char)file.read();
    }

    // Close the file
    file.close();

    // Send the HTML content as the response
    server.send(200, "text/html", htmlContent);
  }
  else
  {
    server.send(500, "text/plain", "Internal Server Error");
  }
}