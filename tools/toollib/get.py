
import os

QUESTION_ENDING = "? "
FILLIN_ENDING = ": "
DEFAULT_FORMAT = "{} [{}]"

def getq(title, default=None):
    print(DEFAULT_FORMAT.format(title, default) if default else title,
          end=FILLIN_ENDING)
    try:
        return input()
    except EOFError:
        print("\n\nCanceled. Quitting...")
        exit(0)

def menu(choices=("Cancel",), title="Choose an option", value=False,
         default=None):
    choices = tuple(choices)
    print()
    for i, c in enumerate(choices):
        print("{{: {}}}. {{}}".format(len(str(len(choices)))).format(i+1, c))
    print()
    res = 0
    while not res:
        inp = getq(title, default)
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
            print("Invalid choice! Try again...")
    if value:
        return choices[res - 1]
    else:
        return res - 1

def number(title="Enter a float", positive=False, default=None):
    res = None
    while res is None:
        inp = getq(title, default)
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

def string(title="Enter a string", default=None):
    res = None
    while res is None:
        inp = getq(title, default)
        if not res and default:
            res = default
    return res

Y = "y"
N = "n"
CHOICES = { Y : True, N : False }
def yesno(title="Are you sure", yesno=" [{y}/{n}]", default=N):
    yn = yesno.format(y=Y.upper() if default == Y else Y,
                      n=N.upper() if default == N else N)
    res = False
    while not res:
        print(title + yn, end=QUESTION_ENDING)
        res = input().lower()
        if not res:
            res = default
        elif len(res) > 1:
            res = res[0]
        if not res in CHOICES:
            print("Invalid response! Please enter yes or no...")
            res = False
    return CHOICES.get(res)

def another(func, title="Enter more", prompt=False, default=N):
    another = yesno(prompt, default=default) if prompt else True
    while another:
          func()
          another = yesno(title, default=default)
          
def filename(folder=".", title="Choose a file", default=None, complete=False):
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
