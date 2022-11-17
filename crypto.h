

#ifndef LAB1_CRYPTO_H
#define LAB1_CRYPTO_H

#endif //LAB1_CRYPTO_H

struct ShoppingCenter {
    char name[64];
    int freePlaces[20];
};

union ShoppingCenterSerializer{
    struct ShoppingCenter center;
    char binary[sizeof(struct ShoppingCenter)];
};

union ShoppingCenterSerializer encryptData(union ShoppingCenterSerializer*);
union ShoppingCenterSerializer decryptData(union ShoppingCenterSerializer*);