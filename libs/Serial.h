#pragma once
#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

namespace Serial
{
    class SerialUtil
    {
    private:
        //Serial comm handler
        HANDLE m_hSerial;
        //Connection status
        BOOL m_bConnected;
        //Get various information about the connection
        COMSTAT m_Status;
        //Keep track of last error
        DWORD m_dwErrors;

    public:
        SerialUtil();
        //Initialize Serial communication with the given COM port
        SerialUtil(LPCWSTR lpPortName);
        //Close the connection
        virtual ~SerialUtil();

        bool Init(LPCWSTR lpPortName);

        void DisPose();

        //Read data in a buffer, if nbChar is greater than the
        //maximum number of bytes available, it will return only the
        //bytes available. The function return -1 when nothing could
        //be read, the number of bytes actually read.
        int ReadData(BYTE* lpBuffer, UINT nBufSize);
        //Writes data from a buffer through the Serial connection
        //return true on success.
        bool WriteData(BYTE* lpBuffer, UINT nWriteSize);
        //Check if we are actually connected
        bool IsConnected();
    };
}