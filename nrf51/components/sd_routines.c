//******************************************************************
//******************************************************************
//** Author : Syed Salman Alam
//** Custome code for Reading, Writing and erasing data to and from SD card
//** every function is tested. It works for both SD and SDHC cards
//******************************************************************
//******************************************************************
#include "nrf.h"
#include <string.h>
#include <stdio.h>
#include "nrf_delay.h"

#include "app_gpiote.h"
#include "nrf_gpio.h"
#include "common.h"

#include "app_util_platform.h"
#include "nrf_drv_gpiote.h"
#include "sd_routines.h"
#include "spi_master2.h"

#define FAT_TESTING_ONLY

#define SD_CS_ASSERT     PORTB &= ~0x02
#define SD_CS_DEASSERT   PORTB |= 0x02

#define GO_IDLE_STATE            0
#define SEND_OP_COND            1
#define SEND_CSD                 9
#define STOP_TRANSMISSION        12
#define SEND_STATUS              13
#define SET_BLOCK_LEN            16
#define READ_SINGLE_BLOCK        17
#define READ_MULTIPLE_BLOCKS     18
#define WRITE_SINGLE_BLOCK       24
#define WRITE_MULTIPLE_BLOCKS    25
#define ERASE_BLOCK_START_ADDR   32
#define ERASE_BLOCK_END_ADDR     33
#define ERASE_SELECTED_BLOCKS    38
#define CRC_ON_OFF               59

#define MMCSD_PIN_SELECT 29

#define ON     1
#define OFF    0


uint8_t sd_cmd1[9]  = {0xFF,0x40,0x00,0x00,0x00,0x00,0x95,0xFF,0xFF};
uint8_t sd_cmd2[13] = {0xFF,0x48,0x00,0x00,0x01,0xAA,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t sd_cmd3[8]  = {0xFF,0x77,0x00,0x00,0x00,0x00,0xFF,0xFF};
uint8_t sd_cmd4[9]  = {0xFF,0x69,0x40,0x00,0x00,0x00,0xFF,0xFF,0xFF};
uint8_t sd_cmd5[10] = {0xFF,0x7A,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};

//uint32_t *SDCard_spi;

uint32_t startBlock;
uint32_t totalBlocks;
uint8_t sd_buffer[512];

static SPIConfig_t *spi_config;
static SPIModuleNumber spi_num;

static uint32_t cs_pin;
static nrf_drv_gpiote_out_config_t cs_config = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);

static uint8_t spi_txbuf[2] = {};
static uint8_t spi_rxbuf[2] = {}; 


//******************************************************************
//Function: to initialize SPI and  SD/SDHC  Cards
//Arguments: none
//return: 1 if SD Card, 2 if SDHC card, 0 if error
//******************************************************************
uint8_t SD_Card_Initialize(SPIModuleNumber n, SPIConfig_t *s, uint32_t p) {
    spi_config = s;
    spi_num = n;
    cs_pin = p;
    uint8_t ret = 0;

    nrf_drv_gpiote_out_init(cs_pin, &cs_config);
    nrf_drv_gpiote_out_set(cs_pin);

    if(SD_init())
    {
        if(Initialize_SDHC())
            ret = 0;
        else
            ret = 2;			//SDHC card
    }
    else
        ret = 1;				// SD card

    return ret;
}

uint8_t spi_xfer(uint8_t data) {
    spi_txbuf[0]=data;
    spi_master_tx_rx(spi_num, 1, spi_txbuf, spi_rxbuf);
    return spi_rxbuf[0];
}

void mmcsd_select()
{
    nrf_drv_gpiote_out_clear(cs_pin);
}

void mmcsd_deselect()
{
    spi_xfer( 0xFF);
    nrf_drv_gpiote_out_set(cs_pin);
}

uint8_t send_spi(uint8_t spi_msg)
{
    static uint8_t spi_rcv;
    spi_rcv=spi_xfer( spi_msg);

    return spi_rcv;
}

uint8_t Send_Command(uint8_t cmd[], uint8_t size)
{
    static uint8_t p;
    static uint8_t resp;
    for(p=0;p<size;p++)
    {
        resp=send_spi(cmd[p]);
    }
    return resp;
}




