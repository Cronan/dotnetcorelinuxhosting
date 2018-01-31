from distutils.core import setup, Extension

module1 = Extension('clr',
                    sources = ["clrmod.cpp", "pynetinit.cpp"],
                        extra_compile_args=['-std=c++11'])

setup(
    ext_modules=[module1]
)
