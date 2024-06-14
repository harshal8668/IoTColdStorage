// Adding libraries
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Setting wifi password and name
const char* ssid = "iotcold";
const char* password = "1234567890";

// Creating wifi and http client object
WiFiClient  client;
HTTPClient http;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Declaring variables
int statusCode = 0,statusCode1 = 0,statusCode2 = 0;
int device_status1,device_status2,device_status3;
int httpCode1,httpCode2,httpCode3;
int device1_pin=D1,device2_pin=D2,device3_pin=D5;

String payload,payload2,payload3;

long currentMillis=0,currTime=0,onTime1=0,onTime2=0,onTime3=0,offTime1=0,offTime2=0,offTime3=0;

int r1=0,r1on=0,r1off=0,dev1on,dev1off,offTimeStart1=0;
int r2=0,r2on=0,r2off=0,dev2on,dev2off,offTimeStart2=0;
int r3=0,r3on=0,r3off=0,dev3on,dev3off,offTimeStart3=0;


// Setting Thingspeak details 
unsigned long counterChannelNumber = 2473069;            // Channel ID
const char * myCounterReadAPIKey = "FW6PX9J38PRLL7JP"; // Read API Key


void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  pinMode(device1_pin,OUTPUT);
  digitalWrite(device1_pin,LOW);
  pinMode(device2_pin,OUTPUT);
  digitalWrite(device2_pin,LOW);
  pinMode(device3_pin,OUTPUT);
  digitalWrite(device3_pin,LOW);
  if (WiFi.status() != WL_CONNECTED){ 
    Serial.println("Connecting to " + String(ssid));
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(19800);
}

