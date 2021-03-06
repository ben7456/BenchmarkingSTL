// ParallelSTL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

//volatile int sink;
int main()
  {
  const auto memorySizeGB = 6ull;
  const auto count = memorySizeGB * 1000 * 1000 * 1000 / sizeof(int);
  std::cout.imbue(std::locale(""));
  std::cout << "Time to operate on a vector of " << count << " ints (which uses " << memorySizeGB << "GB of memory):" << std::endl;
  for (auto i = 0; i < 10; i++)
    {
    // Construct vector of integers
    std::vector<int> v(count);
    //std::vector<int> v2(size);

    // Fill the vector
    std::iota(std::begin(v), std::end(v), 0);

    /// Shuffle before std::sort
    //// Use a uniformly-distributed integer random number generator that produces non-deterministic random numbers
    //std::random_device randomDevice;
    //// Use a random number engine based on Mersenne Twister algorithm
    //std::mt19937 randomEngine(randomDevice());
    //// Shuffle elements in the vector
    //std::shuffle(std::begin(v), std::end(v), randomEngine);
    // record start time

    const auto start = std::chrono::high_resolution_clock::now();

    // Measuring different algorithms

    // Sort: par_unseq (same as par) is 4.5 times faster than seq (same as no execution policy)
    //std::sort(std::execution::par_unseq, std::begin(v), std::end(v));

    // Transform into the same vector: par_unseq and par are 2.86 times faster than seq and no execution policy
    // Transform into a different vector: par_unseq and par are 1.5 times faster than seq and no execution policy
    //std::transform(std::execution::par_unseq, std::begin(v), std::end(v), std::begin(v2), [](auto element) { return element + 2; });

    // for_each is 1.46 times faster par_unseq and par are 1.46 times fasterthan seq and no execution policy
    std::for_each(std::execution::par_unseq, std::begin(v), std::end(v), [](auto& element) { element += 2; });

    // record end time
    const auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Round " << i << ": " << diff.count() << " s" << std::endl;
    }
  }