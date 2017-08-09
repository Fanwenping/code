/**
 * generate_random_data - generate specified size random data
 * @size:	data size()
 *
 * Description: Allocates a buffer for integrity metadata, maps the
 * pages and attaches them to a bio.  The bio must have data
 * direction, target device and start sector set priot to calling.  In
 * the WRITE case, integrity metadata will be generated using the
 * block device's integrity function.  In the READ case, the buffer
 * will be prepared for DMA and a suitable end_io handler set up.
 */
#include <sys/times.h>
void generate_random_data(unsigned int size, char *output_file)
{
	unsigned int cycle_size = sizeof(unsigned long);
	unsigned int cycle_count = (size + cycle_size - 1) % cycle_size;
	unsigned int aligned_size = cycle_count * cycle_size;
	
	clock_t tBeginTime = times(NULL);
	unsigned long *rand_mem = (unsigned long *)malloc(aligned_size);
	clock_t tEndTime = times(NULL);
	double fCostTime = (double)(tEndTime - tBeginTime)/sysconf(_SC_CLK_TCK);
	printf("user space malloc 0x%x memory cost time: %f\n",aligned_size, fCostTime);
	if(rand_mem == NULL) {
		printf("malloc fail\n");
		return -1;
	}
	
	srand((int)time(0));
	u32 i;
	double max_size = 1 << cycle_size;
	for(i = 0; i < cycle_count; i++)
		 *(rand_mem + i) = (unsigned long)(max_size * rand() / RAND_MAX);	
	tBeginTime = times(NULL);
	fCostTime = (double)(tBeginTime - tEndTime)/sysconf(_SC_CLK_TCK);
	PRINT("user space generate 0x%x random data cost time: %f\n", aligned_size, fCostTime);
	if (OK != parse_write_file(output_file, (void *)rand_mem, size, 1)) {
		perror("write file");
		ret = ERROR;
	}
	free((void *)rand_mem);
}