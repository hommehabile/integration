#include "Instruction.h"

Instruction::Instruction() {}

Instruction::Instruction(uint8_t opcode, uint8_t operande) {
    opcode_ = opcode;
    operande_ = operande;
}

Instruction::~Instruction() {}

uint8_t Instruction::getOpcode() {
    return opcode_;
}

uint8_t Instruction::getOperande() {
    return operande_;
}

void Instruction::setOpcode(uint8_t nouveauOpcode) {
    opcode_ = nouveauOpcode;
}

void Instruction::setOperande(uint8_t nouvelleOperande) {
    operande_ = nouvelleOperande;
}