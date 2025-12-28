#ifndef _EVENTS_H_
#define _EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

void evVolClick();
void evTempAddChronoClick(int temp);
void evTempPlayClick (int temp);
void evTempStopClick (int temp);
void evTempNewOKClick();
void evEntradaLightChange();
void evEntradaLightClick();
void evEntradaDishClick();
void evRiegoChange();
void evTerrazaRiegoClick();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  // _EVENTS_H_