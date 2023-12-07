/*
Audiobadge

by Paulus
License: GNU GPL v3
*/

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
//#include "symbols.h"
//#include "stereorecorder.h" //including recorder library, sd, fs and spi libs is already included

#define micL 36 //pin of left channel microphone
#define micR 39 //pin of right channel microphone

int micRval = 0;
int micLval = 0;
int micRmid = 0;
int micLmid = 0;
int R1 = 0x52;
int I1 = 0x49;
int F1 = 0x46;
int sizeCharacter1 = 0xff; // one of Size Chunks characters
int W1 = 0x57;
int A1 = 0x41;
int V1 = 0x56;
int E1 = 0x45;
int f1 = 0x66;
int m1 = 0x6d;
int t1 = 0x74;
int space1 = 0x20;
int d1 = 0x64;
int a1 = 0x61;
int nul1 = 0x00;
int subchunk1size1 = 0x10;
int audioFormat1 = 0x01;
int numChannels1 = 0x02;
int sampleRateChar11 = 0x44;
int sampleRateChar21 = 0xac;
int byteRateChar11 = 0x88;
int byteRateChar21 = 0x58;
int byteRateChar31 = 0x01;
int blockAlign1 = 0x02;
int bitsPerSample1 = 0x08;

const char* R = (const char*)R1;
const char* I = (const char*)I1;
const char* F = (const char*)F1;
const char* sizeCharacter = (const char*)sizeCharacter1;
const char* W = (const char*)W1;
const char* A = (const char*)A1;
const char* V = (const char*)V1;
const char* E = (const char*)E1;
const char* f = (const char*)f1;
const char* m = (const char*)m1;
const char* t = (const char*)t1;
const char* space = (const char*)space1;
const char* d = (const char*)d1;
const char* a = (const char*)a1;
const char* nul = (const char*)nul1;
const char* subchunk1size = (const char*)subchunk1size1;
const char* audioFormat = (const char*)audioFormat1;
const char* numChannels = (const char*)numChannels1;
const char* sampleRateChar1 = (const char*)sampleRateChar11;
const char* sampleRateChar2 = (const char*)sampleRateChar21;
const char* byteRateChar1 = (const char*)byteRateChar11;
const char* byteRateChar2 = (const char*)byteRateChar21;
const char* byteRateChar3 = (const char*)byteRateChar31;
const char* blockAlign = (const char*)blockAlign1;
const char* bitsPerSample = (const char*)bitsPerSample1;

int treshhold = 2000; //level of sound when record starting
int recordTime = 5000; //minimum time of recording

int num = 0;

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();

    //basic function for writing files
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();

    //basic function for appending files
}

void writeHeader(){   
    // char buf [6];
    // strcpy(buf, "/");
    String numf = "/" +String(num)+ ".wav";
    const char *indx = numf.c_str();
    // char* indx = 
    // strcat(buf, indx);
    // strcat(buf, ".wav");
    Serial.println("Writing header of:");
    Serial.println("/" + String(num) + ".wav");
    writeFile(SD, indx, R);
    appendFile(SD, indx, I);
    appendFile(SD, indx, F);
    appendFile(SD, indx, F); //chunkId
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter); //chunkSize
    appendFile(SD, indx, W);
    appendFile(SD, indx, A);
    appendFile(SD, indx, V);
    appendFile(SD, indx, E); //format
    appendFile(SD, indx, f);
    appendFile(SD, indx, m);
    appendFile(SD, indx, t);
    appendFile(SD, indx, space); //subchunk1id
    appendFile(SD, indx, subchunk1size);
    appendFile(SD, indx, nul);
    appendFile(SD, indx, nul);
    appendFile(SD, indx, nul); //subchunk1size
    appendFile(SD, indx, audioFormat);
    appendFile(SD, indx, nul); //audioFormat
    appendFile(SD, indx, numChannels);
    appendFile(SD, indx, nul); //numChannels
    appendFile(SD, indx, sampleRateChar1);
    appendFile(SD, indx, sampleRateChar2);
    appendFile(SD, indx, nul);
    appendFile(SD, indx, nul); //sampleRate
    appendFile(SD, indx, byteRateChar1);
    appendFile(SD, indx, byteRateChar2);
    appendFile(SD, indx, byteRateChar3);
    appendFile(SD, indx, nul); //byteRate
    appendFile(SD, indx, blockAlign);
    appendFile(SD, indx, nul); //blockAlign
    appendFile(SD, indx, bitsPerSample);
    appendFile(SD, indx, nul); //bitsPerSample
    appendFile(SD, indx, d);
    appendFile(SD, indx, a);
    appendFile(SD, indx, t);
    appendFile(SD, indx, a); //subchunk2id
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter);
    appendFile(SD, indx, sizeCharacter); //subchunk2size
    num += 1; //plusing 1 to number of file*/

    //basic function for writing wav header
}

void recordAudio(){
    micLval = analogRead(micL); //assigning a value of left microphone to a micLval variable
    int leftLevel = map(micLval, 0, 4095, 0, 255); //changing bit depth from 12 bit to 8 bit
    const char * leftSymbol = (const char *)leftLevel; //changing value of microphone from number format to symbols for writing to file
    micRval = analogRead(micR); //assigning a value of right microphone to a micLval variable
    int rightLevel = map(micRval, 0, 4095, 0, 255); //changing bit depth from 12 bit to 8 bit
    const char * rightSymbol = (const char *)rightLevel; //changing value of microphone from number format to symbols for writing to file
    appendFile(SD, indx, leftSymbol); //writing symbol to file
    appendFile(SD, indx, rightSymbol); //writing symbol to file
    // delayMicroseconds(18); //pause for samling frequency

    //basic function for recording audio data
}

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
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
    writeHeader();
    recordAudio();
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
