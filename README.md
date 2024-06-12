# Radix tree

> A prototype radix tree made with C++

## What

- This is a basic radix tree, or a compressed trie.
It is useful for quick text retrieval (hence the name trie in re_trie_val),
at time complexity O(l) where l is the length of the string to search.
- This is noticeably faster than a giant switch statement (which has time complexity
of O(n*l) where n is the number of valid strings).

## How

1. Run this, alongside the demo

- Make sure to have CMake installed. Compile with Clang or GCC.
  - In the [convenience script](cmake-default-init.sh), the chosen compiler is Clang.
  - Support for MSVC isn't considered. If you want to compile with MSVC, you need
  to manually edit the CMakeLists.

> [!IMPORTANT]
> On Windows, GCC and/or Clang can be downloaded and run using MSYS2.
> [Go to MSYS2's website for the installer](https://www.msys2.org/).
> After finishing installing, the UCRT64 terminal should open up.
> In this terminal, run the following to install:
>
> ```bash
> sudo pacman -Syuu
> sudo pacman -S mingw-w64-ucrt-x86_64-cmake \
> mingw-w64-ucrt-x86_64-clang
> sudo pacman -Syuu
>```

- Run:

```bash
./cmake-default-init.sh
./radix-test
# or ./radix-test.exe on Windows
```
