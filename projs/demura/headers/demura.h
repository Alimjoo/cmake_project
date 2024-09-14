#ifndef ALI_DEMURA_HEADER
#define ALI_DEMURA_HEADER
#define ALI_DEBUG_DEV_DEMURA true

#include "ali_common.h"


//////////////////////////////
//////////DEFINES/////////////
// #define CLR_GREEN   1
// #define CLR_BLUE    2
// #define CLR_RED     4
// #define CLR_ALL     7
//////////////////////////////

enum demura_mode{
    Mode_Diamond,
    Mode_Delta,
    Mode_2_in_1,
    Mode_Pentile
};

enum demura_color{
    CLR_GREEN,
    CLR_BLUE,
    CLR_RED,
    CLR_ALL
};

struct demura_param{
    int height, width; // height and width of the panel
    demura_mode mode;
    demura_color color; 
    int placed_angle; // clock wise;
    string store_path;
};


int begin_demura(uchar* img, int rows, int cols, demura_param para);

#pragma region Assis functions
bool get_demura_base_based_on_angle(vector<ALIPointF>& rect, float angle);

#pragma endregion




#endif





