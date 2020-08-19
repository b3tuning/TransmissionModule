//
// Created by Bucky Fellini on 2/28/20.
//

#ifndef TRANSCONTROLLER_FLASHHELPER_H
#define TRANSCONTROLLER_FLASHHELPER_H

#include <Adafruit_SPIFlash.h>
#include <SdFat.h>

class FlashHelper {
public:
	FlashHelper();

//	void init();

	static FatFileSystem& getFatFS();

	static bool removeFile(const char* path);

	static File openFile(const char* path, oflag_t oflag = FILE_READ);

private:
};

#endif //TRANSCONTROLLER_FLASHHELPER_H
