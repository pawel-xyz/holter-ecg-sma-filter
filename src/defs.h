#ifndef DEFS_H
#define DEFS_H

#define PERIOD 5


typedef struct {

    float MA_data[PERIOD];
    int head;
    int tail;
    int count;

}CircularBuffer;




void IniBuffer( CircularBuffer* Sptr);
bool IsBufferFull( CircularBuffer* Sptr );
bool HeadLimit( CircularBuffer* Sptr );
void BufferAdd( float NewRecord, CircularBuffer* Sptr );
float CalcSMA( CircularBuffer* Sptr );



#endif
