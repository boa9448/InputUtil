#include <SoftwareSerial.h>
#include <Keyboard.h>
#include <Mouse.h>

enum class ButtonType
{
  LEFT_BUTTON_DOWN
  , LEFT_BUTTON_UP
  , RIGHT_BUTTON_DOWN
  , RIGHT_BUTTON_UP
};

enum class MoveType
{
  MOVE_ABSOLUTE
  , MOVE_RELATIVE
};

enum class WheelType
{
  WHEEL_DOWN
  , WHELL_UP
};

enum class KeyType
{
  KEY_DOWN
  , KEY_UP
  , KEY_PRESS
};

enum class InputDataType
{
  KEY
  , MOUSE
  , BUTTON
  , WHEEL
};

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
    Mouse.begin();
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

        /*mySerial.print("type : ");
        mySerial.println(data.inputType);
        mySerial.print("data1 : ");
        mySerial.println(data.data1);
        mySerial.print("data2 : ");
        mySerial.println(data.data2);*/

        if(data.inputType == (byte)InputDataType::KEY)
        {
            if(data.data1 == (int16_t)KeyType::KEY_DOWN) Keyboard.write(data.data2);
            else if(data.data1 == (int16_t)KeyType::KEY_UP) Keyboard.release(data.data2);
            else if(data.data1 == (int16_t)KeyType::KEY_PRESS) Keyboard.press(data.data2);
        }
        else if(data.inputType == (byte)InputDataType::MOUSE)
        {
            Mouse.move(data.data1, data.data2, 0);
        }
        else if(data.inputType == (byte)InputDataType::BUTTON)
        {
            // 다듬어야 하는 코드 블럭
            if(data.data1 == (int16_t)ButtonType::LEFT_BUTTON_DOWN)
            {
                Mouse.press(MOUSE_LEFT);
            }
            else if(data.data1 == (int16_t)ButtonType::RIGHT_BUTTON_DOWN)
            {
                Mouse.press(MOUSE_RIGHT);
            }
            else if(data.data1 == (int16_t)ButtonType::LEFT_BUTTON_UP)
            {
                Mouse.release(MOUSE_LEFT);
            }
            else if(data.data1 == (int16_t)ButtonType::RIGHT_BUTTON_UP)
            {
                Mouse.release(MOUSE_RIGHT);
            }
        }
        else if(data.inputType == (byte)InputDataType::WHEEL)
        {
            unsigned char way = data.data1 == (int16_t)WheelType::WHEEL_DOWN ? data.data2 : data.data2 * -1;
            Mouse.move(0, 0, way);
        }
    }
}
