#!/usr/bin/env python3

import sys, os, webbrowser, threading, time

from toollib import get, level, put

from visual.ve import app

def synchronize():
    put.system("git pull")
    os.execv(sys.executable, ["python3"] + sys.argv + ["restart"])

def openvisual():
    time.sleep(0.5)
    put.system("open http://localhost:5000/")
    
def visualeditor():
    threading.Thread(target=openvisual).start()
    app.run()
    print()
    
MAIN_MENU = get.make_menu(
    ("Level Editor", level.edit),
    ("Visual Editor (Opens in Web Browser)", visualeditor),
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
