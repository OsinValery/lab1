#include "limits.h"
#include <stdio.h>
#include "crypto.h"
#include "stdlib.h"

void printInstruction() {
    printf("valid syntax: \n        decrypter <file_path> <digit>\n");
    printf("where:\n    file_path - valid file path for result writing\n digit - how much elements should read\n");
}

void printRecord(struct ShoppingCenter* center) {
    printf("name = %s \n", center->name);
    printf("places = %d", center->freePlaces[0]);
    for (int i = 1;i<20;i++) {
        printf(", %d",center->freePlaces[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printInstruction();
        return 0;
    }

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

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        printf("can't read file");
        return 0;
    }

    char* encryptedContent = (char *) malloc(sizeof(struct ShoppingCenter) * numRecords + 1);

    unsigned int length = 0;
    length = fread(encryptedContent, sizeof(struct ShoppingCenter), numRecords, file);
    union ShoppingCenterSerializer* encryptedRecord = (union ShoppingCenterSerializer*) encryptedContent;

    for (int i = 0; i < length;i++) {
        union ShoppingCenterSerializer record = decryptData(&encryptedRecord[i]);
        printRecord(&record.center);
    }

    printf("end\n");

    fclose(file);
    free(encryptedContent);

    return 0;
}