#include "demura.h"


// get the base of the image based on the angle
// also arrange them in such way 
/*
    [1]                     [2]
    -----------------------> x
    |
    |
    |   -------------> panel placed direction
    |
    |
    v [0]                   [3]
     y
*/
bool get_demura_base_based_on_angle(vector<ALIPointF>& rect, float angle) {
    ALIPointF placed_vec;
    placed_vec.x = cos(angle);
    placed_vec.y = sin(angle);
    float orient = ali_cross_product(rect[0], rect[1]);
    if (orient > 0) std::reverse(rect.begin(), rect.end());
    int y_0 = -1;
    for (int i = 0; i < 4; i++) {
        ALIPointF temp;
        ali_get_normal_vector(rect[i], rect[(i + 1) % 4], temp);
        bool is_same_dir = ali_is_two_vec_same_dir(placed_vec, temp);
        if (!is_same_dir) continue;
        float vec_angle = ali_get_angle_of_two_vec(placed_vec, temp);
        if (abs(vec_angle) > 0.78) continue;
        y_0 = (i + 4 - 1) % 4;
        break;
    }
    if (y_0 < 0) {
        cout << "some thing goes wrong here: " << __FUNCTION__ << endl;
        return false;
    }
    if (y_0 == 0) return true;
    for (int i = 0; i < y_0; i++) {
        rect.push_back(rect[0]);
        rect.erase(rect.begin());
        // int iiiiii = 0;
    }
    return true;
}











