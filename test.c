#include "vm.h"

int main(int argc, char **argv) {
	int outcome;
	char *option, *filename;

	if (argc <= 1)
	{
		printf("%s\n", LOGS[1]);
		printf("%s\n", LOGS[2]);
		return -1;
	}

	if (argc <= 2)
	{
		printf("%s\n", LOGS[2]);
		return -1;
	}

	option = argv[1];
	filename = argv[2];

	outcome = bootstrap(option, filename);

	printf("%s\n", LOGS[outcome]);

	return outcome;
}