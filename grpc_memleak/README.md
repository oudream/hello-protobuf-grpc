# grpc_memleak
The python grpc code leaks memory when accessing a long stream of elements.
In this example the server creates an infinte stream of random numbers. The client prints every 10.000th number. There is no leak in the C++ client, only the python client leaks memory.

# Pre-requisites
The code was tested on Ubuntu 16.04 and python 3.5.2.
- Make sure you have grpc installed from [sources](https://github.com/grpc/grpc/blob/master/INSTALL.md)
- Install grpcio-tools for python
```sh
pip3 install grpcio-tools
```

# Clone and build

```sh
$ git clone https://github.com/d0m3nik/grpc_memleak.git
$ cd grpc_memleak
$ make
```

# Run the server
From within the build directory:
```sh
./randnum_server
```

# Run the C++ client
For reference run the C++ client:
```sh
./randnum_client
```
The client process does not leak memory.

# Run the Python client
To reproduce the leak run the python client:
```sh
python3 randnum_client.py
```

