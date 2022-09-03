#ifndef SD_CARD_H
#define SD_CARD_H

//#define SD_CLK 14
//#define SD_CMD 15
//#define SD_D0   2
//#define SD_D1   4
//#define SD_D2  12
//#define SD_D3  13

#include "FS.h"
#include "SD_MMC.h"
 
class SdCard
{
private:
     char buf[128];

public:
     //bool init(int clk = SD_CLK, int cmd = SD_CMD, int d0 = SD_D0, int d1 = SD_D1, int d2 = SD_D2, int d3 = SD_D3);
     bool init();

    void listDir(const char *dirname, uint8_t levels);

    void createDir(const char *path);

    void removeDir(const char *path);

    void readFile(const char *path);

    String readFileLine(const char * path, int num);

    void writeFile(const char *path, const char *message);

    void appendFile(const char *path, const char *message);

    void renameFile(const char *path1, const char *path2);

    void deleteFile(const char *path);

    void readBinFromSd(const char *path, uint8_t* buf);

    void writeBinToSd(const char * path, uint8_t* buf);

    void fileIO(const char *path);

};

extern SdCard tf;

#endif