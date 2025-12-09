#pragma once
#include <cstdint>
#include <vector>

class IntCodeCPU {
private:
    std::int64_t input;
    std::int64_t output;
    std::int64_t relativeBase;

public:
    std::vector<std::int64_t> memory;
    bool halted;
    unsigned int ip;
    bool awaitingInput;
    bool outputReady;

    IntCodeCPU(std::vector<std::int64_t> program);

private:
    inline void Tick();

public:
    // Run Modes
    void RunToEnd();
    void RunToInput();
    void RunToOutput();
    void RunToIO();

    // I/O
    void Input(std::int64_t input);
    std::int64_t Output();

private:
    // Memory Manipulation
    inline std::int64_t MemoryRead(std::int64_t address);
    inline void MemoryWrite(std::int64_t address, std::int64_t value);
    inline std::int64_t LoadParam(std::int64_t memoryModes, std::int64_t paramNumber);
    inline std::int64_t LoadAddressParam(std::int64_t memoryModes, std::int64_t paramNumber);

    // Opcodes
    inline void Op_Add(int64_t memoryModes);
    inline void Op_Multiply(int64_t memoryModes);
    inline void Op_Input(int64_t memoryModes);
    inline void Op_Output(int64_t memoryModes);
    inline void Op_JumpIfNotZero(int64_t memoryModes);
    inline void Op_JumpIfZero(int64_t memoryModes);
    inline void Op_LessThan(int64_t memoryModes);
    inline void Op_EqualTo(int64_t memoryModes);
    inline void Op_ModifyRelativeBase(int64_t memoryModes);
    inline void Op_Halt(int64_t memoryModes);
};