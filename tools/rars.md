# Using [RARS](https://github.com/TheThirdOne/rars) - the RISC-V Assembler and Runtime Simulator

RARS is a RISC-V/32 simulator designed for teaching.  Many RISC-V
simulators exist, but RARS is particularly simple to use.  Its
graphical user interface supports single-stepping, rewinding, decent
error messages, and basic IO.  It can also be run from the command
line, which we will use for automatic testing.

## Installation

RARS is written in Java, and should run on all major operating
systems.  The precise version of Java should not matter.  If you can
run the `java` command in a terminal prompt, then you should be able
to run RARS.

### Installing Java on Windows

You should use the [Windows Subsystem for
Linux](https://docs.microsoft.com/en-us/windows/wsl/install) (WSL),
and then see [this guide on installing Java on
WSL](https://kontext.tech/article/621/install-open-jdk-on-wsl)

### Installing Java on macOS

If you have [Homebrew](https://brew.sh/), run:

    $ brew install openjdk

### Installing Java on Linux

If you run Debian, do

    $ sudo apt-get install default-jre

If you run Arch btw, do

    $ sudo pacman -S jre-openjdk

If you run [NixOS](https://nixos.org/) (the superior choice), just use
the `rars` derivation from Nixpkgs and don't worry about Java.  You
also don't need the `java -jar` business at all; just run `rars` on
the command line.

### Installing RARS

Once you have Java, download
[rars1_5.jar](https://github.com/TheThirdOne/rars/releases/download/v1.5/rars1_5.jar)
and run it as appropriate.  Either by double-clicking on it, or by
running the following command in a terminal:

    $ java -jar path/to/rars1_5.jar

You should see a GUI appear.  This is the default when no command line
options are passed.

## Using the RARS GUI

GUIs are supposed to be intuitive, so no instructions needed.

## Using the RARS command line

You can run a RISC-V program `prog.s` with RARS as follows:

    $ java -jar path/to/rars1_5.jar prog.s

If something is wrong, RARS will complain with details about when and
where.  The command line does not provide much debugging assistance,
so you might need to load your program into the RARS GUI and test it
there.

RARS supports various "environment calls" (usually called *system
calls*) for IO and similar.  They are [documented
here](https://github.com/TheThirdOne/rars/wiki/Environment-Calls), but
we will use only a few in this course, and they will be introduced as
needed.
