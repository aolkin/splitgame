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

if get.yesno("Edit player start position"):
    level.starts[0].x = get.number("x")
    level.starts[0].y = get.number("y")

e = level.entities.add()
e.name = get.string("Entity type", "generic")
get.another(pb.adder(e.nargs, get.number),
            prompt="Enter float arguments")
e.sargs.append(get.filename("art/entity", "Select the entity texture"))
get.another(pb.adder(e.sargs, get.string),
            prompt="Enter string arguments")

fd = open(fn, "wb")
fd.write(level.SerializeToString())
fd.close()
