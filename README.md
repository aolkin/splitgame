SPLIT
============

Uses SFML, sfeMovie, and Google's protocol buffers.

Install the necessary libraries (on OSX):

- `brew install sfml`
- `brew install protobuf --with-python3`


`make protobuf` then `make` to build the project.
`make run` will run the compiled executable, `make fs` will run in fullscreen
mode.

Use `make editor` to run the python level editor.
Python 3.6 has been tested, requirements are in `tools/requirements.txt` in
pip-friendly form.
Use `make editor ARG={filename}.dat` to create a new file, otherwise it will
let you choose from existing files.

Use `make nomovie` to build without `sfeMovie` installed.
You may need to run `make cleanmovie` first.
(sfeMovie must be built against the same version of SFML you are
building against, so it typically has to be built manually.
It also requires SDL to be installed to use it, and a number of other
libraries to build it.)


Make Rules
------------

The makefile is setup to build on an OSX system.

- build (default): build the executable in debug mode with the movie enabled.
- all: build the protocol buffer code, the documentation, and the above.
- nodebug: build the executable without debugging code but with the movie.
- cleanmovie: delete object files that link the movie code so they will be
  rebuilt, used automatically when building without the movie, but must be run
  manually when switching to include the movie.
- run: builds the executable using the default rule, then runs it.
- fs: builds the executable using the default rule, then runs it in fullscreen
  mode.
- docs: builds the documentation then opens it in a web browser.
- docbuild: just builds the documentation.
- docbrowse: just opens the documentation in a web browser.
- protobuf: builds the protocol buffer c++ code.
- editor: runs the python level editor script.
- clean: removes all build artifacts, including the executable.
- cleanexe: deletes the executable.
- genclean: deletes generated files, such as protocol buffers code.
- cleanall: runs all three of the above rules.
