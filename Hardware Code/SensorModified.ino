// Including Libraries
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include "ThingSpeak.h"

// Creating wifi & http client objects
WiFiClient client;
HTTPClient http;

// Setting wifi name and password
const char* ssid = "POCO M4 5G";
const char* password = "@np@s.....@"; 

// Defining pins for sensors
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Setting api keys for thingspeak 
unsigned long myChannelNumber = 2473069;
const char * myWriteAPIKey = "16BD2RV42BA6HC3R";
const char * myReadAPIKey = "FW6PX9J38PRLL7JP";
String myStatus = "";

// Defining variables
float MQ3pin = A0,t,h;
const int gas = 0;
int cloud=0,statusCode, httpCode, httpResponseCode;
int bf1,bf2,bf3,bf4,bf5,bf6,af1,af2,af3,af4,af5,af6,x;


void setup(){
  // Initializing LCD
  lcd.init();
  lcd.backlight();

  // Setting serial monitor
  Serial.begin(115200);

  // Connecting to wifi
  WiFi.begin(ssid, password);
  lcd.setCursor(0,0);
  lcd.print("Connecting..");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi network with IP Address: ");
  Serial.print(WiFi.localIP());
  lcd.setCursor(0,0);
  lcd.print("Connected..");
  ThingSpeak.begin(client);  
  Wire.begin();
  delay(2000);
  lcd.clear();
}


void loop(){

  // Reading sensor data
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float x = analogRead(MQ3pin);
  int z = (x/1024)*100;

  while(isnan(t)){
    t = dht.readTemperature();
  }
  while(isnan(h)){
    h = dht.readHumidity();
  }
  while(isnan(x)){
    x = analogRead(MQ3pin);
  }
  z = (x/1024)*100;

  // Handling NaN values
  if (isnan(h) || isnan(t) ) {
   t=15;
   h=35;
  }

  // Displaying Sensor data
  String curr_condition="Temp: " + String(t)+" deg Cel, Hum: "+String(h)+"%, Gas: "+String(z) + "%";
  Serial.println(curr_condition);

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(2,0);
  lcd.print(t);
  
  lcd.setCursor(10,0);
  lcd.print("H:");
  lcd.setCursor(12,0);
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0,1);
  lcd.print("Gas:");
  lcd.setCursor(5,1);
  lcd.print(z);
  lcd.setCursor(8,1);
  lcd.print("%");

  cloud=cloud+1;
  // Updating cloud to database after every 30 iterations
  if(cloud>=30){
    Serial.println("Database updation...");
    cloud=0;
    http.begin(client,"http://coldstoragemonitor.000webhostapp.com/add.php?temp="+ String(t)+ "&hum="+String(h)+"&gas="+String(z)); 
    httpCode = http.GET();
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.println("[HTTP] GET... failed, error: %s\n");
    }
    http.end(); 
    Serial.println();
  }

  // Sending alert to user when temperature goes beyond Ideal values
  if(t<=13 || t>=20 ){
    Serial.println("SendAlert Call");
    String message="Alert...Take Action. "+ curr_condition;
    String url = "http://api.callmebot.com/text.php?user=borkarh&text="+urlEncode(message);

    httpResponseCode = 0;

    while(httpResponseCode!=200){
      http.begin(client, url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      httpResponseCode = http.POST(url);
      delay(200);
    }


    if (httpResponseCode == 200){
        Serial.println("Message sent successfully");
    }
    else{
        Serial.println("Error sending the message");
    }
    http.end();

    Serial.println("Waiting for response");
    // Reading thingspeak data
    statusCode=0;
    while(statusCode!=200){
      bf1 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }

    statusCode=0;
    while(statusCode!=200){
      bf2 = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      bf3 = ThingSpeak.readLongField(myChannelNumber, 3, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      bf4 = ThingSpeak.readLongField(myChannelNumber, 4, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      bf5 = ThingSpeak.readLongField(myChannelNumber, 5, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      bf6 = ThingSpeak.readLongField(myChannelNumber, 6, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }

    Serial.println("Thingspeak before code " + String(statusCode));
    Serial.println("Before value: bf1: " + String(bf1) + " bf2: " + String(bf2) + " bf3: " + String(bf3)+ " bf4: " + String(bf4)+ " bf5: " +String(bf5)+ " bf6: " +String(bf6) );

    delay(30000);

    Serial.println("Thingspeak started");

    statusCode=0;
    while(statusCode!=200){
      af1 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }

    statusCode=0;
    while(statusCode!=200){
      af2 = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      af3 = ThingSpeak.readLongField(myChannelNumber, 3, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      af4 = ThingSpeak.readLongField(myChannelNumber, 4, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      af5 = ThingSpeak.readLongField(myChannelNumber, 5, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    statusCode=0;
    while(statusCode!=200){
      af6 = ThingSpeak.readLongField(myChannelNumber, 6, myReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    
    Serial.println("Thingspeak After code " + String(statusCode));
    Serial.println("After value: af1: " + String(af1) + " af2: " + String(af2) + " af3: " + String(af3)+ " af4: " + String(af4)+ " af5: " +String(af5)+ " af6: " +String(af6) );

    
    
    
    if(af1==bf1 && af2==bf2 && af3==bf3 && af4==bf4 && af5==bf5 && af6==bf6) {
      // Writing Thingspeak data
      ThingSpeak.setField(1, 2);
      ThingSpeak.setField(2, 2);
      ThingSpeak.setField(3, 2);
      ThingSpeak.setField(4, 2);
      ThingSpeak.setField(5, 2);
      ThingSpeak.setField(6, 2);

      ThingSpeak.setStatus(myStatus);
  
      // write to the ThingSpeak channel
      x=0;
      while(x!=200){
        x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        delay(1000);
      }

      if(x == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
 
    }
    else{
      Serial.println("User has taken action");
    }
  }
  Serial.println("Iteration Completed............");
  Serial.println();
  Serial.println();
  delay(200);
}