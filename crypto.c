#include "crypto.h"

char encryptByte(char data) {
    return (char)(~data);
}


void encryptBuffer(const char input[], char output[], int length, char (function)(char)) {
    for (int i = 0; i < length; i ++) {
        if (i != length - 1) {
            output[i] = function(input[i]);
        } else {
            output[i] = input[i];
        }

    }
}


union ShoppingCenterSerializer encryptData(union ShoppingCenterSerializer* data) {
    union ShoppingCenterSerializer result;

    char* in = data->binary;
    char* out = result.binary;
    encryptBuffer(in,out,sizeof(struct ShoppingCenter),encryptByte);
    return result;
}

union ShoppingCenterSerializer decryptData(union ShoppingCenterSerializer* data) {
    return encryptData(data);
}