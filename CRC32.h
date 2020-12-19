//
// Created by Slonik on 03.12.2020.
//

#ifndef STATIC_ANALYZER_CRC32_H
#define STATIC_ANALYZER_CRC32_H

// Function that calculates cyclic redundancy checksum (ISO/IEC/IEEE 802-3 (Ethernet))
// Param 1: pData - pointer to begin of data block to proceed
// Param 2: len - size of data block in butes
unsigned int CRC32(const void *pData, unsigned int len);

#endif //STATIC_ANALYZER_CRC32_H
