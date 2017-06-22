
import sys, os, subprocess

def clear():
    subprocess.run(["clear"])

def less(text):
    subprocess.run(["less"], input=text,
                   universal_newlines=True)
