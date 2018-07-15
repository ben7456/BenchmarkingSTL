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
  for (auto i = 0; i < 10; i++)
    {
    for (auto size = 100000000ull; size <= 1000000000ull; size *= 10)
      {
      // Construct vector of integers
      std::vector<int> v(size);
      std::vector<int> v2(size);

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
      std::transform(std::execution::par_unseq, std::begin(v), std::end(v), std::begin(v2), [](auto element) { return element + 2; });

      // record end time
      const auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> diff = end - start;
      std::cout << "Time to fill and iterate a vector of "
        << size << " ints : " << diff.count() << " s\n";
      }
    std::cout << std::endl;
    }
  }