#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

	//���� ����
void InverseImage(BYTE *Img, BYTE *Out, int W, int H)
{
	
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = 255 - Img[i];
	}
}

	//���� ��� ����
void BrightnessAdj(BYTE* Img, BYTE* Out, int W, int H, int Val)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		if (Img[i] + Val > 255) //Ŭ���� ó��
		{
			Out[i] = 255;
		}
		else if (Img[i] + Val < 0)
		{
			Out[i] = 0;
		}
		else Out[i] = Img[i] + Val;
	}
}

	//���� ��� ����
void ContrastAdj(BYTE* Img, BYTE* Out, int W, int H, double Val)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		if (Img[i] + Val > 255.0) //Ŭ���� ó��
		{
			Out[i] = 255;
		}
		else Out[i] = (BYTE)Img[i] + Val; 
						//BYTE�� 1����Ʈ double�� 8����Ʈ�Ƿ� ���� ����ȯ
	}
}

	//������׷� �����
void ObtainHistogram(BYTE* Img, int* Histo, int W, int H)
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
		Histo[Img[i]]++;
	/*for (int i = 0; i < 256; i++)
		printf("%d\n", Histo[i]);*/
}

	//���� ������׷� �����
void ObtainAHistogram(int* Histo, int* AHisto)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < i; j++) // j(������)�� i(ū��)�� �� ������ ����
		{
			AHisto[i] += Histo[j];
		}
	}
}

	//��Ʈ��Ī �ڵ�
void HistogramStretching(BYTE* Img, BYTE* Out, int* Histo, int W, int H)
{
	int ImgSize = W * H;
	BYTE Low, High;
	for (int i = 0; i < 256; i++)
	{
		if (Histo[i] != 0)
		{
			Low = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--)
	{
		if (Histo[i] != 0)
		{
			High = i;
			break;
		}
	}
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = (BYTE)((double)(Img[i] - Low) / (High - Low) * 255.0); // ����
	}
}

	//��Ȱȭ �ڵ�
void HistogramEqualization(BYTE* Img, BYTE* Out, int* AHisto, int W, int H)
{
	int ImgSize = W * H;
	int Nt = W * H, Gmax = 255;
	double Ratio = Gmax / (double)Nt;
	BYTE NormSum[256]; //����ȭ�� ������׷�
	for (int i = 0; i < 256; i++)
	{
		NormSum[i] = (BYTE)(Ratio * AHisto[i]);	//��Ȱȭ ����
	}
	for (int i = 0; i < ImgSize; i++)
	{
		Out[i] = NormSum[Img[i]];	//��� ������ ȭ�Ұ��� ����ȭ������ �ٲ����.
	}
}

	// ����ȭ �ڵ�
void Binarization(BYTE *Img, BYTE *Out, int W, int H, BYTE Threshold) //Threshold : �Ӱ�ġ
{
	int ImgSize = W * H;
	for (int i = 0; i < ImgSize; i++)
	{
		if (Img[i] < Threshold) Out[i] = 0;
		else Out[i] = 255;
	}
}

	// ���߷��� ��谪 �ڵ� ���� ���

//int GozalezBinThresh(BYTE* Img, BYTE* Out, int* Histo, int W, int H, int ipsilon)
//{
//	// �ԽǷ� ���� 3����
//	
//	BYTE Low, High;
//
//	//1��
//	for (int i = 0; i < 256; i++)	// 1���� Low��
//	{
//		if (Histo[i] != 0)
//		{
//			Low = i;
//			break;
//		}
//	}
//	for (int i = 255; i >= 0; i--)	// 1���� High��
//	{
//		if (Histo[i] != 0)
//		{
//			High = i;
//			break;
//		}
//	}
//	int T = ((int)(Low + High) / 2);
//	
//	int G1, G2 = 0;
//	int Highdi, Lowdi = 0;
//	int newT = 0;
//
//	for (int i = 1; i > 0; i++) //4��
//	{
//		for (int i = Low; i < T; i++) 
//		{
//			G1 += i * Histo[i];
//			Highdi += Histo[i];
//		}
//		G1 = G1 / Lowdi; //2��
//
//		for (int i = T; i < High; i++) 
//		{
//			G2 += i * Histo[i];
//			Highdi += Histo[i];
//		}
//
//		G2 = G2 / Highdi; //2��
//
//		newT = (G1 + G2) / 2; //3��
//		
//		if (ipsilon > abs(newT - T))	// 5��
//			return newT;
//		
//		else
//		{
//			T = newT;
//			G1 = 0;
//			G2 = 0;
//			Highdi = 0;
//			Lowdi = 0;
//		}
//	}
//
//	return T;
//}

void SaveBMPFile(BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo,
	RGBQUAD* hRGB, BYTE* Output, int W, int H, const char* FileName)
{
	FILE* fp = fopen("output.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), W*H, fp);
	fclose(fp);
}

//---------------------------------main------------------------------------
void main()
{
	BITMAPFILEHEADER hf; // BMP ������� 14Bytes
	BITMAPINFOHEADER hInfo; // BMP ������� 40Bytes
	RGBQUAD hRGB[256]; // �ȷ�Ʈ (256 * 4Bytes)
	FILE* fp;
	fp = fopen("coin.bmp", "rb");
	if (fp == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE* Image = (BYTE*)malloc(ImgSize);
	BYTE* Output = (BYTE*)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	fclose(fp);

	int Histo[256] = { 0 }; // 0���� ��� �ʱ�ȭ
	int AHisto[256] = { 0 }; // ����������׷� ������ �迭

	/*ObtainHistogram(Image, Histo, hInfo.biWidth, hInfo.biHeight);
	ObtainAHistogram(Histo, AHisto);*/ 
	//�ڵ��ּ� : Ctrl+K+C ���� : Ctrl+K+U

	//Gonzalez �Ӱ�ġ �ڵ� ���� ����� ���� ����ȭ
	//int Thres = GozalezBinThresh(Image, Output, Histo, hInfo.biWidth, hInfo.biHeight, 3); //�ԽǷ� ��=3
	//Binarization(Image, Output, hInfo.biWidth, hInfo.biHeight, Thres);

	//HistogramStretching(Image, Output, Histo, hInfo.biWidth, hInfo.biHeight);
	//HistogramEqualization(Image, Output, AHisto, hInfo.biWidth, hInfo.biHeight);

	//InverseImage(Image, Output, hInfo.biWidth, hInfo.biHeight);
	//BrightnessAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 70);
	//ContrastAdj(Image, Output, hInfo.biWidth, hInfo.biHeight, 1.5);

	//1��
	SaveBMPFile(hf, hInfo, hRGB, Image, hInfo.biWidth, hInfo.biHeight, "output4.bmp");
	
	//2��
	for (int i = 0; i < ImgSize; i++) Output[i] = Image[i] + 50;
	SaveBMPFile(hf, hInfo, hRGB, Output, hInfo.biWidth, hInfo.biHeight, "output5.bmp");
	//3��
	for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Image[i];
	SaveBMPFile(hf, hInfo, hRGB, Output, hInfo.biWidth, hInfo.biHeight, "output6.bmp");


	free(Image);
	free(Output);
}