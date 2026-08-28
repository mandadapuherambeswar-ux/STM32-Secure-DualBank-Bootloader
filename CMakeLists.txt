cmake_minimum_required(VERSION 3.20)
project(STM32_Secure_DualBank_Bootloader C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(bootloader_sim ${SOURCES})
target_compile_options(bootloader_sim PRIVATE -Wall -Wextra -O2)
