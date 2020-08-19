//
// Created by Bucky Fellini on 2/28/20.
//

#include <FlashHelper.h>
#include <ConfigHelper.h>

const char* FLASH_INIT_FAILURE = "ERROR failed to initialize flash";
const char* FILE_MOUNT_FAILURE = "ERROR failed to mount file system";
const char* FILE_MOUNT_SUCCESS = "Mounted file system successfully";

Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0,
										PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);

Adafruit_SPIFlash flash(&flashTransport);
FatFileSystem     fatFS;

FlashHelper::FlashHelper() {
	if(!flash.begin()) {
		printDebug(FLASH_INIT_FAILURE, FLASH_DEBUG);
		while(1) {}
	}
	if(!fatFS.begin(&flash)) {
		printDebug(FILE_MOUNT_FAILURE, FLASH_DEBUG);
		while(1) {}
	}
	printDebug(FILE_MOUNT_SUCCESS, FLASH_DEBUG);
}

//void FlashHelper::init() {
//	if(!flash.begin()) {
//		printDebug(FLASH_INIT_FAILURE, FLASH_DEBUG);
//		while(1) {}
//	}
//	if(!fatFS.begin(&flash)) {
//		printDebug(FILE_MOUNT_FAILURE, FLASH_DEBUG);
//		while(1) {}
//	}
//	printDebug(FILE_MOUNT_SUCCESS, FLASH_DEBUG);
//}

FatFileSystem& FlashHelper::getFatFS() {
	return fatFS;
}

bool FlashHelper::removeFile(const char* path) {
	return fatFS.remove(path);
}

File FlashHelper::openFile(const char* path, oflag_t oflag) {
	return fatFS.open(path, oflag);
}
