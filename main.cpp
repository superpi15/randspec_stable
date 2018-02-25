#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <gmp.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <random> //random engine

int main( int argc, char * argv[] ){
	int nEntry,  power, percent;
	char * NameSeed;
	unsigned long int nCare;
	double percent_f, nCare_f;
	power = 4;
	percent = 100;
	NameSeed = NULL;
	if( argc>1 )
		power = atoi(argv[1]);
	if( argc>2 )
		percent = atoi(argv[2]);
	if( argc>3 )
		NameSeed = argv[3];

	nEntry = 1<<power;
	nCare  = nEntry;
	std::vector<unsigned long> Output, CareEntry;
	std::vector<bool> CareMask;
	Output.resize( nEntry, 0 );
	CareMask.resize( nEntry, false );
	
	nCare_f = nCare;
	percent_f = percent;
	nCare_f *= percent_f;
	nCare_f /= 100;
	nCare = nCare_f;
	CareEntry.resize( nCare );

	for( unsigned long i=0; i<nCare; i++ ){
		CareMask[i] = true;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle( CareMask.begin(), CareMask.end(), std::default_random_engine(seed) );

	unsigned long top = 0;
	for( unsigned long i=0; i<nEntry; i++ ){
		Output[i] = i;
		if( CareMask[i] )
			CareEntry[top++] = Output[i];
		//printf("%d\n", CareMask[i]==1 );
	}
	
	std::shuffle( CareEntry.begin(), CareEntry.end(), std::default_random_engine(seed) );
	top = 0;
	for( unsigned long i=0; i<nEntry; i++ ){
		if( CareMask[i] )
			Output[i] = CareEntry[top++];
		//printf("%d %d\n", i, Output[i] );
	}


	if( NameSeed ){
		std::string FileName;
		std::ostringstream FileNameStream;
		FileNameStream << NameSeed<< power<< '_'<< percent;
		FileName = FileNameStream.str();
		std::fstream FileCmp( FileName+ "_cmp.spec", std::ios::out );
		std::fstream FileIncmp( FileName+ "_incmp.spec", std::ios::out );
		//Complete Specified One
		FileCmp << power <<" "<< 10 << std::endl;
		for( size_t i=0; i<Output.size(); i++  ){
			FileCmp<< i <<" "<< Output[i]<< std::endl;
		}
		FileCmp.close();
		//Incomplete Specified One
		FileIncmp << power <<" "<< 10 << std::endl;
		for( size_t i=0; i<Output.size(); i++  ){
			if( CareMask[i] )
				FileIncmp<< i <<" "<< Output[i]<< std::endl;
		}
		FileIncmp.close();
	}

}


