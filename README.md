
![](https://img.shields.io/badge/stable-0.1.1-f65) ![](https://img.shields.io/github/license/acrylic-os/packager)

# Acrylic packager

This is a simple command-line tool that packages and unpackages `.acr` (Acrylic) packages.

Acrylic packages are actually just JSON files. In the JSON is an object, with the keys being the file paths and the values being the file contents.

For writing and reading JSON, this tool uses [nlohmann/json](https://github.com/nlohmann/json), which is put in `include/json.hpp`.

## Compiling

**On Linux:**
1. Clone the repo
2. Get GCC if you don't already have it
3. `g++ src/acr.cpp -o acr`

**On Windows:**\
Just do the same thing but with MinGW

## Examples

### Packaging

To package the folder `sample` into an Acrylic package:
```
./acr -p sample
```

You can also specify an output filename:
```
./acr -p sample coolname
```

### Extracting

To extract the package `sample.acr` back into a normal folder:
```
./acr -e sample.acr
```

Once again, you can also specify an output filename:
```
./acr -e sample.acr coolname
```

### Other things

To get the help menu:
```
./acr -h
```

To get version info:
```
./acr -v
```