//******************************************************************
//Function: to initialize the SD card 
//Arguments: none
//return: 0 if no error, 1 if error
//******************************************************************
uint8_t SD_init(void)
{
    uint8_t i, response, retry=0 ;
    mmcsd_select();
    do
    {
        for(i=0;i<10;i++)
            //SPI_transmit(0xff);
            spi_xfer( 0xFF);
        response = SD_sendCommand(GO_IDLE_STATE, 0);//send 'reset & go idle' command
        retry++;
        if(retry>0xfe) { return 1; }//time out
    } while(response != 0x01);

    mmcsd_deselect();

    spi_xfer( 0xFF);
    spi_xfer( 0xFF);

    retry = 0;

    do
    {
        response = SD_sendCommand(SEND_OP_COND, 0); //activate card's initialization process
        response = SD_sendCommand(SEND_OP_COND, 0); //resend command (for compatibility with some cards)
        retry++;
        if(retry>0xFE) return 1; //time out
    }while(response);

    SD_sendCommand(CRC_ON_OFF, OFF); //disable CRC; deafault - CRC disabled in SPI mode
    SD_sendCommand(SET_BLOCK_LEN, 512); //set block size to 512

    return 0; //normal return
}


//******************************************************************
//Function: to Initialize SDHC card
//Arguments: non
//return: 0 if no error, 1 if error
//******************************************************************
bool Initialize_SDHC(void)
{
    bool done=0;
    static uint8_t rcv;
    static uint16_t count=0;
    //Send Dummys

    nrf_gpio_pin_set(MMCSD_PIN_SELECT);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    spi_xfer( 0xFF);
    nrf_gpio_pin_clear(MMCSD_PIN_SELECT);
    mmcsd_deselect();

    mmcsd_select();
    Send_Command(sd_cmd1,9);
    mmcsd_deselect();

    mmcsd_select();
    Send_Command(sd_cmd2,13);
    mmcsd_deselect();
    while(!done)
    {

        mmcsd_select();
        rcv=Send_Command(sd_cmd3,8);
        if (rcv == 0x00 ){done=1;}
        else{ mmcsd_deselect();}

        mmcsd_select();
        rcv=Send_Command(sd_cmd4,9);
        if (rcv == 0x00 ){done=1;}
        else{ mmcsd_deselect();}

        count++;
        if(count==5000){return 1;}
    }

    mmcsd_select();
    if(Send_Command(sd_cmd5,10) == 0xC0)
    {
        send_spi(0xFF);
        send_spi(0xFF);
        send_spi(0xFF);
        send_spi(0xFF);

        return 0;
    }
    else {mmcsd_deselect(); return 1;}
}

//******************************************************************
//Function: to send a command to SD card
//Arguments: unsigned char (8-bit command value)
// & unsigned long (32-bit command argument)
//return: unsigned char; response byte
//******************************************************************
uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg)
{
    uint8_t response, retry=0;

    mmcsd_select();

    spi_xfer(cmd | 0x40); //send command, first two bits always '01'
    spi_xfer(arg>>24);
    spi_xfer(arg>>16);
    spi_xfer(arg>>8);
    spi_xfer(arg);
    spi_xfer(0x95);

    while((response = spi_xfer( 0xFF)) == 0xff) //wait response
        if(retry++ > 0xfe) break; //time out error

    spi_xfer( 0xFF); //extra 8 CLK
    mmcsd_deselect();

    return response; //return state
}

//*****************************************************************
//Function: to erase specified no. of blocks of SD card
//param: starting block address
//param: number of blocks to erase
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
// problem it is wring FF when erasing sector
//*****************************************************************
uint8_t SD_erase (uint32_t startBlock, uint32_t totalBlocks)
{
    uint8_t response;

    response = SD_sendCommand(ERASE_BLOCK_START_ADDR, startBlock<<9); //send starting block address
    if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
        return response;

    response = SD_sendCommand(ERASE_BLOCK_END_ADDR,(startBlock + totalBlocks - 1)<<9); //send end block address
    if(response != 0x00)
        return response;

    response = SD_sendCommand(ERASE_SELECTED_BLOCKS, 0); //erase all selected blocks
    if(response != 0x00)
        return response;

    return 0; //normal return
}

//*****************************************************************
//Function: to erase specified no. of blocks of SD card
//param: starting block address
//param: number of blocks to erase
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
// problem it is wring FF when erasing sector
//*****************************************************************
void SD_erase_Modified(uint32_t startBlock, uint32_t totalBlocks)
{

    uint8_t erase_with[512];
    uint32_t c;
    memset(erase_with,'\0',512);

    for(c=startBlock;c<totalBlocks;c++)
        SD_writeSingleBlock_BUFF(c,erase_with);
}




