#ifndef TEST_HEADER
#define TEST_HEADER


#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#pragma region Usings
using std::cout;
using std::endl;
using std::vector;
using std::string;
#pragma endregion


#pragma regin Test Functions

namespace DEMURA_TEST {
    void Simple_Test();
}

namespace HSM_3D_TEST {
    void Simple_Test();
    void test_multi_median();
}


namespace IMGUI_GLFW_VULKAN_TEST {
    int imgui_glfw_vulkan_test();
}



#pragma endregion





#endif