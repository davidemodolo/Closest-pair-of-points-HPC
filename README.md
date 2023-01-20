# HPC Project - Closest Pair of Points

TODO:

- [x] function for distance between two points in $k$-dimensional space: $\displaystyle\text{distance}(p_a, p_b) = \sqrt{\sum_{i=0}^{k}(a_i - b_i)^2}$

- [x] create random points using `python.exe points_gen.py {n_points} {n_dimensions}` command $\to$ it saves the result in `points.txt` with `{n_points} {n_dimensions}` in the first line and every point coordinate in the following lines (one point per line)

- [] $O(n^2)$ serial version [IMPROVE READABILITY]
---
**Resources:**
- [Wikipedia probem description](https://en.wikipedia.org/wiki/Closest_pair_of_points_problem)
    
- $O(n\log n)$ [CPP linear implementation](https://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/): sort points based on a dimension (e.g. `x`)

- [Computer Science University of British Culumbia problem explanation](https://www.cs.ubc.ca/~liorma/cpsc320/files/closest-points.pdf)


https://sites.cs.ucsb.edu/~suri/cs235/ClosestPair.pdf