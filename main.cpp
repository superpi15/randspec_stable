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
#include <set>
#include <assert.h>

int ForceMap( std::vector<bool>& CareMask, std::vector<unsigned long>& Output ){
	std::vector<unsigned long> OAssign;
	std::set<unsigned long> Unused;
	
	OAssign.resize( Output.size(), -1 );
	for( int i=0; i<Output.size(); i++ ){
		if( CareMask[i] )
			OAssign[i] = Output[i];
		else
			Unused.insert( Output[i] );
	}
	
	std::set<unsigned long>::iterator itr;
	for( int i=0; i<Output.size(); i++ ){
		if( CareMask[i] )
			continue;
		itr = Unused.find(i);
		if( itr == Unused.end() )
			continue;
		OAssign[i] = i;
		Unused.erase(i);
	}

	itr = Unused.begin();
	for( int i=0; i<Output.size(); i++ ){
		if( CareMask[i] )
			continue;
		if( itr == Unused.end() )
			continue;
		OAssign[i] = *itr;
		itr++;
	}
	assert( itr == Unused.end() );
	for( int i=0; i<Output.size(); i++ ){
		assert( OAssign[i]>=0 );
		if( CareMask[i] ){
			assert( OAssign[i] == Output[i] );
		}
	}
	Output = OAssign;
}

int main( int argc, char * argv[] ){
	int nEntry,  power, percent;
	char * NameSeed;
	unsigned long int nCare;
	double percent_f, nCare_f;
	bool AllRand;
	power = 4;
	percent = 100;
	NameSeed = NULL;
	AllRand  = false;
	if( argc>1 )
		power = atoi(argv[1]);
	if( argc>2 )
		percent = atoi(argv[2]);
	if( argc>3 )
		NameSeed = argv[3];
	if( argc>4 )
		AllRand = true;
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

	if( AllRand )
		std::shuffle( Output.begin(), Output.end(), std::default_random_engine(seed) );


	if( NameSeed ){
		std::string FileName;
		std::ostringstream FileNameStream;
		FileNameStream << NameSeed<< power<< '_'<< percent;
		FileName = FileNameStream.str();
		if( AllRand )
			FileName += "_allrand";
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
		//
		if( AllRand ){
			std::fstream FileFcmp( FileName+ "_fcmp.spec", std::ios::out );
			FileFcmp << power <<" "<< 10 << std::endl;
			ForceMap( CareMask, Output );
			for( size_t i=0; i<Output.size(); i++  ){
				FileFcmp<< i <<" "<< Output[i]<< std::endl;
			}
			FileFcmp.close();
		}
	}

}


