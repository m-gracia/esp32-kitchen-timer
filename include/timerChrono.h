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
    unsigned long timerTime;       // Tiempo de inicio/referencia
    unsigned long timerTimePause;  // Tiempo acumulado cuando se pausa
    unsigned long timerLastCheck;  // Ultima comprobacion de cambio
    char timeBuffer[16];           // Buffer para devolver el texto formateado

public:
    timerChrono();                 // Constructor
    ~timerChrono();                // Destructor

    void start(bool timerMode = TIMER_MODE_TIMER, int minutes = 0); // Start
    void play_pause();
    void stop();
    uint8_t getStatus();
    bool hasChanged();
    bool isOverflow();
    unsigned long getTimeMillis();      
    char* getTimeChar();           // Retorna el tiempo formateado "MM:SS"
};

#endif
