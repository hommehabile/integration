#include "pwmSon.h"

class Piezo {
public:
    Piezo();
    Piezo(uint8_t frequence);

    ~Piezo();
    
    void debutSon();
    void arretSon();

    void setFrequence(uint8_t note);
private:
    PwmSon onde_;
};
