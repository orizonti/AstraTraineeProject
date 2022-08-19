#include "mppd_wrap.h"
#include "mppd_cmd_definitions.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

// Инициализация оболочки
mppd_wrap::mppd_wrap() {
    _devHandle = -1;
}

// Инициализация модуля
void mppd_wrap::OpenDevice(char* fileName) {
    _devHandle = open(fileName, O_RDWR | O_ASYNC | O_NONBLOCK);
}

// Закрытие модуля
void mppd_wrap::CloseDevice() {
    if (_devHandle != -1) {
        close(_devHandle);
        _devHandle = -1;
    }
}

// Флаг открытия
bool mppd_wrap::IsOpen() {
    return _devHandle > 0;
}

// Программный сброс модуля
int mppd_wrap::ResetCard() {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_SET_CARD_RESET;
    cmd.data_in = NULL;
    cmd.data_out = NULL;
    cmd.size_in = 0;
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Прерывание ожидания информации о прерывании
int mppd_wrap::AbortGetResult() {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_ABORT_DMA_GET_RESULT;
    cmd.data_in = NULL;
    cmd.data_out = NULL;
    cmd.size_in = 0;
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);

}

// апрос даты и времени прошивки модуля
int mppd_wrap::GetFirmwareInfo(union sFirmwareInfo& deviceID) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_FIRMWARE_VER;
    cmd.data_in = NULL;
    cmd.data_out = &deviceID;
    cmd.size_in = 0;
    cmd.size_out = sizeof(deviceID);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос состояния канала FC
int mppd_wrap::GetPortState(enum FcChannel fcChannel, union sPortStatus& portStatus) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_PORT_STATE;
    cmd.data_in = &fcChannel;
    cmd.data_out = &portStatus;
    cmd.size_in = sizeof(fcChannel);
    cmd.size_out = sizeof(portStatus);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос информации о температуре модуля и времени наработки
int mppd_wrap::GetCardStateInfo(struct sCardStateInfo& cardStateInfo){

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_CARD_INFO;
    cmd.data_in = NULL;
    cmd.data_out = &cardStateInfo;
    cmd.size_in = 0;
    cmd.size_out = sizeof(cardStateInfo);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}


// Задание кода времени
int mppd_wrap::SetTimeStampUtc(unsigned long long time_stamp){

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_SET_TIME_STAMP_UTC;
    cmd.data_in = &time_stamp;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(time_stamp);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}



// Настройка приемных виртуальных каналов
int mppd_wrap::SetVirtualChannelsParams(sVirtChannelsParamsInfo channelsParamsInfo[],
                                        unsigned int channelsCnt) {
    if (channelsParamsInfo == NULL || channelsCnt == 0)
        return -EINVAL;

    const unsigned int ElementSize = sizeof(struct sVirtChannelsParamsInfo);

    unsigned int size = ElementSize * channelsCnt + sizeof(unsigned int);
    char* ptrData = new char[size];

    memcpy(ptrData, &channelsCnt, sizeof(unsigned int));
    memcpy(ptrData + sizeof(unsigned int), channelsParamsInfo, ElementSize * channelsCnt);

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_SET_VIRT_CHANNELS_PARAMS;
    cmd.data_in = ptrData;
    cmd.data_out = NULL;
    cmd.size_in = size;
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}


// Запрос состояния приемных виртуальных каналов
int mppd_wrap::GetVirtualChannelsParams(sVirtChannelsParamsInfo channelsParamsInfo[MAX_NUMBER_VIRT_CHANNELS],
                                            unsigned int &channelsCnt) {
    const unsigned int ElementSize = sizeof(struct sVirtChannelsParamsInfo);
    unsigned int size = MAX_NUMBER_VIRT_CHANNELS * ElementSize + sizeof(unsigned int);
    char* ptrData = new char[size];    

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_VIRT_CHANNELS_PARAMS;
    cmd.data_in = NULL;
    cmd.data_out = ptrData;
    cmd.size_in = 0;
    cmd.size_out = size;

    int res = ioctl(_devHandle, IOCTL_CMD, &cmd);

    if (res == 0) {

        memcpy(&channelsCnt, ptrData, sizeof(unsigned int));
        channelsCnt = (channelsCnt > MAX_NUMBER_VIRT_CHANNELS)? MAX_NUMBER_VIRT_CHANNELS: channelsCnt;

        memcpy(channelsParamsInfo, ptrData + sizeof(unsigned int), channelsCnt * ElementSize );
    }

    return res;
}


