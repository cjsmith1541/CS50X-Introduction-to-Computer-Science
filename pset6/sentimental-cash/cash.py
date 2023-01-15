from cs50 import get_float


def main():
    cents = get_cents()

    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    pennies = calculate_pennies(cents)
    cents -= pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(coins)


def get_cents():
    while True:
        cash = get_float("Change owed: ")
        if cash > 0:
            cash *= 100
            return cash


def calculate_quarters(cents):
    quarter = cents // 25
    return quarter


def calculate_dimes(cents):
    dime = cents // 10
    return dime


def calculate_nickels(cents):
    nickel = cents // 5
    return nickel


def calculate_pennies(cents):
    pennie = cents
    return pennie


main()