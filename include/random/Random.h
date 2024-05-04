#include <ctime>
#include <array>

using namespace std;
// Генератор случайных чисел на основе алгоритма Мерсенна-Твистера
class MersenneTwister {
private:
    static constexpr unsigned int N = 624;
    static constexpr unsigned int M = 397;
    static constexpr unsigned int MATRIX_A = 0x9908b0df;
    static constexpr unsigned int UPPER_MASK = 0x80000000;
    static constexpr unsigned int LOWER_MASK = 0x7fffffff;

    unsigned int mt[N];
    unsigned int index;

public:
    MersenneTwister(unsigned int seed) {
        mt[0] = seed;
        for (unsigned int i = 1; i < N; ++i) {
            mt[i] = 1812433253 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
        }
        index = N;
    }

    unsigned int extractNumber() {
        if (index >= N) {
            generateNumbers();
        }

        unsigned int y = mt[index];
        y ^= (y >> 11);
        y ^= ((y << 7) & MATRIX_A);
        y ^= ((y << 15) & 0xefc60000);
        y ^= (y >> 18);

        ++index;

        return y;
    }

private:
    void generateNumbers() {
        for (unsigned int i = 0; i < N; ++i) {
            unsigned int y = (mt[i] & UPPER_MASK) + (mt[(i + 1) % N] & LOWER_MASK);
            mt[i] = mt[(i + M) % N] ^ (y >> 1);
            if (y % 2 != 0) {
                mt[i] ^= 0x9908b0df;
            }
        }
        index = 0;
    }
};

// Функция для генерации случайного перемешивания массива
void shuffleArray(array<char, 8>& array){
    // Получаем текущее время в секундах
    std::time_t currentTime = std::time(nullptr);

    MersenneTwister mt(static_cast<unsigned int>(currentTime));

    // Перемешиваем массив
    for (int i = 7; i > 0; --i) {
        int j = mt.extractNumber() % (i + 1);
        swap(array[i], array[j]);
    }
}