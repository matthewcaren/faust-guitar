#include <Audio.h>
#include "EffectChain.h"

EffectChain effectChain;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;

AudioConnection patchCord0(in,0,effectChain,0);
AudioConnection patchCord1(effectChain, 0, out, 0);
AudioConnection patchCord2(effectChain, 0, out, 1);

// COMPRESSOR : PHASER : ECHO : VERB
int numEffects = 4;
int state = 0;

float paramValue = 0;
float lastParamValue = 0;
float depthValue = 0;
float lastDepthValue = 0;


void setup() {
  Serial.begin(9600);
  AudioMemory(6);
  audioShield.enable();
  audioShield.volume(0.3);
  audioShield.lineInLevel(5);

  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);

  digitalWrite(36, HIGH);
}

void loop() {
  int switchValue = (1024-analogRead(A12)) / (1024/numEffects);
  paramValue = ((1024-analogRead(A14))/16)/64.0;
  depthValue = ((1024-analogRead(A13))/16)/64.0;

  if(state != switchValue) {
    switch(switchValue) {
      case 0:
        digitalWrite(36, HIGH);
        digitalWrite(37, LOW);
        digitalWrite(38, LOW);
        digitalWrite(39, LOW);
        break;
        
      case 1:
        digitalWrite(36, LOW);
        digitalWrite(37, HIGH);
        digitalWrite(38, LOW);
        digitalWrite(39, LOW);
        break;
 
      case 2:
        digitalWrite(36, LOW);
        digitalWrite(37, LOW);
        digitalWrite(38, HIGH);
        digitalWrite(39, LOW);
        break;
 
      case 3:
        digitalWrite(36, LOW);
        digitalWrite(37, LOW);
        digitalWrite(38, LOW);
        digitalWrite(39, HIGH);
        break;
    }

    state = switchValue;
    Serial.print("switch to state ");
    Serial.println(state);
  }  else {

    if (lastParamValue != paramValue) {

      switch(switchValue) {
        case 0:
          effectChain.setParamValue(("compressorParam"),paramValue*19 +1);
          break;
          
        case 1:
        effectChain.setParamValue(("fuzzParam"),paramValue*1.2);
          break;
   
        case 2:
          effectChain.setParamValue(("phaserParam"),paramValue*6.5 +0.4);
          break;
   
        case 3:
          effectChain.setParamValue(("reverbParam"),paramValue*44 +1);
          break;
      }
      
      Serial.println("changing param");
      Serial.println(paramValue);
      lastParamValue = paramValue;

      digitalWrite(35, HIGH);
    } else if (lastDepthValue != depthValue) {
      switch(switchValue) {
        case 0:
          effectChain.setParamValue(("compressorDepth"),depthValue);
          
          break;
          
        case 1:
        effectChain.setParamValue(("fuzzDepth"),depthValue*0.3);
          break;
   
        case 2:
          effectChain.setParamValue(("phaserDepth"),depthValue);
          break;
   
        case 3:
          effectChain.setParamValue(("reverbDepth"),depthValue);
          break;
      }
      
      Serial.println("changing depth");
      Serial.println(depthValue);
      lastDepthValue = depthValue;

      digitalWrite(35, HIGH);
    } else {
      digitalWrite(35, LOW);
    }
  }

  delay(50);
}
