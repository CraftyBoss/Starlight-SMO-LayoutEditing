#include <cstdlib>
#include <cstring>
#include <string>
#include "types.h"
#include "nn.h"
#include "log.h"

const char* explanation_for_exception_type(u32 exceptionType);

const char* name_for_register(u32 id);

void exception_handler(nn::os::UserExceptionInfo* exceptionInfo);

void exception_handler_initialize();