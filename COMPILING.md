# Compiling

This file will document the process of compiling this project from source.

## Requirements

### Xmake

[Xmake](https://xmake.io/#/) is the build system used for this project.
It facilitates compiling the module across Windows/Linux/macOS with a single
configuration script written in Lua.

Xmake can be installed by downloading a release from
[GitHub](https://github.com/xmake-io/xmake/releases).

If you are using Linux, it is recommended to install Xmake from the official
repositories of your distribution, if possible. Other installation methods
are documented [here](https://xmake.io/#/guide/installation).

### Compiler

In addition to Xmake, you will also need a C++ compiler to do the actual
compiling.

The following are the standard toolchains for each operating system, and are
recommended for this project:

+ Windows: [Microsoft Visual C++](https://visualstudio.microsoft.com/vs/features/cplusplus/)
+ Linux: [GNU Compiler Collection](https://gcc.gnu.org/)
+ macOS: [LLVM](https://llvm.org/)

> **NOTE**: It is possible to use alternative toolchains, e.g. GCC/LLVM on Windows,
LLVM on Linux, GCC on macOS etc. but this is outside the scope of this project.

> **NOTE**: Cross compilation is not supported at this time.

### ALSA (Linux)

For Linux, make sure the ALSA library and development files (i.e. headers) are
installed.

The ALSA library should normally be installed already on a desktop setup,
usually from a package called `alsa-lib`, however the development files may
be packaged separately and need to be installed manually. Consult your
distribution for more information.

## Building

Once the above requirements are satisfied, building the module is as simple as
opening a terminal, changing the directory to the root of this repository, and
running:

```bash
$ xmake
```

This will build the module in release mode for the operating system and
architecture you're building on.

This means that if you're on a 64-bit machine (which you probably are), Xmake
will build the project for use on the 64-bit version of Garry's Mod by default.

The default branch of Garry's Mod is the 32-bit version. So, if you want to
build the module for the 32-bit version of Garry's Mod, you need to tell Xmake:

```bash
$ xmake f -a x86
```

The `f` is an alias for the `config` action, which is used to configure the
build process.

The `-a` option specifies the architecture to build for. In this case, `i386`
means a 32-bit binary will be produced on Linux. On Windows, `x86` is used
instead.

> **NOTE**: Only the 64-bit version of Garry's Mod can run on macOS, therefore
only the `x86_64` architecture can be specified to Xmake.

After the module has successfully built, it will be written to the `build`
directory in the root directory of the repository, which you can then install
to your Garry's Mod installation in the `garrysmod/lua/bin` directory, relative
to the game's root directory. If the `bin` directory does not exist, simply
create it.
