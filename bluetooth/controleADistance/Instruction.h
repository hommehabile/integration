#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <avr/io.h>

class Instruction {
public :
    Instruction();
    Instruction(uint8_t opcode, uint8_t operande);
    ~Instruction();
    uint8_t getOpcode();
    uint8_t getOperande();
    void setOpcode(uint8_t nouveauOpcode);
    void setOperande(uint8_t nouvelleOperande);
private:
    uint8_t opcode_;
    uint8_t operande_;
};

#endif
