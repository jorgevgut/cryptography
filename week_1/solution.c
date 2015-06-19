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
	raw_buffer = (char *)malloc (sizeof(char)*rlength);
	
	if (raw_buffer) fread (raw_buffer, 1, rlength ,fCipher);
	fclose(fCipher);

	//print original cipher text
	printf("print original cipher text\n");
	printf("%s\n",raw_buffer);
	
	//get the correct string with buffer
	length = rlength / 2;
	buffer = (char *) malloc (sizeof(char)*(length+1));
	int i,j ;
	for (i = 0,j = 0; i< length; j+=2,i++) {
		buffer[i] = (raw_buffer[j] << 4) | raw_buffer[j+1];
	}
	buffer[i] = '\0';
	
	//print original cipher text
	printf("processed original cipher: %s\n",buffer);
	
	/* Problem 1. find the length of the key, we know that the key length is somewhere between 1 and 13 
	 according to the excercise, I will create an array (size 13) to store probability of that being the 
	correct length */

    //first step is to retrieve all distributions
    //this is the distribution function
    /* struct distribution getDist(unsigned long b_size
                            ,unsigned char * buffer
                            ,unsigned int k_len
                            ,unsigned char * key
                            ,unsigned int index) */
    
    //test for sizes, we first need the most probable size
    int start;
    distribution good;
    unsigned char * key_set;
    
    for(start = 1 ;start <= 13;start++){
        //select the "index" to test, and get dists with 256 ascii chars or alphabet
        unsigned char alph;
        key_set = (char *)malloc(sizeof(char)*start); //allocate space for "key"
        
        for(alph = START_A; alph <= END_A ;alph++) {
            //try
            memset(key_set,alph,start); //set key values
            //printf("char: %02x, size: %d, key_set:%s\n",alph,start,key_set);
            distribution dt = getDist((unsigned long)length,buffer,start,key_set
                                      ,0); //index
                        printf("key: %02x - key_size:%d   distance:%f -- e:%f   - t:%f  - a:%f \n "
                       ,alph,start,good.distance
                       ,dt.e_frequency
                       ,dt.t_frequency
                       ,dt.a_frequency );
            int k = 0;
            //printf("%s -%f\n",tkey,dt.distance);
            if(good.distance == -1) {
                good = dt;
                printf("key: %02x - key_size:%d   distance:%f -- e:%f   - t:%f  - a:%f \n "
                       ,alph,start,good.distance
                       ,good.e_frequency
                       ,good.t_frequency
                       ,good.a_frequency );
            } else if(dt.distance < fabs(good.distance)) {
                good = dt;
                /* while(k < start) { */
                /*     printf("%02x",good.key[k]); */
                    
                /* } */
                //printf("%s - distance:%f\n",good.key,good.distance );
                //printf(" - distance:%f\n",good.distance );
                /* printf("key: %02x - key_size:%d   distance:%f -- e:%f   - t:%f  - a:%f \n " */
                /*        ,alph,start,good.distance */
                /*        ,good.e_frequency */
                /*        ,good.t_frequency */
                /*        ,good.a_frequency ); */
                k++;
                
            }
        }
        free(key_set);
    }
    
    /* int ci; */
    /* unsigned char cj; */
    /* int dist_index = 0; */
    /* //first iterate by length */
    /* unsigned char * tkey; */
    /* unsigned int position = 0; */
    /* unsigned char * last_key; */
   


    /* int the_index = 0; */
    /* for(the_index = 0; the_index < 13;the_index++) { */
    /*     good.distance = -1; */
    /* for(ci = start;ci <= 9; ci++) { */
    /*     if(ci > start) { */
    /*         free(tkey); */
    /*         free(last_key); */
    /*     } */
    /*     tkey = (char *)malloc(sizeof(char)*(ci+1)); */
    /*     last_key  = (char *)malloc(sizeof(char)*(ci+1)); */
    /*     memset(tkey,START_A,ci); */
    /*     //memset(tkey,END_A,ci-1); */
    /*     memset(last_key,END_A,ci); */
    /*     tkey[ci] = '\0'; */
    /*     last_key[ci] = '\0'; */
    /*     //try all possible keys within the same alphabet and size */
    /*     unsigned int pos = 0; */
    /*     unsigned int limit = pos; */
    /*     //then by our alphabet */
    /*     printf("start search:\n"); */
        
    /*     /\* while (strncmp(tkey,last_key,1) != 0) { *\/ */
    /*     while (tkey[the_index] != last_key[the_index]) {  */
    /*         //printf("%s\n",tkey); */
    /*         distribution dt = getDist((unsigned long)length,buffer,ci,tkey */
    /*                                   ,the_index); //index */
    /*         int k = 0; */
    /*         //printf("%s -%f\n",tkey,dt.distance); */
    /*         if(good.distance == -1) { */
    /*             good = dt; */
    /*             /\* while(k < ci) { *\/ */
    /*             /\*     printf("%02x",good.key[k]); *\/ */
    /*             /\*     k++; *\/ */
    /*             /\* } *\/ */
    /*             //if (good.distance < 2 )printf("%s - distance:%f\n",good.key,good.distance ); */
    /*         } else if(dt.distance < fabs(good.distance)) { */
    /*             good = dt; */
    /*             while(k < ci) { */
    /*                 printf("%02x",good.key[k]); */
    /*                 k++; */
    /*             } */
    /*             //printf("%s - distance:%f\n",good.key,good.distance ); */
    /*             //printf(" - distance:%f\n",good.distance ); */
    /*             printf(" - key_size:%d   distance:%f -- e:%f   - t:%f  - a:%f \n ",ci,good.distance,good.e_frequency,good.t_frequency,good.a_frequency ); */
            
    /*         } */

    /*         /\* if(good.distance < 0.5) { *\/ */
    /*         /\*     while(k < ci) { *\/ */
    /*         /\*         printf("%02x",good.key[k]); *\/ */
    /*         /\*         k++; *\/ */
    /*         /\*     } *\/ */
    /*         /\*     printf(" - distance:%f -- e:%f   - t:%f  - a:%f \n ",good.distance,good.e_frequency,good.t_frequency,good.a_frequency ); *\/ */
    /*         /\* } *\/ */

    /*         tkey = nextKey(tkey,ci); */
    /*     } */
    /* } */
    /* } */


	/* double p_length[13]; */
    

	return;
			
}


/* char * str = (char*)malloc(sizeof(char)*(length+1)); */


/* const char* str = "angel"; */
/* str[length] = '\0'; */

