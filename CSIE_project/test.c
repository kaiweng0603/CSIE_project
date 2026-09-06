#include <pbc/pbc.h>
#include "common.h"

int test (SystemParams *param, Ciphertext *cipher1, Trapdoor *td1, Ciphertext *cipher2, Trapdoor *td2) {

    element_t F1, F2;

    element_init_G1(F1, param->pairing);
    element_init_G1(F2, param->pairing);

    element_div(F1, cipher1->delta3, td1->T);
    element_div(F2, cipher2->delta3, td2->T);

    element_t temp1, temp2;

    element_init_GT(temp1, param->pairing);
    element_init_GT(temp2, param->pairing);

    pairing_apply(temp1, cipher1->delta2, F2, param->pairing);
    pairing_apply(temp2, cipher2->delta2, F1, param->pairing);

    // 比較等式是否相等
    // 若等式相等，result = 1
    // 若等式不相等，result = 0
    int result = !element_cmp(temp1, temp2);

    element_clear(F1);
    element_clear(F2);
    element_clear(temp1);
    element_clear(temp2);

    return result;
}