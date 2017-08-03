#include <iostream>
#include <vector>
#include <string>

int quick_solve(std::string line_, size_t fp_);

int main(int argc_, char** argv_) {
  int nb = 0;
  // Input
  std::cin >> nb;
  for(int i = 1; i <= nb; i++) {
    std::string line;
    size_t fp = 0;
    std::cin >> line >> fp;
    int ret = quick_solve(line, fp);
    // Output
    if(ret >= 0)
      std::cout << "Case #" << i << ": " << ret << '\n';
    else
      std::cout << "Case #" << i << ": " << "IMPOSSIBLE" << '\n';
  }
  return 0;
}

int quick_solve(std::string line_, size_t fp_) {
  int cnt = 0;
  size_t len = line_.size();
  for(size_t i = 0; i < len; i++) {
    if(line_[i] != '+') {
      if(i + fp_ - 1 < len) {
        cnt++;
        for(size_t j = 0; j < fp_; j++) {
          size_t p = i + j;
          if(line_[p] == '+') {
            line_[p] = '-';
          } else {
            line_[p] = '+';
          }
        }
      } else {
        cnt = -1;
        break;
      }
    }
  }
  return cnt;
}