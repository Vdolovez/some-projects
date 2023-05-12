#include "BMP.h"

void InitBMFH(BITMAPFILEHEADER *BMFH, size_t W, size_t H){
    BMFH->Signature = 0x4D42;
    BMFH->FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGB)*W*H;
    BMFH->Reserved1 = 0;
    BMFH->Reserved2 = 0;
    BMFH->FileOffsetToPixelArray = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
}

void InitBMIH(BITMAPINFOHEADER *BMIH, size_t W, size_t H){
    BMIH->Size = sizeof(BITMAPINFOHEADER);
    BMIH->Width = W;
    BMIH->Height = H;
    BMIH->Planes = 1;
    BMIH->BitsPerPixelCount = sizeof(RGB);
    BMIH->Compression = 0;
    BMIH->ImageSize = 0;
    BMIH->xPixelsPerMeter = 4700;
    BMIH->yPixelsPerMeter = 4700;
    BMIH->ColorTableSize = 3;
    BMIH->ColorTableImportant = 0;
}

void InitData(BMP *Image, size_t W, size_t H){
    Image->data = (RGB**)malloc(sizeof(RGB*)*H);
    for(size_t y = 0; y < H; y++){
        Image->data[y] = (RGB*)malloc(sizeof(RGB)*W);
        for(size_t x = 0; x < W; x++){
            if(y < H/3){
                painting(Image, (RGB){0, 0, 255}, x, y);
            }
            else if(y >= H/3 && y < H*2/3){
                painting(Image, (RGB){255, 0, 0}, x, y);
            }
            else{
                painting(Image, (RGB){255, 255, 255}, x, y);
            }
        }
    }   
}

BMP InitBMP(size_t W, size_t H){
    BMP Image;
    InitBMFH(&Image.BMFH, W, H);
    InitBMIH(&Image.BMIH, W, H);
    InitData(&Image, W, H);
    return Image;
}

BMP OpenBMP(const char* path){
    FILE* f = fopen(path, "rb");
    if(f){
        BMP Image;

        fread(&Image.BMFH, sizeof(BITMAPFILEHEADER), 1, f);
        fread(&Image.BMIH, sizeof(BITMAPINFOHEADER), 1, f);

        size_t H = Image.BMIH.Height;
        size_t W = Image.BMIH.Width;
        Image.data = (RGB**)malloc(sizeof(RGB*)*H);
        for(size_t i = 0; i < H; i++){
            Image.data[i] = (RGB*)malloc(sizeof(RGB)*W);
            fread(Image.data[i], sizeof(RGB), W, f);
        }
        fclose(f);
        return Image;
    }
    else{
        puts("Current file is not here");
    }
}

void SaveBMP(const char * path, BMP Image){
    FILE* f = fopen(path, "wb");
    fwrite(&Image.BMFH, sizeof(BITMAPFILEHEADER), 1, f);
    fwrite(&Image.BMIH, sizeof(BITMAPINFOHEADER), 1, f);
    size_t H = Image.BMIH.Height;
    size_t W = Image.BMIH.Width;
    for(size_t i = 0; i < H; i++){
        fwrite(Image.data[i], sizeof(RGB), W, f);
    }
    fclose(f);
}