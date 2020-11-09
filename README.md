# 16b-gfs-as-search
16-branch GFS Active S-box Search

The following program will generate a file that contains truncated differences, the number of rounds, the number of AS and permutation pattern for each sample.
Special thanks to Yeoh Wei Zhu (https://github.com/yeohweizhu) and Lee Ting Rong (https://github.com/trlee) for earlier versions of the code.
Note that the program may have redundant code from another full differential search algorithm.

Instructions:
1. Modify the variable NROUNDS in common.h to specify the number of rounds for the search.
2. Modify the permutation pattern in trail_as_search.cpp to specify the 16-branch permutation used for the search.
3. Search for the "!!" symbol in as_search.cpp to see where to modify the search space

Output file columns : Input truncated diff, output truncated diff, active s-boxes , number of rounds, permutation pattern (as 16 columns)
