# Author: Marko Solajic

from cs50 import get_float

while True:
    change = get_float("Change: ")
    if change > 0:
        break

# Convert change to cents
change = round(change * 100)

# Coin values
coins = [25, 10, 5, 1]

count = 0

# Calculating min number of coins
for coin in coins:
    while change >= coin:
        change -= coin
        count += 1

print(count)
