import os


def euler(n):
    result = n
    prime = 2
    while prime * prime <= n:
        if n % prime == 0:
            while n % prime == 0:
                n = int(n / prime)
            result -= int(result / prime)
        prime += 1
    if n > 1:
        result -= int(result / n)
    return result


def numbers():
    with open("numbers.txt", "r+") as file:
        data = file.read()
        dataSplit = data.split("\n")
        dataIntegerized = [int(i) for i in dataSplit]
    return dataIntegerized

def numbers_12():
    byteSize = 12
    numbers = 10
    data_rand_bytes = [int.from_bytes(os.urandom(byteSize), "little") for _ in range(numbers)]
    return data_rand_bytes



def main():
    # ex1.a
    for num in numbers():
        print(f"phi({num}) = {euler(num)}")
    # ex1.b
    for num in numbers_12():
        print(f"phi({num}) = {euler(num)}")
   

if __name__ == '__main__':
    main()
