#include <SoftwareSerial.h>

// Defining Arduino ports //----------

// for SIM card
SoftwareSerial sim(10, 11);
SoftwareSerial gsm(10,11); //RX, TX

// for person counter
#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7
int percentage;
const int ledPin_green =  13;      // for the indicator
const int ledPin_red =  14;

// for other sensors
int VOCSensor = A0;
int LDR = A1;
int lf = 0;
int rf = 0;
int counter=0;

// Defining Variables //----------

// For notifications //----------
int _timeout;
String _buffer;
String number = "+917208439877"; //-> change with your number

// for person counter //---------
int count_in = 0;
int count_out = 0;
int PC_in_lf = 0;
int PC_out_rf = 0;

// for LDR Sensor
int LDRValue;   

// for others
int circheat = 9;
float VOC, CO, Temp, Sound;
int WL;       
long duration, distance, RightSensor,LeftSensor;
float distance1,distance2,distance3;
int peopleinside=0;
int intvoc, intwl, intpc;

//For the Relay
#define RELAY1  8    
#define RELAY2  9  


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

/* Relay Module Setup */
  pinMode(RELAY1, OUTPUT); 
  pinMode(RELAY2, OUTPUT); 

  pinMode(ledPin_green, OUTPUT);
  pinMode(ledPin_red, OUTPUT);

  //falan();
  //singlecon();
}

void loop() {

  // GetLDR();
   // GetVOC();
   // GetPC();
  GetWL();

    //Indicator_lights();
    //Automate_Lights();
    //Automate_Fans();   

    delay(2000);
    ShowSerialData();
    
   // falan();
   // singlecon();
  //  ShowSerialData();  

    if((LDRValue >= 675) && (VOC >= 54) && (WL <= 30))
    {
      digitalWrite(ledPin_red, HIGH);
      digitalWrite(ledPin_green, LOW);
    }
    else
    {
      digitalWrite(ledPin_green, HIGH);
      digitalWrite(ledPin_red, LOW);
    }
    
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
  gsm.print("imis/internet");
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
  gsm.print("&field4=");
  gsm.print(counter);
  delay(2000);
  gsm.print("&field5=");
  gsm.print(peopleinside);
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
  Serial.print(" Light sensor readings = ");
  Serial.println(LDRValue); 
  
  if(LDRValue>675)
  {
    SendMessage1_notify_light();
  }
   return LDRValue;
}

void Automate_Lights()
{ 
  if (LDRValue >=345){
   digitalWrite(RELAY1,1);          // Turns Relay Off
   Serial.println(" ");
   Serial.println("--> AUTOMATICALLY Lights have been turned OFF "); 
  }
  else{
   digitalWrite(RELAY1,0);          // Turns Relay ON
   Serial.println(" ");
   Serial.println("--> AUTOMATICALLY Lights have been turned ON");
  } 
}

int GetVOC() 
{
 digitalWrite(circheat, HIGH);
 float val0 = analogRead(VOCSensor);
  Serial.println(val0);
 VOC = map(val0, 0, 1023, 0, 100);
 Serial.print("--> Gas Sensor Readinds :  ");
 Serial.println(VOC);
}

void Automate_Fans()
{
 if(VOC > 54)
 {
 digitalWrite(RELAY2,0);                                                   // Turns ON RELAY 2 (Exhaust Fan)
 Serial.println("--> AUTOMATICALLY Exhaust Fan has been Turned ON ");
 }
 else
 {
 digitalWrite(RELAY2,1);                                                    // Turns OFF RELAY 2 (Exhaust fan)
 Serial.println("--> AUTOMATICALLY Exhaust fan has been turned OFF ");
 }
}

void Indicator_lights()
{
  
}

void GetPC()
{
  distance1 = SonarSensor(trigPin1, echoPin1);
  distance2 = SonarSensor(trigPin2, echoPin2);
  Serial.println(distance1);
  if(distance1<50){
  rf=1;
  rfout();
  
  }
  if(distance2<50){
  lf=1;
  lfin();
  }  
   
}

void lfin()
{ 
  delay(200);
  distance1=SonarSensor(trigPin1, echoPin1);
  if(distance1<50){
  rf=1;
  }
  else
  {
    GetPC();
  }
  if((lf==1)&&(rf==1 )){
  counter=counter+1;
  //Serial.println("total number of people visited");
  //Serial.println(counter);
  Serial.println("number of people inside");
  peopleinside=peopleinside+1;
  Serial.println(peopleinside);
  lf=0;
  rf=0;
  if(counter>50)
  {
    SendMessage3_notify_person_count();
  }
  loop();
 }
}

void rfout()
{
  delay(200);
  distance2 = SonarSensor(trigPin2, echoPin2);
  if(distance2<50){
  lf=1;
  }
  else
  {
    GetPC();
  }
  if(lf==1 && rf==1 )
  {
   counter=counter+1;
  // Serial.println("Person counter:");
   //Serial.println(counter);  
   lf=0;
   rf=0;
   Serial.println("number of people inside");
   peopleinside=peopleinside-1;
   if(peopleinside<0)
   {
  peopleinside=0;
   
   }
  
   Serial.println(peopleinside);
   loop();
  }
}
int GetWL() 
{
  distance3=SonarSensor( trigPin3, echoPin3 );
  WL=12-distance3;
percentage=distance3*10;
  Serial.print("Water Level in percentage is: ");
  Serial.println(percentage);
  return WL;
 
  if (WL <= 4){
  Serial.println("Water Level is Less than 20% ");
  SendMessage2_notify_water();
 }
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}


void SendMessage1_notify_light()
{
  sim.println("AT+CSQ");
  Serial.println ("Connection Success----------1");
  sim.println("AT+COPS?"); 
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("sending message");
  
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Faulty Lights, Its already dark and lights aren't turning ON \t दोषपूर्ण रोशनी, इसके पहले से ही अंधेरे और रोशनी चालू नहीं हैं \t सदोष लाइट्स, हे आधीपासूनच गडद आणि दिवे चालू होत नाहीत";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
   Serial.println ("the end");
}

void SendMessage2_notify_water()
{
sim.println("AT+CSQ");
 Serial.println ("Connection Success--------------------2");
 Serial.println ("Coion Succss");
   sim.println("AT+COPS?"); 
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("sending message");
  
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "The water level has reached the minimum level, the Toilet has become unusable \t जल स्तर न्यूनतम स्तर पर पहुंच गया है, शौचालय अनुपयोगी हो गया है \t पाण्याची पातळी किमान पातळीवर पोहोचली आहे, शौचालय निरुपयोगी झाले आहे";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
   Serial.println ("the end");
}

void SendMessage3_notify_person_count()
{
sim.println("AT+CSQ");
  Serial.println ("Connection Success-----------------3");
  Serial.println ("Coion Succss");
  sim.println("AT+COPS?"); 
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("sending message");
  
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "The toilet has been used 50 times today, may require cleaning. \t शौचालय का उपयोग आज 50 बार किया गया है, सफाई की आवश्यकता हो सकती है। \t शौचालय आज 50 वेळा वापरलेले आहे, कदाचित साफसफाईची आवश्यकता असू शकते.";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
   Serial.println ("the end");
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
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
 return distance;
}


void Getmess(){
     
  }
  
void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
  Serial.println("._.");
}
