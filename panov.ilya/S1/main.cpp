#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <stdexcept>

template<typename T>
using Vec = std::vector<T>;

int main() {
  Vec<std::pair<std::string, Vec<unsigned long long>>> nums;
  Vec<unsigned long long> sums;
  std::string l, t, w, n;
  bool d = false, e = false;

  while (std::getline(std::cin, l) && !l.empty()) {
    std::istringstream s(l);
    s >> w;
    t = w;

    Vec<unsigned long long> ns;

    while (s >> n) ns.push_back(std::stoull(n));
    nums.push_back(std::make_pair(w, ns));
    if (!ns.empty()) d = true;
  }

  if (nums.empty()) std::cout << 0 << '\n';
  else {
    if (!d) {
      std::cout << t << "\n" << 0 << "\n";
      return 0;
    }
    size_t ml = 0;
    for (auto& i : nums) ml = std::max(ml, i.second.size());

    for (auto it = nums.begin(); it != nums.end(); ++it) {
      std::cout << it->first;
      auto nextIt = it; ++nextIt;
      if (nextIt != nums.end()) std::cout << " ";
    }
    std::cout << std::endl;

    size_t ms = 0;
    for (const auto& p : nums) ms = std::max(ms, p.second.size());

    for (size_t i = 0; i < ms; ++i) {
      bool fe = true;
      for (const auto& p : nums) {
        const auto& s = p.second;
        if (i < s.size()) {
          if (!fe) std::cout << " ";
          std::cout << s[i];
          fe = false;
        }
      }
      std::cout << std::endl;
    }

    try {
      for (size_t i = 0; i < ml; ++i) {
        unsigned long long sm = 0;
        for (auto it = nums.begin(); it != nums.end(); ++it) {
          if (i < it->second.size()) {
            if (sm > std::numeric_limits<unsigned long long>::max() - it->second[i])
              throw std::overflow_error("Overflow");
            sm += it->second[i];
          }
        }
        sums.push_back(sm);
      }
    }
    catch (const std::overflow_error& x) {
      std::cerr << x.what() << '\n';
      return 1;
    }
    for (auto it = sums.begin(); it != sums.end(); ++it) {
      std::cout << *it;
      auto nextIt = it; ++nextIt;
      if (nextIt != sums.end()) std::cout << " ";
    }
    std::cout << "\n";
  }
  if (e) return 1;
  return 0;
}
