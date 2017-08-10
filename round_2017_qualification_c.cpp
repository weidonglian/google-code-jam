#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <tuple>
#include <assert.h>
#include <algorithm>

std::tuple<uint64_t, uint64_t> calc_ls_rs(const std::vector<bool>& s_, uint64_t i) {
  assert(i >= 0 && i < s_.size());
  uint64_t ls = 0;
  uint64_t rs = 0;
  for(uint64_t j = i - 1; j >= 0; j--) {
    if(s_[j])
      break;
    else
      ls++;
  }

  for(uint64_t k = i + 1; k < s_.size(); k++) {
    if(s_[k])
      break;
    else
      rs++;
  }
  return std::make_tuple(ls, rs);
}

uint64_t choose_position(const std::vector<bool>& s_) {
  uint64_t maxOfMinLsRs = 0; // keep track the max of min(Ls, Rs)
  uint64_t curMaxLsRs = 0; // keep track the current max (Ls, Rs)
  uint64_t curPosition = 0;
  uint64_t ls;
  uint64_t rs;
  for(uint64_t i = 0; i < s_.size(); i++) {
    if(!s_[i]) {
      std::tie(ls, rs) = calc_ls_rs(s_, i);
      uint64_t minLsRs = std::min(ls, rs);
      uint64_t maxLsRs = std::max(ls, rs);
      if(curPosition == 0 || minLsRs > maxOfMinLsRs || 
        (minLsRs == maxOfMinLsRs && maxLsRs > curMaxLsRs)) {
        maxOfMinLsRs = minLsRs;
        curMaxLsRs = maxLsRs;
        curPosition = i;
      }
    }
  }
  return curPosition;
}

std::tuple<uint64_t, uint64_t> solve_case(uint64_t n_, uint64_t k_) {
  std::vector<bool> s(n_ + 2, false);
  s[0] = true;
  s[n_ + 1] = true;
  assert(k_ <= n_);
  uint64_t pos = 0;
  for(uint64_t i = 0; i < k_; i++) {
    // Choose a position Person i 
    pos = choose_position(s);
    assert(pos);
    s[pos] = true;
  }
  uint64_t ls, rs;
  std::tie(ls, rs) = calc_ls_rs(s, pos);
  return std::make_tuple(std::max(ls, rs), std::min(ls, rs));
}

std::tuple<uint64_t, uint64_t> quick_solve_case(uint64_t n_, uint64_t k_) {
  return std::make_tuple(0, 0);
}

int main(int argc_, char** argv_) {
  int t = 0;
  // Input
  std::cin >> t;
  for(int i = 1; i <= t; i++) {
    uint64_t n = 0, k = 0;
    uint64_t y = 0, z = 0;
    std::cin >> n >> k;
    std::tie(y, z) = solve_case(n, k);
    // Output
    std::cout << "Case #" << i << ": " << y << ' ' << z << '\n';
  }
  return 0;
}
