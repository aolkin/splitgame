#!/usr/bin/env python3

import sys, os

from toollib import get, level, put

MAIN_MENU = get.make_menu(
    ("Level Editor", level.edit),
)

put.clear()
print("\nWelcome!\n")
print("Press Ctrl-D (EOF) to exit the current menu/action at any time.")
while True:
    try:
        f = get.menu(MAIN_MENU).data
    except get.Cancel:
        print("\n\nBye!\n")
        exit()
    try:
        f()
        put.clear()
    except get.Cancel:
        put.clear()
        print("\nCancelled...")
