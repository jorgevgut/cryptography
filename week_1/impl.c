#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_A 0x61
#define END_A 0x7A

/* For this program we are going to assume 26 dictionary letters
ascii from lowercase a to z
a -> 0x61
z -> 0x7A
*/


struct distribution {
    unsigned int n; //the number of letters in this dist
    unsigned int letter_count[256]; //the frequency of letters direct addr table 
    float e_frequency; //avg is 12.7%  e is 0x65
    float t_frequency; //avg is 9.1%  t is 0x74
    float a_frequency; //avg is 8.2%  a is 0x61
    float distance; //closer to 0 is better
    unsigned long key_length; //key length used
};

typedef struct distribution distribution;


//this function will get the distribution of a given buffer with index to test, length and key
struct distribution getDist(unsigned long b_size
                            ,char * buffer
                            ,unsigned int k_len
                            ,unsigned char * key
                            ,unsigned int index) {

    distribution d;
    unsigned int lc[256];
    int i,count;
    unsigned int * list = (int * )malloc(b_size);
    memset(list,0,b_size);
    char c;
    for(i = 0,count = index; count < k_len; count += b_size,i++) {
        c = buffer[count] ^ key[index % k_len];
        
    }
    return d;
}

