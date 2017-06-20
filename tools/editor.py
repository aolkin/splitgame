#!/usr/bin/env python3

import sys

from toollib import pb, get

fn = sys.argv[1] if len(sys.argv) > 1 else get.filename("rooms", complete=True)

level = pb.Level()
try:
    fd = open(fn, "rb")
    level.ParseFromString(fd.read())
    fd.close()
    parsed = True
except Exception:
    parsed = False

level.texture = get.filename("art/room", "Select the background image",
                             default=level.texture)

if get.yesno("Edit boundaries"):
    print("\n".join([str(i) for i in level.bounds]))
    del level.bounds[:]
    get.another(lambda:
                pb.rect(level.bounds.add(),
                        get.number("x"),
                        get.number("y"),
                        get.number("width", True),
                        get.number("height", True)))

level.playerVisibility = True
level.inputMode = pb.Level.Player

def editstart():
    i = int(get.number("Enter start id"))
    pb.vector(level.starts[i],
              get.number("x", default=level.starts[i].x),
              get.number("y", default=level.starts[i].y))

if get.yesno("Edit player start position"):
    print("\n".join([
        "{}:\t".format(i) +
        str(level.starts[i]).replace("\n","\n\t") for i in level.starts]))
    get.another(editstart)

def addentity():
    e = level.entities.add()
    e.name = get.string("Entity type", "generic")
    get.another(pb.adder(e.nargs, get.number),
                prompt="Enter float arguments", default=get.Y)
    if e.name == "generic":
        e.sargs.append(get.filename("art/entity", "Select the entity texture"))
    get.another(pb.adder(e.sargs, get.string),
                prompt="Enter string arguments", default=get.Y)
get.another(addentity, "Add another entity", prompt="Add an entity")

print()
if get.yesno("Display level data"):
    print(pb.MessageToJson(level))

if get.yesno("Save level data", default=get.Y):
    fd = open(fn, "wb")
    fd.write(level.SerializeToString())
    fd.close()
