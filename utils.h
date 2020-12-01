//
//  utils.h
//  stacks_n_queues
//
//  Created by William McCarthy on 267//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef __utils_h__
#define __utils_h__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>

#define ARGC_ERROR  1
#define FILENAME_ERROR  2

template <typename T>
bool less(T& v, T& w) { return v < w; }

template <typename T>
bool compare(T& v, T& w) {
  int result;

  if (less(v, w))        { result = -1;
  } else if (less(w, v)) { result = 1;
  } else                 { result = 0; }

  return result;
}


template <typename T>
void exchange(T* a, size_t i, size_t j) {
  T swap = a[i];
  a[i] = a[j];
  a[j] = swap;
}


template <typename T>
bool is_sorted(T* a, size_t low, size_t high) {
  for (size_t i = low + 1; i < high; ++i) {
    if (less(a[i], a[i - 1])) { return false; }
  }
  return true;
}
template <typename T>
bool is_sorted(T* a, size_t size) { return is_sorted(a, 0, size - 1); }

//==========================================================================


#endif /* __utils_h__ */
