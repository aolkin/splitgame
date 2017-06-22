
import sys, os, subprocess, shlex

def system(cmd):
    subprocess.run(shlex.split(cmd))
    
def make_system(cmd):
    return lambda: system(cmd)

def clear():
    subprocess.run(["clear"])

def less(text):
    subprocess.run(["less"], input=text,
                   universal_newlines=True)

