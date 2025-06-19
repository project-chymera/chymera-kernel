#include <studio.h>
#include <stdint.h>

typedef uint8_t bool;
#define true 1
#define false 0

typedef struct{
	BPB_OEM		db	'MSWIN4.1'  ; 8 bytes - OEM
	BPB_BPS		dw	512	; 2 bytes - Bytes por setor
	BPB_SPC		db	1	; 1 byte - Número de setores por cluster
	BPB_RSC		dw	1	; 2 bytes - Número setores reservados
	BPB_FATC	db	2	; 1 byte - Contagem da FAT
	BPB_DEC		dw	0xe0	; 2 bytes - Contagem de entradas no diretório raiz
	BPB_NTS		dw	2880	; 2 bytes - Número total de setores (2880 x 512 bytes - 1440 bytes)
	BPB_MDT		db	0xf0	; 1 byte - Descritor de tipo de mídia (0xf0 = disquete 3 1/2)
	BPB_SPT		dw	18	; 2 bytes - Setores por trilha
	BPB_NH		dw	2	; 2 bytes - Número de cabeçotes/faces
	BPB_HS		dd	0	; 4 bytes - Número de setores ocultos
	BPB_LSC		dd	0	; 4 bytes - Contagem de grandes setores
} __attribute__((packed)) BootSector;

BootSector g_BootSector;
uint8_t* g_Fat = NULL;

bool readBootSector(FILE* disk){
	return fread(&g_BootSector, sizeof(g_BootSector), 1, disk) > 0;
}

bool readSectors(FILE* disk, uint32_t lba, uint32_t count, void* bufferOut){
	bool ok = true;
	ok = ok && (fseek(disk, lba * g_BootSector.BytesPerSector, SEEK_SET) == 0);
	ok = ok && (fread(bufferOut, g_BootSector.BytesPerSector, count, disk) == count);
	return ok;	
}

bool readFAT(FILE* disk){
	g_Fat = (uint8_t*) malloc(g_BootSector.SectorsPerFat * g_BOotSector.BytesPerSector);
	
}

int main(int argc, char** argv) {

	if (argc < 3) {
		printf("Syntax: %s <disk image> <file name>\n", argv[0]);
		return -1;
	}

	FILE* disk = fopen(argv[1], "rb");
	if (!disk){
		fprintf(stderr, "Cannot open disk image %s!", arg[1]);
	}

	if (!readBootSector(disk)){
		fprintf(stderr, "Could not read boot sector!\n");
		return -2;
	}

	return 0;
}

