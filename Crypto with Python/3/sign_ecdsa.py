from os import urandom
from ecc import EC
from modular_funcs import inverse
from Cryptodome.Hash import SHA256
from make_keys import readcoin



def hash_e(m):
    with open(m) as f:
        f2 = f.read()
        f2 = bytes(f2,'utf-8')
        f2 = str(int.from_bytes(f2, 'little'))
        hashie = SHA256.new()
        hashie.update(f2.encode())
        return int(hashie.hexdigest(), 16)

def main():
    m = input("enter file name: ")
    with open("private_key.txt", "r+") as f:
        d = int(f.read())
    
    dictionary = readcoin("ec_bitcoin.txt")
    while True:
        k = (int.from_bytes(urandom(dictionary["n"].bit_length() // 8 + 1), 'little') % dictionary["n"] - 2) + 1
        kg = EC(dictionary["p"], dictionary["a"], dictionary["b"]).power(dictionary["g"], k)
        r = kg.x % dictionary["n"]
        if r != 0:
            e = hash_e(m)
            s = (inverse(k, dictionary["n"]) * (e + d * r)) % dictionary["n"]
            if s != 0:
                break
    with open(m.split(".")[0] + "_sig.txt", "w+") as f:
        f.write(str(r) + " " + str(s))



if __name__ == '__main__':
    main()
