#include <stdio.h>
#include <stdlib.h>
#include "impl.c"




void main () {
	
	unsigned char * raw_buffer;
	unsigned char * buffer;
	long length;
    unsigned int dist_len = 26*13;
    distribution * dists = malloc(sizeof(struct distribution)*dist_len);

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
    for(ci = 1;ci <= 13; ci++) {
        tkey = (char *)malloc(ci);
        last_key  = (char *)malloc(ci);
        memset(tkey,START_A,ci);
        memset(last_key,END_A,ci);
        //try all possible keys within the same alphabet and size
        unsigned int pos = ci-1;
        unsigned int limit = pos;
        //then by our alphabet
        printf("start search:\n");
        /* while (tkey != last_key) { */
        /*     while(limit >= 0) { */
        /*         int i; */
        /*         for(i = ci-1; i > limit; i--) { */
                    //while(tkey[i] <= END_A) {
                        tkey[i]++;
                        //get dist
                        printf("%s\n",tkey);
//}
                        //                  tkey[pos] = START_A;
          /*       } */
        /*         limit--; */
        /*     } */
        /* }  */
        /* for(cj = START_A; cj <= END_A; cj++) { */
            
        /*     dists[dist_index] = getDist((unsigned long)length,buffer,tkey,cj,0); //to find length we will only use index 0 as a start */
        /*     dist_index++; */
        /* } */

    }


	double p_length[13];
    

	return;
			
}
