#pragma once
#include <spdlog/spdlog.h>

namespace STATUS{

void PrintLogVersion(void) {
    spdlog::info("Welcome to the spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
};

void SayHello(void) {
    spdlog::info("Hello World, this is the STATUS module!");
};

}