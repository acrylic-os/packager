
![](https://img.shields.io/badge/stable-0.1.1-f65) ![](https://img.shields.io/github/license/acrylic-os/packager)

# Acrylic packager

This is a simple command-line tool that packages and unpackages `.acr` (Acrylic) packages. They are actually just JSON files which contain a object with the keys being the file paths and the values being the file contents.

For writing and reading JSON, this tool uses [nlohmann/json](https://github.com/nlohmann/json), which is put in `include/json.hpp`.

> [!NOTE]
> Acrylic itself currently doesn't have support for unpacking `.acr` packages. However, it'll be implemented very soon.

## Why?

Acrylic extensions that actually do something need to have multiple files.

The standard for bundling several files into 1 file, for Unix at least, is `.tar`. However, it has a lot of limitations (filenames can only be up to 100 characters, support in Windows is kinda bad, etc.)

Additionally, it would be easier to identify Acrylic extension files if they had their own extension, `.acr`, instead of being mixed in with all the other Unix compressed files.

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


