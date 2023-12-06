/*
Audiobadge

by Paulus
License: GNU GPL v3
*/

#include "stereorecorder.h" //including recorder library, sd, fs and spi libs is already included

#define micL 36 //pin of left channel microphone
#define micR 39 //pin of right channel microphone

int treshhold = 2000; //level of sound when record starting
int recordTime = 5000; //minimum time of recording

void setup(){
    pinMode(micL, INPUT); //initialisation micL as input
    pinMode(micR, INPUT); //initialisation micR as input
    
    Serial.begin(115200); //initialisation of serial
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    writeHeader();
}

void loop(){
    /*micRval = analogRead(micR);
    micLval = analogRead(micL);
    if(treshhold < micRval || treshhold < micLval){
        writeHeader();
        if(treshhold < micRval || treshhold < micLval){
            recordAudio();
            if(treshhold < micRval || treshhold < micLval){
                recordAudio();
            }
            else {
                for(int f = 0; f <= 20; f++){
                    if(treshhold < micRval || treshhold < micLval) {
                        recordAudio();
                    }
                    else {
                        for(int i = 0; i <=220500 ; i++)
                        {
                            recordAudio();
                        }
                    }
                }
            }
        }
    }*/
}
