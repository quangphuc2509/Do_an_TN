//Blynk
#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "Qc1uDkxHAQzNyHMWVIW92jxuYMRXqn0d"
//firebase
#define WIFI_SSID "NHT"
#define WIFI_PASSWORD "28022002"
#define API_KEY "AIzaSyAJs36AwQqRf45Wi1jV7RDwhcaZEO_FYd8"
#define DATABASE_URL "https://datagpstracking-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define USER_EMAIL "thanhnhpy@gmail.com"
#define USER_PASSWORD "Thanh@28022002"

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_RED       "#D3435C"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <FirebaseESP32.h>
#include <TinyGPSPlus.h>
#include <esp32-hal-timer.h>
#include <SoftwareSerial.h> // SoftPin ESP32 for Module SIM
#include <HardwareSerial.h> // HardPin ESP32 for Module GPS
#include <math.h>
#include <String.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

hw_timer_t *timerEsp = NULL;
int timerInterval = 15000;  // Setup timer ESP32 15s

static const uint32_t GPSBaud = 9600; // Baudrate GPS
TinyGPSPlus gps;
HardwareSerial ss(1); // Pin 16 17

// sim
SoftwareSerial simSerial(26,27); // RX | TX
char msg;
char call;
//String number1 = "0944785820";// nhap sdt vào đây 0944785820 0374978022
String number1 = "0374978022";
String Phone[2] = {"0374978022", "0938839631"};
int countNumber = 0;
// Config Struct Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

volatile double latitude = 0, longtitude = 0;
volatile double latitudeStation = 0, longtitudeStation = 0;
volatile double latitudeTest =0, longtitudeTest = 0;
volatile float distance = 0,distanceTest=0;     //km
volatile float limitDistance = 1; // km
const double R = 6371.0; // Bán kính trái đất (km)
long stationState = 0, isSent = 0, simState = 0;
int contactStatus = 0;
int updateStation = 0;

bool readData = false;
bool sendCoordinateStation = false;
bool emergency = false;
bool successContact = false;
String message;

char ssid[] = "NHT";
char pass[] = "28022002";

WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget
WidgetLED myLed(V6);
BlynkTimer timer;

BLYNK_CONNECTED() 
{
  myLed.on();
}

void onTimer() 
{
  readData = true;
}

float calculatorDistance(double lat, double lon, double latS, double lonS) 
{
  lat = lat * M_PI / 180.0;
  lon = lon * M_PI / 180.0;
  latS = latS * M_PI / 180.0;
  lonS = lonS * M_PI / 180.0;
  double dlat = latS - lat;
  double dlon = lonS - lon;

  // Áp dụng công thức Haversine
  double a = sin(dlat/2) * sin(dlat/2) + cos(lat) * cos(latS) * sin(dlon/2) * sin(dlon/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double dist = R * c;

  return dist;
}

void readDatafromServer() 
{
  if (Firebase.getFloat(fbdo, "/gps/latitude")) 
  {
    latitude = fbdo.to<float>()/1000000;
  }
  if (Firebase.getFloat(fbdo, "/gps/longtitude")) 
  {
    longtitude = fbdo.to<float>()/1000000;
  }
}

// send station coordinates
void sendDatatoServer(float lat, float lng, float dis, int st)
{
  if (Firebase.ready()) 
  {
    Firebase.setFloat(fbdo, "/gps/latitudeStation", lat);
    Firebase.setFloat(fbdo, "/gps/longtitudeStation", lng);
    Firebase.setFloat(fbdo, "/gps/distance", dis);
    Firebase.setInt(fbdo, "/gps/contactStatus", st);
  }
}

void myTimerEvent() {
  updateStation++;
  Blynk.virtualWrite(V1, latitude);
  Blynk.virtualWrite(V2, longtitude);
  Blynk.virtualWrite(V3, distance);
  if(updateStation >= 20)
  {
    Blynk.virtualWrite(V4, latitudeStation);
    Blynk.virtualWrite(V5, longtitudeStation);
    updateStation = 0;
  }
  myMap.location(1, latitude, longtitude, "Dog");

  if(contactStatus == 0) myLed.setColor(BLYNK_GREEN);
  else if(contactStatus == 1) myLed.setColor(BLYNK_RED);
  else if(contactStatus == 2) myLed.setColor(BLYNK_BLUE);

  if(distance > limitDistance)
  {
    Blynk.setProperty(V1,"color","#FF0000");
    Blynk.setProperty(V2,"color","#FF0000"); //Red
    Blynk.setProperty(V3,"color","#FF0000");
  }
  else
  {
    Blynk.setProperty(V1,"color","#00FF00");
    Blynk.setProperty(V2,"color","#00FF00"); //Green
    Blynk.setProperty(V3,"color","#00FF00");
  }
}

// Get station coordinates of GPS
void getCoordinates()
{
  // LOCATION
  // Serial.print("StationLocation: ");
  if(gps.location.isValid())
  {
    latitudeStation = gps.location.lat();
    longtitudeStation = gps.location.lng();
    
    Serial.printf("%.7f",latitudeStation);
    Serial.print(" , ");
    Serial.printf("%.7f",longtitudeStation);
  }
  else
  {
    Serial.println("INVALID");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, 16, 17); // Serial for Module GPS
  simSerial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Connect Wifi ESP32
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  timerEsp = timerBegin(0, 80, true);
  timerAttachInterrupt(timerEsp, &onTimer, true);
  timerAlarmWrite(timerEsp, timerInterval * 1000, true);
  timerAlarmEnable(timerEsp);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk-server.com", 8080);

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);

  timer.setInterval(1000L, myTimerEvent);   //Update Blynk every 1s
}

