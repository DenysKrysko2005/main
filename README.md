# Release v1.0 — Optimized Algorithms and Efficient Splitting Strategies

This final version improves performance and memory efficiency.

### Implemented two strategies:

#### Strategy 1 — Copy-based
- Base container stays unchanged.
- Students are **copied** into `failed` and `passed`.
- Simple but memory-inefficient.

#### Strategy 2 — Move & Erase
- Students are **moved** into `failed`.
- Passed students remain in the base container.
- More memory-efficient but erase operations are expensive for some containers.

### Algorithms used:
- `std::copy`
- `std::copy_if`
- `std::remove_if`
- `std::stable_partition`
- `std::find`
- `std::find_if`

### Additional:
- Performance comparison across:
  - vector
  - list
  - deque
- Added Makefile and CMakeLists.txt.
- README updated for all releases.

This version completes the project.
