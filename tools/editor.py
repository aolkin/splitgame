#!/usr/bin/env python3

def menu(choices=("Cancel",), title="Choose an option:"):
    print()
    for i, c in enumerate(choices):
        print("{}. {}".format(i+1, c))
    print()
    res = 0
    while not res:
        print(title, end=" ")
        inp = input()
        try:
            res = int(inp)
            if not (0 < res < len(choices) + 1):
                res = 0
                raise RuntimeError()
        except:
            print("Invalid input! Try again...")
    return res - 1

MAIN = ("Room Options (Size, Texture, Bounds)", "Player Options (Visibility, InputMode)", "Entities")
res = menu(MAIN)
print("Congrats, you chose {}.".format(MAIN[res]))
