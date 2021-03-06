// STLContainers.cpp : Defines the entry point for the console application.
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
  using std::cout;
  using std::endl;

  const auto memorySizeMB = 400ull;
  const auto count = memorySizeMB * 1000 * 1000 / sizeof(int);
  cout.imbue(std::locale(""));
  cout << "Time to operate on a vector of " << count << " ints (which uses " << memorySizeMB << "MB of memory):" << endl;
  for (auto i = 0; i < 10; i++)
    {
    cout << "Round " << i << ":" << endl;
    using std::chrono::high_resolution_clock;

    // Constructing a vector of 100,000,000 integers is 50 times faster than list
    auto start = high_resolution_clock::now();
    std::vector<int> v(count);
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "  Construct a vector of " << count << " integers: " << diff.count() << " s" << endl;

    start = high_resolution_clock::now();
    std::list<int> l(count);
    end = high_resolution_clock::now();
    diff = end - start;
    cout << "  Construct a list   of " << count << " integers: " << diff.count() << " s" << endl;

    // iota a vector of 100,000,000 integers is 20 times faster than list
    start = high_resolution_clock::now();
    std::iota(std::begin(v), std::end(v), 0);
    end = high_resolution_clock::now();
    diff = end - start;
    cout << "  iota      a vector of " << count << " integers: " << diff.count() << " s" << endl;

    start = high_resolution_clock::now();
    std::iota(std::begin(l), std::end(l), 0);
    end = high_resolution_clock::now();
    diff = end - start;
    cout << "  iota      a list   of " << count << " integers: " << diff.count() << " s" << endl;

    //Shuffle before std::sort
    // Use a uniformly-distributed integer random number generator that produces non-deterministic random numbers
    std::random_device randomDevice;
    // Use a random number engine based on Mersenne Twister algorithm
    std::mt19937 randomEngine(randomDevice());
    // Shuffle elements in the vector
    std::shuffle(std::begin(v), std::end(v), randomEngine);
     //record start time


    //// Measuring different algorithms

    start = std::chrono::high_resolution_clock::now();
    //Sort: par_unseq (same as par) is 4.5 times faster than seq (same as no execution policy)
    std::sort(std::execution::par_unseq, std::begin(v), std::end(v));
    // record end time
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    cout << "  sort      a vector of " << count << " integers: " << diff.count() << " s" << endl;

    //// Transform into the same vector: par_unseq and par are 2.86 times faster than seq and no execution policy
    //// Transform into a different vector: par_unseq and par are 1.5 times faster than seq and no execution policy
    ////std::transform(std::execution::par_unseq, std::begin(v), std::end(v), std::begin(v2), [](auto element) { return element + 2; });

    //// for_each is 1.46 times faster par_unseq and par are 1.46 times fasterthan seq and no execution policy
    //std::for_each(std::execution::par_unseq, std::begin(v), std::end(v), [](auto& element) { element += 2; });

    }
  }