#include <stdio.h>
#include <pbc/pbc.h>
#include "common.h"

// ======= 讀取param並初始化pairing =======
int init_pairing_from_file (pairing_t pairing, const char *filename) {

    // 打開param檔案。
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 1;  // 回傳1，代表失敗。

    // 讀取param檔案的長度。
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    // 把param檔案的內容存進param字串。
    char *param = malloc(fsize + 1);
    fread(param, 1, fsize, fp);
    fclose(fp);
    param[fsize] = '\0';

    // 初始化pairing參數。
    pairing_init_set_buf(pairing, param, fsize);

    // 印出param內容。
    printf("===== PARAM CONTENT =====\n");
    printf("%s\n", param);
    printf("=========================\n");

    free(param);

    return 0;   // 回傳0，代表正常。
}

int setup (SystemParams *param) {
    
    if (init_pairing_from_file(param->pairing, "param/a.param")) {
        printf("Error opening param file\n");
        return 1;   // 回傳1，代表失敗。
    }

    element_init_G1(param->g, param->pairing);
    element_init_G1(param->W, param->pairing);
    element_init_Zr(param->mu, param->pairing);

    element_random(param->g);
    element_random(param->mu);

    element_pow_zn(param->W, param->g, param->mu);  // W = g^mu;

    return 0;   // 回傳0，代表正常。
}