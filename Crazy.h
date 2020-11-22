#ifndef CRAZY_H
#define CRAZY_H

class Crazy {
private:
public:
    int scales[9][7] = {
        {0, 2, 4, 6, 7, 9, 11},
        {0, 2, 4, 5, 7, 9, 11},
        {0, 2, 4, 5, 7, 9, 10},
        {0, 2, 3, 5, 7, 9, 10},
        {0, 2, 3, 5, 7, 8, 10},
        {0, 1, 3, 5, 7, 8, 10},
        {0, 1, 3, 5, 6, 8, 10},
        {0, 2, 3, 5, 7, 8, 11},
        {0, 1, 4, 5, 7, 8, 10},
    };
    float midiToFreq(int _noteNr);
    float randFloat();
    int randNote(int _range);
    int randNoteKey(int _scale, int _key, int _range);
    float randNoteFreq(int _scale, int _key, int _range);
    

};
#endif