#include <stdio.h>
#include <math.h>
#include <stdlib.h>

extern int mandelbrot(int, int, int);

struct BMP_header
{
	char header[2];
	char file_size[4];
	short int res1;
	short int res2;
	int offset;
};

struct DIB_header
{
	int header_size;
	int image_width;
	int image_height;
	short int planes;
	short int bits_per_pixel;
	int compression;
	int bitmap_data_size;
	int h_res;
	int v_res;
	int color_palette;
	int important_colors;
};

struct Color
{
	char r;
	char g;
	char b;
};

int main(int argc, char** argv)
{	
	int power=atoi(argv[1]);
	int n=pow(2, power);
	int size=n*n;
	int file_size = 3*n*n+54;
	printf("%d\n", n);
	printf("%d\n", n*n);

	
	
	
	struct BMP_header BMPH;
	
	BMPH.header[0]=0x42;
	BMPH.header[1]=0x4d;
	BMPH.file_size[3]=file_size && 0xFF;
	BMPH.file_size[2]=(file_size>>8) && 0xFF;
	BMPH.file_size[1]=(file_size>>16) && 0xFF;
	BMPH.file_size[0]=(file_size>>24) && 0xFF;
	BMPH.res1=0;
	BMPH.res2=0;
	BMPH.offset=54;
	
	struct DIB_header DIBH;
	
	DIBH.header_size=40;
	DIBH.image_width=n;
	DIBH.image_height=n;
	DIBH.planes=1;
	DIBH.bits_per_pixel=24;
	DIBH.compression=0;
	DIBH.bitmap_data_size=3*n*n;
	DIBH.h_res=n;
	DIBH.v_res=n;
	DIBH.color_palette=0;
	DIBH.important_colors=0;
	
	char BMP_head[14];
	//head
	BMP_head[0]=0x42;
	BMP_head[1]=0x4d;
	
	//filesize
	BMP_head[2]=(file_size);
	BMP_head[3]=((file_size>>(8*1)));
	BMP_head[4]=((file_size>>(8*2)));
	BMP_head[5]=((file_size>>(8*3)));
	
	//res1
	BMP_head[6]=0;
	BMP_head[7]=0;
	//res1
	BMP_head[8]=0;
	BMP_head[9]=0;
	
	//offset
	BMP_head[10]=54;
	BMP_head[11]=0;
	BMP_head[12]=0;
	BMP_head[13]=0;
	
	char DIB_head[40];
	
	//header size
	DIB_head[0]=40;
	DIB_head[1]=0;
	DIB_head[2]=0;
	DIB_head[3]=0;
	
	//width;
	DIB_head[4]=n;
	DIB_head[5]=0;
	DIB_head[6]=0;
	DIB_head[7]=0;
	
	//height
	DIB_head[8]=n;
	DIB_head[9]=0;
	DIB_head[10]=0;
	DIB_head[11]=0;
	
	//color planes
	DIB_head[12]=1;
	DIB_head[13]=0;
	
	//bits per pixel
	DIB_head[14]=24;
	DIB_head[15]=0;
	
	//compression
	DIB_head[16]=0;
	DIB_head[17]=0;
	DIB_head[18]=0;
	DIB_head[19]=0;
	
	//image size
	DIB_head[20]=0;
	DIB_head[21]=0;
	DIB_head[22]=0;
	DIB_head[23]=0;
	
	char* PIX=(char*)malloc(3*n*n*sizeof(char));
	
	FILE* file=fopen("image.bmp", "w");
	fwrite(BMP_head, 1, 14, file);
	fwrite(&DIBH, 1, 40, file);
	
	int mandel, val;
	float intensity;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			mandel=mandelbrot(j, i, power);
			intensity=(float)mandel/100;
			val=(int)(intensity*255);
			putc(val, file);
			putc(val, file);
			putc(val, file);
		}
		printf("\n");
		
	}
	
	

}
