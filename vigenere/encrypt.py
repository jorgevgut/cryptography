#!/usr/bin/python3

def main():
    ptext = input("please enter plain-text\n")
    key = input("now enter your key\n")
    ctext = get_cipher(key,ptext)
    f_out = open('cipher.txt','w')
    f_out.write(ctext)

def get_cipher(key,ptext):
    ctext = ""
    ksize = len(key)
    for index,val in enumerate(ptext):
        c = ord(val) ^ ord(key[index % ksize])
        ctext += str(chr(c))

    return ctext


main()
