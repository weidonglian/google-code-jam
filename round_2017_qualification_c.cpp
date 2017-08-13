#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <tuple>
#include <assert.h>
#include <memory>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>

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

/**	Slowest algorithm can be used for testing and understand the problem. */
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

/**	From the slowest algorithm, it is easy to realize the pattern is as follow:
 * e.g. N=20, ==> {9, 10} ==> {9, {4,5}} ==> {4, 4, 4, 5} ==> {4,4,4,{2,2}} ==>
 * {4, 4, {1,2}, {2, 2}} ... 
 * With the number's evolution pattern, it always half divide the largest number.
 * A lot of items will be duplicated. For duplicated largest number lead to 
 * the same operation, we can remove all the largest duplicated numbers one time.
 */
std::tuple<uint64_t, uint64_t> quick_solve_case(uint64_t n_, uint64_t k_) {
  uint64_t ls, rs;
  std::set<uint64_t> candidates;
  std::map<uint64_t, uint64_t> counts;
  candidates.insert(n_);
  counts[n_] = 1;
  uint64_t p = 0; // Person    
  while(true) {
    uint64_t maxC = *std::rbegin(candidates);
    ls = static_cast<uint64_t>(std::floor((maxC - 1) / 2.0));
    rs = static_cast<uint64_t>(std::ceil((maxC - 1) / 2.0));
    uint64_t cntMaxC = counts[maxC];
    p += cntMaxC;

    if(p >= k_)
      break;

    candidates.erase(maxC);
    counts.erase(maxC);
    candidates.insert(rs);
    candidates.insert(ls);
    if(counts.find(ls) == counts.end())
      counts[ls] = cntMaxC;
    else
      counts[ls] += cntMaxC;

    if(counts.find(rs) == counts.end())
      counts[rs] = cntMaxC;
    else
      counts[rs] += cntMaxC;
  }
  return std::make_tuple(rs, ls);
}

int main(int argc_, char** argv_) {        
  int t = 0;
  // Input
  std::cin >> t;
  for(int i = 1; i <= t; i++) {
    uint64_t n = 0, k = 0;
    uint64_t y = 0, z = 0;
    std::cin >> n >> k;
    std::tie(y, z) = quick_solve_case(n, k);
    // Output
    std::cout << "Case #" << i << ": " << y << ' ' << z << '\n';
  }
  return 0;
}
