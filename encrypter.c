#include <stdio.h>
#include "stdlib.h"
#include "limits.h"
#include "crypto.h"
#include "string.h"

void printInstruction() {
    printf("valid syntax: \n        encryptor <file_path> <digit>\n");
    printf("where:\n    file_path - valid file path for result writing\n   digit - how much addresses you would enter.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printInstruction();
        return 0;
    }
    char * filePath = argv[1];

    char* unused;
    long int numRecords = strtol(argv[2], &unused, 0);

    if (numRecords <= 0) {
        printf("You entered bad digit");
        printInstruction();
        return 0;
    } else if (numRecords == LONG_MAX) {
        printf("You entered too huge digit");
        printInstruction();
        return 0;
    }

    union ShoppingCenterSerializer* encryptedSymbols = (union ShoppingCenterSerializer*)malloc(numRecords);
    int bufferIndex = 0;

    for (int i = 0; i < numRecords;i++) {
        char name[64] = "";
        struct ShoppingCenter center;

        printf("enter name of center(no more than 64 symbols without spaces)\n>>>");
        scanf("%s", name);
        strcpy(center.name, name);
        printf("enter digits (20):");
        long int place = 0;
        char placeStr[10];
        int pos = 0;
        while (pos < 20) {
            scanf("%s", placeStr);
            place = strtol(placeStr, &unused, 0);
            if ((place <= 0) || (place == LONG_MAX)) {
                printf("You entered invalid digit: %s \n", placeStr);
            } else {
                center.freePlaces[pos] = (signed)place;
                pos += 1;
            }
        }

        union ShoppingCenterSerializer serializer;
        serializer.center = center;
        union ShoppingCenterSerializer encryptedRecord = encryptData(&serializer);
        encryptedSymbols[bufferIndex] = encryptedRecord;
        bufferIndex += 1;
    }

    char* encryptedData = (char*) encryptedSymbols;
    unsigned int length = sizeof(struct ShoppingCenter) * numRecords;

    FILE* file = fopen(filePath, "wb");
    if (!file) {
        free(encryptedSymbols);
        printf("can't open file");
        return 0;
    }
    fwrite(encryptedData, length, 1, file);

    fclose(file);
    free(encryptedSymbols);
    return 0;
}
