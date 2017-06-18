
import os

def menu(choices=("Cancel",), title="Choose an option:", value=False):
    choices = tuple(choices)
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
            print("Invalid choice! Try again...")
    if value:
        return choices[res - 1]
    else:
        return res - 1

def number(title="Enter a float:", positive=False):
    res = None
    while res is None:
        print(title, end=" ")
        inp = input()
        try:
            res = float(inp)
            if positive and res < 0:
                res = None
                raise RuntimeError()
        except RuntimeError:
            print("Input must be positive! Try again...")
        except ValueError:
            print("Invalid input! Please enter a float...")
    return res

def string(title="Enter a string:"):
    res = None
    while res is None:
        print(title, end=" ")
        res = input()
    return res

Y = "y"
N = "n"
def another(title="Enter more [{y}/{n}]?", default=N):
    CHOICES = { Y : True, N : False }
    print(title.format(y=Y.upper() if default == Y else Y,
                       n=N.upper() if default == N else N), end=" ")
    res = input().lower()
    return CHOICES.get(res, CHOICES[default])

def filename(folder=".", title="Choose a file:"):
    res = False
    path = ""
    while not res:
        items = map(lambda x: x.name if x.is_file() else x.name + "/",
                    os.scandir(folder))
        res = menu(filter(lambda x: not x.startswith("."), items),
                   title, True)
        if os.path.isdir(os.path.join(folder, res)):
            path += res
            folder = os.path.join(folder, res)
            res = False
    return os.path.join(path, res)
