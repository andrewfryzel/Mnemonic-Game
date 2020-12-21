# Mnemonics Game
A simple educational game, written in C++
using Qt 5.12.

## Building
Box2D code is injected manually into the project.
Note that this project requires the use of Qt version 5.13.
You may need to install it from a PPA (for Ubuntu-based Linux distributions),
or build Qt from source.

For Debianoids (Ubuntu, Linux Mint, Knoppix, etc.), you'll need to
either upgrade your operating system to a more recent one, install a
PPA for a more recent version of Qt, or build it from source. At this time,
only Ubuntu 18.04 is supported if the required version of Qt is installed.
Other than this, the project is known to build on Ubuntu 19.10 with
the supplied version of Qt from the package manager.

For RHEL based systems (CentOS, Scientific Linux, Fedora, etc.), 
you'll need to use either `yum` or `dnf`, depending
on your specific version of your operating system.
You'll most likely want to build Qt from source, or fetch a pre-built
version of the libraries, especially for CentOS and RHEL proper.
Other than this, the supplied libraries from Fedora Rawhide and Fedora 30+
will most likely work.

For OpenSUSE based systems, you'll want to follow the same steps as
RHEL, except with using `zypper` instead.

For Arch-based systems, you'll want to install Qt 5.
At this time, no packages from the AUR are required.

For ReactOS-like systems (Such as NT), since no package manager is
available by default in a consistent and clear manner, you'll probably
want to download a pre-built EXE package for Qt, and use it's DLLs.
It's possible that this application can be built for ReactOS-like systems
using MinGW, and several ports of Unixen tools. A source of the appropriate 
DLLs may be from Cygwin libraries. This configuration is absolutely not 
supported. Because dependency management is very hard for ReactOS-like
systems, this configuration is strongly recommended against.

For XNU/Darwin based systems, you'll probably wish to install a package manager
such as `brew`. From there, you'll probably want to
install the needed Qt5 packages. Look for your package manager's
documentation for more details. PureDrawin's implementation of OPENSTEP
appears complete enough to run Qt applications, but this is not yet
reproduced for this project. This configuration is not supported.

For FreeBSD-based systems, it is likely you can build by building both
sfml and qt5 from the ports tree. `cd` into `/usr/ports` and run
`find . | grep "qt5"` , and build components as appropriate, mostly from
`devel`. You'll also need a valid X server installed, preferably with
video acceleration.

For OS/2 based systems, since upstream Qt no longer supports this platform,
it is expected that this application will never run on OS/2. Likewise
for other platforms in a similar state such as BeOS. However, it appears
that some initial porting work was done to bring Qt 5 applications to
Haiku. For a *technically* "BeOS" port, it may be possible to build
under Haiku with enough Unixen compatibility used.


## Running
You'll want to run the project inside Qt Creator, and from there click on
'Run', if already configured. It is possible with a fresh clone that
the project needs to be reconfigured with Qt Creator. To do so,
simply follow it's directions to generate a configuration, which should
be sufficient by default.

After this, the program will be available in an (unfortunately) same directory
build tree in the directory which was cloned. It may be desirable to package
up the application in there sans the MOC files and other unncessary data,
which should be sufficient to run.
