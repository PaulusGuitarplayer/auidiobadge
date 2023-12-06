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
    writeFile(SD, (const char*)index, R); //chunkId
    /*appendFile(SD, "/" + index + ".wav", sizeCharacter + sizeCharacter + sizeCharacter + sizeCharacter); //chunkSize
    appendFile(SD, "/" + index + ".wav", W + A + V + E); //format
    appendFile(SD, "/" + index + ".wav", f + m + t + space); //subchunk1id
    appendFile(SD, "/" + index + ".wav", subchunk1size + nul + nul + nul); //subchunk1size
    appendFile(SD, "/" + index + ".wav", audioFormat + nul); //audioFormat
    appendFile(SD, "/" + index + ".wav", numChannels + nul); //numChannels
    appendFile(SD, "/" + index + ".wav", sampleRateChar1 + sampleRateChar2 + nul + nul); //sampleRate
    appendFile(SD, "/" + index + ".wav", byteRateChar1 + byteRateChar2 + byteRateChar3 + nul); //byteRate
    appendFile(SD, "/" + index + ".wav", blockAlign + nul); //blockAlign
    appendFile(SD, "/" + index + ".wav", bitsPerSample + nul); //bitsPerSample
    appendFile(SD, "/" + index + ".wav", d + a + t + a); //subchunk2id
    appendFile(SD, "/" + index + ".wav", sizeCharacter + sizeCharacter + sizeCharacter + sizeCharacter); //subchunk2size
    index += 1; //plusing 1 to number of file*/

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