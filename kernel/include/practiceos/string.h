#ifndef STRING_H
#define STRING_H
#include <practiceos/types.h>

uint32_t strlen(char*);
void memset(void*, uint8_t, uint32_t);
void memcpy(void*,void*,uint32_t);
char upperc(char);
char lowerc(char);
void upper(char*);
void lower(char*);
int32_t strcmp(char*,char*);
int32_t strncmp(char*,char*,uint32_t);
int32_t atoi(char*);
char *itoa(char*,int32_t,int32_t);

#endif