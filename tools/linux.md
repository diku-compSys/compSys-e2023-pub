# Linux tools -- Roll Your Own Toolchain on Linux

Given that the course will focus on Linux systems, rolling your toolchain is easy. Here is a conservative list of the software you'll need for this course:

  * `apt-get` is the general package manager for your
    Debian/Ubuntu. You can use it to install the following packages.
  * [GCC](https://gcc.gnu.org/) and
    [Binutils](https://www.gnu.org/software/binutils/)". On
    Debian/Ubuntu you get these with the `build-essential` package. On
    Arch Linux/Antergos this is called base-devel.
  * [GDB](https://www.gnu.org/software/gdb/). In most package managers
    this is called `gdb`.  You can also use
    [LLDB](https://lldb.llvm.org/) if you wish.
  * `make`. The build tool.  You also get this with the `build-essential` package.

Further, the following tools are recommended:

  * [Valgrind](http://www.valgrind.org/) for detecting memory errors
    in C programs.  Available as `valgrind` in most package managers.
