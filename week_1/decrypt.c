#include <stdio.h>
#include <stdlib.h>
#include "impl.c"


#define KEY_LENGTH 6 // Can be anything from 1 to 13


void main () {
	
	unsigned char * raw_buffer;
	unsigned char * buffer;
	long length;
	unsigned char key[KEY_LENGTH] = {0x12,0x12,0x13,0x12,0x12,0x12};//,0x12,0x07,0x10,0x10};
    /* 
       1. 12 --
       2. 16 , 31
       3. 12 ---10,  or 01,14,12
       4. 12
       5.
       6.
       7.
       8.
       9.
    */
	// the very first thing we need is to read the cipher text
	FILE *fCipher;
	long rlength;
	fCipher = fopen("ctext.txt","r");
	//remember that the cipher text is formated 02x in hex, so we need to translate that
	fseek (fCipher,0,SEEK_END);
	rlength = ftell (fCipher);
	fseek (fCipher,0,SEEK_SET);
	raw_buffer = (char *)malloc (sizeof(char)*rlength);
	
	if (raw_buffer) fread (raw_buffer, 1, rlength ,fCipher);
	fclose(fCipher);

	//print original cipher text
	printf("%s\n",raw_buffer);
	
	//get the correct string with buffer
	length = rlength / 2;
	buffer = (char *) malloc (length);
	int i,j ;
	for (i = 0,j = 0; i< length; j+=2,i++) {
		buffer[i] = ((raw_buffer[j] << 4) | raw_buffer[j+1]);
	}
    int k = 0;
    while( *buffer != '\0') {
        //if (k % KEY_LENGTH == 0) printf("\n");
        printf("%c",*buffer ^ key[k % KEY_LENGTH]);
        buffer++;

        k++;
    }
    printf("\n");

}
