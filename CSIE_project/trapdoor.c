#include <pbc/pbc.h>
#include "common.h"

int trapdoor (SystemParams *param, UserPrivateKey *key, Trapdoor *td) {

    // T = g ^ S

    element_init_G1(td->T, param->pairing);

    element_pow_zn(td->T, param->g, key->S);

    return 0;   // 回傳0，代表正常。

}