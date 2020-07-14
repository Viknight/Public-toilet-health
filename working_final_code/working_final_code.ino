#include <SoftwareSerial.h>

SoftwareSerial gsm(10,11); //RX, TX

// for person counter
#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7

// for other sensors
int VOCSensor = A0;
int LDR = A1;

// for ultrasonic sensor (person counter)
int counter = 0;
int counter1 = 0;
int lf = 0;
int rf = 0;

// variables

int LDRValue;   //LDR sensor
int chk;
int circ = 5;
int heat = 10000;
int circheat = 9;
boolean found = false; 
float VOC, CO, Temp, Sound;


int WL;       
long duration, distance, RightSensor,LeftSensor;
float distance1,distance2,distance3;
int peopleinside=0;
int intvoc, intwl, intpc;

void ShowSerialData()
{
 while(gsm.available()!=0)
   Serial.write(gsm.read());
}

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);
  pinMode(LDR, INPUT);
 
/* Ultrasonic Setup */
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  falan();
  singlecon();
 
}

void loop() {
  
  Serial.print("LDR ");
  Serial.print("%");
  Serial.print(",\t");
  Serial.print("Temperature: ");
  Serial.println("*C");
  

  LDRValue = GetLDR();
  intvoc = GetVOC();
  Serial.println(intvoc);
  GetPC();
  intpc = peopleinside;
  Serial.println(intpc);
  intwl= GetWL();
  Serial.println(intwl);
  
  delay(2000);
  ShowSerialData();
  falan();
  singlecon();
  ShowSerialData();

}
void falan()
{
  Serial.println("Wait...");
  gsm.println("AT");
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CPIN?");
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CREG?");
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CIPSHUT");
  delay(3000);
  ShowSerialData();
  gsm.println("AT+CIPSTATUS");
 
  delay(2000);
  ShowSerialData();
}
void singlecon()
{
  Serial.println("Wait 2...");
  gsm.println("AT+CIPMUX=0");
  delay(2000);
  ShowSerialData();
  gsm.print("AT+CSTT=");
  gsm.print('"');
  gsm.print("airtelgprs.com");
  gsm.println('"');
 
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CIICR");
  delay(2000);
 
  ShowSerialData();
  gsm.println("AT+CIFSR");
  delay(2000);
 
  ShowSerialData();
  gsm.print("AT+CIPSTART=");
  gsm.print('"');
  gsm.print("TCP");
  gsm.print('"');
  gsm.print(',');
  gsm.print('"');
  gsm.print("api.thingspeak.com");
  gsm.print('"');
  gsm.print(',');
  gsm.print("80");
  gsm.write(0x0d);
  gsm.write(0x0a);
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CIPSEND");
  delay(5000);
  ShowSerialData();
  gsm.print("GET");
  gsm.print(' ');
  //gsm.print("http:");
  //gsm.print('/');
  //gsm.print('/');
  //gsm.print("api.thingspeak.com");
  gsm.print('/');
  gsm.print("update?api_key=");
  gsm.print("IOSGSKEAXASPP5HE");//my API Key
  gsm.print("&field1=");
  gsm.print(LDRValue);
  delay(2000);
 gsm.print("&field2=");
  gsm.print(intvoc);
  delay(2000);
 gsm.print("&field3=");
  gsm.print(intwl);
  delay(2000);
 //gsm.print("&field4=");
  //gsm.print(intwl);
 delay(2000);
  gsm.write(0x0d);
  gsm.write(0x0a);
 
  gsm.write(0x1a); // the trick is here to send the request. Its Ctrl+Z to start send process.
  delay(15000);
 
  ShowSerialData();
 
  //gsm.println("AT+CIPSHUT");
  gsm.println("AT+CIPCLOSE");
  gsm.write(0x0d);
  gsm.write(0x0a);
  delay(30000);
  ShowSerialData();
}


int GetLDR(){
  int LDRValue = analogRead(LDR);
  Serial.print(" Light sensor = ");
  Serial.print(LDRValue);  
  if (LDRValue <=700){
  //digitalWrite(RELAY1,1);          // Turns Relay Off
  Serial.println("Light OFF");
  Serial.println("It's Bright Inside;");
  }
  else{
  Serial.println("It's Dark Inside;");
  //digitalWrite(RELAY1,0);           // Turns ON Relays 1
  Serial.println("Light ON");
  }
  return LDRValue;
}


int GetVOC() 
{
 digitalWrite(circheat, HIGH);
 float val0 = analogRead(VOCSensor);
 VOC = map(val0, 0, 1023, 0, 100);
 Serial.print("--> Gas Sensor Readinds :  ");
 Serial.println(VOC);
 
 if(VOC > 30)
 {
 //digitalWrite(RELAY2,0);                               // Turns ON RELAY 2 (Exhaust Fan)
 Serial.println("--> Exhaust Fan is Turned ON ");
 }
 else if( VOC < 30 )
 {
 //digitalWrite(RELAY2,1);                                  // Turns OFF RELAY 2 (Exhaust fan)
 Serial.println("--> Exhaust fan is turned OFF ");
 }

 return VOC;
}



void GetPC()
{
  distance1 = SonarSensor(trigPin1, echoPin1);
  distance2 = SonarSensor(trigPin2, echoPin2);
  
  if(distance2<150){
  lf=1;
  lfin();
  } 
  
  else if(distance1<150){
  rf=1;
  rfout();
  }
   
}

int lfin()
{ 
  delay(250);
  distance1=SonarSensor(trigPin1, echoPin1);

  if(distance1<150)
  {
  rf=1;
  }
  else
  {
    GetPC();
  }
  if((lf==1)&&(rf==1 ))
  {
  Serial.println("--> Out  ");
  Serial.print("Number of People Entered :  ");
  Serial.println(counter);
  
  counter1+=1;
  //Serial.print("Number of People Left :  ");
  //Serial.println(counter1);
 
  
  peopleinside=peopleinside-1;
  Serial.print("Number of people Inside :  ");
  Serial.println(peopleinside);
  Serial.println(" ");
  
  lf=0;
  rf=0;
  return peopleinside;
     GetPC();
 }
}

int rfout()
{
delay(250);
distance2 = SonarSensor(trigPin2, echoPin2);

  if(distance2<150)
  {
  lf=1;
  }
  else
  {
     GetPC();
  }
  if(rf==1 && lf==1 )
  {
   Serial.println("--> In ");
   counter+=1;
   Serial.print("Number of People Entered :  ");
   Serial.println(counter); 
    
   //Serial.print("Number of People Left :  ");
   //Serial.println(counter1);
  

   peopleinside=peopleinside+1;
   Serial.print("Number of people Inside :  ");
   Serial.println(peopleinside);
   Serial.println(" ");

  return peopleinside;

   lf=0;
   rf=0;
   
    GetPC();
  }
}

int GetWL() 
{
distance3=SonarSensor( trigPin3, echoPin3 );

 WL=100-distance3;
  //if (WL <= 30){
  //Serial.println("Water Level is Less than 20% ");
 // }
  //else if ((WL <= 70)&&(WL > 30)){
  //Serial.println("Water Level Adequate : 70%");
 // }
  //else if(WL > 70){
  //Serial.println("Water Level Enough : Above 70%");
  //}
  return WL;
  
}

float getVoltage(int pin){
  return (analogRead(pin)*(5.0/1023.0));
}

float map(float x, float in_min, float in_max, float out_min, float out_max){
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float SonarSensor(int trigPin,int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    pinMode(echoPin, INPUT);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
   
    return distance;
}
