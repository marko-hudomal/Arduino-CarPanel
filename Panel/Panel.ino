int digit1 = 12; //PWM Display pin 1
int digit2 = 11; //PWM Display pin 2
int digit3 = 10; //PWM Display pin 6
int digit4 = 9; //PWM Display pin 8

//Pin mapping from Arduino to the ATmega DIP28 if you need it
int segA = 8; //Display pin 14
int segB = 7; //Display pin 16
int segC = 6; //Display pin 13
int segD = 5; //Display pin 3
int segE = 4; //Display pin 5
int segF = 3; //Display pin 11
int segG = 2; //Display pin 15
int push = 1;
int haarp = 13;
int started_haarp=0;
int pressed_push=0;
int clicked_push=0;
int tempMode=0;
long startedPush=0;
long endedPush=0;
long tempTime=0;
int AP=A1;
int BUZZ=A2;
int INC=1000;
long LINC=0;
long TIME=0;
int tempC=0;
int MINUS=0;
int nazad=0;
int DB=6;
int DISPLAY_BRIGHTNESS=1000;
void setup() {                
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  
  //pinMode(13, OUTPUT);
 pinMode(BUZZ,OUTPUT);
 pinMode(push,INPUT);
 pinMode(haarp,INPUT);
}

void loop() {
//5000 blindingly bright (15.7mA current draw per digit)
//2000 shockingly bright (11.4mA current draw per digit)
//1000 pretty bright (5.9mA)
//500 normal (3mA)
//200 dim but readable (1.4mA)
//50 dim but readable (0.56mA)
//5 dim but readable (0.31mA)
//1 dim but readable in dark (0.28mA)

  switch (DB){
    case 1: {DISPLAY_BRIGHTNESS=1;break;}
    case 2: {DISPLAY_BRIGHTNESS=5;break;}
    case 3: {DISPLAY_BRIGHTNESS=50;break;}
    case 4: {DISPLAY_BRIGHTNESS=200;break;}
    case 5: {DISPLAY_BRIGHTNESS=500;break;}
    case 6: {DISPLAY_BRIGHTNESS=1000;break;}
    case 7: {DISPLAY_BRIGHTNESS=2000;break;}
    case 8: {DISPLAY_BRIGHTNESS=3500;break;}
    default: {DB=2;break;}
    }
    if ((!pressed_push)&&(!clicked_push)){
      if (digitalRead(push)){
        startedPush=millis();
        pressed_push=1;
        }
      }
  if ((!digitalRead(push))&&(pressed_push))
    {
    clicked_push=1;
    pressed_push=0;
    endedPush=millis();
    }
  if ((endedPush-startedPush) >500) {tempMode=!tempMode;tempTime=millis();clicked_push=0; startedPush=0;endedPush=0;}
  if (clicked_push) {DB++;clicked_push=0;startedPush=0;endedPush=0;} 
 
if (digitalRead(haarp)){
  if (!started_haarp){
    analogWrite(BUZZ,200);delay(500);analogWrite(BUZZ,0);
    TIME=0;
    started_haarp=1;
    }
    
  INC=1022-analogRead(AP);
  INC/=50;
  //analogWrite(BUZZ,200);
 if (TIME<1) TIME=0;
 if (INC==0) INC =1;
 if (INC >=17){
  if (INC==18) if ((millis()/10)%30==0){TIME--;if (TIME<15){analogWrite(BUZZ,200);delay(100);analogWrite(BUZZ,0);} }
  if (INC==19) if ((millis()/10)%20==0){TIME--;if (TIME<15){analogWrite(BUZZ,200);delay(100);analogWrite(BUZZ,0);}}
  if (INC==20) if ((millis()/10)%5==0){TIME--;if (TIME<15){analogWrite(BUZZ,200);delay(100);analogWrite(BUZZ,0);}}
  } 
  else{
   if ((millis()/10)%INC==0){ TIME++;}
  }
  //long startTime = millis();
//displayNumber(INC);
  //displayNumber(millis()/1000);
  displayNumber(TIME);
  //while( (millis() - startTime) < 2000) {
  //displayNumber(1217);
  //}
  //delay(1000);  
}else{
  if (!tempMode)
    displayNumber(11111);
    else
    {


     if (((millis()-tempTime)>2500 )||(tempC==0)){ tempC=((int)(5.0 * analogRead(3) * 100.0) / 1024);tempTime=millis();}
    	//tempC=analogRead(3);
         displayTemp(tempC);
    }
    //delay(500);
   // delay(1000);
   // displayNumber(11111);
   // delay(1000);
   started_haarp=0;
  }
}

//Display brightness
//Each digit is on for a certain amount of microseconds
//Then it is off until we have reached a total of 20ms for the function call
//Let's assume each digit is on for 1000us
//Each digit is on for 1ms, there are 4 digits, so the display is off for 16ms.
//That's a ratio of 1ms to 16ms or 6.25% on time (PWM).
//Let's define a variable called brightness that varies from:
//5000 blindingly bright (15.7mA current draw per digit)
//2000 shockingly bright (11.4mA current draw per digit)
//1000 pretty bright (5.9mA)
//500 normal (3mA)
//200 dim but readable (1.4mA)
//50 dim but readable (0.56mA)
//5 dim but readable (0.31mA)
//1 dim but readable in dark (0.28mA)
//----------------------------------------------------------------------------------------------------------------
void displayNumber(int toDisplay) {
//#define DISPLAY_BRIGHTNESS  2000

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
    if (toDisplay==11111){
      lightNumber(11);
      }else if (toDisplay==22222)
      {
       if (digit==1) lightNumber(10);
       if (digit==2) lightNumber(0);
       if (digit==3) lightNumber(12);
       if (digit==4) lightNumber(12);
       }
    else{
    lightNumber(toDisplay % 10);
    toDisplay /= 10;
    }
  
    delayMicroseconds(DISPLAY_BRIGHTNESS); 
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10); 

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ; 
  //Wait for 20ms to pass before we paint the display again
}


//Given a number, turns on those segments
//If number == 10, then turn off number
//-------------------------------------------------------------------------------------------------------------------------
void displayTemp(int toDisplay) {
//#define DISPLAY_BRIGHTNESS  2000

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
   
       if (digit==1) lightNumber(toDisplay/10);
       if (digit==2) lightNumber(toDisplay%10);
       if (digit==3) lightNumber(13);
       if (digit==4) lightNumber(14);
      
  
   
    
  
    delayMicroseconds(DISPLAY_BRIGHTNESS); 
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10); 

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ; 
  //Wait for 20ms to pass before we paint the display again
}
//----------------------------------------------------------------------------------------------
void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
case 11: //(-)
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
case 12://(F)
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
case 13://(°)
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
case 14://(C)
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;    
  }
}

