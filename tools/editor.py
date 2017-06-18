#!/usr/bin/env python3

import sys

from toollib import pb, get

level = pb.Level()
try:
    fd = open(sys.argv[1], "rb")
    level.ParseFromString(fd.read())
    fd.close()
    parsed = True
except Exception:
    parsed = False

level.texture = get.filename("art/room")

print("\nBOUNDARY RECTANGLES:")
print("\n".join([str(i) for i in level.bounds]))
del level.bounds[:]
another = True
while another:
    pb.rect(level.bounds.add(),
            get.number("x:"),
            get.number("y:"),
            get.number("width:", True),
            get.number("height:", True))
    another = get.another()
                    
level.playerVisibility = True
level.inputMode = pb.Level.Player

print("\nPLAYER START POSITION")
level.starts[0].x = get.number("x")
level.starts[0].y = get.number("y")

fd = open(sys.argv[1], "wb")
fd.write(level.SerializeToString())
fd.close()
