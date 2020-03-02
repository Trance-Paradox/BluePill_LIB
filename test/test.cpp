#include <iostream>
#include <bitset>

using namespace std;

uint64_t st0 = 1470134824450120;
uint32_t timestamp1 = (uint32_t)st0;
uint32_t timestamp2 = st0 >> 32;

int main()
{
    uint16_t num = 0b1001;
    std::cout << std::bitset<16>(num)<<' '<<std::bitset<16>(~(~num<<6)) <<' '<<std::bitset<16>(~((num ^ 0xf)<<6));
}