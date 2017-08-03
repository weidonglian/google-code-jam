#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>

using namespace std;

/**	Easy way, but not optimal. */
uint64_t solve(uint64_t l_, uint64_t u_);

/**	Binary search to the most tight range. */
uint64_t quick_solve(uint64_t l_, uint64_t u_);

int main(int argc_, char** argv_) {
  int nb = 0;
  // Input
  cin >> nb;
  for(int i = 1; i <= nb; i++) {
    uint64_t n = 0;
    cin >> n;
    uint64_t ret = quick_solve(1, n);
    if(ret == 0) {
      cerr << "Unexpected return value for case #\n" << i;
    }
    // Output
    cout << "Case #" << i << ": " << ret << '\n';
  }
  return 0;
}

bool is_tidy(uint64_t n_) {
  if(n_ < 10)
    return true;

  ostringstream oss;
  oss << n_;
  string strnum = oss.str();

  for(size_t j = 0; j < strnum.size() - 1; j++) {
    if(strnum[j] > strnum[j + 1]) {
      return false;
    }
  }
  return true;
}

uint64_t next_tidy(uint64_t n_) {
  if(n_ < 10) {
    return n_ == 9 ? 11 : n_ + 1;
  } else {
    ostringstream oss;
    oss << n_;
    string strnum = oss.str();
    for(size_t j = 0; j < strnum.size() - 1; j++) {
      if(strnum[j] > strnum[j + 1]) {
        for(size_t k = j + 1; k < strnum.size(); k++) {
          strnum[k] = strnum[j];
        }
        istringstream iss(strnum);
        iss >> n_;
        return n_;
      }
    }
    return n_;
  }
}

uint64_t solve(uint64_t l_, uint64_t u_) {
  //cerr << "Testing:" << n_ << std::endl;
  for(uint64_t i = u_; i >= l_; i--) {
    if(is_tidy(i))
      return i;
  }
  return 0;
}

uint64_t quick_solve(uint64_t l_, uint64_t u_) {
  // Binary Search
  if(is_tidy(u_)) {
    return u_;
  } else if(u_ - l_ == 1) {
    if(is_tidy(l_))
      return l_;
    else
      return 0;
  } else {
    uint64_t m = l_ + (u_ - l_) / 2;
    uint64_t nextm = next_tidy(m);
    if(nextm < u_) {
      return quick_solve(nextm, u_);
    } else {
      return quick_solve(l_, m);
    }
  }
}