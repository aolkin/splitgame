#!/usr/bin/env python3

import sys, os

from toollib import get, level, put

def synchronize():
    put.system("git pull")
    os.execv(sys.executable, ["python3"] + sys.argv + ["restart"])

MAIN_MENU = get.make_menu(
    ("Level Editor", level.edit),
    ("Get Latest Code", synchronize),
    ("Run Game", put.make_system("./SPLIT"))
)

if "restart" in sys.argv:
    print("\nFinished. ", end="")
    get.goon()
    
put.clear()
print("\nWelcome!")
    
while True:
    print("\nPress Ctrl-D (EOF) to exit the current menu/action at any time.")
    try:
        f = get.menu(MAIN_MENU).data
    except get.Top:
        print("\n\nBye!\n")
        exit()
    try:
        put.clear()
        print()
        if not f():
            print()
            get.goon()
        put.clear()
    except get.Top:
        put.clear()
        print("\nCancelled...")
