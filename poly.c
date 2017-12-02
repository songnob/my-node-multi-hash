#include "poly.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sha3/sph_skein.h"
#include "sha3/sph_echo.h"
#include "sha3/sph_fugue.h"
#include "sha3/sph_luffa.h"
#include "sha3/sph_shabal.h"
#include "sha3/sph_gost.h"

void poly_hash(const char* input, char* output, uint32_t len)
{
    sph_skein512_context    ctx_skein;
    sph_shabal512_context   ctx_shabal1;
    sph_echo512_context ctx_echo1;
    sph_luffa512_context    ctx_luffa1;
    sph_fugue512_context    ctx_fugue1;
    sph_gost512_context ctx_gost;

    uint32_t hashA[16], hashB[16];

    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, input, len);
    sph_skein512_close(&ctx_skein, hashA);

    sph_shabal512_init(&ctx_shabal1);
    sph_shabal512(&ctx_shabal1, hashA, 64);
    sph_shabal512_close(&ctx_shabal1, hashB);

    sph_echo512_init(&ctx_echo1);
    sph_echo512(&ctx_echo1, hashB, 64);
    sph_echo512_close(&ctx_echo1, hashA);

    sph_luffa512_init(&ctx_luffa1);
    sph_luffa512(&ctx_luffa1, hashA, 64);
    sph_luffa512_close(&ctx_luffa1, hashB);

    sph_fugue512_init(&ctx_fugue1);
    sph_fugue512(&ctx_fugue1, hashB, 64);
    sph_fugue512_close(&ctx_fugue1, hashA);

    sph_gost512_init(&ctx_gost);
    sph_gost512(&ctx_gost, hashA, 64);
    sph_gost512_close(&ctx_gost, hashB);

    memcpy(output, hashB, 32);

}
