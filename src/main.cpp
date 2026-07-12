#include <iostream>
#include <_inttypes.h>

#include "defs.h"


int main() {

    FILE* fin = NULL;

    fin = fopen("data.txt", "r");

    if( !fin ) {
        printf( "Error opening file !!\n" );
        return 2;
    }


    CircularBuffer new_Buffer;
    IniBuffer( &new_Buffer );

    float CurrRecord;

    FILE* fout = fopen("calculatedStats.txt", "w");

    if( !fout ) {
        printf( "Error opening file !!\n" );
        return 3;
    }

    while( fscanf(fin, "%f", &CurrRecord) == 1) {

        BufferAdd( CurrRecord, &new_Buffer );

        float CalcRec = CalcSMA( &new_Buffer );


        fprintf(fout, "%f\n", CalcRec );

    }

    fclose( fin );
    fclose( fout );

    return 0;
}