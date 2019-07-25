# Visual TORCS server

## Linux build & installation on Ubuntu 18.04

For Ubuntu 18.04, please proceed as follow:

### Step 1 - Install all necessary requirements

```
sudo apt-get install libglib2.0-dev  libgl1-mesa-dev libglu1-mesa-dev  freeglut3-dev  libplib-dev  libopenal-dev libalut-dev libxi-dev libxmu-dev libxrender-dev  libxrandr-dev libpng-dev
```

### Step 2 - Build VTORCS

```
$ export CFLAGS="-fPIC"
$ export CPPFLAGS=$CFLAGS
$ export CXXFLAGS=$CFLAGS
$ ./configure --prefix=$(pwd)/BUILD  # local install dir
$ make
$ make install
$ make datainstall
```

## Start VTORCS

Start VTORCS with `./torcs` on the commandline

Get to run the _quickrace_  in the menu - you won't be able to though, it will lock expecting a car to connect from the network. It's the sign that everything's good to go!
