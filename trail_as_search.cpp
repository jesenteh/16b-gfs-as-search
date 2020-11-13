
// #include "stdafx.h"
#ifndef COMMON_H
#include "common.h"
#include <fstream>
#include <bitset>
#endif

#ifndef CP_DIFF_TRAIL_SEARCH_H_
#include "trail_as_search.h"
#endif

using namespace std;
std::map<string, int> truncSet;

long globalCount = 0;

unsigned int trunc_diff[10000]={};

std::string perm_str = "";
std::string file_name = "training-data-";

void roundProcess(const int n, const int nrounds, int as, int B[], int* Bn,
	unsigned short internalTruncState[NROUNDS + 1][2])
{
	unsigned short ori = internalTruncState[n][1];
	unsigned short new_diff = 0;
	unsigned short mask = 0;
	int hw = 0;
	unsigned short tmp_diff, tmp = 0;

	//1 - 0x1	9 - 0x100
	//2 - 0x2	10- 0x200
	//3 - 0x4	11- 0x400
	//4 - 0x8	12- 0x800
	//5 - 0x10	13- 0x1000
	//6 - 0x20	14- 0x2000
	//7 - 0x40	15- 0x4000
	//8 - 0x80	16- 0x8000
	int p[16]={};
	for (int i=0; i<16; i++){
        p[i]=perm[i]-i;
	}


	//Bit position 0 and 1
	new_diff = new_diff | ((ori&0x8000)>>p[0]); //perm[0]-0 is always larger than 0, so shift right
	if (p[1]>=0) new_diff = new_diff | ((((ori&0x8000)>>1) ^ (ori&0x4000))>>p[1]);
	else new_diff = new_diff | ((((ori&0x8000)>>1) ^ (ori&0x4000))<<abs(p[1]));
	if (((ori&0x8000)!=0) && ((ori&0x4000)!=0)){
        if (p[1]>=0) mask = mask | (0x4000>>p[1]);
        else mask = mask | (0x4000<<abs(p[1]));
        hw++;
	}

    //Bit position 2 and 3
	if (p[2]>=0) new_diff = new_diff | ((ori&0x2000)>>p[2]);
	else new_diff = new_diff | ((ori&0x2000)<<abs(p[2]));
	if (p[3]>=0) new_diff = new_diff | ((((ori&0x2000)>>1) ^ (ori&0x1000))>>p[3]);
	else new_diff = new_diff | ((((ori&0x2000)>>1) ^ (ori&0x1000))<<abs(p[3]));
	if (((ori&0x2000)!=0) && ((ori&0x1000)!=0)){
        if (p[3]>=0) mask = mask | (0x1000>>p[3]);
        else mask = mask | (0x1000<<abs(p[3]));
        hw++;
	}

    //Bit position 4 and 5
	if (p[4]>=0) new_diff = new_diff | ((ori&0x800)>>p[4]);
	else new_diff = new_diff | ((ori&0x800)<<abs(p[4]));
	if (p[5]>=0) new_diff = new_diff | ((((ori&0x800)>>1) ^ (ori&0x400))>>p[5]);
	else new_diff = new_diff | ((((ori&0x800)>>1) ^ (ori&0x400))<<abs(p[5]));
	if (((ori&0x800)!=0) && ((ori&0x400)!=0)){
        if (p[5]>=0) mask = mask | (0x400>>p[5]);
        else mask = mask | (0x400<<abs(p[5]));
        hw++;
	}

	//Bit position 6 and 7
	if (p[6]>=0) new_diff = new_diff | ((ori&0x200)>>p[6]);
	else new_diff = new_diff | ((ori&0x200)<<abs(p[6]));
	if (p[7]>=0) new_diff = new_diff | ((((ori&0x200)>>1) ^ (ori&0x100))>>p[7]);
	else new_diff = new_diff | ((((ori&0x200)>>1) ^ (ori&0x100))<<abs(p[7]));
	if (((ori&0x200)!=0) && ((ori&0x100)!=0)){
        if (p[7]>=0) mask = mask | (0x100>>p[7]);
        else mask = mask | (0x100<<abs(p[7]));
        hw++;
	}

    //Bit position 8 and 9
	if (p[8]>=0) new_diff = new_diff | ((ori&0x80)>>p[8]);
	else new_diff = new_diff | ((ori&0x80)<<abs(p[8]));
	if (p[9]>=0) new_diff = new_diff | ((((ori&0x80)>>1) ^ (ori&0x40))>>p[9]);
	else new_diff = new_diff | ((((ori&0x80)>>1) ^ (ori&0x40))<<abs(p[9]));
	if (((ori&0x80)!=0) && ((ori&0x40)!=0)){
        if (p[9]>=0) mask = mask | (0x40>>p[9]);
        else mask = mask | (0x40<<abs(p[9]));
        hw++;
	}

	//Bit position 10 and 11
	if (p[10]>=0) new_diff = new_diff | ((ori&0x20)>>p[10]);
	else new_diff = new_diff | ((ori&0x20)<<abs(p[10]));
	if (p[11]>=0) new_diff = new_diff | ((((ori&0x20)>>1) ^ (ori&0x10))>>p[11]);
	else new_diff = new_diff | ((((ori&0x20)>>1) ^ (ori&0x10))<<abs(p[11]));
	if (((ori&0x20)!=0) && ((ori&0x10)!=0)){
        if (p[11]>=0) mask = mask | (0x10>>p[11]);
        else mask = mask | (0x10<<abs(p[11]));
        hw++;
	}

    //Bit position 12 and 13
	if (p[12]>=0) new_diff = new_diff | ((ori&0x8)>>p[12]);
	else new_diff = new_diff | ((ori&0x8)<<abs(p[12]));
	if (p[13]>=0) new_diff = new_diff | ((((ori&0x8)>>1) ^ (ori&0x4))>>p[13]);
	else new_diff = new_diff | ((((ori&0x8)>>1) ^ (ori&0x4))<<abs(p[13]));
	if (((ori&0x8)!=0) && ((ori&0x4)!=0)){
        if (p[13]>=0) mask = mask | (0x4>>p[13]);
        else mask = mask | (0x4<<abs(p[13]));
        hw++;
	}

	//Bit position 14 and 15
	if (p[14]>=0) new_diff = new_diff | ((ori&0x2)>>p[14]);
	else new_diff = new_diff | ((ori&0x2)<<abs(p[14]));
	if (p[15]>=0) new_diff = new_diff | ((((ori&0x2)>>1) ^ (ori&0x1))>>p[15]);
	else new_diff = new_diff | ((((ori&0x2)>>1) ^ (ori&0x1))<<abs(p[15]));
	if (((ori&0x2)!=0) && ((ori&0x1)!=0)){
        if (p[15]>=0) mask = mask | (0x1>>p[15]);
        else mask = mask | (0x1<<abs(p[15]));
        hw++;
	}

    //Generate Mask End

	for(unsigned i=0;i<(1<<hw);i++){
		 unsigned int tmp_as;
		 unsigned bitIdx = 0;
		 for(unsigned k=0;k<16;k++){
		 	if(((mask>>k)&(0x1))!=0){
		 		tmp = tmp ^ (((i>>bitIdx)&0x1)<<k);
		 		bitIdx++;
		 	}
		 }

		tmp_as = as + hw16_check_even_pos(ori);

		// only one round
		if (((n == 0) && (nrounds == 1)) /*&& ((tmp_as <= *Bn))*/) {
			internalTruncState[n+1][0]=tmp_as;
			internalTruncState[n+1][1]=new_diff^tmp;
			//------------ update Bn value!!------------
			*Bn = tmp_as;
			B[n] = tmp_as;

			int AS = 0;
            for (int i = 0; i < nrounds; i++)
            {
                AS = AS + internalTruncState[i][0];
            }

            AS = AS + internalTruncState[NROUNDS][0];
            if(NROUNDS==1){
                ofstream file;
                file.open(file_name, ios::in | ios::app);
                cout << "Number of samples: " << ++globalCount << endl;
                file << std::bitset<16>(internalTruncState[0][1]) << ", " << std::bitset<16>(internalTruncState[NROUNDS][1]) << ", " << AS << ", " << NROUNDS <<  ", " << perm_str << endl;
                if (globalCount == MAX_SAMPLES) exit(0);
            }
		}

		// Round-0 and not last round
		if ((n == 0) && (nrounds > 1)){
			//if (tmp_as <= *Bn){
				internalTruncState[n+1][0]=hw16_check_even_pos(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				cp_AS_threshold_search(n+1, nrounds, B, Bn, internalTruncState);
			//}
		}

		// Round-i and not last round
		if ((n >= 1) && (n != (nrounds - 1))){
			//if (tmp_as <= *Bn) {
				internalTruncState[n+1][0]=hw16_check_even_pos(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				cp_AS_threshold_search(n+1, nrounds, B, Bn, internalTruncState);
			//}
		}

		// last round
		if((n == (nrounds - 1)) && (nrounds > 1)) {
			//if (tmp_as <= *Bn) {
				internalTruncState[n+1][0]=hw16_check_even_pos(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				//------------ update Bn value!!------------
				*Bn = tmp_as;
				B[n] = tmp_as;

				//[round from 0 to NROUNDS-1][0-Number of AS, 1-Truncated Difference]
				if (n==NROUNDS-1)
				{
					int AS = 0;
					for (int i = 0; i < nrounds; i++)
					{

						AS = AS + internalTruncState[i][0];
					}

					AS = AS + internalTruncState[NROUNDS][0];

                    if(NROUNDS!=1){
                        ofstream file;
                        file.open(file_name, ios::in | ios::app);
                        cout << "Number of samples: " << ++globalCount << endl;
                        file << std::bitset<16>(internalTruncState[0][1]) << ", " << std::bitset<16>(internalTruncState[NROUNDS][1]) << ", " << AS << ", " << NROUNDS <<  ", " << perm_str << endl;
                        if (globalCount == MAX_SAMPLES) exit(0);
                    }
				}
			//}
        }
		tmp = 0;
	}
}


int cp_init_estimate(uint32_t next_round,  int B[NROUNDS], unsigned short internalTruncState[NROUNDS+1][2])
{
	int Bn_init;

	unsigned short diff = internalTruncState[next_round][1];

	int estimate_as = hw16_check_even_pos(diff) + 2;  // error is set to 2

	Bn_init = B[next_round-1] + estimate_as;

	cout << "Extend trail to round "<< next_round<<", "<< dec <<"Next round estimated as: "<< estimate_as
	  <<", Bn_init = "<< Bn_init <<endl;
	cout<<"-----------------------------------------------------"<<endl;
	return Bn_init;
}

void cp_AS_threshold_search(const int n, const int nrounds, int B[NROUNDS], int* Bn,
								unsigned short internalTruncState[NROUNDS + 1][2])
{
	// Only one round
	if ((n == 0) && (nrounds == 1)) {
		assert(*Bn == 2);
		//!!Modify below to specify the search space. Remember to modify the second if statement below this one as well.
        for(int i=0; i<5000; i++){
                unsigned int diff = trunc_diff[i];

                internalTruncState[0][0]=0;
                internalTruncState[0][1]=diff; // plaintext differences
                roundProcess(n, nrounds, 0, B, Bn, internalTruncState);
		}
	}

	// Round-0 and not last round
	if ((n == 0) && (nrounds > 1)) {
		//!!Modify below to specify the search space (along with the one above)
        for(int i=0; i<5000; i++){
            unsigned int diff = trunc_diff[i];

                internalTruncState[0][0]=0;
                internalTruncState[0][1]=diff; // plaintext differences
                unsigned int as = B[nrounds-1-(n+1)];  // assign B[nrounds-2] to pn,  ( B[0],...,B[nrounds-2],B[nrounds-1])
                roundProcess(n, nrounds, as, B, Bn, internalTruncState);
		}
	}

	// Round-i and not last round
	if ((n >= 1) && (n != (nrounds - 1))) {
		int as = 0;
		for(int k = 0; k < n; k++) { // as[0] + as[1]+...
			as += internalTruncState[k+1][0];
		}
		as += B[nrounds-1-(n+1)];
		roundProcess(n, nrounds, as, B, Bn, internalTruncState);
	}

	// last round
	if ((n == (nrounds - 1)) && (nrounds > 1)) {
		int as = 0;
		for(int k = 0; k < n; k++) { // as[0] + as[1]+...
			as += internalTruncState[k+1][0];
		}
		roundProcess(n, nrounds, as, B, Bn, internalTruncState);
	}
}

uint32_t cp_AS_search(int B[])
{
    //Generate 10000 random input differences
    srand(time(NULL));
    unsigned int check[65536]={0};
    for (int i=0; i<5000; i++)
    {
        unsigned int r = rand()%65536+1;
        while ((check[r]!=0) || (hw16(r)>HW_LIMIT)) //Remove repetitions and limit the hW
        {
            r = rand()%65536+1;
        }
        trunc_diff[i]=r;
        check[r]++;
    }

    for (int i=0;i<15;i++){
        perm_str += ( std::to_string(perm[i]) + ", ");
    }
    perm_str+= std::to_string(perm[15]);

    file_name+= (std::to_string(NROUNDS) + "-");
    for (int i=0;i<15;i++){
        file_name += (std::to_string(perm[i]));
    }
    file_name+= std::to_string(perm[15]);
    file_name+=".csv";

	// uint32_t num_rounds = NROUNDS; //UNUSED
	// number of AS, truncated_diff,
	// [0] = AS
	// [1] = truncated state for 16 different F-function unit
	unsigned short internalTruncState[NROUNDS+1][2]={0};
	//Can be changed to shorter bit length as the original intention of the author was to use it for 16bit structure only. Now we have to define it to be one sbox unit (in this case byte 8-bit to cover potential expansion to 8-bit sbox [still require to change something])

	// init bounds for number of AS
	//B[i] = number of minimum AS at round i+1
	for(int i = 0; i < NROUNDS; i++)
	{
		B[i] = 0;
	}

	// initial bound - best largest round prob estimation
	int Bn_init = 2; // largest as for one round

	uint32_t nrounds = 0;

	do {
		nrounds++; //Lets do the first/n round
		//cout<<"number rounds to process(nrounds) = "<<nrounds <<", Bn_init = "<<Bn_init<<endl;

		int Bn = Bn_init;		  //Set the min AS to initial bound
		B[nrounds - 1] = Bn_init;
		int r = 0;						  // initial round

		// initialize the diff path and probability for NROUNDS
		for (int i = 0; i <= NROUNDS; i++) {
			internalTruncState[i][0] = 0; // AS
			internalTruncState[i][1] = 0; // truncated_diff
		}

		// r: index of current round(0~), nrounds: total number of rounds(NROUNDS), Bn: the best found probability on n rounds
		cp_AS_threshold_search(r, nrounds, B, &Bn, internalTruncState);
		assert(B[nrounds - 1] == Bn);

		// print out the active sbox found for "nrounds" rounds
		for (uint32_t i = 0; i < nrounds; i++) {
			cout<<"B[" << i << "] = "<< B[i] ;
			cout<<endl;
		}

		// compute initial estimate for next round
		uint32_t next_round = nrounds;
		Bn_init = cp_init_estimate(next_round, B, internalTruncState);

	} while ((nrounds < NROUNDS) //Check rounds complete after doing round n
		&& ((B[nrounds - 1] < max_as) || (nrounds == 0)));

	return nrounds;
}
