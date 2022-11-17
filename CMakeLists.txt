cmake_minimum_required(VERSION 3.23)
project(lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(encryptor encrypter.c crypto.c crypto.h)
add_executable(decrypter decrypter.c crypto.c crypto.h)