#include <cassert>
#include <deque>
#include <limits>
#include <optional>
#include <vector>

struct subproblem {
  std::vector<float> times;

  subproblem() : times() {}
  subproblem(float val, int ntimes) : times(val, ntimes) {}
  template<typename It>
  subproblem(It start, It end) : times(start, end) {}
};

bool operator<=(const subproblem& a, const subproblem& b) {
  if (a.times.size() > b.times.size()) {
    return false;
  }
  for (int a_idx = 0; a_idx < a.times.size(); ++a_idx) {
    auto& a_time = a.times[a_idx];
    auto& b_time = b.times[a_idx];
    if (a_time > b_time) {
      return false;
    }
  }
  return true;
}

struct problem {
  std::vector<subproblem> subproblems;

  problem() : subproblems() {}
  template<typename It>
  problem(It start, It end) : subproblems(start, end) {}
};

bool operator<=(const problem& a, const problem& b) {
  if (a.subproblems.size() > b.subproblems.size()) {
    return false;
  }
  for (int a_idx = 0; a_idx < a.subproblems.size(); ++a_idx) {
    const auto& a_subproblem = a.subproblems[a_idx];
    const auto& b_subproblem = b.subproblems[a_idx];
    if (!(a_subproblem <= b_subproblem)) {
      return false;
    }
  }
  return true;
}

problem add_two_binaries(int nbits) {
  auto p = problem();
  p.subproblems.reserve(nbits);
  for (int b = 0; b < nbits; ++b) {
    p.subproblems.emplace_back(0, 2);
  }
  return p;
}

struct next_problem_it {
  const problem& cur_p;

  virtual void operator++() = 0;
  virtual problem operator*() = 0;
};

std::pair<next_problem_it, next_problem_it>
generate_next_problems(const problem* cur_p) {
  assert false;
}

std::optional<float> evaluate_final_res(const problem& p) {
  assert false;
}

float optimize(const problem& p) {
  float best = std::numeric_limits<float>::infinity();
  std::deque<problem> unexplored = {p};
  while (unexplored.size() > 0) {
    auto& cur_p = unexplored.front();

    auto final_res_op = evaluate_final_res(cur_p);
    if (final_res_op) {
      best = std::min(best, *final_res_op);
    } else {
      auto [next_p_it_start, next_p_it_end] = generate_next_problems(cur_p);
      for (auto it = next_p_it_start; it != next_p_it_end; ++it) {
        auto next_p = *it;

        suboptimal = false;
        for (auto& p : unexplored) {
          if (!(next_p <= p)) {
            suboptimal = true;
            break;
          }
        }
        if (!suboptimal) {
          unexplored.push_back(std::move(next_p));
        }
      }
    }

    unexplored.pop_front();
  }
}

int main(int argc, char* argv[]) {
  auto p = add_two_binaries(4);
  optimize(p);
}
