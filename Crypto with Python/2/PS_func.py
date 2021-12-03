
def numOfZeros(n):
    bin_str = bin(n)[2:]
    count = 0
    for x in reversed(bin_str):
        if x == '1':
            break
        else:
            count += 1
    return count



def miller_rabin(a, n):
    s = numOfZeros(n)
    t = n - 1
    d = my_pow(a, t, n)
    if d == 1 or d == n - 1:
        return True
    for i in range(s - 1):
        d = (d * d) % n
        if d == n - 1:
            return True
    return False

def my_pow(base,expon,mod):
    result = base
    for i in range(1,expon):
        result = (result*base)%mod
    return result

def lehmann(a, n):
    t = my_pow(a, (n-1)//2, n)
    t = t%n
    if t != 1 and t != n - 1:
        return False
    return True



def run(num_list):
    psMiller = 0
    maxPsMiller = -1
    sumPsMiller = 0
    
    
    psLehmann = 0
    maxPsLehmann = -1
    sumPsLehmann = 0;
    
    countMillerBigger = 0
    countLehmannBigger = 0
    countEqual = 0

    primes_cnt2 = 0

    for n in num_list:
        print("we're now at n = " + str(n) + "")
        psMiller = 0
        psLehmann = 0
        for a in range(1,n):
            if miller_rabin(a,n):
                if psMiller / (n-1) != 1:
                    psMiller += 1
            
            if lehmann(a,n):
                if psLehmann / (n-1) != 1:
                    psLehmann += 1
            
                 
        psMiller = psMiller / (n-1)
        psLehmann = psLehmann / (n-1)
        
        if psMiller == 1 or psLehmann == 1:
            primes_cnt2 +=1
            continue
        
        if maxPsMiller < psMiller:
            maxPsMiller = psMiller
            
        sumPsMiller += psMiller
        
        
        
        if maxPsLehmann < psLehmann:
            maxPsLehmann = psLehmann
                
        sumPsLehmann += psLehmann
        
        if psMiller > psLehmann:
            countMillerBigger += 1
        if psMiller < psLehmann:
            countLehmannBigger+= 1
        if psMiller == psLehmann:
            countEqual += 1
        
    print(primes_cnt2)
    total = len(odd_list) - primes_cnt2
    print(f'PS(n)/(n-1) MAX non-prime n is  {(maxPsMiller):.4f}')
    print(f'PS(n)/(n-1) average non-prime n is {(sumPsMiller/(total)):.4f}')
    print(f'PS*(n)/(n-1) MAX non-prime n is {(maxPsLehmann):.4f}')
    print(f'PS*(n)/(n-1) average non-prime n is {(sumPsLehmann/(total)):.4f}')
    print(f'PS*(n)/(n-1) < PS(n)/(n-1) is {(countMillerBigger)}')
    print(f'PS*(n)/(n-1) > PS(n)/(n-1) is {(countLehmannBigger)}')
    print(f'PS*(n)/(n-1) = PS(n)/(n-1) is {(countEqual)}')
    return


if __name__ == "__main__":
    start = 5
    end = 2200
    odd_list = list(range(start, end, 2))
    res = run(odd_list)
