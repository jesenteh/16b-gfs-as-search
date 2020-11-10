# 16b-gfs-as-search
16-branch GFS Active S-box Search

The following program will generate a file that contains truncated differences, the number of rounds, the number of AS and permutation pattern for each sample.
Special thanks to Yeoh Wei Zhu (https://github.com/yeohweizhu) and Lee Ting Rong (https://github.com/trlee) for earlier versions of the code.
Note that the program may have redundant code from another full differential search algorithm.

All parameters to control the program are under the "Control Panel" in common.h.

NROUNDS = Number of block cipher rounds
MIN_DIFF = The minimum value of the input difference. E.g. 1 =    {0000000000000001}
MAX_DIFF = The maximum value of the input difference. E.g. 128 =  {0000000010000000}
SAMPLE_INTERVAL = How many samples taken between MIN_DIFF to MAX_DIFF. Set to MAX_DIFF sampling is not required.

Output file columns : Input truncated diff, output truncated diff, active s-boxes , number of rounds, permutation pattern (as 16 columns where the LSB is 0 and MSB is 15 - {15,14,13,...,2,1,0)
