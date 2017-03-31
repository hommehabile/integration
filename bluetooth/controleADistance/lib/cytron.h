ENUM = {DECT1, DECT2, DECT3, DECT4, DECT5}

class Cytron {
public:
    Cytron();
    Cytron(int DLS);

    ~Cytron();
    
    void debutDetection();
    void arretDetection();
 
    void Initialisation();

    int getPin(int DECT);

    bool Detection(int DECT);
private:
    int DECT_;
};
