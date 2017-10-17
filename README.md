# rmap
`rmap` is a range mapper. It can be used to significantly reduce the filesize of arbitrary files without changing the code that accesses them. `rmap` doesn't compress your file, but extracts specified byte ranges which are then contiguously placed in a dump. Moreover, `rmap` emits an address mapper that takes the *original file offset address* and maps it to a *dump file offset address*. Depending on the options provided, the address mapper can be emitted as a C/C++ header file or as an ECMAScript module.

![rmap](https://user-images.githubusercontent.com/4442505/31670355-ae6b3d46-b357-11e7-9fc5-e3be00b9f3eb.png)

## Inputs
- A file from which you need to generate a partial dump
- A file containing the range offsets that need to be placed in the resulting dump

## Outputs
- A dump that contains only the ranges specified
- An address mapper that converts an address from "file space" into "dump space"
