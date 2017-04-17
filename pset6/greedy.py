import cs50

change = 0
while True:
    print("O hai, how much is owed ?", end="")
    change = cs50.get_float()
    if change >= 0:
        break;


coins = 0
cents = int(round(change * 100))

coins += cents // 25
cents = cents % 25

coins += cents // 10
cents = cents % 10

coins += cents // 5
cents = cents % 5

coins += cents // 1
cents = cents % 1
    
print(coins)
    


    
    