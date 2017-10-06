/*
(c) Haley Euphemia Eleanor Ashley Lisa Praesent (Codeawayhaley) 6-10-2017
This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.
See: http://creativecommons.org/licenses/by-sa/4.0/
*/
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t hash(uint64_t x, uint64_t a, uint64_t p, uint64_t s){
	fprintf(stderr, "x = %llu\n a = %llu\n p = %llu\n s = %llu\n", x, a, p, s);
	uint64_t ea,eb,ec,ed,ee,ef,eg;ea=0x19ccc279872db905;eb=0x1e6540a2354a61e4;ec=0x1ed881f64eaf1e15;ed=0xdacd88a2bbc7a432;ee=0x963096e5554346e8;ef=0x419ce08a5908d2e4;eg=0x70F69A8B80A7727F;
	fprintf(stderr, "ea = %llu\n eb = %llu\n ec = %llu\n ed = %llu\n ee = %llu\n ef = %llu\neg = %llu\n", ea, eb, ec, ed, ee, ef,eg);
	uint64_t h = (s+ea)%ef;
	fprintf(stderr, "h = %llu\n", h);
	for (uint8_t i=0 ; i < 10 ; ++i){
		h =(((eb+h*a) + x + i)*((h*(ec * ed))% ee)*h+ea+eb+ec+ed+ee+ef) % p;
		h = eg ^ h;
		fprintf(stderr, "h = %llu at i = %llu\n", h, i);
	}
	return h;
}
uint64_t randreturn(){
	FILE *fd;
	fd = fopen("/dev/random","r");
	uint64_t *output = malloc(sizeof(uint64_t));
	fread(output, 1, 8, fd);
		if ((int)output == 0) {
			exit(3);
		}
	fprintf(stderr, "pointer for (uint64_t)output = %llu\n(uint64_t)output %llu\n", (uint64_t)output, (uint64_t)*output); 
	fclose(fd);
	uint64_t res;
	memcpy(&res, output, 8);
	fprintf(stderr, "res = *output = %lld\n", res);
	free(output);
	return res;
}

uint32_t main(int argc,const char *argv[]) {
	if (argc > 2) {
		exit(1);
	}
	else {
		uint32_t size = strlen(argv[1]);
		char *strn = malloc(sizeof(char *)*size);
		memcpy(strn, argv[1], sizeof(char *)*size);
		uint32_t i = 0;
		uint64_t prepr = 0;
		while (i < size) {
			prepr = prepr ^ (uint64_t)strn[i];
			i = i+8;
		}
		fprintf(stderr, "Point A has been reached. \n");
		uint64_t r1 = randreturn();
		fprintf(stderr, "r1 now set to %llu\n", r1);
		uint64_t r2 = randreturn();
		fprintf(stderr, "r2 now set to %llu\n", r2);
		uint64_t r3 = randreturn();
		fprintf(stderr, "r3 now set to %llu\n", r3);
		fprintf(stderr, "Point B has been reached\n*strn = %hhd\n strn = %s\n argv[1] = %s\n(uint64_t)strn = %llu\nprepr = %llu\n", *strn, strn, argv[1],(uint64_t)strn, prepr);
		uint64_t result = hash(prepr, r1, r2, r3);
		printf("hash = %016llX\n", result);
		free(strn);
		exit(0);
	}
}
