#include <stdio.h>
#include <stdlib.h>





void main () {
	
	unsigned char * raw_buffer;
	unsigned char * buffer;
	long length;

	// the very first thing we need is to read the cipher text
	FILE *fCipher;
	long rlength;
	fCipher = fopen("ctext.txt","r");
	//remember that the cipher text is formated 02x in hex, so we need to translate that
	fseek (fCipher,0,SEEK_END);
	rlength = ftell (fCipher);
	fseek (fCipher,0,SEEK_SET);
	raw_buffer = malloc (sizeof(char *)*rlength);
	
	if (raw_buffer) fread (raw_buffer, 1, length ,fCipher);
	fclose(fCipher);

	//print original cipher text
	printf("%s\n",raw_buffer);
	
	//get the correct string with buffer
	length = rlength / 2;
	buffer = malloc (sizeof(char *)*length);
	int i,j ;
	for (i = 0,j = 0; i< length; j+=2,i++) {
		buffer[i] = (raw_buffer[j] << 4) | raw_buffer[j+1];
	}
	
	//print original cipher text
	printf("%s\n",buffer);
	
	/* Problem 1. find the length of the key, we know that the key length is somewhere between 1 and 13 
	 according to the excercise, I will create an array (size 13) to store probability of that being the 
	correct length */
	double p_length[13];
    

	return;
			
}
