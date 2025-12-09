#include "IntCodeCPU.h"

#include <cmath>

IntCodeCPU::IntCodeCPU(std::vector<std::int64_t> program) {
    memory = program;
    halted = false;
    awaitingInput = true;
    outputReady = false;
    ip = 0;
    relativeBase = 0;
}

inline void IntCodeCPU::Tick() {
    if (halted) { return; }

    std::int64_t opcode = memory[ip] % 100;
    std::int64_t memoryModes = memory[ip] / 100;

    // Increment IP prior to processing opcodes so that parameters are 0-indexed
    ip++;

    switch (opcode) {
    case 1: // ADD
        Op_Add(memoryModes);
        break;
    case 2: // MUL
        Op_Multiply(memoryModes);
        break;
    case 3: // IN
        Op_Input(memoryModes);
        break;
    case 4: // OUT
        Op_Output(memoryModes);
        break;
    case 5: // JNZ
        Op_JumpIfNotZero(memoryModes);
        break;
    case 6: // JEZ
        Op_JumpIfZero(memoryModes);
        break;
    case 7: // LT
        Op_LessThan(memoryModes);
        break;
    case 8: // EQ
        Op_EqualTo(memoryModes);
        break;
    case 9: // MRB
        Op_ModifyRelativeBase(memoryModes);
        break;
    case 99:
        Op_Halt(memoryModes);
        break;
    }
}

void IntCodeCPU::RunToEnd() {
    while (!halted) { Tick(); }
}

void IntCodeCPU::RunToInput() {
    while (!awaitingInput && !halted) { Tick(); }
}

void IntCodeCPU::RunToOutput() {
    while (!outputReady && !halted) { Tick(); }
}

void IntCodeCPU::RunToIO() {
    while (!awaitingInput && !outputReady && !halted) { Tick(); }
}

void IntCodeCPU::Input(std::int64_t input) {
    this->input = input;
    awaitingInput = false;
}

std::int64_t IntCodeCPU::Output() {
    outputReady = false;
    return output;
}

inline std::int64_t IntCodeCPU::LoadParam(std::int64_t memoryModes, std::int64_t paramNumber) {
    std::int64_t addressMode = memoryModes / (std::int64_t)std::pow(10, paramNumber) % 10;
    return addressMode == 0 ? MemoryRead(MemoryRead(ip + paramNumber))
        : addressMode == 1 ? MemoryRead(ip + paramNumber)
        : MemoryRead(relativeBase + MemoryRead(ip + paramNumber));
}

inline std::int64_t IntCodeCPU::LoadAddressParam(std::int64_t memoryModes, std::int64_t paramNumber) {
    std::int64_t addressMode = memoryModes / (std::int64_t)std::pow(10, paramNumber) % 10;
    return addressMode == 0 ? MemoryRead(ip + paramNumber) : relativeBase + MemoryRead(ip + paramNumber);
}

inline std::int64_t IntCodeCPU::MemoryRead(std::int64_t address) {
    if (address < memory.size()) {
        return memory[(unsigned int)address];
    }
    return 0;
}

inline void IntCodeCPU::MemoryWrite(std::int64_t address, std::int64_t value) {
    if (memory.size() <= address) {
        memory.resize(address + 1);
    }
    memory[(unsigned int)address] = value;
}

inline void IntCodeCPU::Op_Add(int64_t memoryModes) {
    MemoryWrite(LoadAddressParam(memoryModes, 2), LoadParam(memoryModes, 0) + LoadParam(memoryModes, 1));
    ip += 3;
}

inline void IntCodeCPU::Op_Multiply(int64_t memoryModes) {
    MemoryWrite(LoadAddressParam(memoryModes, 2), LoadParam(memoryModes, 0) * LoadParam(memoryModes, 1));
    ip += 3;
}

inline void IntCodeCPU::Op_Input(int64_t memoryModes) {
    MemoryWrite(LoadAddressParam(memoryModes, 0), input);
    awaitingInput = true;
    ip += 1;
}

inline void IntCodeCPU::Op_Output(int64_t memoryModes) {
    output = LoadParam(memoryModes, 0);
    outputReady = true;
    ip += 1;
}

inline void IntCodeCPU::Op_JumpIfNotZero(int64_t memoryModes) {
    ip = LoadParam(memoryModes, 0) != 0 ? (unsigned int)LoadParam(memoryModes, 1) : ip + 2;
}

inline void IntCodeCPU::Op_JumpIfZero(int64_t memoryModes) {
    ip = LoadParam(memoryModes, 0) == 0 ? (unsigned int)LoadParam(memoryModes, 1) : ip + 2;
}

inline void IntCodeCPU::Op_LessThan(int64_t memoryModes) {
    MemoryWrite(LoadAddressParam(memoryModes, 2), LoadParam(memoryModes, 0) < LoadParam(memoryModes, 1) ? 1 : 0);
    ip += 3;
}

inline void IntCodeCPU::Op_EqualTo(int64_t memoryModes) {
    MemoryWrite(LoadAddressParam(memoryModes, 2), LoadParam(memoryModes, 0) == LoadParam(memoryModes, 1) ? 1 : 0);
    ip += 3;
}

inline void IntCodeCPU::Op_ModifyRelativeBase(int64_t memoryModes) {
    relativeBase += LoadParam(memoryModes, 0);
    ip += 1;
}

inline void IntCodeCPU::Op_Halt(int64_t memoryModes) {
    halted = true;
}