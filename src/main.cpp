/****************************************************************

Many thanks to dzlonline for the great synth library
https://github.com/dzlonline/the_synth


****************************************************************/

#include <Arduino.h>
#include <synth.h>

#define muxPinA 6
#define muxPinB 7
#define muxPinC 8
#define muxInhibitPin 13
#define pitchPin A0
#define tempoPin A1
#define waveformPin A2
#define envelopePin A3
#define durationPin A6
#define modPin A7

int pitch = 40;
int tempo = 500;
int waveform = 0;
int envelope = 0;
int duration = 40;
int mod = 40;

synth bob;

void setup() {
  //bob.begin(CHA);     //CHA (same as default) Audio Out Pin 11
  //bob.begin(CHB);     //CHB Audio Out Pin 3
  bob.begin(DIFF);      //Differential [Pin 11 Speaker/Piezo +]  [Pin 3 Speaker/Piezo -]
  Serial.begin(9600);
  pinMode(pitchPin, INPUT);
  pinMode(tempoPin, INPUT);
  pinMode(waveformPin, INPUT);
  pinMode(envelopePin, INPUT);
  pinMode(durationPin, INPUT);  
  pinMode(modPin, INPUT);
  pinMode(muxPinA, OUTPUT);
  pinMode(muxPinB, OUTPUT);
  pinMode(muxPinC, OUTPUT);
  pinMode(muxInhibitPin, OUTPUT);

  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], duration[0-127], mod[0-127, 64=no mod] )
  bob.setupVoice(0,waveform,pitch,envelope,duration,mod);
  bob.setupVoice(1,waveform,pitch,envelope,duration,mod);
  bob.setupVoice(2,waveform,pitch,envelope,duration,mod);
  bob.setupVoice(3,waveform,pitch,envelope,duration,mod);

}

void loop() {
  for (int step = 0; step < 8; step++){

    digitalWrite(muxInhibitPin, HIGH);
    digitalWrite(muxPinA, bitRead(step, 0));
    digitalWrite(muxPinB, bitRead(step, 1));
    digitalWrite(muxPinC, bitRead(step, 2));
    digitalWrite(muxInhibitPin, LOW);  

    pitch = map(analogRead(pitchPin), 0, 500, 0, 127);

    tempo = map(analogRead(tempoPin), 0, 1023, 0, 1023);
    waveform = map(analogRead(waveformPin), 0, 1023, 0, 6);
    envelope = map(analogRead(envelopePin), 0, 1023, 0, 4);
    duration = map(analogRead(durationPin), 0, 1023, 0, 127);
    mod = map(analogRead(modPin), 0, 1023, 0, 127);

    bob.setupVoice(0,waveform,pitch,envelope,duration,mod);
    bob.setupVoice(1,waveform,pitch * 0.75,envelope,duration,mod);
    bob.setupVoice(2,waveform,pitch * 0.5,envelope,duration,mod);
    bob.setupVoice(3,waveform,pitch * 0.25,envelope,duration,mod);

    bob.trigger(0);
    bob.trigger(1);
    bob.trigger(2);
    bob.trigger(3);

    // Serial.println(bitRead(step, 0));
    // Serial.println(bitRead(step, 1));
    // Serial.println(bitRead(step, 2));
    // Serial.println();
    // Serial.println(analogRead(pitchPin));
    // Serial.println(pitch);
    // Serial.println(tempo);
    // Serial.println(waveform);
    // Serial.println(envelope);
    // Serial.println(duration);
    // Serial.println(mod);
    // Serial.println();

    delay(tempo);

  }

}






