/*   
 *    CableCam with Blynk
 *    7/16/2018
 *    Rob Reynolds
 *    
 *    This code is to be loaded onto your Thing ESP8266 board.
 *    You'll need to insert the auth code generated by the Blynk app
 *    into line 37, char auth[]. You'll also need to insert your
 *    network name and password into Blynk.begin, line 46.
 *    
 *    This code is public domain, but if you find it useful, and we
 *    mee at the local someday, you buy me a beer (Beerware License).
 */


#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <SparkFun_TB6612.h> // This is the library that contains the class Motor and all the functions

// Next are the pins for all inputs, keep in mind the PWM defines must be on PWM pins

#define AIN1 4
#define AIN2 12
#define PWMA 13
#define STBY 2 // This is labeled SDA on the Thing board, but is also D2

const int offsetA = 1;

#define BLYNK_PRINT Serial

int travelSpeed = 0;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

char auth[] = "Blynk Auth Token"; // You should get Auth Token in the Blynk App.

Servo servo;  
Servo servo1;   //Defining the two servo motors used.


void setup()  
{
  Serial.begin(9600);
  Blynk.begin(auth, "Network", "Password"); //Put your network and password here, each in quotes
  servo.attach(0);  //Define first servo pin
  servo1.attach(5);  //Define second servo pin
}


BLYNK_WRITE(V1)  
{
  servo.write(param.asInt());  //Takes output from Virtual Pin 1, writes it to Pin 0
}


BLYNK_WRITE(V6)  
{ 
  servo1.write(param.asInt());  //Takes output from Virtual Pin 6, writes it to Pin 5
}  


BLYNK_WRITE(V10)
{
  travelSpeed = map((param.asInt()), 0, 100, -255, 255);  //Controls travel motor speed.
                                                          //Range is reduced to make it easier to park at still
                                                          //Mapped because Blynk wont allow negative values
  motor1.drive(travelSpeed);
}


void loop()  
{ 
  Blynk.run();
}
