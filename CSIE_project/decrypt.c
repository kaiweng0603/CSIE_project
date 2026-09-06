#include <pbc/pbc.h>
#include "common.h"
#include "hash.h"

int decrypt (SystemParams *param, UserPrivateKey *key, Ciphertext *cipher, char M[32]) {

    // temp1 = e(X1, delta1) 

    element_t temp1;
    element_init_GT(temp1, param->pairing);

    pairing_apply(temp1, key->X1, cipher->delta1, param->pairing);

    // temp2 = delta3 / (g ^ X2)

    element_t g_pow_X2;
    element_init_G1(g_pow_X2, param->pairing);

    element_pow_zn(g_pow_X2, param->g, key->S); // X2 = S

    element_t temp2;
    element_init_G1(temp2, param->pairing);

    element_div(temp2, cipher->delta3, g_pow_X2);

    // M || h0(M) = delta4 xor h3(temp1, delta1, delta2, temp2) 

    unsigned char h3[64];

    hash_h3(temp1, cipher->delta1, cipher->delta2, temp2, h3);

    for (int i = 0; i < 32; i++) {
        M[i] = cipher->delta4[i] ^ h3[i];
    }

    return 0;   // 回傳0，代表正常。
}