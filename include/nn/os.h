#pragma once

#include "types.h"

namespace nn { namespace os {

struct ThreadType
{
    u8 _0[0x20-0x0];    // 0
    u8 state;           // 20
    u8 _21;             // 21
    u8 _22;             // 22
    u8 _23;             // 23
    s32 priority;       // 24
    void* initialStack; // 28
    void* stack;        // 2C
    u32 stackSize;      // 30
    void* argument;     // 34
    void* function;     // 38
    u32 _3C[0xC8-0x3C]; // 3C
    char name[0x20];    // C8
    char* namePtr;      // E8
    // Incomplete
};

struct FiberType
{
    u8 _0[0x10-0x0];        // 0
    u8 state;               // 10
    u8 _11;                 // 11
    void* function;         // 14
    void* argument;         // 18
    void* initialStack;     // 1C
    void* stack;            // 20
    u32 stackSize;          // 24
    u32 _28;                // 28
};

struct MemoryInfo
{
    u64 availableMemorySize;
    u32 usedMemorySize;
    u32 heapSize;
    u32 heapUsedSize;
    u32 executableSize;
    u32 threadsStackSize;
    u32 threadCount;
};

struct UserExceptionInfo
{
    u32 type;           // 0
    u8 _4[0xC];         // 4

    union
    {
        u32 r[16];      // 10

        struct
        {
            u32 r0;     // 10
            u32 r1;     // 14
            u32 r2;     // 18
            u32 r3;     // 1C
            u32 r4;     // 20
            u32 r5;     // 24
            u32 r6;     // 28
            u32 r7;     // 2C
            u32 r8;     // 30
            u32 r9;     // 34
            u32 r10;    // 38
            u32 r11;    // 3C
            u32 r12;    // 40
            u32 sp;     // 44
            u32 lr;     // 48
            u32 pc;     // 4C
        };
    };

    u32 unk[0x1000];    // Unknown size: Todo
};

// MUTEX
struct MutexType
{
    u8 curState; // _0
    bool isRecursiveMutex; // _1
    s32 lockLevel; // _2
    u8 _6[0x20-0x6];
};

typedef void (*UserExceptionHandler)(UserExceptionInfo* exceptionInfo);

ThreadType* GetCurrentThread();
const char* GetThreadNamePointer(const ThreadType* thread);

FiberType* GetCurrentFiber();

void SetUserExceptionHandler(UserExceptionHandler handler, void* stack, u32 stackSize, UserExceptionInfo* exceptionInfo);
void QueryMemoryInfo(MemoryInfo* memoryInfo);
void GetCurrentStackInfo(u32* outStackAddress, u32* outStackSize);
s32 GetCurrentCoreNumber();

} }
