#include <SoftwareSerial.h>
#include "Keyboard.h"

#pragma pack(push, 1)
typedef struct _InputData
{
    byte inputType;
    int16_t data1;
    int16_t data2;
}INPUT_DATA;
#pragma pack(pop)

SoftwareSerial mySerial(10, 11); // RX, TX
void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    Keyboard.begin();
}

void loop()
{
    if (Serial.available() >= sizeof(INPUT_DATA))
    {
        INPUT_DATA data = {0, };
        for(int idx = 0; idx < sizeof(INPUT_DATA); idx++)
        {
            ((byte*)&data)[idx] = Serial.read();
        }

        mySerial.print("type : ");
        mySerial.println(data.inputType);
        mySerial.print("data1 : ");
        mySerial.println(data.data1);
        mySerial.print("data2 : ");
        mySerial.println(data.data2);
        
        //Keyboard.write(inChar + 1);
    }
}
