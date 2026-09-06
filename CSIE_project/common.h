#ifndef COMMON_H
#define COMMON_H

typedef struct
{
    pairing_t pairing;
    element_t g;
    element_t W;
    element_t mu;

} SystemParams;

typedef struct
{
    element_t X1;
    element_t S;

} UserPrivateKey;

typedef struct
{
    element_t delta1;
    element_t delta2;
    element_t delta3;
    unsigned char delta4[64];

} Ciphertext;

typedef struct
{
    element_t T;

} Trapdoor;

#endif