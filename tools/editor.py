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

level.texture = get.filename("art/room", "Select the background image:",
                             default=level.texture)

print("\nBOUNDARY RECTANGLES:")
print("\n".join([str(i) for i in level.bounds]))
del level.bounds[:]
get.another(lambda:
            pb.rect(level.bounds.add(),
                    get.number("x:"),
                    get.number("y:"),
                    get.number("width:", True),
                    get.number("height:", True)))

level.playerVisibility = True
level.inputMode = pb.Level.Player

print("\nPLAYER START POSITION")
level.starts[0].x = get.number("x")
level.starts[0].y = get.number("y")

print("\nENTITIES")


fd = open(fn, "wb")
fd.write(level.SerializeToString())
fd.close()
