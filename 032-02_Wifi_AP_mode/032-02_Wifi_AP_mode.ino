/**********************************************************************
  Filename    : 032-02_Wifi_AP_mode
  Description : Setting ESP32 to open an access point
  Auther      : Alternatives Solutions.
  Modification: 2026/04/07
**********************************************************************/
//ESP32 for now does not support 5G connection

#include <WiFi.h>
#include <esp_wifi.h> // Required for station list structures
//#include <esp_netif.h>
//#include <esp_netif_types.h>

const char* ap_ssid = "ESP32-Wrov_Network";
const char* ap_password = "pwd@123ESP"; // Must be at least 8 characters


void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Configuring Access Point ...");

  //WiFi.softAP(ap_ssid) can be used for an open network
  if (WiFi.softAP(ap_ssid, ap_password)) {
    Serial.println("Access Point is Ready!");

    // In AP mode, the ESP32 usually defaults to 192.168.4.1
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  } else {
    Serial.println("AP Config Failed.");
  }

}

void loop() {
  // We can monitor how many devices are connected
  int num = WiFi.softAPgetStationNum();
  Serial.printf("Stations connected: %d\n", num);
  if (0 < num) {
    displayConnectedDevices();
  }
  delay(5000);
}


void displayConnectedDevices() {
  wifi_sta_list_t stationList;
  esp_wifi_ap_get_sta_list(&stationList);

  Serial.printf("\n--- Devices connected: %d ---\n", stationList.num);

  for (int i = 0; i < stationList.num; i++) {
    Serial.printf("Device %d | MAC: ", i + 1);
    for (int j = 0; j < 6; j++) {
        Serial.printf("%02X%c", stationList.sta[i].mac[j], j < 5 ? ':' : ' ');
    }
      
    // Note: In Core 3.x, getting the IP string reliably from the 
    // underlying DHCP server without the netif_sta_list struct
    // is tricky. For now, let's confirm the MACs show up!
    Serial.println();
  }
}


/*
void displayConnectedDevices() {
    wifi_sta_list_t stationList;
    esp_wifi_ap_get_sta_list(&stationList);

    Serial.printf("\n--- Connected Devices: %d ---\n", stationList.num);

    // Get the network interface for the Access Point
    esp_netif_t* ap_netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
    esp_netif_sta_list_t netif_sta_list;
    
    // Fetch the IP info for all associated stations
    if (esp_netif_get_sta_list(ap_netif, &stationList, &netif_sta_list) == ESP_OK) {
        for (int i = 0; i < netif_sta_list.num; i++) {
            // Print MAC Address
            Serial.printf("Device %d | MAC: ", i + 1);
            for (int j = 0; j < 6; j++) {
                Serial.printf("%02X%c", netif_sta_list.sta[i].mac[j], j < 5 ? ':' : ' ');
            }
            
            // Print IP Address
            // we use esp_ip4addr_ntoa to convert the raw IP to a readable string
            char ip_str[16];
            esp_ip4addr_ntoa(&netif_sta_list.sta[i].ip, ip_str, sizeof(ip_str));
            Serial.printf("| IP: %s\n", ip_str);
        }
    }
}
*/


/*
void displayConnectedDevices() {
  wifi_sta_list_t stationList;
  tcpip_adapter_sta_list_t adapterList;

  // Get the list of connected stations (MAC addresses)
  esp_wifi_ap_get_sta_list(&stationList);
  // Get the IP addresses corresponding to those MACs
  tcpip_adapter_get_sta_list(&stationList, &adapterList);

  Serial.printf("\nDevices connected: %d\n", adapterList.num);

  for (int i = 0; i < adapterList.num; i++) {
    tcpip_adapter_sta_info_t station = adapterList.sta[i];
    
    Serial.print("Device ");
    Serial.print(i + 1);
    Serial.print(" | MAC: ");
    // Print MAC address
    for (int j = 0; j < 6; j++) {
      Serial.printf("%02X%c", station.mac[j], j < 5 ? ':' : ' ');
    }
    
    Serial.print(" | IP: ");
    Serial.println(ip4addr_ntoa(&(station.ip)));
  }
}
*/