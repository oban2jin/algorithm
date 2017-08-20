#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

extern void encode(char [] src, char [][] qrc){};
extern void decode();

const int TS = 1000;
const int SZ = 100;

static char SRC[TS][SZ];
static char QRC[TS][SZ][SZ];
static char GRY[TS][SZ][SZ];
static char IMG[TS][SZ*2][SZ*2];
static char DST[TS][SZ];

int main(){
    srand(5);
    cout << "SCORE : ";

    for(int ts=0;ts<TS;ts++){
        for(int sz=0;sz<SZ;sz++){
            SRC[ts][sz] = 'A' + rand()%26;
        }
    }

    char TMP[SZ];
    for(int ts=0;ts<TS;ts++){

    }

    return 0;
}