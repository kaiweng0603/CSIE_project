#include <pbc/pbc.h>
#include <string.h>
#include "common.h"
#include "hash.h"

int encrypt (SystemParams *param, const unsigned char M[32], element_t Q, const char *id, UserPrivateKey *key, Ciphertext *cipher) {

    //========= delta1 = g^c ==========
    //========= delta2 = g^t ==========

    element_t c, t;

    element_init_Zr(c, param->pairing);
    element_init_Zr(t, param->pairing);

    element_random(c);
    element_random(t);

    element_init_G1(cipher->delta1, param->pairing);
    element_init_G1(cipher->delta2, param->pairing);

    element_pow_zn(cipher->delta1, param->g, c);
    element_pow_zn(cipher->delta2, param->g, t);

    //====== delta3 = Q^t · g^S =======

    element_t Q_pow_t;

    element_init_G1(Q_pow_t, param->pairing);

    element_pow_zn(Q_pow_t, Q, t);

    element_t g_pow_S;

    element_init_G1(g_pow_S, param->pairing);

    element_pow_zn(g_pow_S, param->g, key->S);

    element_init_G1(cipher->delta3, param->pairing);

    element_mul(cipher->delta3, Q_pow_t, g_pow_S);
    
    // temp1 = h1(ID||S) · h2​(ID) 

    element_t h1;

    element_init_G1(h1, param->pairing);

    hash_h1(h1, id, key->S);

    element_t h2, temp1;

    element_init_G1(h2, param->pairing);
    element_init_G1(temp1, param->pairing);

    hash_h2(h2, id);

    element_mul(temp1, h1, h2);

    // temp2 = temp1 ^ c

    element_t temp2;

    element_init_G1(temp2, param->pairing);

    element_pow_zn(temp2, temp1, c);

    // temp3 = e(W, temp2)

    element_t temp3;

    element_init_GT(temp3, param->pairing);

    pairing_apply(temp3, param->W, temp2, param->pairing);

    // h3(temp3, delta1, delta2, Q ^ t)

    unsigned char h3[64];

    hash_h3(temp3, cipher->delta1, cipher->delta2, Q_pow_t, h3);

    // delta4 = (M || h0(M)) xor h3(temp3, delta1, delta2, Q ^ t)

    unsigned char Mh0M[64];

    for (int i = 0; i < 32; i++) {
        Mh0M[i] = M[i];
    }

    hash_h0(M, &Mh0M[32]);

    for (int i = 0; i < 64; i++) {
        cipher->delta4[i] = Mh0M[i] ^ h3[i];
    }

    element_clear(c);
    element_clear(t);
    element_clear(Q_pow_t);
    element_clear(g_pow_S);
    element_clear(h1);
    element_clear(h2);
    element_clear(temp1);
    element_clear(temp2);
    element_clear(temp3);
    
    return 0;   // 回傳0，代表正常。

}