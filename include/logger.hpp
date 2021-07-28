#pragma once

#include <string>
#include <cstring>
#include "types.h"
#include "nn.h"
#include "log.h"


void socket_log(const char* str);

s32 socket_read_char(char *out);

void socket_log_initialize();

void tryInitSocket();