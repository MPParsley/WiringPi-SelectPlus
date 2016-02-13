#define byte uint8_t

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
#include <sys/types.h>

using namespace std;

const byte rfPin = 7;

void SelectPlus(uint32_t address) {
    int pulseWidth = 325; // Pulse width in uS
    byte repeat = 40;     // Repeat send
    uint32_t databit;
    uint32_t mask = 0x10000;
    uint32_t sendbuff;

    for (byte j = 0; j <= repeat; j++) {
        sendbuff = address;
        // send 3 HIGH pulses for syncing
        digitalWrite(rfPin, HIGH);
        delayMicroseconds(pulseWidth * 3);

        // Send command
        for (int i = 0; i < 17; i++) {  // 13+4 bits
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
    // Check if WiringPi is properly installed.
    if (wiringPiSetup () == -1) {
      std::cout << "Please install WiringPi first (http://wiringpi.com/download-and-install/)." << '\n';
      return 1;
    }

    // Check if an argument is present.
    if (argc < 2) {
      std::cout << "Please enter at least one argument: ./Ring white" << '\n' << "You can also use multiple arguments: ./Ring black white black." << '\n';
      return 1;
    }

    // Loop through arguments.
    for (int count=1; count < argc; ++count) {
        if (!strcmp(argv[count], "white")) {
            SelectPlus(0x3BB40); // White
            std::cout << count << " Ding Dong (White) " << '\n';
        } else {
            SelectPlus(0x3C330); // Black
            std::cout << count << " Ding Dong (Black)" << '\n';
        }
        if (count < argc) {
            std::cout << count << " Pause (5s)" << '\n';
            usleep(5000000);
        }
    }
}

/*           ___
'0':     _|   |   (T,3T)
            _
'1':    ___| |     (3T,T)
*/
