#ifndef __HEADER_H__
#define __HEADER_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "structs.h"

void encoder(FILE *in, FILE *out);
void decoder(FILE *in, FILE *out);
#endif