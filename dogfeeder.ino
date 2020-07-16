//Automatic Dog Feeder.  
//It can be programmed for any time and any day



#define servo1control OCR1A       // servo1 is connected to Arduino pin9
#define servo2control OCR1B     // servo2 is connected to Arduino pin10

//servo constants -- trim as needed
#define servo1null 3035
#define servo2null 3035
// Most servos are analog devices so the exact null point may vary somewhat device to device.
// This is particularly true of continuous rotation servos.


unsigned long now = 0;
unsigned long then = 0;
unsigned long rollover = 0;
unsigned long stoptime = 0;

int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 0;
int weeks = 0;

int oldseconds = 0;
int oldminutes = 0;
int oldhours = 0;






void setup(){
 Serial.begin(9600);
 
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 TCCR1B = 0b00011010;          // Fast PWM, top in ICR1, /8 prescale (.5 uSec)
 TCCR1A = 0b10100010;          //clear on compare match, fast PWM
                               // to use pin 9 as normal input or output, use  TCCR1A = 0b00100010
                               // to use pin 10 as normal input or output, use  TCCR1A = 0b10000010
 ICR1 =  39999;                // 40,000 clocks @ .5 uS = 20mS
 servo1control = servo1null;         // controls chip pin 15  ARDUINO pin 9
 servo2control = servo2null;         // controls chip pin 16  ARDUINO pin 10
}


void loop(){
 
 
 
 
 now = millis();
 
  if (rollover > now){  // this takes into account the eventual
  then = rollover;      //  millis rollover
  }
  rollover = millis();
 
 
 
 if (now - then >= 1000){
Serial.print("Hours: ");
 Serial.println(hours);
Serial.print("Minutes: ");
 Serial.println(minutes);
 Serial.print("Seconds: ");
 Serial.println(seconds);
//Serial.print("Days: ");
//  Serial.println(days);

}
 
 
 if (now - then >= 1000){
 seconds ++;
 then = now;
}
 
 
 if (seconds >= 60){
 minutes++;
 seconds = 0;
}

if (minutes >=60){
hours++;
minutes = 0;
}

if (hours >= 24){
days++;
hours = 0;
}

if (days >=7){
  weeks++;
   days = 0;
}


 
 
 
 

 // Max Speed is 4035 or 2035, 3035 is stationary

   
 if (hours == 0 && minutes == 0 && seconds == 0){
   stoptime= now + 1000;  //set duration of dispensing (1000)
 }
   
 
   
   //TURN ON THE DOG FEEDER
 if (now < stoptime){
 
 servo1control = 2035;             // valid range is servonull +/- 1000
                                  //  - is counter clockwise
                                  //   + is clockwise
                                  // The difference from servonull represents servo angle or,
                                  //for continuous rotation servos, speed.
                                  //These values may differ somewhat unit to unit
 servo2control = 4035;
 
 now=millis();
Serial.print("Stoptime: ");
 Serial.println(stoptime);
 Serial.print("Now is: ");
 Serial.println(now);

 }

 




}
