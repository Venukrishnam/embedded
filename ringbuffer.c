#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_RB_COUNT 5 + 1
typedef struct
{
    int16_t head_s16;
    int16_t tail_s16;
    uint16_t maxRbElements_u16;
    uint8_t pBuffer_u8[MAX_RB_COUNT];
} rb_st;

rb_st s_rbUart;
rb_st *ps_rbUart = &s_rbUart;

void SRB_clear()
{
    ps_rbUart->head_s16 = 0;
    ps_rbUart->tail_s16 = 0;
}

bool SRB_init()
{
    bool initStatus_b8 = false;
    if (MAX_RB_COUNT)
    {
        SRB_clear();
        // ps_rbUart->pBuffer_u8 = (uint8_t *)malloc(noOfElements_u16 * sizeof(uint8_t));

        if (ps_rbUart->pBuffer_u8)
        {
            ps_rbUart->maxRbElements_u16 = MAX_RB_COUNT;
            initStatus_b8 = true;
        }
        else
        {
            ps_rbUart->maxRbElements_u16 = 0;
        }
    }

    return initStatus_b8;
}

int SRB_isAvailable()
{
    return  ((ps_rbUart->head_s16 - ps_rbUart->tail_s16 + ps_rbUart->maxRbElements_u16) % ps_rbUart->maxRbElements_u16);
}

int SRB_hasSpace()
{
    return ( ps_rbUart->maxRbElements_u16 - SRB_isAvailable() );
}

bool SRB_write(uint8_t element_u8)
{
    bool writeSuccess_b8 = false;

    // printf("Size: %d, %d, %d, %d\n", ps_rbUart->head_s16, ps_rbUart->tail_s16, SRB_hasSpace(ps_rbUart), SRB_isAvailable());

    if (SRB_hasSpace() - 1)
    {
        // if (ps_rbUart->head_s16 == ps_rbUart->tail_s16)
        // {
        //     SRB_clear();
        // }
        ps_rbUart->pBuffer_u8[ps_rbUart->head_s16] = element_u8;
        ps_rbUart->head_s16 = (ps_rbUart->head_s16 + 1) % ps_rbUart->maxRbElements_u16;
        writeSuccess_b8 = true;
    }

    return writeSuccess_b8;
}

bool SRB_read( uint8_t *element_u8)
{
    bool readSuccess_b8 = false;
    if (SRB_isAvailable())
    {
        *element_u8 = ps_rbUart->pBuffer_u8[ps_rbUart->tail_s16];
        
        ps_rbUart->tail_s16 = (ps_rbUart->tail_s16 + 1) % ps_rbUart->maxRbElements_u16;
        readSuccess_b8 = true;
    }

    return readSuccess_b8;
}

void main()
{
    uint8_t serialChar = 0;

    printf("init: %d\n", SRB_init(5));

    printf("Write 0: %d\n", SRB_write(7));
    printf("Write 1: %d\n", SRB_write(1));
    printf("Write 2: %d\n", SRB_write(2));
    printf("Write 3: %d\n", SRB_write(3));
    printf("Write 4: %d\n", SRB_write(4));
    printf("Write 5: %d\n", SRB_write(5));
    printf("Write 5: %d\n", SRB_write(5));

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Write 5: %d\n", SRB_write(5));

    printf("Write 5: %d\n", SRB_write(5));

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    printf("Write 5: %d\n", SRB_write(5));

    printf("Read: %d\n", SRB_read(&serialChar));
    printf("read data: %d\n", serialChar);

    // SRB_free(ps_rbUart);
}

// D:/Test/test_proj