#include <pbc/pbc.h>
#include "common.h"
#include "hash.h"

int extract (SystemParams *param, const char *id, UserPrivateKey *key) {

    //=========== g^d ===========

    element_t d, g_pow_d;

    element_init_Zr(d, param->pairing);
    element_init_G1(g_pow_d, param->pairing);

    element_random(d);

    element_pow_zn(g_pow_d, param->g, d);

    //=========== h1(ID||S) ===========

    element_t h1;

    element_init_G1(h1, param->pairing);
    element_init_Zr(key->S, param->pairing);

    element_random(key->S);

    hash_h1(h1, id, key->S);

    //====== D = g^d · h1(ID||S) =======

    element_t D;

    element_init_G1(D, param->pairing);

    element_mul(D, g_pow_d, h1);

    //======= temp = D · h2​(ID) ========

    element_t h2, temp;

    element_init_G1(h2, param->pairing);
    element_init_G1(temp, param->pairing);

    hash_h2(h2, id);

    element_mul(temp, D, h2);

    //===== X_prime = ( D · h2​(ID) ) ^ mu =====

    element_t X_prime;

    element_init_G1(X_prime, param->pairing);

    element_pow_zn(X_prime, temp, param->mu);

    //======= X1 = X_prime / W^d =========

    element_t W_pow_d;

    element_init_G1(W_pow_d, param->pairing);

    element_pow_zn(W_pow_d, param->W, d);

    element_init_G1(key->X1, param->pairing);

    element_div(key->X1, X_prime, W_pow_d);
    
    // clear

    element_clear(d);
    element_clear(g_pow_d);
    element_clear(h1);
    element_clear(D);
    element_clear(temp);
    element_clear(h2);
    element_clear(X_prime);
    element_clear(W_pow_d);

    return 0;   // 回傳0，代表正常。
}