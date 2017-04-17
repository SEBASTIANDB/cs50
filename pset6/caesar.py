import sys
import cs50

while True:
        print("enter key :", end="")
        key = cs50.get_int()
        if key >= 0:
            break;
    
    

encrypted = []
print("give something to ceasarize")
encrypt_it = cs50.get_string()
    
def caesarize(char, key):
    if char.isupper():
        return chr(((ord(char) - 65 + key) % 26) + 65)
    else:
        return chr(((ord(char) - 65 + key) % 26) + 97)
            
for symbol in encrypt_it:
    if symbol.isalpha():
        encrypted.append(caesarize(symbol, key))
    else:
        encrypted.append(symbol)
            
print("".join(encrypted))#get rid of the braces and stuff
                