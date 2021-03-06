/*
 * DirectMappedCache.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: jbb
 */

#include "Cache.h"

#include "global.h"

	Cache::Cache(unsigned logBlockSize_, unsigned logDepth_)
: logBlockSize(logBlockSize_),
	logDepth(logDepth_),
	accesses(0),
	hits(0),
	tagArray(new unsigned [1<<logDepth]),
	validArray(new bool [1<<logDepth])
{ }

Cache::~Cache() {
	delete tagArray;
	delete validArray;
}

bool Cache::checkHit(unsigned addr) {
	unsigned nTagBits = 32 - (logDepth + logBlockSize);
	unsigned tag = addr >> (logDepth + logBlockSize);

	unsigned offset = addr << (nTagBits + logDepth);
	offset = offset >> (nTagBits + logDepth);

	unsigned index = addr << nTagBits;
	index = index >> (32 - logBlockSize);
	
	accesses++;

	if (validArray[index]) {
		if (tagArray[index] == tag) {
			hits++;
			return true;
		}	
		else {
			tagArray[index] = tag;
		}
	}
	else {
		tagArray[index] = tag;
		validArray[index] = true;
	}

	return false;
}

void Cache::printStats() {
	printf("accesses = %u  hits = %u  hit rate = %f\n", accesses, hits, (float) hits/accesses);
}
