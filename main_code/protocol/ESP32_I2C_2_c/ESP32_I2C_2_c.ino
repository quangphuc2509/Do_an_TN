#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>

const char* ssid = "NHA TRO LE VAN VIET";
const char* password = "0902511322";
const char* host = "192.168.1.51";
const uint16_t port = 55555;

int bitArray_int[5];
int32_t decimalNum ;
void setup() 
{
  Wire.begin(); // Khởi động thư viện Wire (I2C)
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  Serial.println("WiFi connected");
}

void loop() 
{


  decimalNum = 0;
  WiFiClient client;

// while(1)
// {
  //Wire.beginTransmission(0x12); // Bắt đầu gửi dữ liệu tới địa chỉ I2C
      for(int j = 0; j < 5; j++)
      {
        Wire.beginTransmission(0x12); 
        for (int i = 0; i < 5; i++) 
            {  
              //Wire.write(bitArray_int[i]); // Gửi dữ liệu
              Wire.write(0x25);
              Serial.println("Data 0x15");
            }
            Wire.write(0x01);
            Wire.endTransmission(); // Kết thúc gửi dữ liệu
      }
//       Wire.beginTransmission(0x12); 
//       for (int i = 0; i < 5; i++) 
//             {  
//               //Wire.write(bitArray_int[i]); // Gửi dữ liệu
//               Wire.write(0x20);
//               Serial.println("Data 0x20 V2");
//             }
//             Wire.write(0xA5);
//       Wire.endTransmission(); // Kết thúc gửi dữ liệu
// }
    // for(int j = 0; j<5; j++)
    // {
    //   Wire.beginTransmission(0x12); 
    //   for(int i = 0; i<5; i++)
    //   {
    //     Wire.write(0xB7);
    //   }
    //   Wire.write(0x01);
    //   Serial.println("gui B7 *****");
    //   Wire.endTransmission(); // Kết thúc gửi dữ liệu
    // }
    

    // Wire.beginTransmission(0x12); 
    // Wire.write(0xB7);
    // Wire.write(0xB7);
    // Wire.write(0xB5);
    // Wire.write(0xB4);
    // Wire.write(0xB7);
    // Wire.write(0xA5);
    //  Serial.println("gui a5 --------");
    // Wire.endTransmission(); // Kết thúc gửi dữ liệu


  // if (!client.connect(host, port)) 
  //   {
  //     Serial.println("Connection to server failed");
  //     return;
  //   }

  // while (client.connected()) 
  //   {
  //     if (client.available()) 
  //     {
        
  //       String receivedData = client.readStringUntil('\n');
  //       Serial.print("Received data from server: ");
  //       Serial.println(receivedData);


  //       // Tách thành 32 bit liên tiếp và phần còn lại
  //       String first32Bits = receivedData.substring(0, 32);
  //       String remainingBits = receivedData.substring(32);
  //       decimalNum = strtol(first32Bits.c_str(), NULL, 2);
  //       // In ra 24 bit đầu tiên và phần còn lại
  //       Serial.print("First 32 bits: ");
  //       Serial.println(first32Bits);
  //       Serial.print("Remaining bits: ");
  //       Serial.println(remainingBits);
  //       Serial.print("SO THAP PHAN : ");
  //       Serial.println(decimalNum);
         
  //       // Tạo 5 phần tử từ first24Bits và remainingBits
  //       for (int i = 0; i < 5; i++) 
  //         {
  //             String binaryString;
  //             if (i < 4) 
  //               {
  //                   binaryString = first32Bits.substring(i * 8, (i + 1) * 8);
  //               } 
  //             else 
  //               {
  //                   binaryString = first32Bits.substring(i * 8) + remainingBits;
  //               }
              
  //             bitArray_int[i] = strtol(binaryString.c_str(), NULL, 2);// Chuyển đổi từ chuỗi nhị phân thành số nguyên và gán vào mảng
  //         }
  //     //In ra mảng
  //       for (int i = 0; i < 5; i++) 
  //         {
  //             Serial.print("GIA TRI PHAN TU THU  ");
  //             Serial.print(i);
  //             Serial.print(": ");
  //             Serial.println(bitArray_int[i]);
  //         }

  //       Wire.beginTransmission(0x12); // Bắt đầu gửi dữ liệu tới địa chỉ I2C
 
  //       for (int i = 0; i < 5; i++) 
  //           {  
  //             //Wire.write(bitArray_int[i]); // Gửi dữ liệu
  //             Wire.write(0x32);
  //             Serial.print("0x12");
  //           }
  //       Wire.endTransmission(); // Kết thúc gửi dữ liệu


    //   }// ifclient.available

    

      

    // }
      

  //client.stop();

}