// Message function 
void SendMessage()
{

  simSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(10);
  simSerial.println("AT+CMGS=\"" + Phone[countNumber] + "\"\r");
  // simSerial.println("AT+CMGS=\"" + number1 + "\"\r");  //Mobile phone number to send message
  delay(10);
  simSerial.println("Warning!!!, Your Pet has lost. Please, open Blynk app or access this link https://www.google.com/maps/dir/?api=1&destination=" + String(latitude) + "," + String(longtitude));// Messsage content
  delay(1000);
  simSerial.println((char)26);// ASCII code of CTRL+Z
  delay(10);
  countNumber++;
  if (countNumber >= 2) countNumber = 0;
}

// Call function
void MakeCall() 
{
  simSerial.print (F("ATD"));
  simSerial.print (number1);
  simSerial.print (F(";\r\n"));
  delay(10);
}

//Receive message
void RecieveMessage()
{
  simSerial.println ("AT+CNMI=2,2,0,0,0");
}

void loop() 
{
  Blynk.run();
  timer.run();  // Initiates BlynkTimer
  // Read data of GPS Station
  if(ss.available() > 0)
  {
    if(gps.encode(ss.read()))
    {
      getCoordinates();
    }
  }

  if(simSerial.available() > 0)
  {
    message = simSerial.readString();
    if (message.indexOf("OKE") != -1) 
    {
      Serial.println("Successfully Contacted");
      successContact = true;
      contactStatus = 2;
      // latitudeTest = 10.8423479; longtitudeTest = 106.7632166;
    } 
    else 
    {
      if(successContact == false)
      {
        Serial.println("Contact again!!!");
      }
    }
  }

  if((latitudeStation != 0) && (longtitudeStation !=0) && ((stationState % 2) == 0) && (isSent == 0))
  {
    sendDatatoServer(latitudeStation, longtitudeStation, distance, contactStatus); 
    Serial.println("Sent data to server !!!");
    isSent = 1;
  }

  if (readData)
  {
    readDatafromServer();
    if((latitudeStation != 0) && (longtitudeStation !=0))
    {
      distance = calculatorDistance(latitude, longtitude, latitudeStation, longtitudeStation);
      stationState++;
      if(stationState % 2 == 0) isSent = 0;
      if(distance > limitDistance)
      {
        simState++;
        if(simState % 4 == 0 && successContact == false)
        {
          contactStatus = 1;
          Serial.println("SOS...SOS...SOS");
          SendMessage();// Message
          // MakeCall();// Call

        }
      }
      else 
      {
        simState++;
        successContact = false;
        contactStatus = 0;
      }
    }
    readData = false;
  }
}
