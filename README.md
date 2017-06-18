SPLIT
============

Uses SFML, sfeMovie, and Google's protocol buffers.

Install the necessary libraries:

- `brew install sfml`
- `brew install protobuf --with-python3`


`make protobuf` then `make` to build the project.
`make run` will run the compiled executable, `make fs` will run in fullscreen
mode.

Use `make editor` to run the python level editor.
Use `make editor ARG=003.dat` to create a new file, otherwise it will
let you choose from existing files.

Use `make nomovie` to build without `sfeMovie` installed.
You may need to run `make cleanmovie` first.
(sfeMovie must be built against the same version of SFML you are
building against, so it typically has to be built manually.)
