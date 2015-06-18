#include <stdio.h>
#include <stdlib.h>
#include "impl.c"




void main () {
	
	unsigned char * raw_buffer;
	unsigned char * buffer;
	long length;
    unsigned int dist_len = 26*13;
    //distribution * dists = malloc(sizeof(struct distribution)*dist_len);

	// the very first thing we need is to read the cipher text
	FILE *fCipher;
	long rlength;
	fCipher = fopen("ctext.txt","r");
	//remember that the cipher text is formated 02x in hex, so we need to translate that
	fseek (fCipher,0,SEEK_END);
	rlength = ftell (fCipher);
	fseek (fCipher,0,SEEK_SET);
	raw_buffer = (char *)malloc (rlength);
	
	if (raw_buffer) fread (raw_buffer, 1, length ,fCipher);
	fclose(fCipher);

	//print original cipher text
	printf("%s\n",raw_buffer);
	
	//get the correct string with buffer
	length = rlength / 2;
	buffer = (char *) malloc (length);
	int i,j ;
	for (i = 0,j = 0; i< length; j+=2,i++) {
		buffer[i] = (raw_buffer[j] << 4) | raw_buffer[j+1];
	}
	
	//print original cipher text
	printf("%s\n",buffer);
	
	/* Problem 1. find the length of the key, we know that the key length is somewhere between 1 and 13 
	 according to the excercise, I will create an array (size 13) to store probability of that being the 
	correct length */

    //first step is to retrieve all distributions
    int ci;
    unsigned char cj;
    int dist_index = 0;
    //first iterate by length
    unsigned char * tkey;
    unsigned int position = 0;
    unsigned char * last_key;
    
    distribution good;
    good.distance = -1;
    int start = 1;
    for(ci = start;ci <= 13; ci++) {
        if(ci > start) {
            free(tkey);
            free(last_key);
        }
        tkey = (char *)malloc(sizeof(char)*(ci+1));
        last_key  = (char *)malloc(sizeof(char)*(ci+1));
        memset(tkey,START_A,ci);
        memset(last_key,END_A,ci);
        tkey[ci] = '\0';
        last_key[ci] = '\0';
        //try all possible keys within the same alphabet and size
        unsigned int pos = 0;
        unsigned int limit = pos;
        //then by our alphabet
        printf("start search:\n");

        while (strncmp(tkey,last_key,ci) != 0) {
            
            //printf("%s\n",tkey);
            distribution dt = getDist((unsigned long)length,buffer,ci,tkey,0);
            int k = 0;
            //printf("%s -%f\n",tkey,dt.distance);
            if(good.distance == -1) {
                good = dt;
                /* while(k < ci) { */
                /*     printf("%02x",good.key[k]); */
                /*     k++; */
                /* } */
                //if (good.distance < 2 )printf("%s - distance:%f\n",good.key,good.distance );
            } else if(dt.distance < fabs(good.distance)) {
                good = dt;
                while(k < ci) {
                    printf("%02x",good.key[k]);
                    k++;
                }
                //printf("%s - distance:%f\n",good.key,good.distance );
                //printf(" - distance:%f\n",good.distance );
                printf(" - distance:%f -- e:%f   - t:%f  - a:%f \n ",good.distance,good.e_frequency,good.t_frequency,good.a_frequency );
            }
            /* if(good.distance != 99) { */
            /*     while(k < ci) { */
            /*         printf("%02x",good.key[k]); */
            /*         k++; */
            /*     } */
            /*     printf(" - distance:%f -- e:%f   - t:%f  - a:%f \n ",good.distance,good.e_frequency,good.t_frequency,good.a_frequency ); */
            /* } */

            tkey = nextKey(tkey,ci);
        }

    }


	double p_length[13];
    

	return;
			
}


/* char * str = (char*)malloc(sizeof(char)*(length+1)); */


/* const char* str = "angel"; */
/* str[length] = '\0'; */

