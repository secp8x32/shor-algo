Shor's Algorithm
================

This is a C++ implementation of Shor's algorithm, which is a quantum algorithm for factoring integers. The purpose of this project is to experiment with Shor's algorithm and gain a better understanding of its workings.

Getting Started
---------------

To get started with this project, you will need to have the following tools installed on your computer:

*   C++17 compiler (such as GCC or Clang)

Once you have these tools installed, you can clone the repository and build the project using the following commands:


```bash
git clone https://github.com/secp8x32/shor-algo.git
cd shor-algo
make
```

This will compile the project and generate an executable file called `shor`. You can then run the executable with the following command:


```
./shor
p = 16183 (14-bit prime)
q = 12689 (14-bit prime)
N = 205346087 (28-bit)
r = 2 (fixed for testing purpose)

found g = 81691783 for r = 2, such that g^r = 1 mod N and coprime with N
    N   = 205346087 (28-bit)
    sp  = 3
    g   = 81691783 (27-bit)
    t0  = 6673547409719089 (53-bit)
    p1  = 81691784
    p2  = 81691782
    p   = 16183 (14-bit)
    q   = 12689 (14-bit)
    p*q = 205346087 (28-bit)

found g = 123654304 for r = 2, such that g^r = 1 mod N and coprime with N
    N   = 205346087 (28-bit)
    sp  = 3
    g   = 123654304 (27-bit)
    t0  = 15290386897724416 (54-bit)
    p1  = 123654305
    p2  = 123654303
    p   = 12689 (14-bit)
    q   = 16183 (14-bit)
    p*q = 205346087 (28-bit)

```

The program will generate two p and q 14-bit random primes (14-bit is chosen to keep runtime lower) and calculate `N = p * q` and try to factor with `shor` algoritm and output the factors of the integer if they are found, or indicate that no factors were found. Note that the program may take a long time to run for large integers, as Shor's algorithm is known to be computationally intensive.

Acknowledgments
---------------

This project is inspired by this YouTube video, which provided a helpful introduction to [Shor's algorithm](https://en.wikipedia.org/wiki/Shor%27s_algorithm).

[![How Quantum Computers Break The Internet... Starting Now](https://img.youtube.com/vi/-UrdExQW0cs/0.jpg)](https://www.youtube.com/watch?v=-UrdExQW0cs)

License
-------

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Remarks
-------

You can customize this template as needed to reflect the specifics of your project. Be sure to include any relevant details about how the algorithm is implemented, what libraries or tools are used, and any other information that may be helpful to someone using or contributing to your project. Good luck!