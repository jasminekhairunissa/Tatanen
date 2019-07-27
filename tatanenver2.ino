#include "DHT.h"
#include <Servo.h>

#define DHTPIN 8
#define DHTTYPE DHT22
int airQuality;//MQ135
//motor#1
int enA = 5;
int in1 = 4;
//motor#2
int enB = 2;
int in3 = 3;
//servo position
int pos = 0;
//led
int ledPin = 13;
//ldr
int ldrPin = A1;

DHT dht(DHTPIN,DHTTYPE);
Servo myservo;
Servo myservo2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in3,OUTPUT);
  myservo.attach(9);
  myservo2.attach(10);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(2000);
  //Air Quality(ammonia)
  airQuality = analogRead(0);
  Serial.print("Air Quality = ");
  Serial.print(airQuality);
  Serial.println(" PPM");
  delay(2000);

  //call motor function
  if(airQuality > 600){
      //motor#1
    digitalWrite(in1,HIGH);
    //set speed 0-255
    analogWrite(enA, 200);
    //motor#2
    digitalWrite(in3,HIGH);
    //set speed 0-255
    analogWrite(enB, 200); 
    delay(1000);
  }

  //servo
   // start dari 0 derajar sampai 180 derajat 
 for(pos = 0; pos < 180; pos += 1)  
 {
  // pada posisi 1 derajat
  // memberitahu servo untuk pergi ke posisi  'pos'
  myservo.write(pos);
  myservo2.write(pos);
  // tunggu 15ms untuk pencapaian  posisi servo    
  delay(15);                  
 } 
 // start dari 180 derajat ke 0 derajat 
 for(pos = 180; pos>=1; pos-=1)  
 {
  // memberitahu servo untuk pergi ke posisi  'pos'                                
  myservo.write(pos);
  myservo2.write(pos);                 
  // tunggu 15ms untuk pencapaian  posisi servo    
  delay(15);                        
 }
 
 //ldr
 int ldrStatus = analogRead(ldrPin);
 Serial.print("light= ");
 Serial.print( ldrStatus);
 if(ldrStatus <= 300){
   digitalWrite(ledPin, HIGH); 
 }else{
   digitalWrite(ledPin, LOW); 
 }
}
