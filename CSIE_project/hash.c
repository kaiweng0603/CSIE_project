#include <string.h>
#include <pbc/pbc.h>
#include <openssl/sha.h>

void hash_h0 (const unsigned char *data, unsigned char digest[32]) {

    SHA256(data, 32, digest);
}

void hash_h1 (element_t h, const char *id, element_t S) {

    int id_len = strlen(id);

    int s_len = element_length_in_bytes(S);

    unsigned char *buffer = malloc(id_len + s_len);

    memcpy(buffer, id, id_len);

    element_to_bytes(buffer + id_len, S);

    element_from_hash(h, buffer, strlen(buffer));

    free(buffer);
}

void hash_h2 (element_t h, const char *id) {

    element_from_hash(h, id, strlen(id));
}

void hash_h3 (element_t gt, element_t g1, element_t g2, element_t g3, unsigned char digest[64]) {

    int gt_len = element_length_in_bytes(gt);
    int g1_len = element_length_in_bytes(g1);
    int g2_len = element_length_in_bytes(g2);
    int g3_len = element_length_in_bytes(g3);

    int total = gt_len + g1_len + g2_len + g3_len;

    unsigned char *buffer = malloc(total + 1);

    int pos = 0;

    element_to_bytes(buffer, gt);
    pos += gt_len;

    element_to_bytes(buffer + pos, g1);
    pos += g1_len;

    element_to_bytes(buffer + pos, g2);
    pos += g2_len;

    element_to_bytes(buffer + pos, g3);
    pos += g3_len;

    buffer[pos] = '0';
    SHA256(buffer, total + 1, digest);

    buffer[pos] = '1';
    SHA256(buffer, total + 1, digest + 32);

    free(buffer);

}