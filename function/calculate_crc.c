/* return crc value */
static unsigned short calculate_crc(unsigned char *frame, unsigned long length) {
	unsigned short const poly = 0x8BB7L; /* Polynomial */
	unsigned const int poly_length = 16;
	unsigned short crc_gen;
	unsigned short x;
	unsigned int i, j, fb;
    //20160921 zhangm
	unsigned const int invert = 0;/* 1=seed with 1s and invert the CRC */
	
	crc_gen = 0x0000;
	crc_gen ^= invert? 0xFFFF: 0x0000; /* seed generator */
	
	for (i = 0; i < length; i += 2) {
		/* assume little endian */
		x = (frame[i] << 8) | frame[i+1];
		
		/* serial shift register implementation */
		for (j = 0; j < poly_length; j++) {
			fb = ((x & 0x8000L) == 0x8000L) ^ ((crc_gen & 0x8000L) == 0x8000L);
			x <<= 1;
			crc_gen <<= 1;
			if (fb)
				crc_gen ^= poly;
		}
	}
	return crc_gen ^ (invert? 0xFFFF: 0x0000); /* invert output */
}