void loop(){ 
  Serial.println();
  // currTime=millis();
  // Serial.println(millis());

//DEVICE 1
  httpCode1=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=1");  
  httpCode1 = http.GET();                                  
  if(httpCode1 > 0) { 
    payload = http.getString();   
    device_status1 = payload.toInt();
  }
    
  if(device_status1 == 0){
    Serial.println("Device 1 AC Timer ON");

      //---------------- Device 1 ON TIME ----------------//
    statusCode=0;

    do{
      dev1on = ThingSpeak.readLongField(counterChannelNumber, 1, myCounterReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }while(statusCode!=200);
    dev1on=dev1on*1000;

    Serial.println("Dev1 on time: "+ String(dev1on));
  
    //---------------- Device 1 OFF TIME ----------------//
    statusCode =0;
    do{
      dev1off = ThingSpeak.readLongField(counterChannelNumber, 2, myCounterReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }while(statusCode!=200);
    dev1off=dev1off*1000;
    Serial.println("Dev1 off time: "+ String(dev1off));

    if(dev1on>0 && r1==0 && offTimeStart1==0){
      onTime1 = millis();
      Serial.println("DEV 1 ONTIME "+ String(onTime1));
      r1=1;
      offTime1=0;
    }
    
    if(r1==1){
      digitalWrite(device1_pin,HIGH);
      Serial.println("ON");
    }
  
    if(currTime-onTime1>=dev1on && r1==1 && onTime1>0){
      offTime1 = millis();
      Serial.println("DEV 1 OFFTIME "+ String(offTime1));
      r1=0;
      offTimeStart1=1;
    }
  
    if(r1==0){
      digitalWrite(device1_pin,LOW);
      Serial.println("OFF");
    }
  
    if(currTime-offTime1>=dev1off && offTime1>0){
      r1=0;
      offTimeStart1=0;
      Serial.println("CYCLE FOR DEV 1 OVER");
    }

  }   
  else{
    digitalWrite(device1_pin,HIGH);
    r1=0;
    onTime1=0;
    offTime1=0;
    offTimeStart1=0;
    Serial.println("Device 1 AC Timer OFF");
  }



//DEVICE 2
  httpCode2=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=2");  
  httpCode2 = http.GET();                                        
  if (httpCode2 > 0) { 
    payload = http.getString();  
    device_status2 = payload.toInt();
  }

  if(device_status2 == 0){
    Serial.println("Device 2 GAS TIMER ON");

      //---------------- Device 2 ON TIME ----------------//
    statusCode1=0;
    do{
      dev2on = ThingSpeak.readLongField(counterChannelNumber, 3, myCounterReadAPIKey);
      statusCode1 = ThingSpeak.getLastReadStatus();
      delay(200);
    }while(statusCode1!=200);
    dev2on=dev2on*1000;
    Serial.println("dev2 on time: "+String(dev2on));
  
    //---------------- Device 2 OFF TIME ----------------//
    statusCode1=0;
    do{
      dev2off = ThingSpeak.readLongField(counterChannelNumber, 4, myCounterReadAPIKey);
      statusCode1 = ThingSpeak.getLastReadStatus();
      delay(200);
    }while(statusCode1!=200);
    dev2off=dev2off*1000;
    Serial.println("dev2 off time: "+String(dev2off));

    if(dev2on>0 && r2==0 && offTimeStart2==0){
      onTime2 = millis();
      Serial.println("DEV 2 ONTIME "+ String(onTime2));
      r2=1;
      offTime2=0;
    }

    if(r2==1){
      digitalWrite(device2_pin,HIGH);
      Serial.println("ON");
    }  

    if(currTime-onTime2>=dev2on && r2==1 && onTime2>0){
      offTime2 = millis();
      Serial.println("DEV 2 OFFTIME "+ String(offTime2));
      r2=0;
      offTimeStart2=1;    
    }
    if(r2==0){
      digitalWrite(device2_pin,LOW);
      Serial.println("OFF");
    }   

    if(currTime-offTime2>=dev2off && offTime2>0){
      r2=0;
      offTimeStart2=0;
      Serial.println("CYCLE FOR DEV 2 OVER");
    }  
  }   
  else{
    digitalWrite(device2_pin,HIGH);
    r2=0;
    onTime2=0;
    offTime2=0;
    offTimeStart2=0;
    Serial.println("Device 2 GAS TIMER OFF");
  }

//DEVICE 3
  httpCode3=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=3");  
  httpCode3 = http.GET();                                       
  if (httpCode3 > 0) { 
    payload = http.getString();   
    device_status3 = payload.toInt();
  }

  if(device_status3 == 0){
    Serial.println("Device 3 FAN TIMER ON");

    //---------------- Device 3 ON TIME ----------------//
    statusCode2=0;
    do{
      dev3on = ThingSpeak.readLongField(counterChannelNumber, 5, myCounterReadAPIKey);
      statusCode2 = ThingSpeak.getLastReadStatus();
      delay(200);
    }while(statusCode2!=200);
    dev3on=dev3on*1000;
    Serial.println("dev3 on: "+String(dev3on));
 
    //---------------- Device 3 OFF TIME ----------------//
    statusCode2=0;
    do{
      dev3off = ThingSpeak.readLongField(counterChannelNumber, 6, myCounterReadAPIKey);
      statusCode2 = ThingSpeak.getLastReadStatus();
      delay(200);
    } while(statusCode2!=200);
    dev3off=dev3off*1000;
    Serial.println("dev3 off: "+String(dev3off));

    if(dev3on>0 && r3==0 && offTimeStart3==0){
      onTime3 = millis();
      Serial.println("DEV 3 ONTIME "+ String(onTime3));
      r3=1;
      offTime3=0;
    }

    if(r3==1){
      digitalWrite(device3_pin,HIGH);
      Serial.println("ON");
    }

    if(currTime-onTime3>=dev3on && r3==1 && onTime3>0){
      offTime3 = millis();
      Serial.println("DEV 3 OFFTIME "+ String(offTime3));
      r3=0;
      offTimeStart3=1;
    }
    if(r3==0){
      digitalWrite(device3_pin,LOW);
      Serial.println("OFF");
    }

    if(currTime-offTime3>=dev3off && offTime3>0){
      r3=0;
      offTimeStart3=0; 
      Serial.println("CYCLE FOR DEV 3 OVER");
    }
  }   
  else{
    digitalWrite(device3_pin,HIGH);
    r3=0;
    onTime3=0;
    offTime3=0;
    offTimeStart3=0;
    Serial.println("Device 3 FAN ON");
  }
  http.end();
//************************************************* 
  currTime=millis(); 
  Serial.println();
  Serial.println();

}