//******************************************************************
//Function: to read a single block from SD card
//param: block address
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_readSingleBlock(uint32_t startBlock)
{
    uint8_t response;
    uint16_t i, retry=0;

    response = SD_sendCommand(READ_SINGLE_BLOCK, startBlock<<9); //read a Block command
    //block address converted to starting address of 512 byte Block
    if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
        return response;

    mmcsd_select();

    while(spi_xfer( 0xFF) != 0xFE) //wait for start block token 0xfe (0x11111110)
        if(retry++ > 0xfffe){mmcsd_deselect(); return 1;} //return if time-out

    for(i=0; i<512; i++) //read 512 bytes
        sd_buffer[i] = spi_xfer( 0xFF);

    spi_xfer( 0xFF); //receive incoming CRC (16-bit), CRC is ignored here
    spi_xfer( 0xFF);

    spi_xfer( 0xFF); //extra 8 clock pulses
    mmcsd_deselect();

    return 0;
}

//******************************************************************
//Function: to write to a single block of SD card
//param: block address
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_writeSingleBlock(uint32_t startBlock)
{
    uint8_t response;
    uint16_t i, retry=0;

    response = SD_sendCommand(WRITE_SINGLE_BLOCK, startBlock<<9); //write a Block command
    if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
        return response;

    mmcsd_select();
    //spi_xfer( 0xFF)
    spi_xfer(0xfe);     //Send start block token 0xfe (0x11111110)

    for(i=0; i<512; i++)    //send 512 bytes data
        spi_xfer(sd_buffer[i]);

    spi_xfer(0xff);     //transmit dummy CRC (16-bit), CRC is ignored here
    spi_xfer(0xff);

    response = spi_xfer( 0xFF);

    if( (response & 0x1f) != 0x05) //response= 0xXXX0AAA1 ; AAA='010' - data accepted
    {                              //AAA='101'-data rejected due to CRC error
        mmcsd_deselect();              //AAA='110'-data rejected due to write error
        return response;
    }

    while(!spi_xfer( 0xFF)) //wait for SD card to complete writing and get idle
        if(retry++ > 0xfffe){mmcsd_deselect(); return 1;}

    mmcsd_deselect();
    spi_xfer(0xFF);   //just spend 8 clock cycle delay before reasserting the CS line
    mmcsd_select();          //re-asserting the CS line to verify if card is still busy

    while(!spi_xfer( 0xFF)) //wait for SD card to complete writing and get idle
        if(retry++ > 0xfffe){mmcsd_deselect(); return 1;}
    mmcsd_deselect();

    return 0;
}

//******************************************************************
//Function: to write to a single block of SD card
//param: block address
//param: pointer to data buffer(data buffer should be of size 512
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//******************************************************************
uint8_t SD_writeSingleBlock_BUFF(uint32_t startBlock,uint8_t *data )
{
    uint8_t response;
    uint16_t i, retry=0;

    response = SD_sendCommand(WRITE_SINGLE_BLOCK, startBlock<<9); //write a Block command
    if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
        return response;

    mmcsd_select();
    //spi_xfer( 0xFF)
    spi_xfer(0xfe);     //Send start block token 0xfe (0x11111110)

    for(i=0; i<512; i++)    //send 512 bytes data
        spi_xfer(data[i]);

    spi_xfer(0xff);     //transmit dummy CRC (16-bit), CRC is ignored here
    spi_xfer(0xff);

    response = spi_xfer( 0xFF);

    if( (response & 0x1f) != 0x05) //response= 0xXXX0AAA1 ; AAA='010' - data accepted
    {                              //AAA='101'-data rejected due to CRC error
        mmcsd_deselect();              //AAA='110'-data rejected due to write error
        return response;
    }

    while(!spi_xfer( 0xFF)) //wait for SD card to complete writing and get idle
        if(retry++ > 0xfffe){mmcsd_deselect(); return 1;}

    mmcsd_deselect();
    spi_xfer(0xFF);   //just spend 8 clock cycle delay before reasserting the CS line
    mmcsd_select();          //re-asserting the CS line to verify if card is still busy

    while(!spi_xfer( 0xFF)) //wait for SD card to complete writing and get idle
        if(retry++ > 0xfffe){mmcsd_deselect(); return 1;}
    mmcsd_deselect();

    return 0;
}


//***************************************************************************
//Function: to read multiple blocks from SD card & send every block to UART
//param: starting block address
//param: ending block address
//return: unsigned char; will be 0 if no error,
// otherwise the response byte will be sent
//****************************************************************************
void Read_Sectors(uint32_t startBlock, uint32_t totalBlocks)
{
    uint32_t c_bytes,blocks_2print;
    for(blocks_2print=startBlock; blocks_2print<totalBlocks; blocks_2print++) //read 512 bytes
    {
        memset(sd_buffer,'\0',sizeof(sd_buffer));
        SD_readSingleBlock(blocks_2print);
        for(c_bytes=0; c_bytes<512; c_bytes++) //read 512 bytes
        {
            printf( "%c" ,sd_buffer[c_bytes]);
            // nrf_delay_ms(1);
        }
    }
}




