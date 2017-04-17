import cs50

while True:
    print("give height between 0 and 23")
    num = cs50.get_int()
    if num < 23 or num > 0:
        break
    
spaces = num - 1
hashes = 2
i = 0
for i in range(num):
    for j in range(num - i - 1):
        print(" ", end="")
    for k in range(i + 2):
        print("#", end="")
    print()
    
    
    
    
    