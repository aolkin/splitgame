
import os

QUESTION_ENDING = "? "
FILLIN_ENDING = ": "
DEFAULT_FORMAT = "{} [{}]"

## Holds a string for display and data
class MenuChoice:
    def __init__(self, name, data):
        self.name = name
        self.data = data
        
    def __str__(self):
        return self.name

class Cancel(Exception): pass

## Takes an iterable of iterables, each one containing a string and data.
# Creates MenuChoice objects out of each inner iterable.
def make_menu(*args, backwards=False):
    return tuple(map(lambda x: MenuChoice(x[1], x[0])
                     if backwards else MenuChoice(x[0], x[1]),
                 args))

def getq(title, default=None):
    print(DEFAULT_FORMAT.format(title, default) if default else title,
          end=FILLIN_ENDING)
    try:
        return input()
    except EOFError as e:
        raise Cancel()

## Offers a list of choices to the user and allows them to enter the
#  number corresponding to their choice.
# \param choices Iterable of choices, will be displayed as strings.
# \param title The question that will be presented to the user for input.
# \param default If provided, the question will show the default value
#        and use it if the user enters nothing.
# \param create If provided, this should be a string, which will be
#        shown as option zero.
# \param value If set to false, this function will return the chosen index,
#        rather than the item from the iterable. The "create" choice, if
#        provided, will return -1.
def menu(choices, title="Choose an option", default=None, create=False,
         value=True):
    offset = 0 if create else 1
    if create:
        items = [create]
        items.extend(choices)
    else:
        items = tuple(choices)
    fmt = "{{: {}}}. {{}}".format(len(str(len(items))) - (1 if create else 0))
    print()
    for i, c in enumerate(items[1:] if create else items):
        print(fmt.format(i + 1, c))
    if create:
        print(fmt.format(0, create))
    print()
    res = offset - 1
    while res < offset:
        inp = getq(title, default)
        if not inp and default:
            if type(default) == int:
                inp = default
            else:
                inp = items.index(default) + offset
        try:
            res = int(inp)
            if not (offset - 1 < res < len(items) + offset):
                res = offset - 1
                raise RuntimeError()
        except Exception as err:
            print("Invalid choice! Try again...")
    if value:
        return items[res - offset]
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
        res = getq(title, default)
        if not res and default:
            res = default
    return res

## True value for get.yesno, can be used as a default
Y = "y"
## False value for get.yesno, can be used as a default
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
          
def filename(folder=".", title="Choose a file", default=None, complete=False,
             create=False):
    res = False
    path = ""
    while not res:
        items = map(lambda x: x.name if x.is_file() else x.name + "/",
                    os.scandir(folder))
        items = filter(lambda x: not x.startswith("."), items)
        res = menu(items, title, default, create)
        if res == create:
            res = string("Enter filename")
        if os.path.isdir(os.path.join(folder, res)):
            path += res
            folder = os.path.join(folder, res)
            res = False
    if complete:
        return os.path.join(folder, res)
    else:
        return os.path.join(path, res)
