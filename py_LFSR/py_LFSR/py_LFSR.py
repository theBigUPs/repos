def lfsr():
    start = 12335645;
    lfsr = start;
    period = 0;

    while True:
        lfsr ^= lfsr >> 31;
        lfsr ^= lfsr << 29;
        lfsr ^= lfsr >> 1;
        period=period+1;
        lfsr = lfsr % 2**31;
        if (lfsr == start):
            break;
    return period;


def stream_cypher(key, mesaj):
    for x in range(len(mesaj)):
        xor=key^ord(mesaj[x]);
        mesaj = mesaj.replace(mesaj[x],chr(xor),1);
    return mesaj;
        



mesaj="nnnnnnnnnn";
key=lfsr();

mesaj=stream_cypher(key,mesaj);
print(mesaj);
mesaj=stream_cypher(key,mesaj);
print(mesaj);






