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
    delayMicroseconds(20);
}