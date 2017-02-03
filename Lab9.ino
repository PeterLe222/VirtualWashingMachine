void setup() {
  pinMode(A0,INPUT); // switch 1
  pinMode(A1,INPUT); // switch 2
  pinMode(A2,INPUT); // switch 3
  Serial.begin(9600);
  pinMode(2,INPUT);  // LED
  pinMode(3,OUTPUT); // motor 1
  pinMode(5,OUTPUT); // motor 2
  pinMode(6,OUTPUT); // relay
  /* pin 7-13 7-segment */
  pinMode(7,OUTPUT);  // A
  pinMode(8,OUTPUT);  // B
  pinMode(9,OUTPUT);  // C
  pinMode(10,OUTPUT); // D
  pinMode(11,OUTPUT); // E
  pinMode(12,OUTPUT); // F
  pinMode(13,OUTPUT); // G
}
#define LED 2
#define motor1 3
#define motor2 5
#define relay 6

const byte ledPin[] = {7,8,9,10,11,12,13};
const byte number[] = { // number display on 7-segment
                       0b1000000, // 0
                       0b1111001, // 1
                       0b0100100, // 2
                       0b0110000, // 3
                       0b0011001, // 4
                       0b0010010, // 5
                       0b0000010, // 6
                       0b1111000, // 7
                       0b0000000, // 8
                       0b0010000, // 9
                       0b1111111  // off
                      };
int S1, S2, S3;   // switch 1, 2, 3
int washStep = 1; // variable to check the steps

void sevenSegment(int num);
void motor(int motorNum,int motorSpeed, int motorTime);    
             
void loop() {
  sevenSegment(10); // turn off the 7-segment
  S1 = analogRead(A0);
  S2 = analogRead(A1);
  S3 = analogRead(A2);
  Serial.print("switch 1 = ");Serial.println(S1);
  Serial.print("switch 2 = ");Serial.println(S2);
  Serial.print("switch 3 = ");Serial.println(S3);
  delay(5000);
  
  if (S1 > 1000) // Switch 1 is ON
  {
    digitalWrite(relay,HIGH); // relay ON
    sevenSegment(0);          // 7-segment displays '0'
    delay(1000);
    
    /* Step 1: Washing machine takes water about 3 s. */
    if (washStep == 1)
    { 
      /* switch 2 '1' whenever there is 
         enough water in the machine. */
      if (S2 > 1000 && S3 == 0)
      {
        sevenSegment(3);
        motor(motor2,255,3000);
        washStep++;
      }
    }
    /* Step 2: Washing machine is washing 9 s. 
       (The speed of the motor should be moderate). */
    if (washStep == 2)
    { 
      /* switch 2 '1' whenever there is 
         enough water in the machine. */
      if (S2 > 1000 && S3 == 0)
      {
        motor(motor1,125,9000);
        washStep++;
      }
    }
    /* Step 3: Dirty water is pumped out 
       of the machine about 3 s.
       Step 6: Rinsing water is pumped out of 
       the machine about 3 s.*/
       // two steps are same function
    if (washStep == 3 || washStep == 6)
    { 
      /* switch 3 '1'  whenever all the water is 
         pumped out of the machine. */
      if (S3 > 1000 && S2 == 0)
      {
        motor(motor2,255,3000);
        washStep++;
      }
    }
    /* Step 4: Washing machine takes water about 3 s. */
    if (washStep == 4)
    { 
      /* switch 3 '1'  whenever all the water is 
         pumped out of the machine. */
      if (S3 > 1000 && S2 == 0)
      {
        motor(motor2,255,3000);
        washStep++;
      }
    }
    /* Step 5: Washing machine is rinsing 5 s. */
    if (washStep == 5)
    { 
      /* switch 2 '1' whenever there is 
         enough water in the machine. */
      if (S2 > 1000 && S3 == 0)
      {
        motor(motor1,255,5000);
        washStep++;
      }
    }
    /* Step 7: Washing machine is centrifuging 5 s. 
       (The speed of the motor should be high).  */
    if (washStep == 7)
    { 
      /* switch 3 '1'  whenever all the water is 
         pumped out of the machine. */
      if (S3 > 1000 && S2 == 0)
      {
        motor(motor1,255,5000);
        washStep++;
      }
    }
    /* final step blink the led 3 times */
    if (washStep == 8)
    {
      for(int i = 0; i < 3; i++)
      {
        digitalWrite(LED,HIGH);
        delay(1000);
        digitalWrite(LED,LOW);
        delay(1000);
      } 
    }
  }
  /* switch 1 is OFF: replay OFF and 
     reset the washStep. */
  if (S1 == 0)
  {
    digitalWrite(relay,LOW);
    washStep = 1;
  }
}

/* function display number on 7-segment */
void sevenSegment(int num) {
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(ledPin[i],bitRead(number[num],i));
  }
}
/* function run and stop the motor */
void motor(int motorNum,int motorSpeed, int motorTime) { 
   analogWrite(motorNum,motorSpeed);
   delay(motorTime);
   analogWrite(motorNum,0);
   sevenSegment(motorTime/1000);
}

