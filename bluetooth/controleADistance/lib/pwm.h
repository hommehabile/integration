#ifndef PWM_H
#define PWM_H

#include "constantes.h"

enum Port {A1, B1};

class PWM {
public:
    PWM();
    PWM(Port port);

    void initialisation();

    void ajustementPWM(uint8_t poucentage);

    void demarrerPwm();
    void arreterPwm();
private:
    Port port_;
};

#endif