# [WIP] Basic CMake

A CMake Starter Project, targeting to be easy to use with conan2 package manager.

The target of this project is:
- One should not worry about cmake comamnds to build project.
- One should not worry about conan commands and cmake syntax to install dependencies.

The project provide 2 scripts:

1. **update\_package** : That automatically installs package listed in `conanfile.txt`.
2. **build** : That automatically builds project and exports `compile_commands.json` in root directory.
