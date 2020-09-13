long int inches, remaincm;
int switch_pin = 4;
int led_pin = 13;
const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 9; // Echo Pin of Ultrasonic Sensor
const int buzz = 12; //buzzer to arduino pin 12
const int motorPin = 6; //vibrating motor

byte leds = 0;

void setup(){
  pinMode(switch_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(buzz, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(motorPin, OUTPUT);
}

void loop() {
  //ultrasonic sensor   
   long duration, inches, cm, total_centimeters;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   //inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   total_centimeters=microseconds_total_centimeters(duration);

   //ultrasonic sensor senses object between 24 & 50cm
   if (total_centimeters<=50 && total_centimeters>0 && total_centimeters>24){                //if far - if switch low:vibrating
                                                                                          //          if switch high: buzzer/beep
    
      if(digitalRead(switch_pin) == LOW){ //vibrating mode
        digitalWrite(motorPin, HIGH);
        digitalWrite(led_pin, HIGH);
        delay(2000);
        digitalWrite(motorPin, LOW);
        digitalWrite(led_pin, LOW);
         delay(2000);
    }


    if(digitalRead(switch_pin) == HIGH){ //buzzer
      int d = map(total_centimeters,1,100,20,2000);
      digitalWrite(led_pin, HIGH);
      tone(buzz,1000);
      delay(1000);
      digitalWrite(led_pin, LOW);
      noTone(buzz);
      delay(1000);
   }
   }

  //ultrasonic sensor senses object between 0 & 24cm
  if (total_centimeters<=24 && total_centimeters>0){                                          //if close (about 9.4 in) - if switch low: vibrating

     if(digitalRead(switch_pin) == LOW){ //vibrating mode
          digitalWrite(motorPin, HIGH);
          digitalWrite(led_pin, HIGH);
          delay(1000);
          digitalWrite(motorPin, LOW);
          digitalWrite(led_pin, LOW);
          delay(1000);
  }

     
if(digitalRead(switch_pin) == HIGH){ //buzzer mode
      int d = map(total_centimeters,1,100,20,2000);
      digitalWrite(led_pin, HIGH);
      tone(buzz,1000);
      delay(100);
      digitalWrite(led_pin, LOW);
      noTone(buzz);
      delay(100);
  }
  }
  
   Serial.print("Distance: ");
//   Serial.print(inches);
//   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm\n");
//   Serial.println();
   delay(100);
}

long microseconds_total_centimeters(long microseconds)
{
  return microseconds/29/2;
}

//inches >>
/*
long microsecondsToInches(long microseconds) {
   return ((microseconds*.0343)/2)/2.54;
}
*/

//cm
long microsecondsToCentimeters(long microseconds) {
   return (microseconds*.0343)/2;
}



/*long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}*/


 //  inches=cm/2.54;
 //  remaincm=cm%2.54; 
