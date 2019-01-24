#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef struct Node {
	unsigned long long int tag;
}Node;
struct Node** hashp;
int reads = 0; int writes = 0; int hit = 0; int miss = 0; //without prefetching
int preads = 0; int pwrites = 0; int phit = 0; int pmiss = 0;
int pref = 0; int l = 0;

int exec(int setCount, int assoc, char cmd, unsigned long long int index, unsigned long long int tag);
struct Node** createHash(int setCount, int assoc);
void add(int assoc, unsigned long long int index, unsigned long long int tag);
void shiftup(int assoc, unsigned long long int index, int j);
void clean(int setCount, int assoc);

int main(int argc, char** argv) {
	int cacheSize = atoi(argv[1]); 
	char* asvt = argv[2]; //associativity
	char* policy = argv[3]; // check valid
	int blockSize = atoi(argv[4]); //will be a power of 2
	
	int assoc; // blocks per row: will be a power of 2
	int setCount = 0; // num of rows
	if ( ceil(log(cacheSize) / log(2)) != floor(log(cacheSize) / log(2))) {
		printf("error1\n");
		return 0;
	}
	if (strcmp(policy, "fifo") != 0 && strcmp(policy, "lru") != 0) { 
		printf("error2\n");
		return 0;
	}
	// C = S * A * B (cacheSize = setCount * assoc * blockSize)
	if (strcmp(asvt, "direct") == 0) assoc = 1; // Direct: A = 1
	else if (strcmp(asvt, "assoc") == 0)  assoc = cacheSize / blockSize; // full assoc: S = 1
	else if (asvt[5] ==':') {
		assoc = atoi(&asvt[6]);
		if ( ceil(log(assoc) / log(2)) != floor(log(assoc) / log(2))) {
			printf("error");
		}
	}
	if (strcmp(asvt, "assoc") == 0) setCount = 1;
	else setCount = cacheSize / (assoc * blockSize);
	if (strcmp(policy, "lru") == 0) { 
		l = 1;
	}
	hashp = createHash(setCount, assoc);
	FILE* fp = fopen(argv[5], "r");
	if (fp == NULL) { printf("error3\n"); return 0;	}
	fseek (fp, 0, SEEK_END);
	if (ftell(fp) == 0) { printf("error4\n"); return 0; }
	rewind(fp);

	char cmd;
	unsigned long long int adr;
	int obits = log(blockSize) / log(2);
	int ibits = log(setCount) / log(2);
	while(fscanf(fp, "%*s %c %llx",&cmd, &adr) == 2) {
		unsigned long long int index = adr >> obits;
		if (ibits == 0) index = 0;
		else {index = index % (unsigned long long int)pow(2, ibits);}
		unsigned long long int tag = adr >> (obits + ibits);
		exec(setCount, assoc, cmd, index, tag);
	}
	pref = 1;
	void clean(int setCount, int assoc); //free first hash
	hashp = createHash(setCount, assoc);
	rewind(fp);
	while(fscanf(fp, "%*s %c %llx",&cmd, &adr) == 2) {
		unsigned long long int index = adr >> obits;
		if (ibits == 0) index = 0;
		else {index = index % (unsigned long long int)pow(2, ibits);}
		unsigned long long int tag = adr >> (obits + ibits);
		int miss = exec(setCount, assoc, cmd, index, tag);
		if (miss == 2 || miss == 4) {
			unsigned long long int adr2 = adr + blockSize;
			unsigned long long int index2 = adr2 >> obits;
			if (ibits == 0) index2 = 0;
			else { index2 = index2 % (unsigned long long int)pow(2, ibits);}
			unsigned long long int tag2 = adr2 >> (obits + ibits);
			exec(setCount, assoc, 'P', index2, tag2);
		} 
	}
	void clean(int setCount, int assoc); //free second hash
	printf("no-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", reads, writes, hit, miss);
	printf("with-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", preads, pwrites, phit, pmiss);

	fclose(fp);
	return 0;
}
struct Node** createHash(int setCount, int assoc) {
	struct Node** hash = (struct Node**) malloc(sizeof(struct Node*) * setCount);
	for (int i = 0; i  < setCount; i++) {
		hash[i] = (struct Node*) malloc(sizeof(struct Node) * assoc);
		for (int j = 0; j < assoc; j++) {
			hash[i][j].tag = 0;
		}
	}
	return hash;
}

int exec(int setCount, int assoc, char cmd, unsigned long long int index, unsigned long long int tag){
	int exists = 0; int ret =0; int loc;
	for (int j = 0; j < assoc; j++) {
		if (hashp[index][j].tag == tag) {
			exists = 1;
			loc = j;
			break;
		}
	}
	if(exists == 1 && cmd == 'R') { 
		if( l == 1) {
			shiftup(assoc, index, loc);
		}
		if(pref == 0) {
			hit += 1; 
			ret = 1;
		} else {
			phit += 1;
			ret = 1;
		}
	} else if(exists == 0 && cmd == 'R') {
		if (pref == 0) {
			miss += 1;	
			reads += 1;
			add(assoc, index, tag);
			ret = 2;
		} else {
			pmiss += 1;
			preads += 1;
			add(assoc, index, tag);
			ret = 2;
		}
	} else if(exists == 1 && cmd == 'W') {
		if( l == 1) {
			shiftup(assoc, index, loc);
		}
		if (pref == 0) {
			hit += 1; 
			writes += 1;
			ret = 3;
		} else {
			phit += 1; 
			pwrites += 1;
			ret = 3;
		}
	} else if(exists == 0 && cmd == 'W') {
		if (pref == 0) {
			miss += 1;	
			reads +=1;	
			writes +=1;
			add(assoc, index, tag);
			ret = 4;
		} else {
			pmiss += 1;	
			preads +=1;	
			pwrites +=1;
			add(assoc, index, tag);
			ret = 4;
		}
	} else if(exists == 0 && cmd == 'P') {
		preads += 1;
		add(assoc, index, tag);
		ret = 5;
	}
	return ret;
}
void add(int assoc, unsigned long long int index, unsigned long long int tag) {
	if (hashp[index][0].tag == 0) {
		hashp[index][0].tag = tag;
	} else {
		for(int i = assoc-2; i >= 0; i--) {
			if (hashp[index][0].tag == 0) continue;
			else {hashp[index][i+1].tag = hashp[index][i].tag; }
		}	
		hashp[index][0].tag = tag;

	}
}
void shiftup(int assoc,unsigned long long int index,int j) {
	unsigned long long int temp = hashp[index][j].tag;
	for(int i = j-1; i >= 0; i--) {
		if (hashp[index][i].tag == 0) continue;
		else {hashp[index][i+1].tag = hashp[index][i].tag; }
	}	
	hashp[index][0].tag = temp;
}
void clean(int setCount, int assoc) {
	for (int i = setCount-1; i >= 0; i--) {
		free(hashp[i]);
	}
	free(hashp);
}
