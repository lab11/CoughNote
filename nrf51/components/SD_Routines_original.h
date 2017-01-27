//******************************************************************
//******************************************************************
//** Author : Syed Salman Alam
//** Custome code for Reading, Writing and erasing data to and from SD card
//** every function is tested. It works for both SD and SDHC cards
//******************************************************************
//******************************************************************


#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"


//******************************************************************
//Function: to initialize SPI and  SD/SDHC  Cards
//Arguments: none
//return: 1 if SD Card, 2 if SDHC card, 0 if error
//******************************************************************
uint8_t SD_Card_Initialize(void);


//******************************************************************
// transfer data
//uint8_t spi_xfer(uint8_t spi, uint8_t data);
uint8_t spi_xfer(uint8_t data);
//******************************************************************


//******************************************************************
//Function: Select CS of SD card
//Description: do not use CS pin of SPI module, map the CS pin of
//             SPI module to some other pin that is not being used
//******************************************************************
void mmcsd_select(void);


//******************************************************************
//Function: deselect CS of SD card
//Description: do not use CS pin of SPI module, map the CS pin of
//             SPI module to some other pin that is not being used
//******************************************************************
void mmcsd_deselect(void);

uint8_t send_spi(uint8_t spi_msg);
uint8_t Send_Command(uint8_t cmd[], uint8_t size);


//******************************************************************
//Function: to initialize the SD card 
//Arguments: none
//return: 0 if no error, 1 if error
//******************************************************************
uint8_t SD_init(void);


//******************************************************************
//Function: to Initialize SDHC card
//Arguments: non
//return: 0 if no error, 1 if error
//******************************************************************
bool Initialize_SDHC(void);


//******************************************************************
//Function: to send a command to SD card
//Arguments: unsigned char (8-bit command value)
// & unsigned long (32-bit command argument)
//return: unsigned char; response byte
//******************************************************************
uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg);


//******************************************************************
//Function: to read a single block from SD card
//param: block address
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_readSingleBlock(uint32_t startBlock);


//******************************************************************
//Function: to write to a single block of SD card
//param: block address
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_writeSingleBlock(uint32_t startBlock);


//*****************************************************************
//Function: to erase specified no. of blocks of SD card
//param: starting block address
//param: number of blocks to erase
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
// problem it is wring FF when erasing sector
//*****************************************************************
uint8_t SD_erase (uint32_t startBlock, uint32_t totalBlocks);
void SD_erase_Modified(uint32_t startBlock, uint32_t totalBlocks);		// recomended function to use


//******************************************************************
//Function: to write to a single block of SD card
//param: block address
//param: pointer to data buffer(data buffer should be of size 512
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_writeSingleBlock_BUFF(uint32_t startBlock,uint8_t *data );


//***************************************************************************
//Function: to read multiple blocks from SD card & send every block to UART
//param: starting block address
//param: ending block address
//return: returns data in buffer[] 
// otherwise the response byte will be sent
//****************************************************************************
void Read_Sectors(uint32_t startBlock, uint32_t totalBlocks);
