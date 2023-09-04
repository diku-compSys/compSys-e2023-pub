# macOS tools -- Roll Your Own Toolchain

## Homebrew
Homebrew is a package manager (similar to apt on Linux) that contain ports of many Linux programs. When you get a new Mac, this should be the first program to install, as it is the most useful.

Install Homebrew ([http://brew.sh/](http://brew.sh/))

## GCC
As standard macOS is setup for using Clang and has even linked `gcc` to run an adapted version of `clang`. For the need in CompSys, there should be no significant difference, so we recommend staying with this. Just type `gcc`.


If you really want a real `gcc`, the easiest way is the following:

  ```
  brew install gcc
  brew install binutils
  ```
To set `gcc` as the compiler to be used, the easiest way is to set `CC=gcc-13`in your `makefile` (In this case assuming you have installed gcc version 13). 
You should also be able to run the real `gcc` with `gcc-13`

If the above does not work, or you still want to link `gcc` to the newly installed `gcc-13`, you should create a symbolic link between the location where `gcc-13` has been installed and the `gcc` terminal command. To do this run:
```
sudo ln -s $(which gcc-13) /usr/local/bin/gcc
```
Restart your terminal.
Running `gcc --version` should now print gcc and not clang.

First time Homebrew will install many needed programs (including compiling them for you system), so it can take a long time.

## Use LLDB instead of GDB

GDB (a C debugger) is tricky to get working on macOS.  Instead, you
should use LLDB (`lldb`), which has equivalent functionality for our
purposes, and almost the same commands.  [See this GDB to LLDB command
map](https://lldb.llvm.org/use/map.html), and note that you likely
need only a small fraction of these commands for CompSys.
