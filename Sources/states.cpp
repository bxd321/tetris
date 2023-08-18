#pragma once
#include "defines.hpp"

typedef struct _stateArray {
    const int arr[4][NUM_BLOCKS][NUM_BLOCKS];
} stateArray;

const stateArray statesI = {
    {
        {{0,0,0,0},
         {I,I,I,I},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,0,I,0},
         {0,0,I,0},
         {0,0,I,0},
         {0,0,I,0}},

        {{0,0,0,0},
         {0,0,0,0},
         {I,I,I,I},
         {0,0,0,0}},

        {{0,I,0,0},
         {0,I,0,0},
         {0,I,0,0},
         {0,I,0,0}}
    }
};

const stateArray statesO = {
    {
        {{0,O,O,0},
         {0,O,O,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,O,O,0},
         {0,O,O,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,O,O,0},
         {0,O,O,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,O,O,0},
         {0,O,O,0},
         {0,0,0,0},
         {0,0,0,0}},
    }
};

const stateArray statesT = {
    {
        {{0,T,0,0},
         {T,T,T,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,T,0,0},
         {0,T,T,0},
         {0,T,0,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {T,T,T,0},
         {0,T,0,0},
         {0,0,0,0}},

        {{0,T,0,0},
         {T,T,0,0},
         {0,T,0,0},
         {0,0,0,0}}
    }
};

const stateArray statesS = {
    {
        {{0,S,S,0},
         {S,S,0,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,S,0,0},
         {0,S,S,0},
         {0,0,S,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {0,S,S,0},
         {S,S,0,0},
         {0,0,0,0}},

        {{S,0,0,0},
         {S,S,0,0},
         {0,S,0,0},
         {0,0,0,0}}
    }
};

const stateArray statesZ = {
    {
        {{Z,Z,0,0},
         {0,Z,Z,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,0,Z,0},
         {0,Z,Z,0},
         {0,Z,0,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {Z,Z,0,0},
         {0,Z,Z,0},
         {0,0,0,0}},

        {{0,Z,0,0},
         {Z,Z,0,0},
         {Z,0,0,0},
         {0,0,0,0}}
    }
};

const stateArray statesJ = {
    {
        {{J,0,0,0},
         {J,J,J,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,J,J,0},
         {0,J,0,0},
         {0,J,0,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {J,J,J,0},
         {0,0,J,0},
         {0,0,0,0}},

        {{0,J,0,0},
         {0,J,0,0},
         {J,J,0,0},
         {0,0,0,0}}
    }
};

const stateArray statesL = {
     {
        {{0,0,L,0},
         {L,L,L,0},
         {0,0,0,0},
         {0,0,0,0}},

        {{0,L,0,0},
         {0,L,0,0},
         {0,L,L,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {L,L,L,0},
         {L,0,0,0},
         {0,0,0,0}},

        {{L,L,0,0},
         {0,L,0,0},
         {0,L,0,0},
         {0,0,0,0}}
    }
};


const int (*getBlockStates(Shape s))[NUM_BLOCKS][NUM_BLOCKS]  {
    switch (s) {
    case I:
        return statesI.arr;
    case O:
        return statesO.arr;
    case T:
        return statesT.arr;
    case S:
        return statesS.arr;
    case Z:
        return statesZ.arr;
    case J:
        return statesJ.arr;
    case L:
        return statesL.arr;
    }

    return nullptr;
}