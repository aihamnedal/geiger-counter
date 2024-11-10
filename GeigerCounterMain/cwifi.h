#pragma once

// Statically load WIFI available to us
const char * ssid = "KSU Guest";
const char * password = "";

void printWiFiStatus(uint8_t p_WiFiStatus) {
  switch (p_WiFiStatus) {
    case WL_IDLE_STATUS:
      Serial.println("WL_IDLE_STATUS temporary status assigned when WiFi.begin() is called");
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("WL_NO_SSID_AVAIL   when no SSID are available");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("WL_SCAN_COMPLETED scan networks is completed");
      break;
    case WL_CONNECTED:
      Serial.println("WL_CONNECTED  when connected to a WiFi network");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("WL_CONNECT_FAILED when the connection fails for all the attempts");
      break;
    case WL_CONNECTION_LOST:
      Serial.println("WL_CONNECTION_LOST  when the connection is lost");
      break;
    case WL_DISCONNECTED:
      Serial.println("WL_DISCONNECTED when disconnected from a network");
      break;
  }
}

void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Disconnected From WiFi Network");
  // Attempt Re-Connection
  WiFi.begin(ssid, password);
}

void setupWIFI(NetworkServer & server) {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.onEvent(WiFi_Disconnected_Handler, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, password); // static for now
  
  // Wait until we are connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  printWiFiStatus(WiFi.status());

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Setup complete");

  server.begin(); // begin network server
  
  delay(10);
}
