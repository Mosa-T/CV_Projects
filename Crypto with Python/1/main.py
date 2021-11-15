import bbs_PRG

def xor_bytes(b1, b2):
    zipped = zip(b1, b2)
    xor_list = [x ^ y for x, y in zipped]
    return bytes(xor_list)

def main():
    i = ''
    print('Type "exit" to close program')
    while i != 'exit':
        encrypted_file = input('Enter encrypted file: ')
        i = encrypted_file
        if i == 'exit':
            break
        password_str = encrypted_file[:-4]
        password_bytes = bytes(password_str, 'utf-8')
        seed = int.from_bytes(password_bytes, byteorder='little')
        with open(encrypted_file, 'rb') as handle:
            cipher_text = handle.read()   
        key = bbs_PRG.generate_key(seed, len(cipher_text))
        decrypted_text = xor_bytes(key, cipher_text)
        decrypted_file = encrypted_file[:-4] + ".AY_ITS_YA_BOI"
        with open(decrypted_file, 'wb') as handle:
            handle.write(decrypted_text)

if __name__ == '__main__':
    main()
