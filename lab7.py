
import math

def mod_exp(base, exp, mod):
    return pow(base, exp, mod)

def baby_step_giant_step(a, b, p):
    n = math.isqrt(p) + 1

    value_table = {}
    current = 1
    for j in range(n):
        value_table[current] = j
        current = (current * a) % p

    a_n = mod_exp(a, n * (p - 2), p)
    current = b
    for i in range(n):
        if current in value_table:
            return i * n + value_table[current]
        current = (current * a_n) % p

    return -1

if __name__ == "__main__":
    print("Розв'язувач задачі дискретного логарифма")
    try:
        a = int(input("Введіть основу (a): "))
        b = int(input("Введіть значення (b): "))
        p = int(input("Введіть модуль (p): "))

        if p <= 1:
            print("Модуль (p) має бути більше 1.")
        elif a <= 0 or b <= 0:
            print("Основа (a) та значення (b) мають бути додатними.")
        else:
            result = baby_step_giant_step(a, b, p)
            if result != -1:
                print(f"log_{a}({b}) mod {p} = {result}")
            else:
                print("Розв'язок не знайдено.")
    except ValueError:
        print("Будь ласка, введіть коректні цілі числа.")
