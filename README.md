
![](https://img.shields.io/badge/stable-0.1.0-f65) ![](https://img.shields.io/github/license/acrylic-os/packager)

# Acrylic packager

This is a simple command-line tool that packages and unpackages `.acr` (Acrylic) packages.

Acrylic packages are actually just JSON files. In the JSON is an object, with the keys being the file paths and the values being the file contents.

## Compiling

1. Clone the repo
2. Get GCC if you don't already have it
3. `g++ src/acr.cpp -o acr`

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

