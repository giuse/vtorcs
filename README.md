# Visual TORCS server

### Linux installation (ubuntu)

```bash
sudo apt-get install libglib2.0-dev  libgl1-mesa-dev libglu1-mesa-dev  freeglut3-dev  libplib-dev  libopenal-dev libalut-dev libxi-dev libxmu-dev libxrender-dev  libxrandr-dev libpng12-dev 
./configure --prefix=$(pwd)/BUILD  # local install dir
make
make install
make datainstall
./torcs
```

Get to run the quickrace - you won't be able to though, it will lock expecting a car to connect from the network. It's the sign that everything's good to go!


