#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "stdavk.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BYTES_PER_PIXEL 2

int main(int argc, char **argv)
{
	int fbfd = open("/dev/fb0", O_RDWR);
	struct fb_var_screeninfo vinfo;
	ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
	
	if(vinfo.bits_per_pixel != 16)
	{
		printf("Deze code ondersteunt alleen 16-bits kleurdiepte.\nvinfo geeft %d\n", vinfo.bits_per_pixel);
		return 1;
	}
	
	size_t screensize = vinfo.xres_virtual * vinfo.yres_virtual * BYTES_PER_PIXEL;
	
	char* framebuffer = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	
	int x, y;
	int squareSize = 1100;
	int squareX = (SCREEN_WIDTH - squareSize) / 2;
	int squareY = (SCREEN_HEIGHT - squareSize) / 2;
	
	for(y = squareY; y < squareY + squareSize; y++)
	{
		for(x = squareX; x < squareX + squareSize; x++)
		{
			size_t offset = (x + vinfo.xoffset) * BYTES_PER_PIXEL + (y + vinfo.yoffset) * vinfo.xres_virtual * BYTES_PER_PIXEL;
			framebuffer[offset] = 0x00;
			framebuffer[offset + 1] = 0xF8;
		}
	}
	
	munmap(framebuffer, screensize);
	close(fbfd);

return 0;
}

