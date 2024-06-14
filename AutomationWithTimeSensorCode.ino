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
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define wifi & http client objects
WiFiClient client;
HTTPClient http;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Setting wifi name and password
const char* ssid = "iotcold";
const char* password = "1234567890"; 

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
float MQ3pin = A0,t,h,g,z;
const int gas = 0;
int cloud=0,statusCode, httpCode, httpResponseCode,send=0;
int bf1,bf2,bf3,bf4,bf5,bf6,af1,af2,af3,af4,af5,af6,x,thingspeak=0;

unsigned long currentMillis,getcurrtime,getSendTime,previousMillis = 0;



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
  Serial.println("Connecting to " + String(ssid));
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(19800);
  Serial.println();
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,0);
  lcd.print("Connected..");
  ThingSpeak.begin(client);  
  Wire.begin();
  delay(2000);
  lcd.clear();
  cloud=0;
}

void loop(){

  Serial.println();
  currentMillis = millis();
  getcurrtime=millis();
  Serial.println("Current millisec: "+ String(currentMillis));

  do{
    t = dht.readTemperature();
    delay(100);
  }while(isnan(t) || t<0 || t>50);

  do{
    h = dht.readHumidity();
    delay(100);
  }while(isnan(h) || h<0 || h>100);
  
  do{
    g = analogRead(MQ3pin);
    delay(100);
  }while(isnan(x) || g>1024);

  z = (g/1024)*100;

  // Displaying Sensor data
  String curr_condition="Temp: " + String(t)+" deg Cel, Hum: "+String(h)+"%, Gas: "+String(z) + "%";
  Serial.println(curr_condition);

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(2,0);
  lcd.print(t);
  
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.setCursor(12,0);
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0,1);
  lcd.print("Gas:");
  lcd.setCursor(5,1);
  lcd.print(z);
  lcd.setCursor(10,1);
  lcd.print("%");

  
     //Updating database after every 30 seconds
  if(cloud==0 || currentMillis - previousMillis >= 20000 ){
    Serial.println("Database updation...");

    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    ThingSpeak.setField(3, z);
    ThingSpeak.setStatus(myStatus);

    // write to the ThingSpeak channel
    x=0;
    do{
      x = ThingSpeak.writeFields(2492979,"BV63T1LIWZUMB5FE");
      delay(200);
    }while(x!=200);


    do{
      http.begin(client,"http://coldstoragemonitor.000webhostapp.com/add.php?temp="+ String(t)+ "&hum="+String(h)+"&gas="+String(z)); 
      httpCode = http.GET();
      Serial.println(httpCode);
      if(httpCode!=200){
        delay(2000);
      }
    }while(httpCode!=200);

    http.end(); 
    cloud=1;
    previousMillis = currentMillis;
  }
  

  // Sending alert to user when temperature goes beyond Ideal values
  if(t<=13 || t>=20){ 

    if(send==0 || getcurrtime-getSendTime>=900000){ //FIRST ALERT MSG or SEND MSG AFTER EVERY 15 Min
      Serial.println("ALERT MSG SEND");
      String message="Alert...Take Action. "+ curr_condition;
      String url = "http://api.callmebot.com/text.php?user=borkarh&text="+urlEncode(message);

      httpResponseCode = 0;

      do{
        http.begin(client, url);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        httpResponseCode = http.POST(url);
        delay(200);
      }while(httpResponseCode!=200);
      
      Serial.println("Message sent successfully");
      http.end();


      send=1;
      getSendTime = getcurrtime;
      thingspeak=1;

      // Reading thingspeak data
      statusCode=0;
      do{
        bf1 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        bf2 = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        bf3 = ThingSpeak.readLongField(myChannelNumber, 3, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        bf4 = ThingSpeak.readLongField(myChannelNumber, 4, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        bf5 = ThingSpeak.readLongField(myChannelNumber, 5, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        bf6 = ThingSpeak.readLongField(myChannelNumber, 6, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);
      
      Serial.println("Thingspeak before code " + String(statusCode));
      Serial.println("Before value: bf1: " + String(bf1) + " bf2: " + String(bf2) + " bf3: " + String(bf3)+ " bf4: " + String(bf4)+ " bf5: " +String(bf5)+ " bf6: " +String(bf6) );

    }

    if(getcurrtime-getSendTime>=60000 && thingspeak==1){ //Waiting for 1 Min
      statusCode=0;
      do{
        af1 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        af2 = ThingSpeak.readLongField(myChannelNumber, 2, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        af3 = ThingSpeak.readLongField(myChannelNumber, 3, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        af4 = ThingSpeak.readLongField(myChannelNumber, 4, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        af5 = ThingSpeak.readLongField(myChannelNumber, 5, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      statusCode=0;
      do{
        af6 = ThingSpeak.readLongField(myChannelNumber, 6, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        delay(200);
      }while(statusCode!=200);

      Serial.println("Thingspeak After code " + String(statusCode));
      Serial.println("After value: af1: " + String(af1) + " af2: " + String(af2) + " af3: " + String(af3)+ " af4: " + String(af4)+ " af5: " +String(af5)+ " af6: " +String(af6) );

      thingspeak=0;
      
      if(af1==bf1 && af2==bf2 && af3==bf3 && af4==bf4 && af5==bf5 && af6==bf6) {
        

        // Writing Thingspeak data
        ThingSpeak.setField(1, 10);
        ThingSpeak.setField(2, 10);
        ThingSpeak.setField(3, 10);
        ThingSpeak.setField(4, 10);
        ThingSpeak.setField(5, 10);
        ThingSpeak.setField(6, 10);
        ThingSpeak.setStatus(myStatus);

        // write to the ThingSpeak channel
        x=0;
        do{
          x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
          if(x!=200){
            delay(1000);
          }
        }while(x!=200);

        if(x == 200){
          Serial.println("Channel update successful.");
          String msg="Automatic time updated";
          String url = "http://api.callmebot.com/text.php?user=borkarh&text="+urlEncode(msg);

          httpResponseCode = 0;

          do{
            http.begin(client, url);
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            httpResponseCode = http.POST(url);
            delay(200);
          }while(httpResponseCode!=200);
          Serial.println("Message sent successfully");
          http.end();

        }
        else{
          Serial.println("Problem updating channel. HTTP error code " + String(x));
        }  
      }
      else{
        Serial.println("User has taken action");
      }
    }
    else{
      Serial.println("Waiting for response");
    }
  }

  Serial.println();
  Serial.println();
  delay(200);
}
