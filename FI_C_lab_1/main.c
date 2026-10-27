#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define UINT_SIZE (sizeof(unsigned int) * 8) 

bool is_uint_binary_palindromic(unsigned int num);
int round_float(float num);
void test_13th_task();
void test_27th_task();

int main(void)
{
    //float num = 123 * 123 * 123.0513513 * 123*17;
    //printf("%f\n", num);
    test_13th_task();
    test_27th_task();
	return 0;
}

void test_13th_task()
{
    int values[] = { 0, 1, 3, 15, 85, 65, 21, 2, 4, 12 };
    int excepted[] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 };

    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        printf("[%u is binary palindromic] is %s referensed to %s.\n", values[i],
            is_uint_binary_palindromic(values[i]) ? "true" : "false",
            excepted[i] ? "true" : "false");
    }
}

bool is_uint_binary_palindromic(unsigned int num)
{
    if (num == 0)
        return true;

    char binary_num[UINT_SIZE + 1];
    int i = 0;
    unsigned int copy = num;

    while (copy > 0)
    {
        binary_num[i++] = (copy & 1) ? '1' : '0';
        copy >>= 1;
    }

    binary_num[i] = '\0';

    for (int j = 0; j < (i / 2); j++)
    {
        if (binary_num[j] != binary_num[i - j - 1])
            return false;
    }

    return true;
}

int round_float(float num)
{
    int sign = (num < 0.0f) ? -1 : 1;

    union {
        float f;
        uint32_t i;
    } u;

    u.f = (num < 0.0f) ? -num : num;

    uint32_t exponent_raw = (u.i >> 23) & ((1 << 8) - 1);
    int exponent = (int)exponent_raw - 127;

    if (u.i == 0) 
        return 0;

    if (exponent < 0) 
        return (u.f >= 0.5f) ? (1 * sign) : 0;

    if (exponent >= 23) 
        return (int)(u.f * sign);

    int fractional_bits = 23 - exponent;
    uint32_t mask = (~0u) << fractional_bits;
    uint32_t half = 1 << (fractional_bits - 1);

    u.i = (u.i + half) & mask;

    uint32_t result = (uint32_t)u.f;
    return result * sign;
}

void test_27th_task()
{
    float values[] = {
        0.0f, 0.4f, 0.5f, 0.6f,
        3.2f, 3.7f, 3.5f, 4.5f,
        -3.2f, -3.7f, -3.5f,
        10.0f, 100.9f };

    int expected[] =
    {
        0, 0, 1, 1,
        3, 4, 4, 5,
        -3, -4, -4,
        10, 101
    };

    int num_tests = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_tests; i++)
    {
        int result = round_float(values[i]);
        bool is_passed = (result == expected[i]);
        printf("[value %6.1f is %4d] actually expected: %4d\n",
            values[i],
            result,
            expected[i]);
    }
}