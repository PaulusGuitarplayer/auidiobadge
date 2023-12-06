#pragma once
#include <Arduino.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "symbols.h"

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

    //basic functoin for writing files
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
    writeFile(SD, "/" + String(num) + ".wav", R);
    appendFile(SD, "/" + String(num) + ".wav", I);
    appendFile(SD, "/" + String(num) + ".wav", F);
    appendFile(SD, "/" + String(num) + ".wav", F); //chunkId
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter); //chunkSize
    appendFile(SD, "/" + String(num) + ".wav", W);
    appendFile(SD, "/" + String(num) + ".wav", A);
    appendFile(SD, "/" + String(num) + ".wav", V);
    appendFile(SD, "/" + String(num) + ".wav", E); //format
    appendFile(SD, "/" + String(num) + ".wav", f);
    appendFile(SD, "/" + String(num) + ".wav", m);
    appendFile(SD, "/" + String(num) + ".wav", t);
    appendFile(SD, "/" + String(num) + ".wav", space); //subchunk1id
    appendFile(SD, "/" + String(num) + ".wav", subchunk1size);
    appendFile(SD, "/" + String(num) + ".wav", nul);
    appendFile(SD, "/" + String(num) + ".wav", nul);
    appendFile(SD, "/" + String(num) + ".wav", nul); //subchunk1size
    appendFile(SD, "/" + String(num) + ".wav", audioFormat);
    appendFile(SD, "/" + String(num) + ".wav", nul); //audioFormat
    appendFile(SD, "/" + String(num) + ".wav", numChannels);
    appendFile(SD, "/" + String(num) + ".wav", nul); //numChannels
    appendFile(SD, "/" + String(num) + ".wav", sampleRateChar1);
    appendFile(SD, "/" + String(num) + ".wav", sampleRateChar2);
    appendFile(SD, "/" + String(num) + ".wav", nul);
    appendFile(SD, "/" + String(num) + ".wav", nul); //sampleRate
    appendFile(SD, "/" + String(num) + ".wav", byteRateChar1);
    appendFile(SD, "/" + String(num) + ".wav", byteRateChar2);
    appendFile(SD, "/" + String(num) + ".wav", byteRateChar3);
    appendFile(SD, "/" + String(num) + ".wav", nul); //byteRate
    appendFile(SD, "/" + String(num) + ".wav", blockAlign);
    appendFile(SD, "/" + String(num) + ".wav", nul); //blockAlign
    appendFile(SD, "/" + String(num) + ".wav", bitsPerSample);
    appendFile(SD, "/" + String(num) + ".wav", nul); //bitsPerSample
    appendFile(SD, "/" + String(num) + ".wav", d);
    appendFile(SD, "/" + String(num) + ".wav", a);
    appendFile(SD, "/" + String(num) + ".wav", t);
    appendFile(SD, "/" + String(num) + ".wav", a); //subchunk2id
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter);
    appendFile(SD, "/" + String(num) + ".wav", sizeCharacter); //subchunk2size
    num += 1; //plusing 1 to number of file

    //basic function for writing wav header
}

void recordAudio(){
    /*micLval = analogRead(micL); //assigning a value of left microphone to a micLval variable
    int leftLevel = map(micLval, 0, 4095, 0, 255); //changing bit depth from 12 bit to 8 bit
    const char * leftSymbol = (const char *)leftLevel; //changing value of microphone from number format to symbols for writing to file
    micRval = analogRead(micR); //assigning a value of right microphone to a micLval variable
    int rightLevel = map(micRval, 0, 4095, 0, 255); //changing bit depth from 12 bit to 8 bit
    const char * rightSymbol = (const char *)rightLevel; //changing value of microphone from number format to symbols for writing to file
    appendFile(SD, "/" + index + ".wav", leftSymbol); //writing symbol to file
    appendFile(SD, "/" + index + ".wav", rightSymbol); //writing symbol to file
    delayMicroseconds(18); //pause for samling frequency*/

    //basic function for recording audio data
}