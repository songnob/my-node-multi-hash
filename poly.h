#ifndef POLY_H
#define POLY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void poly_hash(const char* input, char* output, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
