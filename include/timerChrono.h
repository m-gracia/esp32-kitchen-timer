#ifndef TIMER_CHRONO_H
#define TIMER_CHRONO_H

#include <Arduino.h>

// Timer status
#define STATUS_TIMER_OFF 0          // Stopped
#define STATUS_TIMER_ON 1           // Timer Running
#define STATUS_TIMER_PAUSE 2        // Timer Paused
#define STATUS_TIMER_CHRONO 8       // Chronometer on
#define STATUS_TIMER_CHRONOPAUSE 9  // Chronometer paused

//Timer mode
#define TIMER_MODE_TIMER 0          // Timer
#define TIMER_MODE_CHRONO 1         // Chronometer

class timerChrono {
private:
    uint8_t timerStatus;
    unsigned long timerTime;       // Start/reference time
    unsigned long timerTimePause;  // Time when is paused
    unsigned long timerLastCheck;  // Last change check
    char timeBuffer[16];           // Timer Buffer

public:
    timerChrono();                 // Constructor
    ~timerChrono();                // Destructor

    void start(bool timerMode = TIMER_MODE_TIMER, int minutes = 0); // Start
    void play_pause();      // Play/Pause timer
    void stop();            // Stop timer
    uint8_t getStatus();    // Return timer status STATUS_TIMER_XXXX
    bool hasChanged();      // Return true if timer has changed
    bool isOverflow();      // Return true if timer is overflowed
    unsigned long getTimeMillis();  // Returns timer time in milliseconds
    char* getTimeChar();           // Returns timer time formatted "MM:SS"
};

#endif
