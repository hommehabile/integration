#ifndef pwmSon_h
#define pwmSon_h

#include "constantes.h"

using namespace  std;

class PwmSon {
    
public:
    PwmSon();
    PwmSon(uint8_t ratio);
    ~PwmSon();
    
    void modifierRatio(uint8_t ratio);
    
    void debutPwm();
    void arretPwm();
    
private:
    void init();
};

#endif
