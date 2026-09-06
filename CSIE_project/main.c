#include <stdio.h>
#include <pbc/pbc.h>
#include "common.h"
#include "hash.h"
#include "setup.h"
#include "extract.h"
#include "encrypt.h"
#include "trapdoor.h"
#include "test.h"
#include "decrypt.h"

int main() {

    // 系統初始化。

    SystemParams param;

    if (setup(&param)) {
        printf("setup失敗\n");
    } else {
        printf("setup成功\n");
    }

    // 使用者用ID創建私鑰。

    UserPrivateKey key;

    if (extract(&param, "TestId456", &key)) {
        printf("extract失敗\n");
    } else {
        printf("extract成功\n");
    }

    // 第一組訊息和關鍵字。

    Ciphertext cipher1;

    char M[32] = "This is a testing message";

    element_t Q1;
    element_init_G1(Q1, param.pairing);
    hash_h2(Q1, "Keyword");

    if (encrypt(&param, M, Q1, "TestId123", &key, &cipher1)) {
        printf("encrypt失敗\n");
    } else {
        printf("encrypt成功\n");
    }

    Trapdoor td1;

    if (trapdoor(&param, &key, &td1)) {
        printf("trapdoor失敗\n");
    } else {
        printf("trapdoor成功\n");
    }

    // 第二組訊息和關鍵字。

    Ciphertext cipher2;

    char M2[32] = "This is another message";

    element_t Q2;
    element_init_G1(Q2, param.pairing);
    hash_h2(Q2, "Keyword");

    if (encrypt(&param, M2, Q2, "TestId456", &key, &cipher2)) {
        printf("encrypt失敗\n");
    } else {
        printf("encrypt成功\n");
    }

    Trapdoor td2;

    if (trapdoor(&param, &key, &td2)) {
        printf("trapdoor失敗\n");
    } else {
        printf("trapdoor成功\n");
    }

    // 檢查有沒有相同關鍵字。

    if (test(&param, &cipher1, &td1, &cipher2, &td2)) {
        printf("有相同關鍵字\n");
    } else {
        printf("無相同關鍵字\n");
    }

    // 解密。

    char decrypt_M[32];

    if (decrypt(&param, &key, &cipher2, decrypt_M)) {
        printf("decrypt失敗\n");
    } else {
        printf("decrypt成功，原始訊息為:\n\"");
        for (int i = 0; i < 32; i++) {
            printf("%c", M2[i]);
        }
        printf("\"\n解密後訊息為:\n\"");
        for (int i = 0; i < 32; i++) {
            printf("%c", decrypt_M[i]);
        }
        printf("\"\n");
    }

    return 0;
}