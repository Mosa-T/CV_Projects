from sign_ecdsa import hash_e
from ecc import ECPoint
from ecc import EC
from make_keys import readcoin
from modular_funcs import inverse




def main():
    m = input("enter file name: ")
    e = hash_e(m)
    
    m = m.split(".")
    m = m[0] + "_sig.txt"
    with open(m) as f:
        r_s = f.read()
    r_s = r_s.split(" ")
    r = int(r_s[0])
    s = int(r_s[1])
    
    with open("public_key.txt", "r+") as f:
        q = f.read()
    f_split = q.split("\n")
    q = ECPoint(int(f_split[0]), int(f_split[1]))

    
    dictionary = readcoin("ec_bitcoin.txt")
    n = dictionary["n"]
    w = inverse(s, n)
    u1 = (e * w) % n
    u2 = (r * w) % n
    
    ec = EC(dictionary["p"], dictionary["a"], dictionary["b"])
    q_powed = ec.power(q, u2)
    g_powed = ec.power(dictionary["g"], u1)
    p = ec.add(g_powed, q_powed)
    if (p.x)%n == r:
        print("signature OK")    
    else:
        print("signature failed")


if __name__ == '__main__':
    main()
