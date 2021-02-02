# 16b-gfs-as-search
16-branch GFS Active S-box Search

Note: If you use the code in this repository for your own research and publish about it, please cite the paper:
J. Chen, J. Teh, Z. Liu, C. Su, A. Samsudin, Y. Xiang, "Towards Accurate Statistical Analysis of Security Margins: New Searching Strategies for Differential Attacks," IEEE Transactions on Computers, Vol. 66:10, 2017. DOI: https://doi.org/10.1109/TC.2017.2699190

The following program will generate a file that contains truncated differences, the number of rounds, the number of AS and permutation pattern for each sample.
Special thanks to Yeoh Wei Zhu (https://github.com/yeohweizhu) and Lee Ting Rong (https://github.com/trlee) for earlier versions of the code.
Note that the program may have redundant code from another full differential search algorithm.

All parameters to control the program are under the "Control Panel" in common.h.

NROUNDS = Number of block cipher rounds

MIN_DIFF = The minimum value of the input difference. E.g. 1 =    {0000000000000001}

MAX_DIFF = The maximum value of the input difference. E.g. 128 =  {0000000010000000}

SAMPLE_INTERVAL = How many samples taken between MIN_DIFF to MAX_DIFF. Set to MAX_DIFF sampling is not required.

perm[16] = The permutation involved in the GFS. Note that the permutation takes into account that the MSB is 15 and LSB is 0 - {15,14,...,2,1,0}. 

Output file columns : Input truncated diff, output truncated diff, active s-boxes , number of rounds, permutation pattern (as 16 columns where the LSB is 0 and MSB is 15 - {15,14,13,...,2,1,0)
