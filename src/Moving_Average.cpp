#include <iostream>
#include "defs.h"
#include <memory.h>

bool IsBufferFull( CircularBuffer* Sptr ) {

    if( Sptr->count == PERIOD ) {
        return true;
    }
    return false;
}

bool HeadLimit( CircularBuffer* Sptr ) {
    if( Sptr->head == PERIOD ) {
        return true;
    }
    return false;
}


void IniBuffer( CircularBuffer* Sptr) {
    Sptr->head = 0;
    Sptr->tail = 0;
    Sptr->count = 0;
}

void BufferAdd( float NewRecord, CircularBuffer* Sptr ) {

    if( IsBufferFull( Sptr ) ) {

        Sptr->tail++;
        if( Sptr->tail == PERIOD ) {
            Sptr->tail = 0;
        }
    }

        int temp = Sptr->head;

        Sptr->MA_data[temp] = NewRecord;

        Sptr->count++;

        Sptr->head++;

        if( HeadLimit(Sptr) ) {

            Sptr->head = 0;
        }



}

float CalcSMA( CircularBuffer* Sptr ) {

   float SMA;
   float sum = 0;


    int BufforIndex = Sptr->tail;

    for( int i = 0; i < Sptr->count; i++ ) {

        sum += Sptr->MA_data[BufforIndex];
        BufforIndex++;

        if( BufforIndex == PERIOD ) {
            BufforIndex = 0;
        }
    }

    SMA = sum / Sptr->count;
    return SMA;
}

