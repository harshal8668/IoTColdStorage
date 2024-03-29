// Adding libraries
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Setting wifi password and name
const char* ssid = "POCO M4 5G";
const char* password = "@np@s.....@";

// Creating wifi and http client object
WiFiClient  client;
HTTPClient http;

// Declaring variables
int statusCode = 0,statusCode1 = 0,statusCode2 = 0;
int device_status1,device_status2,device_status3;
int httpCode1,httpCode2,httpCode3;
int device1_pin=D1,device2_pin=D2,device3_pin=D5;

String payload,payload2,payload3;

int r1=0,r1on=0,r1off=0,dev1on,dev1off;
int r2=0,r2on=0,r2off=0,dev2on,dev2off;
int r3=0,r3on=0,r3off=0,dev3on,dev3off;


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
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
}

void loop(){ 
//DEVICE 1
  httpCode1=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=1");  
  httpCode1 = http.GET();                                  
  if(httpCode1 > 0) { 
    payload = http.getString();   
    device_status1 = payload.toInt();
    Serial.println("Device 1 AC Status= "+ payload );
  }
    
  if(device_status1 == 0){
    Serial.println("Device 1 AC OFF Timer ON"); 

      //---------------- Device 1 ON TIME ----------------//
    statusCode=0;
    while(statusCode!=200){
      dev1on = ThingSpeak.readLongField(counterChannelNumber, 1, myCounterReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    
    if (statusCode == 200){
      Serial.println("Dev1 on time: "+ String(dev1on));
    }
  
    //---------------- Device 1 OFF TIME ----------------//
    statusCode =0;
    while(statusCode!=200){
      dev1off = ThingSpeak.readLongField(counterChannelNumber, 2, myCounterReadAPIKey);
      statusCode = ThingSpeak.getLastReadStatus();
      delay(200);
    }

    if (statusCode == 200){
      Serial.println("Dev1 off time: "+ String(dev1off));
    }

    //---------------- Device 1 SWITCHING---------------//
    if(dev1on>0 && r1==0){
      digitalWrite(device1_pin,HIGH);
      r1on=r1on+1;
      r1off=0;
      Serial.println("r1on for : "+String(r1on));
    }
    
    if(r1on==dev1on){ 
      digitalWrite(device1_pin,LOW);
      r1=1;
      r1off=(r1off+1);
      Serial.println("r1off for: "+String(r1off));
    }
    if(r1off==dev1off){
      r1=0;
      r1on=0;
    }
  }   
  else{
    digitalWrite(device1_pin,HIGH);
    r1=0;
    r1on=0;
    r1off=0;
    Serial.println("Device 1 AC ON Timer OFF");
  }
  delay(200);

//DEVICE 2
  httpCode2=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=2");  
  httpCode2 = http.GET();                                        
  if (httpCode2 > 0) { 
    payload = http.getString();  
    device_status2 = payload.toInt();
    Serial.println("Device 2 Gas Status= " + payload);
  }

  if(device_status2 == 0){
    Serial.println("Device 2 GAS OFF TIMER ON");
      //---------------- Device 2 ON TIME ----------------//
    statusCode1=0;
    while(statusCode1!=200){
      dev2on = ThingSpeak.readLongField(counterChannelNumber, 3, myCounterReadAPIKey);
      statusCode1 = ThingSpeak.getLastReadStatus();
      delay(200);
    }

    if (statusCode1 == 200){
      Serial.println("dev2 on time: "+String(dev2on));
    }
  
    //---------------- Device 2 OFF TIME ----------------//
    statusCode1=0;
    while(statusCode1!=200){
      dev2off = ThingSpeak.readLongField(counterChannelNumber, 4, myCounterReadAPIKey);
      statusCode1 = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    if (statusCode1 == 200){
      Serial.println("dev2 off time: "+String(dev2off));
      
    }

    //---------------- Device 2 SWITCHING---------------//
    if(dev2on>0 && r2==0){
      r2on=r2on+1;
      r2off=0;
      digitalWrite(device2_pin,HIGH);
      Serial.println("r2on for : "+String(r2on));
    }
    
    if(r2on==dev2on){ 
      digitalWrite(device2_pin,LOW);
      r2=1;
      r2off=(r2off+1);
      Serial.println("r2off for: "+String(r2off));
    }

    if(r2off==dev2off){
      r2=0;
      r2on=0;
    }  
  }   
  else{
    digitalWrite(device2_pin,HIGH);
    r2=0;
    r2on=0;
    r2off=0;
    Serial.println("Device 2 GAS ON");
  }
  delay(200);

//DEVICE 3
  httpCode3=0;
  http.begin(client,"http://coldstoragemonitor.000webhostapp.com/devicestatus.php?id=3");  
  httpCode3 = http.GET();                                       
  if (httpCode3 > 0) { 
    payload = http.getString();   
    device_status3 = payload.toInt();
    Serial.println("Device 3 FAN Status= "+payload);
  }

  if(device_status3 == 0){
    Serial.println("Device 3 FAN OFF TIMER ON");

    //---------------- Device 3 ON TIME ----------------//
    statusCode2=0;
    while(statusCode2!=200){
      dev3on = ThingSpeak.readLongField(counterChannelNumber, 5, myCounterReadAPIKey);
      statusCode2 = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    if (statusCode2 == 200){
      Serial.println("dev3on: "+String(dev3on));
    }
 
    //---------------- Device 3 OFF TIME ----------------//
    statusCode2=0;
    while(statusCode2!=200){
      dev3off = ThingSpeak.readLongField(counterChannelNumber, 6, myCounterReadAPIKey);
      statusCode2 = ThingSpeak.getLastReadStatus();
      delay(200);
    }
    if (statusCode2 == 200){
      Serial.println("dev3off: "+String(dev3off));
    }

    //---------------- Device 3 SWITCHING---------------//

    if(dev3on>0 && r3==0){
      r3on=r3on+1;
      r3off=0;
      digitalWrite(device3_pin,HIGH);
      Serial.println("r3on for : "+String(r3on));
    }
    
    if(r3on==dev3on){ 
      digitalWrite(device3_pin,LOW);
      r3=1;
      r3off=(r3off+1);
      Serial.println("r3off for: "+String(r3off));
    }

    if(r3off==dev3off){
      r3=0;
      r3on=0;
    }  
  }   
  else{
    digitalWrite(device3_pin,HIGH);
    r3=0;
    r3on=0;
    r3off=0;
    Serial.println("Device 3 FAN ON");
  }

  Serial.println("Iteration Complete....");
  Serial.println();
  Serial.println();
  delay(200);
}