
import os

def menu(choices=("Cancel",), title="Choose an option:", value=False,
         default=None):
    choices = tuple(choices)
    print()
    for i, c in enumerate(choices):
        s = "{{: {}}}. {{}}".format(len(str(len(choices)))).format(i+1, c)
        if i == default or c == default:
            print("[{} ]".format(s))
        else:
            print(" {}".format(s))
    print()
    res = 0
    while not res:
        print(title, end=" ")
        inp = input()
        if not inp and default:
            if type(default) == int:
                inp = default
            else:
                inp = choices.index(default) + 1
        try:
            res = int(inp)
            if not (0 < res < len(choices) + 1):
                res = 0
                raise RuntimeError()
        except Exception as err:
            print(repr(err))
            print("Invalid choice! Try again...")
    if value:
        return choices[res - 1]
    else:
        return res - 1

def number(title="Enter a float:", positive=False, default=None):
    res = None
    while res is None:
        print(title, end=" ")
        inp = input()
        if not inp and default:
            inp = default
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

def string(title="Enter a string:", default=None):
    res = None
    while res is None:
        print(title, end=" ")
        res = input()
        if not res and default:
            res = default
    return res

Y = "y"
N = "n"
def yesno(title="Are you sure {}?", yesno="[{y}/{n}]", default=N):
    CHOICES = { Y : True, N : False }
    yn = yesno.format(y=Y.upper() if default == Y else Y,
                      n=N.upper() if default == N else N)
    print(title.format(yn, end=" "))
    res = input().lower()
    return CHOICES.get(res, CHOICES[default])

def another(func, title="Enter more {}?", default=N):
    another = True
    while another:
          func()
          another = yesno(title, default=default)
          
def filename(folder=".", title="Choose a file:", default=None, complete=False):
    res = False
    path = ""
    while not res:
        items = map(lambda x: x.name if x.is_file() else x.name + "/",
                    os.scandir(folder))
        res = menu(filter(lambda x: not x.startswith("."), items),
                   title, True, default=default)
        if os.path.isdir(os.path.join(folder, res)):
            path += res
            folder = os.path.join(folder, res)
            res = False
    if complete:
        return os.path.join(folder, res)
    else:
        return os.path.join(path, res)
