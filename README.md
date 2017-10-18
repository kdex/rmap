# rmap
`rmap` is a range extractor and address mapping generator. It can be used to significantly reduce the filesize of arbitrary files without changing the code that accesses them. To achieve this, `rmap` doesn't compress your file, but rather extracts specified byte ranges which are then contiguously placed in a dump. Moreover, `rmap` generates an address mapper that takes the *original file offset address* and maps it to a *dump file offset address*. Depending on the options provided, the address mapper can be emitted as a C/C++ header file or as an ECMAScript module.
![2017-10-18-01-54-](https://user-images.githubusercontent.com/4442505/31694914-4e943210-b3a7-11e7-98cf-773e420fb13d.png)
## Inputs
- A file from which you need to generate a partial dump
- A file containing the range offsets that need to be placed in the resulting dump
## Outputs
- A dump that contains only the ranges specified
- An address mapper that converts an address from *file space* into *dump space*

## Address mappers
The generated files can be consumed as headers/modules.
### C API
```c
/*
* `location` denotes a location that you need to map to a dump address.
* `mappedLocation` will contain the result, if successful.
* The return value is `false` when the lookup has failed.
*/
bool toDumpSpace(size_t location, size_t *mappedLocation);
```
### C++ API
```c++
/*
* `location` denotes a location that you need to map to a dump address.
* The return value is the dump address.
* If `location` is not in the dump, this function throws.
*/
std::size_t toDumpSpace(std::size_t location);
```
### ECMAScript API
```js
/*
* `location` denotes a location that you need to map to a dump address.
* The return value is the dump address.
* If `location` is not in the dump, this function throws.
* Input and output values are of type `Number`.
*/
export const toDumpSpace = const location => { … };
```