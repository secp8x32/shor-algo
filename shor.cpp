#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <inttypes.h>

using namespace std;
template <typename T>
class uniform_uint_distribution
{
public:
    using result_type = T;
    using param_type = std::pair<T, T>;

    uniform_uint_distribution(T a = 0, T b = std::numeric_limits<T>::max()) : m_a(a), m_b(b) {}

    void reset() {}

    param_type param() const
    {
        return param_type(m_a, m_b);
    }

    void param(const param_type &params)
    {
        m_a = params.first;
        m_b = params.second;
    }

    template <typename U>
    void generate(U &g, T &value)
    {
        do
        {
            value = static_cast<T>(g() - g.min()) + m_a;
        } while (value > m_b);
    }

    T operator()(std::mt19937_64 &g)
    {
        T value;
        generate(g, value);
        return value;
    }

    T min() const
    {
        return m_a;
    }

    T max() const
    {
        return m_b;
    }

private:
    T m_a;
    T m_b;
};

static std::random_device rd;
static std::mt19937 gen32(rd());
static std::mt19937_64 gen64(rd());
static std::uniform_int_distribution<uint32_t> dist32(0, std::numeric_limits<uint32_t>::max());
static uniform_uint_distribution<uint64_t> dist64(0, std::numeric_limits<uint64_t>::max());

uint64_t rand64()
{
    return dist64(gen64);
}

uint32_t rand32()
{
    return dist32(gen32);
}

uint64_t powerMod64(uint64_t x, uint64_t y, uint64_t p)
{
    uint64_t res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

bool millerTest64(uint64_t d, uint64_t n)
{

    uint64_t a = 2 + rand64() % (n - 4);

    uint64_t x = powerMod64(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    return false;
}

bool isPrime64(uint64_t n, int k = 50)
{
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    uint64_t d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
        if (!millerTest64(d, n))
            return false;

    return true;
}

int getBitLength32(uint32_t x)
{
    return 32 - __builtin_clz(x);
}

int getBitLength64(uint64_t x)
{
    return 64 - __builtin_clzll(x);
}

uint64_t pow64(uint64_t b, uint32_t e)
{
    uint64_t r = 1;
    while (e > 0)
    {
        if (e & 1)
        {
            r *= b;
        }
        b *= b;
        e >>= 1;
    }
    return r;
}

uint64_t mod64(uint64_t a, uint64_t b)
{
    while (a >= b)
    {
        a -= b;
    }
    return a;
}

bool isEven(uint64_t x)
{
    return ((x & 1) == 0);
}

uint64_t calculateSmallestPowerWhichExceeds64bit(uint64_t g)
{
    static const uint64_t MAX_UINT64 = std::numeric_limits<uint64_t>::max();
    return static_cast<uint64_t>(std::ceil(std::log(MAX_UINT64) / std::log(g)));
}

uint32_t randPrime32()
{
    uint32_t n = dist32(gen32);
    n |= 0x80000001;

    if (n % 2 == 0)
    {
        ++n;
    }
    while (!isPrime64(n))
    {
        n += 2;
    }
    return n;
}

uint32_t randPrime16()
{
    uint32_t n = dist32(gen32);
    n &= UINT16_MAX;
    n |= 0x8001;

    if (n % 2 == 0)
    {
        ++n;
    }
    while (!isPrime64(n))
    {
        n += 2;
    }
    return n;
}

uint32_t randPrime14()
{
    uint32_t n = dist32(gen32);
    n &= 0x3FFF;
    n |= 0x2001;

    if (n % 2 == 0)
    {
        ++n;
    }
    while (!isPrime64(n))
    {
        n += 2;
    }
    return n;
}

uint32_t getNextPrime32(uint32_t prime)
{
    uint32_t next = prime + 1;
    while (!isPrime64(next))
    {
        ++next;
    }
    return next;
}

int main()
{
    std::srand(std::time(nullptr));

    uint64_t p = randPrime14();
    uint64_t q = randPrime14();

    uint64_t N = p * q;

    int32_t r = 2;

    cout << "p = " << p << " (" << getBitLength64(p) << "-bit prime)" << endl;
    cout << "q = " << q << " (" << getBitLength64(q) << "-bit prime)" << endl;
    cout << "N = " << N << " (" << getBitLength64(N) << "-bit)" << endl;
    cout << "r = " << r << " (fixed for testing purpose)" << endl
         << endl;

    for (uint32_t g = 2; g < N - 1; g++)
    {
        uint32_t sp = calculateSmallestPowerWhichExceeds64bit(g);

        if (r < sp)
        {
            uint64_t gcd = std::gcd((uint64_t)g, N);

            if (gcd == 1)
            {
                uint64_t t0 = pow64(g, r); // g^r -> t0
                uint64_t t1 = t0 % N;      // t0 mod N -> t1
                uint64_t t2 = pow64(g, r / 2) % N;

                if (t1 == 1 && isEven(r) && t2 != 1 && t2 != N - 1)
                {
                    cout << "found g = " << g << " for r = " << r << ", such that g^r = 1 mod N and coprime with N" << endl;

                    uint64_t p1 = pow64(g, r / 2) + 1;
                    uint64_t p2 = pow64(g, r / 2) - 1;

                    uint64_t gcd1 = std::gcd(p1, N);
                    uint64_t gcd2 = std::gcd(p2, N);

                    cout << "    N   = " << N << " (" << getBitLength64(N) << "-bit)" << endl;
                    cout << "    sp  = " << sp << endl;
                    cout << "    g   = " << g << " (" << getBitLength64(g) << "-bit)" << endl;
                    cout << "    t0  = " << t0 << " (" << getBitLength64(t0) << "-bit)" << endl;
                    cout << "    p1  = " << p1 << endl;
                    cout << "    p2  = " << p2 << endl;
                    cout << "    p   = " << gcd1 << " (" << getBitLength64(gcd1) << "-bit)" << endl;
                    cout << "    q   = " << gcd2 << " (" << getBitLength64(gcd2) << "-bit)" << endl;
                    cout << "    p*q = " << p * q << " (" << getBitLength64(p * q) << "-bit)" << endl
                         << endl;
                }
            }
        }
    }

    return 0;
}
