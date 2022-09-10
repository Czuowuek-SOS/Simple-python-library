from distutils.core import setup, Extension
import os

def main():
    setup(name="CLib",
          version="1.0.0",
          author="Jaroz",
          ext_modules=[Extension("CLib", [".\\src\\main.cpp"])])

if __name__ == "__main__":
    main()
    os.system("move .\\build\\lib.mingw_x86_64-3.9\\CLib.cp39-mingw_x86_64.pyd .\\CLib.pyd")