from os import urandom
from ecc import ECPoint
from ecc import EC


def readcoin(coin_file):
    listy = list()
    with open(coin_file) as f:
        lines = f.read().split("\n")
        for line in lines:
            var_val = line.split("=")
            listy.append(var_val[0])
            listy.append(int(var_val[1]))
    i=iter(listy)
    dictionary = dict(zip(i,i))
    dictionary["g"] = ECPoint(dictionary["x"], dictionary["y"])
    return dictionary


def main():
    dictionary = readcoin("ec_bitcoin.txt")
    d = (int.from_bytes(urandom(dictionary["n"].bit_length() // 8 + 1), 'little') % (dictionary["n"] - 1)) + 1
    q = EC(dictionary["p"], dictionary["a"], dictionary["b"]).power(dictionary["g"],d)
    with open("public_key.txt", "w+") as f:
        f.write(str(q.x) + "\n" + str(q.y))
    with open("private_key.txt", "w+") as f:
        f.write(str(d))



if __name__ == '__main__':
    main()
