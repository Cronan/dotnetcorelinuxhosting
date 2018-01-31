# Hosting .NET Core in C++ on Linux

This project gives a worked example of how to start the .NET Core runtime from C++ on Linux/MacOs, create an initial application domain (AppDomain), and execute managed code in it.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* Linux or MacOs (code tested on Red Hat Enterprise Linux Server release 7.3 (Maipo))
* .NET Core 2.0
* Python (tested using 2.7.11)
* GCC

### Installing

Clone the repository

```
git clone <path_to_repo>
cd <repo_folder>/src
```

Modify the `clrFilesPath` variable in pynetinit.cpp as required, to point to your installed dotnet distribution.

Build the .NET .dll

```
dotnet build ./dotnet
```

Build the python extension (uses GCC)

```
python setup.py build_ext --inplace
```

Run python and call the test function

```
python
>>> import clr
>>> clr.sum(4,5)
9.0
```

## Authors

* **Ivan Cronyn** - *Initial work* - [Cronan on GitHub](https://github.com/Cronan)

## Acknowledgments

* Thanks to [Yi Zhan](https://github.com/yizhang82) for his article on [Embedding CoreCLR in your C/C++ application](http://yizhang82.me/hosting-coreclr)
* Thanks to the [Python for .Net](https://github.com/pythonnet/pythonnet) team