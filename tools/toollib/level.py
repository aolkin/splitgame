
from . import get, pb, entity, put

import os, subprocess

def edit():
    while True:
        try:
            put.clear()
            fn = get.filename("rooms", "Select a level",
                              complete=True, create="new level...")
            if not fn.endswith(".dat"):
                fn += ".dat"
            editmenu(fn)
        except get.Cancel:
            return True

def editmenu(fn):
    level = pb.Level()
    dirty = load(level, fn) == True
    if dirty:
        put.clear()
        print("\nCreating level {}.".format(fn),
              "Please enter all required information:")
        try:
            background(level, fn)
            bounds(level, fn)
            starts(level, fn)
            visibility(level, fn)
        except get.Cancel:
            print("\n\nCancelled level creation...\n")
            get.goon()
            return False
        print("\nRequired information entered...\n")
        get.goon()
    done = False
    put.clear()
    while not done:
        print("\nEditing {0}{1}:".format(fn, " * " if dirty else ""))
        try:
            f = get.menu(DIRTY_MENU if dirty else MENU,
                         "Choose an action").data
            try:
                newfn = f(level, fn)
                if type(newfn) == str:
                    fn = newfn
                    dirty = False
                elif newfn != False:
                    dirty = True
                put.clear()
            except get.Cancel:
                put.clear()
                print("\nAction cancelled...")
        except get.Cancel:
            if dirty:
                try:
                    if get.yesno("\n\nSave changes", default=get.Y):
                        save(level, fn)
                except get.Cancel:
                    pass
            done = True
    return True
            
def load(level, fn):
    try:
        fd = open(fn, "rb")
        level.ParseFromString(fd.read())
        fd.close()
        return fn
    except FileNotFoundError:
        return True

def revert(level, fn):
    if get.yesno("Discard changes without saving", default=get.Y):
        if load(level, fn) != True:
            return fn
        else:
            print("\nFile does not exist, cannot revert...\n")
            get.goon()
    return True
            
def background(level, fn):
    oldt = level.texture
    level.texture = get.filename("art/room", "Select the background image",
                                 default=level.texture)
    if oldt == level.texture:
        return False

def bounds(level, fn):
    if len(level.bounds):
        menu = map(lambda r: " {}x{} at ({}, {})".format(
            r.size.x, r.size.y, r.pos.x, r.pos.y), level.bounds)
        index = get.menu(menu, "Select a boundary",
                         create="add a boundary...", value=False)
    else:
        print("\nAdd a new boundary:")
        index = -1
    if index < 0:
        index = len(level.bounds)
        level.bounds.add()
    b = level.bounds[index]
    pb.rect(b,
            get.number("X coordinate", default=b.pos.x),
            get.number("Y coordinate", default=b.pos.y),
            get.number("Width", default=b.size.x if b.size.x else None),
            get.number("Height", default=b.size.y if b.size.y else None))

def starts(level, fn):
    if len(level.positions):
        menu = map(lambda x: "({}, {})".format(x.x, x.y), level.positions)
        start = get.menu(menu, "Select a start position",
                         create="add a start position...", value=False)
    else:
        print("\nAdd a new start position:")
        start = -1
    if start < 0:
        start = len(level.positions)
        level.positions.add()
    s = level.positions[start]
    pb.vector(s,
              get.number("X coordinate", default=s.x),
              get.number("Y coordinate", default=s.y))

def entities(level, fn):
    menu = map(lambda x: "{} ({})".format(x.identifier, x.name),
               level.entities)
    ent = get.menu(menu, "Select an entity", create="add an entity...",
                   value=False)
    if ent < 0:
        return entity.edit(level.entities.add())
    else:
        return entity.edit(level.entities[ent])

def visibility(level, fn):
    oldval = level.playerVisibility
    level.playerVisibility = get.yesno("\nIs the player visible", default=get.Y)
    return oldval != level.playerVisibility

def save(level, fn):
    level.inputMode = pb.Level.Player
    
    fd = open(fn, "wb")
    fd.write(level.SerializeToString())
    fd.close()
    return fn

def save_as(level, fn):
    fn = get.filename(os.path.dirname(fn), "Save level as",
                      os.path.basename(fn), True, "enter filename...")
    return save(level, fn)

def display(level, fn):
    put.less(pb.MessageToJson(level))
    return False
    
MENU =  get.make_menu(
    ("edit background...", background),
    ("edit player visibility...", visibility),
    ("edit boundaries...", bounds),
    ("edit start positions...", starts),
    ("edit entities...", entities),
    ("Display Data", display)
)

DIRTY_MENU = MENU + get.make_menu(
    ("Revert to Saved", revert),
    ("Save", save),
    ("Save As", save_as),
)

