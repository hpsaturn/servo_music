/********************************************************
// AUTHOR: Rob Tillaart 
// PlatformIO and MFS board version: @hpsaturn
// Released to the public domain
********************************************************/

#include <MultiFuncShield.h>
#include <Servo.h>
#include <Wire.h>

Servo mservo_pin6;
Servo mservo_pin9;

#define MAX_ANGLE 180
#define MIN_ANGLE 0

//Note Definitions
const int NOTE_AS3 = 233;
const int NOTE_C4 = 262;
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_GS4 = 415;
const int NOTE_A4 = 440;
const int NOTE_AS4 = 466;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;
const int NOTE_CS5 = 554;
const int NOTE_D5 = 587;
const int NOTE_DS5 = 622;
const int NOTE_E5 = 659;
const int NOTE_F5 = 699;
const int NOTE_FS5 = 740;
const int NOTE_G5 = 784;
const int NOTE_GS5 = 831;
const int NOTE_A5 = 880;

const int rhythmBuzzerPin = 9;
const int rhythmLength = 10;

int rhythmNotes[] = {NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_C5,NOTE_C5,NOTE_C5,  //Intro 1 (21 Notes)
                    NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,0,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_C5,NOTE_C5,NOTE_C5,   //Intro 2 (21 Notes)
                    NOTE_A4,NOTE_A4,NOTE_A4,NOTE_F4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_C5,NOTE_A4,                                                                                 //Part 1  (9 Notes)
                    0,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_F5,NOTE_C5,NOTE_GS4,NOTE_F4,NOTE_C5,NOTE_A4,                                                                              //Part 2  (10 Notes)
                    0,NOTE_A5,NOTE_A4,NOTE_A4,NOTE_A5,NOTE_GS5,NOTE_G5,NOTE_FS5,NOTE_F5,NOTE_FS5,                                                                            //Part 3  (10 Notes)
                    0,NOTE_AS4,NOTE_DS5,NOTE_D5,NOTE_CS5,NOTE_C5,NOTE_B4,NOTE_C5,                                                                                            //Part 4  (8 Notes)
                    0,NOTE_F4,NOTE_GS4,NOTE_F4,NOTE_A4,NOTE_C5,NOTE_A4,NOTE_C5,NOTE_E5,                                                                                      //Part 5  (9 Notes)
                    0,NOTE_A5,NOTE_A4,NOTE_A4,NOTE_A5,NOTE_GS5,NOTE_G5,NOTE_FS5,NOTE_F5,NOTE_FS5,                                                                            //Part 6  (10 Notes)
                    0,NOTE_AS4,NOTE_DS5,NOTE_D5,NOTE_CS5,NOTE_C5,NOTE_B4,NOTE_C5,                                                                                            //Part 7  (8 Notes)
                    0,NOTE_F4,NOTE_GS4,NOTE_F4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_C5,NOTE_A4};                                                                                     //Part 8  (9 Notes)

int rhythmBeats[] = {1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,   //Intro 1
                    1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,    //Intro 2
                    4,4,4,3,1,4,3,1,4,                            //Part 1       
                    4,4,4,4,3,1,4,3,1,4,                          //Part 2
                    4,4,3,1,4,3,1,1,1,1,                          //Part 3
                    3,2,4,3,1,1,1,1,                              //Part 4 
                    3,2,4,3,1,4,3,1,4,                            //Part 5
                    3,4,3,1,4,3,1,1,1,1,                          //Part 6
                    3,2,4,3,1,1,1,1,                              //Part 7 
                    3,2,4,3,1,4,3,1,4};                           //Part 8

int tempo = 150;

void setup() 
{
  pinMode(rhythmBuzzerPin, OUTPUT);
}

void loop() 
{
  int i, rhythmDuration;
  
  for (i = 0; i < rhythmLength; i++) // step through the song arrays
  {
    rhythmDuration = rhythmBeats[i] * tempo;  // length of note/rest in ms
    
    if (rhythmNotes[i] == '0')          // is this a rest? 
    {
      delay(rhythmDuration);            // then pause for a moment
    }
    
    else                          // otherwise, play the note
    {
      tone(rhythmBuzzerPin, rhythmNotes[i], rhythmDuration);
      delay(rhythmDuration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }
  
  while(true){}
}
/*
uint16_t pos = MIN_ANGLE;
bool stop = true;
uint16_t servo_delay = 45;

void display(int value) {
    MFS.write(value);
}

void mfsLoop() {

    byte btn = MFS.getButton();
    MFS.manualDisplayRefresh();
    MFS.isrCallBack();

    if (btn == BUTTON_1_PRESSED || btn == BUTTON_1_LONG_PRESSED) {
        Serial.print("==> btn stop: ");
        stop = !stop;
        Serial.println(stop);
        if (stop) MFS.beep(3, 4, 3, 3); 
        else MFS.beep(1, 1, 3, 3, 1); 
        delay(100);
    } else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
        Serial.print("==> btn- delay: ");
        if (servo_delay > 0) servo_delay--;
        Serial.println(servo_delay);
    } else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
        Serial.print("==> btn+ delay: ");
        if (servo_delay < 255) servo_delay++;
        Serial.println(servo_delay);
    }
    
    display(servo_delay);

}

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println("================================");
    Serial.println("====== SERVO MFS TESTER  =======");
    Serial.println("================================");

    mservo_pin6.attach(6);
    mservo_pin9.attach(9);

    // Timer1.initialize();
    // MFS.initialize(&Timer1);  // initialize multifunction shield library
    MFS.initialize();  // initialize multifunction shield library
    Serial.println("");
    Serial.println("Parameters:");Serial.println("");
    Serial.print("MAX_ANGLE: ");  Serial.println(MAX_ANGLE);
    Serial.print("MIN_ANGLE: ");  Serial.println(MIN_ANGLE);
    Serial.print("INIT DELAY: "); Serial.println(servo_delay);
    Serial.println("");
    Serial.println("=== Multi Function Shield ready ===");
}

bool toggle;

void servoLoop() {
    static uint_fast32_t timeStamp = 0;
    if (millis() - timeStamp > servo_delay) {
        timeStamp = millis();
        // in steps of 1 degree
        mservo_pin6.write(pos);  // tell servo to go to position in variable 'pos'
        mservo_pin9.write(pos);  // tell servo to go to position in variable 'pos'
        if (pos == MAX_ANGLE || pos == MIN_ANGLE) toggle = !toggle;
        if (toggle) pos++;
        else pos--;
    }
}

void logLoop() {
    static uint_fast32_t timeStamp = 0;
    if (millis() - timeStamp > 500) {
        timeStamp = millis();
        Serial.print("angle: "); Serial.print(pos);
        Serial.print(" delay: "); Serial.println(servo_delay);
    }
}

void loop() {
    if (!stop) {
        servoLoop();
        logLoop();
    }
    mfsLoop();
}
*/