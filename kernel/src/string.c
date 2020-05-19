#include <practiceos/string.h>

uint32_t strlen(char *string)
{
    uint32_t i=0;
    while (string[i] != 0) i++;
    return i;
}


void memset(void *destination, uint8_t value, uint32_t size)
{
    for (uint32_t i=0;i<size;i++) ((char*)destination)[i] = value;
}

void memcpy(void *source, void *destination, uint32_t size)
{
    for (uint32_t i=0;i<size;i++) ((char*)destination)[i] = ((char*)source)[i];
}

char upperc(char character)
{
    return (character >= 0x61 && character <= 0x7a) ? character-0x20 : character;
}

char lowerc(char character)
{
    return (character >= 0x41 && character <= 0x5a) ? character+0x20 : character;
}

void upper(char *string)
{
    uint32_t i=0;
    while (string[i] != 0) {
        string[i] = upperc(string[i]);
        i++;
    }
}

void lower(char *string)
{
    uint32_t i=0;
    while (string[i] != 0) {
        string[i] = lowerc(string[i]);
        i++;
    }
}

int32_t strcmp(char *string1, char *string2)
{
    for (uint32_t i=0;;i++) {
        if (string1[i] != string2[i]) {
            return string1[i] < string2[i] ? -1 : 1;
        }
        if (string1[i] == 0) {
            return 0;
        }
    }
}

int32_t strncmp(char *string1, char *string2,uint32_t n)
{
    for (uint32_t i=0;i<n;i++) {
        if (string1[i] != string2[i]) {
            return string1[i] < string2[i] ? -1 : 1;
        }
    }
    return 0;
}

int32_t atoi(char *string)
{
    uint8_t negative = (string[0] == '-') ? 1 : 0;
    int32_t result = 0;
    for (uint32_t i=negative ? 1 : 0;string[i]!=0;i++) {
        result = result*10 + string[i]-'0';
    }
    return negative ? -result : result;
}

void revnStr(char *string, int32_t length)
{
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    {
        uint8_t buffer = *(string+start);
        *(string+start) = *(string+end);
        *(string+end) = buffer;
        start++; 
        end--; 
    } 
}

char *itoa(char *string, int32_t number, int32_t base)
{
    int i = 0;
    uint8_t negative = 0;

    if (number == 0) 
    { 
        string[i++] = '0'; 
        string[i] = '\0'; 
        return string; 
    }
    if (number < 0 && base == 10) 
    { 
        negative = 1;
        number = -number;
    }
    while (number != 0) 
    { 
        int rem = number % base; 
        string[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        number = number/base; 
    }
    if (negative) string[i++] = '-'; 

    string[i] = '\0';
    revnStr(string, i);
    return string; 
}