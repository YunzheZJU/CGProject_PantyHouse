// Texture.cpp
// Texturing objects

#include "head.h"

#pragma warning(disable:4996)
#pragma warning(disable:4018)

// Count textures
int textureobjectcount = 0;

// Texture Objects
GLuint textureobjects[60];

// Texture picture filename
char texturefilename[60][100];

// Video frame texture
unsigned int texturevideo[32];

void initTexture() {
	readMTL("models/texture.mtl");
	cout << "readMTL OK." << endl;
	loadObjectTextures();
}

// Read texture scr from .mtl file into texturefilename and count textureobjectcount
void readMTL(char * fileName) {
	ifstream fin(fileName);

	string s;
	while (getline(fin, s)) {
		string stemp = s.substr(0, 6);
		if (stemp == "map_Kd") {
			string st = s.substr(7);
			st[st.length()] = '\0';
			strcpy_s(texturefilename[textureobjectcount], st.c_str());
			cout << "Find texture " << textureobjectcount  << ": " << texturefilename[textureobjectcount] << endl;
			textureobjectcount++;
		}
	}

}

// Generate textures from texturefilename into textureobjects
void loadObjectTextures() {
	glGenTextures(textureobjectcount, textureobjects);

	for (int i = 0; i<textureobjectcount; i++)
		loadTexture(i, texturefilename[i], false);
}

void initVideo() {
	glGenTextures(31, texturevideo);

	char videoLoc[20] = "videoframes/00.bmp";
	for (int i = 1; i <= 32; i++) {
		videoLoc[12] = i / 10 + '0';
		videoLoc[13] = i % 10 + '0';
		cout << "Find video texture: " << videoLoc << endl;
		loadTexture(i - 1, videoLoc, true);
	}
}

// Load texture from bitmap file scr into memory
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
	FILE *filePtr;						// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;  // bitmap文件头
	unsigned char   *bitmapImage;       // bitmap图像数据
	int imageIdx = 0;					// 图像位置索引
	unsigned char   tempRGB;			// 交换变量

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

// Load texture from bitmap file scr into textureobjects
void loadTexture(int i, char* filename, bool type) {
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char*   bitmapData;
	bitmapData = loadBitmapFile(filename, &bitmapInfoHeader);
	printf("Load texture: %s\n", filename);
	// bind the texture
	glBindTexture(GL_TEXTURE_2D, type ? texturevideo[i] : textureobjects[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
}
