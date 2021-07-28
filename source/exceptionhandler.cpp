#include "exceptionhandler.hpp"

const u32 exceptionStackSize = 0x10000;
u8 exceptionStack[exceptionStackSize];
nn::os::UserExceptionInfo exceptionInfo;

const char* explanation_for_exception_type(u32 exceptionType)
{
    switch (exceptionType)
    {
        case 0x101: return "Invalid data access";
        case 0x102: return "Unaligned instruction access";
        case 0x103: return "Unaligned data access";
        case 0x104: return "Invalid instruction";
        case 0x105: return "Execution of exception instruction";
        case 0x106: return "Memory system error";
        case 0x200: return "Floating point unit exception";
        case 0x301: return "Invalid SVC";
        default:    return "Unknown";
    }
}

const char* name_for_register(u32 id)
{
    switch (id)
    {
        case 0:     return "r0";
        case 1:     return "r1";
        case 2:     return "r2";
        case 3:     return "r3";
        case 4:     return "r4";
        case 5:     return "r5";
        case 6:     return "r6";
        case 7:     return "r7";
        case 8:     return "r8";
        case 9:     return "r9";
        case 10:    return "r10";
        case 11:    return "r11";
        case 12:    return "r12";
        case 13:    return "sp";
        case 14:    return "lr";
        case 15:    return "pc";
        default:    return "invalid";
    }
}


extern "C" void svcBreak(u32 breakpointId, u32 flags, u32 value);
extern u32 got_main_crt0;
extern u32* __start__;

void exception_handler(nn::os::UserExceptionInfo* exceptionInfo)
{
    LOG("-------------------------------------\n");
    LOG("Exception occured on core %d\n\n", nn::os::GetCurrentCoreNumber());

    LOG("Type: %s (0x%04X)\n\n", explanation_for_exception_type(exceptionInfo->type), exceptionInfo->type);

    LOG("Registers:\n");
    for (u32 i = 0; i < 16; i++)
        LOG(" %-3s 0x%08X\n", name_for_register(i), exceptionInfo->r[i]);
    LOG("\n");


    uintptr_t stackTop;
    uintptr_t stackBottom;
    u32 stackSize;

    nn::os::FiberType* fiber = nn::os::GetCurrentFiber();
    if (fiber)
    {
        stackTop = reinterpret_cast<uintptr_t>(fiber->stack);
        stackSize = fiber->stackSize;
        LOG("Fiber:         0x%P\n", fiber);
    }
    else
    {
        nn::os::ThreadType* thread = nn::os::GetCurrentThread();

        stackTop = reinterpret_cast<uintptr_t>(thread->stack);
        stackSize = thread->stackSize;

        const char* threadName = nn::os::GetThreadNamePointer(thread);

        if (threadName)
            LOG("Thread:        0x%P (%s)\n", thread, threadName);
        else
            LOG("Thread:        0x%P\n", thread);
    }
    stackBottom = stackTop + stackSize;

    LOG(" Stack Top:    0x%P\n", stackTop);
    LOG(" Stack Bottom: 0x%P\n", stackBottom);
    LOG(" Stack Size:   0x%08X\n", stackSize);
    LOG("\n");

    LOG("Stack dump:\n");
    {
        uintptr_t dumpStart = exceptionInfo->sp & ~0xF;
        if (dumpStart < stackTop)
            dumpStart = stackTop;

        uintptr_t dumpEnd = dumpStart + 0x100;
        if (dumpEnd > stackBottom)
            dumpEnd = stackBottom;

        for (uintptr_t i = dumpStart; i < dumpEnd; i++)
        {
            if (!(i & 0xF))
                LOG(" 0x%P  ", i);

            if (i >= exceptionInfo->sp)
                LOG("%02X ", *reinterpret_cast<u8*>(i));
            else
                LOG("   ");

            if ((i & 3) == 3)
                LOG(" ");

            if ((i & 0xF) == 0xF)
            {
                for (s32 j = -0xF; j <= 0; j++)
                {
                    if ((i + j) >= exceptionInfo->sp)
                    {
                        char c = *reinterpret_cast<char*>(i + j);
                        if ((c < 32) || (c > 126))
                            c = '.';
                        LOG("%c", c);
                    }
                    else
                        LOG(" ");
                }
                LOG("\n");
            }
        }
    }
    LOG("\n");

    LOG("Modules:\n");
    LOG(" main    0x%08X\n", got_main_crt0);
    LOG(" subsdk0 0x%08X\n", &__start__);
    LOG("\n");

    svcBreak(0, 0, 0);
    while (true) { }
}

void exception_handler_initialize()
{
    nn::os::SetUserExceptionHandler(&exception_handler, exceptionStack, exceptionStackSize, &exceptionInfo);
}