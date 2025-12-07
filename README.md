# Release v0.25 — List and Deque Performance Comparison

This version extends v0.2 by adding alternative STL container support.

### Containers used:
- `std::vector`
- `std::list`
- `std::deque`

### Features:
- Reads generated student files (1k–10M records).
- Splits students into passed/failed.
- Sorts containers by name + surname.
- Measures timing for all operations:
  - reading
  - splitting
  - sorting
  - writing
- Produces output files for each container type.

Large generated files remain excluded from GitHub.
