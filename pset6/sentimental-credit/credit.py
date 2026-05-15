# Author: Marko Solajic

def main():
    num = list(input("Number: "))

    # Convert list to integers
    num = list(map(int, num))

    # Length of number
    num_len = len(num)

    # Reverse number
    reversed_num = list(reversed(num))

    sum1 = sum_multiplied_digits(reversed_num)
    sum2 = sum_non_multiplied_digits(reversed_num)

    final_sum = sum1 + sum2

    determine_card_type(num, num_len, final_sum)

    return 0


def sum_multiplied_digits(reversed_num):
    # Creating a list of digits multiplied by 2
    multiplied_num = []

    # Add multiplied digits to the new list
    for digit in reversed_num[1::2]:
        multiplied_num.append(digit * 2)

    # Converting all the elements in list  to strings
    multiplied_num = list(map(str, multiplied_num))

    # Adding all the digits multiplied by 2 together
    sum1 = 0
    for number in multiplied_num:
        for digit in number:
            sum1 += int(digit)

    return sum1


def sum_non_multiplied_digits(reversed_num):
    # Creating a list of digits not multiplied by 2
    other_num = []
    for digit in reversed_num[0::2]:
        other_num.append(digit)

    # Adding all the digits not multiplied by 2 together
    sum2 = 0
    for number in other_num:
        sum2 += int(number)

    return sum2


def determine_card_type(num, num_len, final_sum):

    # Determine correct card type
    if final_sum % 10 == 0:
        if num_len == 15 and num[0] == 3 and (num[1] == 4 or num[1] == 7):
            print("AMEX")
        elif num_len == 16 and num[0] == 5 and (num[1] in range(1, 6)):
            print("MASTERCARD")
        elif ((num_len == 13 or num_len == 16) and num[0] == 4):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
        return 1


if __name__ == "__main__":
    main()
