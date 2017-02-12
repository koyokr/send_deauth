# Send Deauth
need
```
cmake
libtins
c++14
```

build
```
./build.sh
```

run
```
cd build
sudo ./send_deauth <interface name> <ap mac> [<station mac>]
```

example
```
sudo ./send_deauth wlan0 12:34:56:78:9A:BC
```