// Разрешение работы виртуальных каналов 
int mppd_wrap::EnableReadVirtChannels(unsigned int enabledChannels){

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_ENABLE_READ_VIRT_CHANNELS;
    cmd.data_in = &enabledChannels;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(enabledChannels);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Получение буферов для чтения данных   
int mppd_wrap::DMAOpenReadBuffers(void** pBuffer1, void** pBuffer2) {    

    unsigned long long readMemSize = READ_CARD_MEMORY_SIZE;
    void *map = NULL; 
    
    /* Now the file is ready to be mmapped.*/
    map = mmap(0, READ_CARD_MEMORY_SIZE,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, _devHandle, 0);

    if (map == MAP_FAILED ) {
        perror("Error mmapping the file");
        return -EFAULT;
    }

    *pBuffer1 = map;
    *pBuffer2 = (void*)((char*)map + (READ_CARD_MEMORY_SIZE / 2));

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_OPEN_DMA_READ;
    cmd.data_in = &readMemSize;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(readMemSize);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Освобождение буферов чтения данных    
// pBuffer - pBuffer1 из DMAOpenReadBuffers
int mppd_wrap::DMAStopReadTransmission (void* pBuffer) {    

    unsigned long long readMemSize = READ_CARD_MEMORY_SIZE;
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_CLOSE_DMA_READ;
    cmd.data_in = &readMemSize;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(readMemSize);
    cmd.size_out = 0;

    int res = ioctl(_devHandle, IOCTL_CMD, &cmd);

    if (res == 0) {
        //free the mmapped memory
        if (munmap(pBuffer, READ_CARD_MEMORY_SIZE) == -1) {
           perror("Error un-mmapping the file");
           /* Decide here whether to close(fd) and exit() or not. Depends... */
           return -EFAULT;
        }
    }

    return res;
}


// Получение буферов для записи данных 
int mppd_wrap::DMAOpenWriteBuffers (void** pBuffer1, void** pBuffer2) {    

    unsigned long long memSize = WRITE_CARD_MEMORY_SIZE;
    void *map = NULL; 

    /* Now the file is ready to be mmapped.*/
    map = mmap(0, WRITE_CARD_MEMORY_SIZE,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, _devHandle, READ_CARD_MEMORY_SIZE);

    if (map == MAP_FAILED ) {
        perror("Error mmapping the file");
        return -EFAULT;
    }

    *pBuffer1 = map;
    *pBuffer2 = (void*)((char*)map + (WRITE_CARD_MEMORY_SIZE / 2));

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_OPEN_DMA_WRITE;
    cmd.data_in = &memSize;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(memSize);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запись данных
int mppd_wrap::DmaNextWriteBuffer(unsigned int bufNumber, unsigned int writeSize, enum OutFcChannelFlags fcChannels) {

    struct dma_next_write_buffer_params writeParams;
    memset(&writeParams, 0, sizeof(writeParams));
    writeParams.buf_number = bufNumber;
    writeParams.length = writeSize;
    writeParams.channels = fcChannels;

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_DMA_NEXT_WRITE_BUFFER;
    cmd.data_in = &writeParams;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(writeParams);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Получение информации о прерывании 
int mppd_wrap::GetInterruptData(struct InterruptData& data) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_DMA_GET_RESULT;
    cmd.data_in = NULL;
    cmd.data_out = &data;
    cmd.size_in = 0;
    cmd.size_out = sizeof(struct InterruptData);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}


// Освобождение буферов записи данных
int mppd_wrap::DMAStopWriteTransmission(void* pBuffer) {

    unsigned long long writeMemSize = WRITE_CARD_MEMORY_SIZE;
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_CLOSE_DMA_WRITE;
    cmd.data_in = &writeMemSize;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(writeMemSize);
    cmd.size_out = 0;

    int res = ioctl(_devHandle, IOCTL_CMD, &cmd);

    if (res == 0) {
        //free the mmapped memory
        if (munmap(pBuffer, WRITE_CARD_MEMORY_SIZE) == -1) {
            perror("Error un-mmapping the file");
            /* Decide here whether to close(fd) and exit() or not. Depends... */
            return -EFAULT;
        }
    }

    return res;
}

// Сообщение об освобождении DMA-буфера чтения
int mppd_wrap::DmaBufferFree(int bufferNum) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_DMA_BUFFER_FREE;
    cmd.data_in = &bufferNum;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(bufferNum);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);

}

// Получение информации о состоянии синхронизации
int mppd_wrap::GetSyncState(union sSync& data) {
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_SYNC_STATE;
    cmd.data_in = NULL;
    cmd.data_out = &data;
    cmd.size_in = 0;
    cmd.size_out = sizeof(union sSync);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Получение информации о режимах синхронизации, поддерживаемых модулем
int mppd_wrap::GetSyncMode(union sSync& data) {
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_SYNC_MODE;
    cmd.data_in = NULL;
    cmd.data_out = &data;
    cmd.size_in = 0;
    cmd.size_out = sizeof(union sSync);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}


// Задание трансляции каналов FC
int mppd_wrap::SetTranslationControl(const union sFcTranslationControl& data) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_SET_TRANSLATION_CONTROL;
    cmd.data_in = (void*)&data;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(union sFcTranslationControl);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Получение текущей трансляции каналов FC
int mppd_wrap::GetTranslationControl(union sFcTranslationControl& data) {
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_TRANSLATION_CONTROL;
    cmd.data_in = NULL;
    cmd.data_out = &data;
    cmd.size_in = 0;
    cmd.size_out = sizeof(union sFcTranslationControl);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Расширенная запись данных
int mppd_wrap::DmaNextWriteBufferExt(const struct dma_next_write_buffer_params2& writeParams) {
    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_DMA_NEXT_WRITE_BUFFER_EXT;
    cmd.data_in = (void*)&writeParams;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(writeParams);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика потерь синхронизации
int mppd_wrap::GetLossSync(enum FcChannel fcChannel, u32& lossSync) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_LOSS_SYNC;
    cmd.data_in = &fcChannel;
    cmd.data_out = &lossSync;
    cmd.size_in = sizeof(fcChannel);
    cmd.size_out = sizeof(lossSync);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика ошибок CRC
int mppd_wrap::GetCrcErrors(enum FcChannel fcChannel, u32& crcErrors) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_CRC_ERRORS;
    cmd.data_in = &fcChannel;
    cmd.data_out = &crcErrors;
    cmd.size_in = sizeof(fcChannel);
    cmd.size_out = sizeof(crcErrors);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика FC-пакетов
int mppd_wrap::GetPacketCount(enum FcChannel fcChannel, u64& packetCount) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_PACKET_COUNT;
    cmd.data_in = &fcChannel;
    cmd.data_out = &packetCount;
    cmd.size_in = sizeof(fcChannel);
    cmd.size_out = sizeof(packetCount);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика ошибок сбора последовательностей
int mppd_wrap::GetSeqErrorsCount(enum FcChannel fcChannel, u32& seqErr) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_SEQ_ERR_COUNT;
    cmd.data_in = &fcChannel;
    cmd.data_out = &seqErr;
    cmd.size_in = sizeof(fcChannel);
    cmd.size_out = sizeof(seqErr);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика пропущенных последовательностей
int mppd_wrap::GetSeqMissCount(u32& seqMiss) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_SEQ_MISS_COUNT;
    cmd.data_in = NULL;
    cmd.data_out = &seqMiss;
    cmd.size_in = 0;
    cmd.size_out = sizeof(seqMiss);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос счетчика ошибок идентификаторов входных последовательностей
int mppd_wrap::GetConnectErrors(u32& connectErr) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_CONNECT_ERRORS;
    cmd.data_in = NULL;
    cmd.data_out = &connectErr;
    cmd.size_in = 0;
    cmd.size_out = sizeof(connectErr);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Запрос регистра особенностей внешней синхронизации
int mppd_wrap::GetFeatureExtSync(const struct feature_ext_sync& sync) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_FEATURE_EXT_SYNC;
    cmd.data_in = NULL;
    cmd.data_out = (void*)&sync;
    cmd.size_in = 0;
    cmd.size_out = sizeof(sync);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}


// Запрос настройки управления сборкой последовательностей
int mppd_wrap::GetSeqAssembly(union SeqAssembly& data) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_GET_SEQ_ASSEMBLY;
    cmd.data_in = NULL;
    cmd.data_out = &data;
    cmd.size_in = 0;
    cmd.size_out = sizeof(data);

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}

// Задание настройки управления сборкой последовательностей
int mppd_wrap::SetSeqAssembly(const union SeqAssembly& data) {

    struct mppd_ioctl_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.command = MPPD_SET_SEQ_ASSEMBLY;
    cmd.data_in = (void*)&data;
    cmd.data_out = NULL;
    cmd.size_in = sizeof(data);
    cmd.size_out = 0;

    return ioctl(_devHandle, IOCTL_CMD, &cmd);
}
