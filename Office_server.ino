#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>
//#include <Servo.h> //Add servo library

//int getFingerprintIDez();
int pos = 0;   
int led =13;
int ldr =A0;
int ir = A5;  
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
boolean lock=0;// variable to store the servo position

//Servo servo1; //Define servo name / object
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//#define servoPin 9 //Define pin number to which servo motor is connected
//#define durationTime 3000 //Define the time it remains in the open position of the door lock (miliseconds)
//#define servoMin 0 //Open position
//#define servoMax 90 // Closed position


SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


void setup()   {
  lcd.begin(16, 2);
      
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object

{
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  Serial.begin(9600);
//  Serial.println

  Serial.println("Detect Test");

//  servo1.attach(servoPin); //Define pin number of the servo
//  servo1.write(servoMax); //The position of the servo at the start of the program

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
//    Serial.println

    Serial.println("Found fingerprint sensor!");
  } else {
    //Serial.println
    Serial.println("Did not find fingerprint sensor :");
    while (1);
  }
//  Serial.println
Serial.println("Waiting for valid finger...");
}
pinMode(led,OUTPUT);
pinMode(ldr,INPUT);
pinMode(ir,INPUT);
}

void loop()                     // run over and over again
{

  int ldrStatus = analogRead (ldr),
   isObjectDetected = analogRead(ir);

if(isObjectDetected<80 && ldrStatus <20){
  digitalWrite(led,LOW);
  delay(0);
 
  }
  else{
    digitalWrite(led,HIGH);
 delay(0);
  }


  if(lock){
  getFingerprintIDez();
  delay(50);}
  else if(!lock){
    getFingerprintIDe();
     delay(50);
     boolean abc=false;
    }//don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println
      Serial.println("Imaging error");
      return p;
    default:
      //Serial.println
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println
      Serial.println("Could not find fingerprint features");
      return p;
    default:
//      Serial.println
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
    
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  
  return -1;

    for (pos = 1; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
    pos=180;
    lock=0;
   // waits 15ms for the servo to reach the position
    }
   
  


//  servo1.write(servoMin); //If the fingerprint is correct open the door lock
//  delay(durationTime); //Keep the lock open for the defined duration
//  servo1.write(servoMax); //take the lock OFF again
  
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
  delay(100);
}
int getFingerprintIDe() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  
  return -1;

    for (pos = 180; pos >= 1; pos -= 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
    pos=1;
    lock=1;
   // waits 15ms for the servo to reach the position
    }
   
  


//  servo1.write(servoMin); //If the fingerprint is correct open the door lock
//  delay(durationTime); //Keep the lock open for the defined duration
//  servo1.write(servoMax); //take the lock OFF again
  
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);
  lcd.setCursor(0,1);
  lcd.print("Matched");

   
    
     //lcd.print(finger.confidence);
    
    
   
//  delay(100);
}
