#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct
{
    int16_t head_s16;
    int16_t tail_s16;
    uint16_t maxRbElements_u16;
    // uint16_t elemetSize_u16;
    uint8_t *pBuffer_u8;
} rb_st;

void SRB_clear(rb_st *ps_rb)
{
    ps_rb->head_s16 = -1;
    ps_rb->tail_s16 = -1;
}

bool SRB_init(rb_st *ps_rb, uint16_t noOfElements_u16)
{
    bool initStatus_b8 = false;
    if (noOfElements_u16)
    {
        SRB_clear(ps_rb);
        ps_rb->pBuffer_u8 = (uint8_t *)malloc(noOfElements_u16 * sizeof(uint8_t));

        if (ps_rb->pBuffer_u8)
        {
            ps_rb->maxRbElements_u16 = noOfElements_u16;
            initStatus_b8 = true;
        }
        else
        {
            ps_rb->maxRbElements_u16 = 0;
        }
    }

    return initStatus_b8;
}

bool SRB_isAvailable(rb_st *ps_rb)
{
    bool isDataAvailable = true;
    if ((ps_rb->head_s16 < 0) || ps_rb->tail_s16 < 0)
    {
        isDataAvailable = false;
    }

    return isDataAvailable;
}

bool SRB_hasSpace(rb_st *ps_rb)
{
    bool isBufferHasSpace = true;
    // if( (ps_rb->head_s16 == ps_rb->maxRbElements_u16) && (ps_rb->tail_s16 == 0)){
    //     isBufferHasSpace = false;
    // }
    // else if( (ps_rb->head_s16 + 1) == ps_rb->tail_s16){
    //     isBufferHasSpace = false;
    // }
    if (((ps_rb->head_s16 + 1) % ps_rb->maxRbElements_u16) == ps_rb->tail_s16)
    {
        isBufferHasSpace = false;
    }

    return isBufferHasSpace;
}

void SRB_free(rb_st *ps_rb)
{
    ps_rb->maxRbElements_u16 = 0;
    SRB_clear(ps_rb);

    if (ps_rb->pBuffer_u8)
    {
        free(ps_rb->pBuffer_u8);
        ps_rb->pBuffer_u8 = NULL;
    }
}

uint16_t SRB_count(rb_st *ps_rb)
{
    uint16_t size_u16 = 0;
    if (SRB_isAvailable(ps_rb))
    {
        if (ps_rb->tail_s16 > ps_rb->head_s16)
        {
            size_u16 = ps_rb->maxRbElements_u16 - (ps_rb->tail_s16 - ps_rb->head_s16 - 1);
        }
        else
        {
            size_u16 = (ps_rb->head_s16 - ps_rb->tail_s16 + 1);
        }
    }

    return size_u16;
}

bool SRB_write(rb_st *ps_rb, uint8_t element_u8)
{
    bool writeSuccess_b8 = false;

    // printf("Size: %d, %d, %d\n", SRB_count(ps_rb), ps_rb->head_s16, ps_rb->tail_s16);

    if (SRB_hasSpace(ps_rb))
    {
        if (!SRB_isAvailable(ps_rb))
        {
            ps_rb->head_s16 = ps_rb->tail_s16 = 0;
        }
        else
        {
            ps_rb->head_s16 = (ps_rb->head_s16 + 1) % ps_rb->maxRbElements_u16;
        }
        ps_rb->pBuffer_u8[ps_rb->head_s16] = element_u8;
        writeSuccess_b8 = true;
    }

    return writeSuccess_b8;
}

bool SRB_read(rb_st *ps_rb, uint8_t *element_u8)
{
    bool readSuccess_b8 = false;
    if (SRB_isAvailable(ps_rb))
    {
        *element_u8 = ps_rb->pBuffer_u8[ps_rb->tail_s16];
        if (ps_rb->head_s16 == ps_rb->tail_s16)
        {
            SRB_clear(ps_rb);
        }
        else
        {
            ps_rb->tail_s16 = (ps_rb->tail_s16 + 1) % ps_rb->maxRbElements_u16;
        }
        readSuccess_b8 = true;
    }

    return readSuccess_b8;
}

rb_st s_rb;
rb_st *ps_rb = &s_rb;
void main()
{
    uint8_t serialChar = 0;

    printf("init: %d\n", SRB_init(ps_rb, 5));

    printf("Write 0: %d\n", SRB_write(ps_rb, 7));
    printf("Write 1: %d\n", SRB_write(ps_rb, 1));
    printf("Write 2: %d\n", SRB_write(ps_rb, 2));
    printf("Write 3: %d\n", SRB_write(ps_rb, 3));
    printf("Write 4: %d\n", SRB_write(ps_rb, 4));
    printf("Write 5: %d\n", SRB_write(ps_rb, 5));
    printf("Write 5: %d\n", SRB_write(ps_rb, 5));

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Write 5: %d\n", SRB_write(ps_rb, 5));

    printf("Write 5: %d\n", SRB_write(ps_rb, 5));

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    printf("Write 5: %d\n", SRB_write(ps_rb, 5));

    printf("Read: %d\n", SRB_read(ps_rb, &serialChar));
    printf("read data: %d\n", serialChar);

    SRB_free(ps_rb);
}

// D:/Test/test_proj