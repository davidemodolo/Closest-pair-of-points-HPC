# HPC Project - Closest Pair of Points

This repository is a student project developed by Kevin Depedri and Davide Modolo for the "High Performance Computing for Data Science" course of the Master in Artificial Intelligent Systems at the University of Trento, a.y. 2022-2023.

We implemented two approaces, a *Bruteforce* one and a *Divide et Impera* one, to solve the **Closest Pair of Points** problem.

The repository is organized in the following way:
- the folder `point_generator` contains the smallest set of input points, together with the python scripts to generate bigger set of input points (that we run on the cluster);
- the folder `sequential` contains the sequential implementation of the Bruteforce and of the Divide et Impera approaches;
- the folder `parallel` contains the parallel implementation of the two approaches (they requires the command `mpiexec` from the library `mpitch` to be run). In particular, for the Divide et Impera approach two files can be found:
  - `parallel_recursive_short.c` shows the logic behind the algorithm from a higher level, abstracting much of what is happening in the Merge Sort and in the Divide et Impera parts of the algorithm;
  - `parallel_recursive_long.c`  shows all the logic behind all the algorithm in a single file, useful to understand in an easier way the communications between processes;
- In the folder `data` it is possible to visualize the data of the runs inserted in tables and plotted.

All the experiments have been ran on a HPC-cluster, but the code can also be tested on your own computer exploiting the cores and threads of your own CPU. This readme file presents all the steps to follow to correctly test the code on your machine.

Details about implementation and results can be found in the `Closest_Pair_of_Points_Report.pdf` report file.