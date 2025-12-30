#include "timerChrono.h"

timerChrono::timerChrono() {
    stop();
}

timerChrono::~timerChrono() {
    // Destructor
}

void timerChrono::start(bool timerMode, int minutes){
    if (timerMode == TIMER_MODE_TIMER) {
        timerTime = millis() + (minutes * 60 * 1000);
        timerStatus = STATUS_TIMER_ON;
    } else { // TIMER_MODE_CHRONO
        timerTime = millis();
        timerStatus = STATUS_TIMER_CHRONO;
    }
    timerLastCheck = millis();
}

void timerChrono::play_pause() {
    switch (timerStatus){
        case STATUS_TIMER_ON:
            timerStatus = STATUS_TIMER_PAUSE;
            timerTimePause = millis();
            break;

        case STATUS_TIMER_CHRONO:
            timerStatus = STATUS_TIMER_CHRONOPAUSE;
            timerTimePause = millis();
            break;

        case STATUS_TIMER_PAUSE:
            timerStatus = STATUS_TIMER_ON;
            timerTime += (millis() - timerTimePause);
            break;

        case STATUS_TIMER_CHRONOPAUSE:
            timerStatus = STATUS_TIMER_CHRONO;
            timerTime += (millis() - timerTimePause);
            break;

        default:
            break;
    }
}

void timerChrono::stop() {
    timerStatus = STATUS_TIMER_OFF;
    timerTime = 0;
    timerTimePause = 0;
    timerLastCheck = 0;
}

uint8_t timerChrono::getStatus() {
    return timerStatus;
}

bool timerChrono::hasChanged() {
    if ((timerStatus ==  STATUS_TIMER_CHRONO || timerStatus == STATUS_TIMER_ON)
        && (millis() > (timerLastCheck + 1000))
    ){
        timerLastCheck = millis();
        return true;
    } else {
        return false;
    }
}

bool timerChrono::isOverflow(){
    if (timerStatus == STATUS_TIMER_ON) {
        return (timerTime < millis());
    } else if (timerStatus == STATUS_TIMER_PAUSE) {
        return (timerTime < timerTimePause);
    } else {
        return false;   // Do not overflow on chrono mode
    }    
}

unsigned long timerChrono::getTimeMillis(){
    unsigned long totalMillis = 0;

    switch (timerStatus){
        case STATUS_TIMER_ON:       // Return time left until timerTime
            if (!isOverflow()) totalMillis = timerTime - millis();
            else totalMillis = millis() - timerTime;
            break;

        case STATUS_TIMER_CHRONO:   // Return time since started
            totalMillis = millis() - timerTime;
            break;

        case STATUS_TIMER_PAUSE:    // Return time left until timerTime since paused
            if (!isOverflow()) totalMillis = timerTime - timerTimePause;
            else totalMillis = timerTimePause - timerTime;
            break;

        case STATUS_TIMER_CHRONOPAUSE:  // Return time since start to paused
            totalMillis = timerTimePause - timerTime;
            break;

        default: totalMillis=0;
            break;
    }

    return totalMillis;
}

char* timerChrono::getTimeChar() {
    unsigned long totalMillis = getTimeMillis();

    // Extract minutes and seconds
    unsigned long totalSeconds = totalMillis / 1000;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    // Format string
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d", minutes, seconds);
    return timeBuffer; 
}
