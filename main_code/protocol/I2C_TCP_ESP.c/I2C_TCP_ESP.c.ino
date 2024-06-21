#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "stdint.h"
#include "string.h"

const char* ssid = "UTE.Aruba325";
const char* password = "vnhcmute";
// const char* ssid = "Bliss";
// const char* password = "Daminh25";
// const char* ssid = "NHA TRO LE VAN VIET";
// const char* password = "0902511322";
const char* host = "172.20.16.14 ";
const uint16_t port = 55555;

int bitArray_int[5];
uint count = 0;
String binaryString;
String receivedData;
String first32Bits;
String remainingBits;
uint8_t Data_send[6];
char charArray[50]; // Ensure enough space for received data

void setup() 
{
  pinMode(4, OUTPUT);
  Wire.begin(); // Initialize Wire (I2C) library
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");
}

void loop() {
  WiFiClient client;
  while (!client.connect(host, port)) 
  {
    Serial.println("Connection to server failed. Retrying...");
    delay(1000); // Wait 1 second before retrying
  }

  count = 0;
  while (client.connected()) 
  {
    client.println("HEARTBEAT");
    // if (client.available())
    // {
      // Step 1: Read the string until newline
      String receivedData = client.readStringUntil('\n');
      Serial.print("Data_01: ");
      Serial.println(receivedData);
      
      // client.println("HEARTBEAT");

      // Step 2: Convert the string to a char array
      Serial.print("Data_char: ");
      receivedData.toCharArray(charArray, sizeof(charArray));
      for(int i = 0; i<5; i++)
      {
        Serial.println(charArray[i]);
      }
      

      if (charArray[0] == 'x' || charArray[0] == 'm')
      {
        String Data_x_string = receivedData.substring(1); // Remove 'x'
        float Data_x_float = Data_x_string.toFloat();  // Convert to float
        int32_t Data_x_Temp_1 = Data_x_float * pow(10, 4); // Scale float
        Data_send[0] = (Data_x_Temp_1 >> 24) & 0xFF;
        Data_send[1] = (Data_x_Temp_1 >> 16) & 0xFF;
        Data_send[2] = (Data_x_Temp_1 >> 8) & 0xFF;
        Data_send[3] = Data_x_Temp_1 & 0xFF;
        Data_send[4] = 0x04; // Exponent of 4
        if(charArray[0] == 'm')
        {
          Data_send[5] = 0x16; // Data X with continue flag
        }
        else
        {
          Data_send[5] = 0x11;
        }
        
      }
      else if (charArray[0] == 'y' || charArray[0] == 'n')
      {
        String Data_y_string = receivedData.substring(1); // Remove 'y'
        float Data_y_float = Data_y_string.toFloat();  // Convert to float
        int32_t Data_y_Temp_1 = Data_y_float * pow(10, 4); // Scale float
        Data_send[0] = (Data_y_Temp_1 >> 24) & 0xFF;
        Data_send[1] = (Data_y_Temp_1 >> 16) & 0xFF;
        Data_send[2] = (Data_y_Temp_1 >> 8) & 0xFF;
        Data_send[3] = Data_y_Temp_1 & 0xFF;
        Data_send[4] = 0x04; // Exponent of 4
        if(charArray[0] == 'm')
        {
          client.println("DONE");
          Data_send[5] = 0x26; // Data X with continue flag
        }
        else
        {
          Data_send[5] = 0x21;
          
        }

      }
      digitalWrite(4, HIGH);

      // Set up and send data via I2C
      Wire.beginTransmission(0x12);
      for (int i = 0; i < 6; i++) 
      {
        Wire.write(Data_send[i]);
        Serial.println(Data_send[i]);
      }
      Wire.endTransmission();

      digitalWrite(4, LOW);
    // }
    // delay(50);
  }

  client.stop(); // Close the connection
}
