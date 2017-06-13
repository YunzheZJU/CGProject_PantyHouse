// Texture.cpp
// Texturing objects

#include "head.h"

#pragma warning(disable:4996)

int textureObjectCnt = 0;

GLuint textureObjects[400];

char texFileName[400][100];

unsigned int textureVideo[30];

void initTexture() {
	readMTL("models/texturetest.mtl");
	cout << "readMTL OK." << endl;
	loadObjectTextures();
	cout << "loadObjectTextures OK." << endl;

	// Uncomment if you want to enable multitexturing
	//glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	//glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	//glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}

// Read texture scr from .mtl file into texFileName and count textureObjectCnt
void readMTL(char * fileName) {
	ifstream fin(fileName);

	string s;
	while (getline(fin, s)) {
		string stemp = s.substr(0, 6);
		/*if (stemp=="newmtl"){
		string sNum=s.substr()
		textureNum==
		}*/
		//cout << "readMTL" << endl;
		if (stemp == "map_Kd") {
			string st = s.substr(7);
			st[st.length()/* - 1*/] = '\0';
			strcpy_s(texFileName[textureObjectCnt], st.c_str());
			cout<< texFileName[textureObjectCnt] <<endl;
			textureObjectCnt++;
		}
	}

}

// Load texture from bitmap file scr into memory
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
	FILE *filePtr;  // 文件指针
	BITMAPFILEHEADER bitmapFileHeader;  // bitmap文件头
	unsigned char   *bitmapImage;       // bitmap图像数据
	int imageIdx = 0;       // 图像位置索引
	unsigned char   tempRGB;    // 交换变量

	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		fprintf(stderr, "Error in loadBitmapFile: the file doesn't exist\n");
		return NULL;
	}
	fread(&bitmapFileHeader, 14, 1, filePtr);
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in loadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage + 2];
	if (!bitmapImage) {
		fprintf(stderr, "Error in loadBitmapFile: memory error\n");
		return NULL;
	}

	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in loadBitmapFile: memory error\n");
		return NULL;
	}

	for (imageIdx = 0;
	imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	fclose(filePtr);
	return bitmapImage;
}

// Load texture from bitmap file scr into textureObjects
void loadTexture(int i, char* filename, bool type) {
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char*   bitmapData;
	bitmapData = loadBitmapFile(filename, &bitmapInfoHeader);
	// bind the texture
	glBindTexture(GL_TEXTURE_2D, type ? textureVideo[i] : textureObjects[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
}

// Generate textures from texFileName into textureObjects
void loadObjectTextures() {
	glGenTextures(textureObjectCnt, textureObjects);

	for (int i = 0; i<textureObjectCnt; i++)
		loadTexture(i, texFileName[i], false);
}
