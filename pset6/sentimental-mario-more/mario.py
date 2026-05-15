# Author: Marko Solajic

from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 0 < height <= 8:
        break

for i in range(height):
    for j in range(height - 1 - i):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()
