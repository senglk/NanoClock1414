#define A1 9
#define A0 8
#define DATA 7
#define LCLK 5
#define SCLK 4
#define DISPLENGTH 4
#define DATALENGTH 8

void softShiftSerial(uint8_t packet){
    digitalWrite(LCLK, LOW);
    
    for (uint8_t i=0; i<DATALENGTH; i++){
        digitalWrite(SCLK, LOW);
        if ((packet>>i)&0x01){
            digitalWrite(DATA, HIGH);
        } else {
            digitalWrite(DATA, LOW);
        }
        digitalWrite(SCLK, HIGH);
    }
    digitalWrite(LCLK, HIGH);
    digitalWrite(SCLK, LOW);
    digitalWrite(DATA, LOW);
}

//Number of bits to shift
//|W|      D      |
//|7 6 5 4 3 2 1 0|
void writeChar(uint8_t chr, uint8_t loc){
    // swap endianess
    uint8_t digitByte;
    for (uint8_t i=0; i<7; i++){ // i goes up to 6
        if ((chr>>i)&0x01){
            // set bit
            digitByte |= 1<<6-i;
        } else {
            // clr bit
            digitByte &= ~(1<<6-i);
        }
    }
    // select correct digit
    switch (loc%4){
        case 0:
            digitalWrite(A0, LOW);
            digitalWrite(A1, LOW);
            break;
        case 1:
            digitalWrite(A0, HIGH);
            digitalWrite(A1, LOW);
            break;
        case 2:
            digitalWrite(A0, LOW);
            digitalWrite(A1, HIGH);
            break;
        case 3:
            digitalWrite(A0, HIGH);
            digitalWrite(A1, HIGH);
            break;
    }
    
    // set WR to LOW
    uint8_t byteData = 0x00;
    softShiftSerial(byteData);
    
    // set data
    byteData |= digitByte;
    softShiftSerial(byteData);
    
    // set WR
    byteData |= 0x1<<7; // 0x80
    softShiftSerial(byteData);
}

void writeString(char charString[DISPLENGTH+1]){
    for (uint8_t i=0; i<DISPLENGTH; i++){
        writeChar(charString[i], DISPLENGTH-1-i);
    }
}

void setup(){
    pinMode(A1, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(DATA, OUTPUT);
    pinMode(LCLK, OUTPUT);
    pinMode(SCLK, OUTPUT);
    
    Serial.begin(19200);
}

void loop(){
    if (Serial.available() > 0){
        char incomingByte;
        char incomingString[DISPLENGTH+1] = {0};
        static const uint8_t buffSize = DISPLENGTH;
        delay(5); // let the buffer grow first
        uint8_t counter = 0;
        while (Serial.available() > 0){
            incomingByte = Serial.read();
            if (counter < buffSize){
                incomingString[counter] = incomingByte;
                counter+=1;
            }
        }
        writeString(incomingString);
    }
}
