#define byte uint8_t

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <iostream>
#include <sys/types.h>

using namespace std;

const byte rfPin=7;

void SelectPlus(uint32_t address) {
    int pulseWidth = 325;// Pulse breedte in uS
    byte repeat = 16;   //  repeat send
    uint32_t databit;
    uint32_t mask = 0x10000;
    uint32_t sendbuff;

    for (byte j = 0; j <= repeat; j++) {
        sendbuff=address;
        // send 3 HIGH pulses for syncing
        digitalWrite(rfPin, HIGH);
        delayMicroseconds(pulseWidth * 3);

        // Send command
        for (int i = 0; i < 17;i++) {  // 13+4 bits
            databit = sendbuff & mask; // Get most left bit
            sendbuff = (sendbuff << 1);// Shift left

            if (databit != mask) {                 // Write 0
                digitalWrite(rfPin, LOW);
                delayMicroseconds(pulseWidth);
                digitalWrite(rfPin, HIGH);
                delayMicroseconds(pulseWidth * 3);
            } else {                               // Write 1
                digitalWrite(rfPin, LOW);
                delayMicroseconds(pulseWidth * 3);
                digitalWrite(rfPin, HIGH);
                delayMicroseconds(pulseWidth);
            }
        }
        digitalWrite(rfPin, LOW);
        delayMicroseconds(pulseWidth * 16);
    }
}

int main(int argc, char* argv[])
{
  if (wiringPiSetup () == -1)
    return 1;

   SelectPlus(0x1BB40);// White
//   SelectPlus(0x1C330);// Black
   char str[] = "Dong";
   cout << "Ding : " << str << endl;
}

/*           ___
'0':     _|   |   (T,3T)
            _
'1':    ___| |     (3T,T)
*/
