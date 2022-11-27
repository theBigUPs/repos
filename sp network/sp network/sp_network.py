sbox1={0:5, 1:7, 2:3, 3:12, 4:9, 5:11, 6:15, 7:0, 8:10, 9:6, 10:14, 11:13, 12:1, 13:8, 14:2, 15:4}
sbox2={0:12, 1:8, 2:11, 3:9, 4:3, 5:7, 6:14, 7:1, 8:5, 9:15, 10:13, 11:10, 12:6, 13:4, 14:2, 15:0}
sbox3={0:8, 1:3, 2:10, 3:5, 4:12, 5:7, 6:14, 7:9, 8:13, 9:11, 10:0, 11:15, 12:2, 13:6, 14:1, 15:4}
sbox4={0:11, 1:5, 2:9, 3:15, 4:0, 5:8, 6:10, 7:13, 8:3, 9:7, 10:1, 11:4, 12:6, 13:2, 14:12, 15:14}


#sbox1={0:0, 1:1, 2:2, 3:3, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}
#sbox2={0:0, 1:1, 2:2, 3:3, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}
#sbox3={0:0, 1:1, 2:2, 3:3, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}
#sbox4={0:0, 1:1, 2:2, 3:3, 4:4, 5:5, 6:6, 7:7, 8:8, 9:9, 10:10, 11:11, 12:12, 13:13, 14:14, 15:15}


pbox1={0:12, 1:8, 2:11, 3:9, 4:3, 5:7, 6:14, 7:1, 8:5, 9:15, 10:13, 11:10, 12:6, 13:4, 14:2, 15:0}


inv_sbox1 = {v: k for k, v in sbox1.items()}
inv_sbox2 = {v: k for k, v in sbox2.items()}
inv_sbox3 = {v: k for k, v in sbox3.items()}
inv_sbox4 = {v: k for k, v in sbox4.items()}


inv_pbox1 = {v: k for k, v in pbox1.items()}


def get_16_bit_binary_string(string):
    
    upper = bin(ord(string[0]))[2:].zfill(8)
    lower = bin(ord(string[1]))[2:].zfill(8)   
    input=upper+lower
    
    
    return input



def string_xor(string_a,string_b):
    
    res=""
    
    for x in range(len(string_a)):
        
        if string_a[x] == string_b[x]:

            res+='0'
            pass

        else:
            res+='1'
            pass

        pass
    
    return res




def substitute(input,sb1,sb2,sb3,sb4):#
    res=""
    
    i1=input[0:4]
    i2=input[4:8]
    i3=input[8:12]
    i4=input[12:16]
    
    x1 = int(i1, 2)
    x2 = int(i2, 2)
    x3 = int(i3, 2)
    x4 = int(i4, 2)

    x1 = sb1.get(x1)
    x2 = sb2.get(x2)
    x3 = sb3.get(x3)
    x4 = sb4.get(x4)

    x1 = bin(x1)[2:].zfill(4)
    x2 = bin(x2)[2:].zfill(4)
    x3 = bin(x3)[2:].zfill(4)
    x4 = bin(x4)[2:].zfill(4)

    res=x1+x2+x3+x4

    return res



def permutate(input,pb):
    res=list("0000000000000000")

    for x in range(len(input)):
        
        t = pb.get(x)

        res[t] = input[x]

        pass

    res= ''.join(res)
    return res



def binary_string_to_character_string(binary_string):
    char_index=0
    res=""

    for x in range(int(len(binary_string)/8)):
        
        
        tmp = binary_string[char_index:char_index+8]
        tmp = int(tmp, 2)
        tmp = chr(tmp)
        res+=tmp
        char_index+=8

        pass

    
    return res



def encrypt(plaintext,key):
    
    res=""   
    text_index = 0
    if len(plaintext)%2!=0:
        plaintext+=' '
        pass

    for x in range(int(len(plaintext)/2)):
                   
        input=get_16_bit_binary_string(plaintext[text_index:text_index+2])
        key_index=0
        for x in range(3):     
            subkey=get_16_bit_binary_string(key[key_index:key_index+2])
            input = string_xor(input,subkey)
            input = substitute(input,sbox1,sbox2,sbox3,sbox4)
            input= permutate(input,pbox1)
            key_index+=2
            pass       
        subkey=get_16_bit_binary_string(key[6:8])
        input = string_xor(input,subkey)
        input = substitute(input,sbox1,sbox2,sbox3,sbox4)
        subkey=get_16_bit_binary_string(key[8:10])
        input = string_xor(input,subkey)
        res+=input
        text_index+=2
        pass
    return res


def decrypt(cyphertext,key):
    
    res=""
    
    text_index = 0



    for x in range(int(len(cyphertext)/2)):
        input=get_16_bit_binary_string(cyphertext[text_index:text_index+2])
        subkey=get_16_bit_binary_string(key[8:10])
        input = string_xor(input,subkey)
        input = substitute(input,inv_sbox1,inv_sbox2,inv_sbox3,inv_sbox4)
        subkey=get_16_bit_binary_string(key[6:8])
        input = string_xor(input,subkey)
    

        key_index = 6
        for x in range(3):
        
            input= permutate(input,inv_pbox1)
            input = substitute(input,inv_sbox1,inv_sbox2,inv_sbox3,inv_sbox4)
            subkey=get_16_bit_binary_string(key[key_index-2:key_index])
            input = string_xor(input,subkey)
            key_index-=2
            pass
        res+=input
        text_index+=2
        pass


    return res




plaintext="hello"
key="qwertyuiop"#the key has to be 10 characters long




cyphertext = encrypt(plaintext,key)
cyphertext = binary_string_to_character_string(cyphertext)
print(cyphertext)

dec = decrypt(cyphertext,key)
dec = binary_string_to_character_string(dec)
print(dec)



