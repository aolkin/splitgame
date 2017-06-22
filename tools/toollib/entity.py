
from collections import defaultdict

from . import pb, get, put

class Wrapper:
    nargs = 0
    sargs = 0
    
    def string(self, e):
        return "\"{}\" ({})".format(e.identifier, e.name)
        
    def display(self, e):
        put.less("\"{}\" ({}): ({}) [\"{}\"]".format(
            e.identifier, e.name,
            ", ".join([str(i) for i in e.nargs]),
            "\", \"".join([str(i) for i in e.sargs])))
        return False
    
    def check(self, e):
        return (len(e.nargs) >= self.nargs and
                len(e.sargs) >= self.sargs)
    
    def editnargs(self, e):
        get.another(pb.adder(e.nargs, get.number),
                    prompt="Enter float arguments", default=get.Y)
    
    def editsargs(self, e):
        get.another(pb.adder(e.sargs, get.string),
                    prompt="Enter string arguments", default=get.Y)

    def name(self, e):
        oldname = e.name
        CREATE = "Enter unknown type..."
        res = get.menu(WRAPPERS.keys(), "Select entity type", e.name,
                       create=CREATE)
        if res == CREATE:
            res = get.string("Enter unknown entity type")
        e.name = res
        return oldname != res
    
    def ident(self, e):
        oldname = e.identifier
        e.identifier = get.string("Name this entity, for reference", e.identifier)
        return oldname != e.identifier

    def menu(self):
        return get.make_menu(
            ("Display Entity Data", self.display),
            ("edit entity type...", self.name),
            ("edit entity reference name...", self.ident),
            #("edit float argument...", self.editfloat),
            #("edit string argument...", self.editstring),
            #("re-enter float arguments...", self.editnargs),
            #("re-enter string arguments...", self.editsargs)
        )
    
class Generic(Wrapper):
    nargs = 5
    sargs = 1

    def texture(self, e):
        if len(e.sargs) < 1:
            e.sargs.append("")
        oldt = e.sargs[0]
        if get.yesno("Use TextureCache"):
            e.sargs[0] = get.string("Enter the TextureCache identifier", e.sargs[0])
        else:
            e.sargs[0] = get.filename("art/entity", "Select the entity texture",
                                      default=e.sargs[0])
        return oldt != e.sargs[0]

    def menu(self):
        return super().menu() + get.make_menu(
            ("edit entity texture...", self.texture)
        )
    
wrapper = Wrapper()
WRAPPERS = {
    "generic": Generic()
}

def getwrapper(e):
    return WRAPPERS.get(e.name, wrapper)

def edit(e):
    dirty = False
    if not e.name:
        dirty = wrapper.name(e) or dirty
    if not e.identifier:
        dirty = wrapper.ident(e) or dirty
    put.clear()
    while True:
        print("\nEditing {}:".format(getwrapper(e).string(e)))
        try:
            f = get.menu(getwrapper(e).menu()).data
            try:
                dirty = f(e) or dirty
                put.clear()
            except get.Cancel:
                put.clear()
                print("\nAction cancelled...")
        except get.Cancel:
            if getwrapper(e).check(e):
                return dirty
            else:
                try:
                    if get.yesno("\n\nEntity is missing fields, exit anyway"):
                        return dirty
                except get.Cancel:
                    return dirty

