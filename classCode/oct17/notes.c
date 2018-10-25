#include <stdlib.h>
#include <stdio.h>
int main() {
	printf("%d\n", 0x0);
	printf("%x\n", ~0x0);
	printf("%x\n", 0x1 & 0x2);
	// shift left by 1 mutliplies by 2
	int num = 7;
	for (int i = 0; i < 20; i++) {
		printf("%d\n", num);
		num = num << 1;
		// left shift shifts x left by y positions, mult by 2
	}
	// logical shift(default) = fill with 0's on left
	// arithmetic shift = relicae most significant bit on left
	// clock cycle determines and syncs fetch executing anddecoding
	return 0;
}
