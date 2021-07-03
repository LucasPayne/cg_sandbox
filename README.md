# cg_sandbox
cg_sandbox is a framework to assist in the development of real-time graphics applications.
The main goal is to be a small, easy-to-extend base of fundamental systems (such as an entity and behaviour system and an input and loop callback system)
for study and experimentation in computer graphics.

# Dependencies
- glfw3

# Source code structure
- examples/: Example applications compiled alongside the library.
- src/: The core source code.
- include/: The core header files. Application programs must include "cg_sandbox.h".
- lib/: Separated internal libraries. These are specific-purpose modules, such as data structures and basic OpenGL utilities.
- dependencies/: External dependencies in the form of git submodules.


