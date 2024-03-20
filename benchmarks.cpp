#include <benchmark/benchmark.h>
#include "linear_allocator.h"
#include "base_allocator.h"
#include "memory"

static void stl_allocator_test(benchmark::State& state){
    for (auto _ : state){
        {
            std::allocator<char> allocator_char;
            char* nums1 = allocator_char.allocate(100'000'000);
            char* nums2 = allocator_char.allocate(400'000'001);
            char* nums3 = allocator_char.allocate(499'999'999);
            allocator_char.deallocate(nums1, 100'000'000);
            allocator_char.deallocate(nums2, 400'000'001);
            allocator_char.deallocate(nums3, 499'999'999);
        }
    }
}
BENCHMARK(stl_allocator_test);

static void base_allocator_test(benchmark::State& state){
    for (auto _: state){
        {
            base_allocator<char> allocator_char_base;
            char* nums1 = allocator_char_base.allocate(100'000'000);
            char* nums2 = allocator_char_base.allocate(400'000'001);
            char* nums3 = allocator_char_base.allocate(499'999'999);
            allocator_char_base.deallocate(nums1, 100'000'000);
            allocator_char_base.deallocate(nums2, 400'000'001);
            allocator_char_base.deallocate(nums3, 499'999'999);
        }
    }
}
BENCHMARK(base_allocator_test);

static void lin_allocator_test(benchmark::State& state){
    for (auto _ : state){
        //Засунул в local scope, чтобы посчиталась работа деструктора
        {
            linear_allocator<char> my_allocator;
            char* nums1 = my_allocator.allocate(100'000'000);
            char* nums2 = my_allocator.allocate(400'000'001);
            char* nums3 = my_allocator.allocate(499'999'998);
        }
    }
}
BENCHMARK(lin_allocator_test);

BENCHMARK_MAIN();