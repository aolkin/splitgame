
from . import get, pb, entity, put

import os, subprocess

def edit():
    put.clear()
    fn = get.filename("rooms", "Select a level",
                      complete=True, create="new level...")
    level = pb.Level()
    load(level, fn)
    done = False
    dirty = False
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
    fd = open(fn, "rb")
    level.ParseFromString(fd.read())
    fd.close()
    return fn

def revert(level, fn):
    if get.yesno("Discard changes without saving", default=get.Y):
        load(level, fn)
        return fn
            
def background(level, fn):
    oldt = level.texture
    level.texture = get.filename("art/room", "Select the background image",
                                 default=level.texture)
    if oldt == level.texture:
        return False

## Edit level boundary rectangles
# \todo Make this nice
def bounds(level, fn):
    print("\n".join([str(i) for i in level.bounds]))
    del level.bounds[:]
    get.another(lambda:
                pb.rect(level.bounds.add(),
                        get.number("x"),
                        get.number("y"),
                        get.number("width", True),
                        get.number("height", True)))

def starts(level, fn):
    menu = map(lambda x: "({}, {})".format(x.x, x.y), level.positions)
    start = get.menu(menu, "Select a start position",
                     create="add a start position...", value=False)
    if start < 0:
        start = len(level.positions)
        level.positions.add()
    pb.vector(level.positions[start],
              get.number("X coordinate", default=level.positions[start].x),
              get.number("Y coordinate", default=level.positions[start].y))

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
    level.playerVisibility = get.yesno("Is the player visible", default=get.Y)
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

