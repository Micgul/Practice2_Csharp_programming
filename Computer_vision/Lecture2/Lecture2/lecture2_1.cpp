#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>  // ���� �����
#include <Windows.h> // ��Ʈ�� ����, �ȷ�Ʈ ����ü ����

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo,
	RGBQUAD* hRGB, BYTE* Output, int W, int H, const char* FileName)
{
	FILE *fp = fopen(FileName, "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), W*H, fp);
	fclose(fp);
}

void main()
{
	BITMAPFILEHEADER hf; // BMP ������� 14Bytes
	BITMAPINFOHEADER hInfo; // BMP ������� 40Bytes
	RGBQUAD hRGB[256]; // �ȷ�Ʈ (256 * 4Bytes)
	FILE* fp;
	fp = fopen("LENNA.bmp", "rb");
	if (fp == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE* Image = (BYTE*)malloc(ImgSize);
	BYTE* Output = (BYTE*)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	SaveBMPFile(hf, hInfo, hRGB, Output, hInfo biWidth, hInfo biHeight, "output1.bmp");
	
	free(Image);
	free(Output);
}