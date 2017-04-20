#include <stdio.h>
#include <stdlib.h>

long addr = 0x1000;

void hexify(char *path) {
	int bytes, i;
	unsigned char buf[32], checksum;
	FILE *in;

	if ( (in = fopen(path,"rb")) == NULL ) {
		fprintf(stderr,"%s: opening %s for read.\n",
			sys_errlist[errno],path);
		return;
		}

	while ( (bytes = fread(buf,1,16,in)) > 0 ) {
		printf(":%02X%04X00",bytes,addr);
		checksum = bytes + (unsigned)(addr>>8)
			+ (unsigned)(addr & 0xFF);
		for ( i=0; i<bytes; checksum += (unsigned) buf[i++] )
			printf("%02X",(unsigned)buf[i] & 0xFF);
		printf("%02X\n",0x100 - (unsigned) (checksum & 0xFF));
		addr += bytes;
		}

	fclose(in);
	}

int main(int argc,char **argv) {
	int i;

	for ( i=1; i<argc; ++i )	
		hexify(argv[i]);
	puts(":00100000F0");
	}
