
rseed=0;
def lcg_seed(seed):
    global rseed;
    rseed=seed;

def lcg():
    a = 214013;
    b = 2531011;
    modulus=pow(2,32)#4294967296;
    global rseed; 
    rseed = (rseed*a+b)%modulus;
    return rseed;



def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        return 1
    else:
        return x % m


def solve_lcr(s1,s2,s3):
    m = pow(2,32)#7296;
    a1 = s2 - s3;
    a2b3 = s1 - s2;
    if (a1<0):
        a1 = a1+m;

    if (a2b3 < 0):
        a2b3 = a2b3 + m;


    a= (a1) *modinv((a2b3),m)  % m; #922649604
    #b = (s2 - s1 * (a1) *modular_inverse((a2b3),m)) % m;
    b = (s2 - a * s1)%m;
    if (b<0):
        b += m;
    print(a,b)


s0=19878888
lcg_seed(s0)
s1=lcg()
s2=lcg()
s3=lcg()
print(s1,s2,s3)
solve_lcr(s1,s2,s3)
