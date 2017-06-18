
from pb.level_pb2 import *
from pb.global_pb2 import *

def vector(v, x, y):
    v.x = x
    v.y = y
    return v

def rect(r, x, y, z, w):
    r.pos.x = x
    r.pos.y = y
    r.size.x = z
    r.size.y = w
    return r
