/*
Audiobadge

by Paulus
License: GNU GPL v3
*/

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "symbols.h"

#define micL 36
#define micR 39

int treshhold = 2000;
int soundlvl = 0;

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
}

void writeHeader(){
    writeFile(SD, "/" + index + ".wav", R + I + F + F); //chunkId
    appendFile(SD, "/" + index + ".wav", sizeCharacter + sizeCharacter + sizeCharacter + sizeCharacter); //chunkSize
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
    indx += 1;
}

void recordAudio(){
    micLval = analogRead(micL);
    int leftLevel = map(micLval, 0, 4095, 0, 255);
    const char * leftSymbol = (const char *)leftLevel;
    micRval = analogRead(micR);
    int rightLevel = map(micRval, 0, 4095, 0, 255);
    const char * rightSymbol = (const char *)rightLevel;
    appendFile(SD, "/" + index + ".wav", leftSymbol);
    appendFile(SD, "/" + index + ".wav", rightSymbol);
    //delayMicroseconds(20);
}

void setup(){
    pinMode(micL, INPUT);
    pinMode(micR, INPUT);
    
    Serial.begin(115200);
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
}

void loop(){
    micRval = analogRead(micR);
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
                        while (millis() < 5000)
                        {
                        recordAudio();
                        }
                    }
                }
            }
        }
    }
}
