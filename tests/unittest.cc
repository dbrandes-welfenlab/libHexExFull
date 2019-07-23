#include <gtest/gtest.h>

//#include "predicate_test.cc"
//#include "navigation_test.cc"
//#include "sanitization_test.cc"
//#include "hportextraction_test.cc"
//#include "hporttrace_test.cc"
//#include "transitionfunction_test.cc"
//#include "faceextraction_test.cc"
//#include "cellextraction_test.cc"
//#include "fileaccess_test.cc"
//#include "openvolumemesh_test.cc"
//#include "lazy_test.cc"
//#include "cornerextraction_test.cc"
//#include "cornerneighborsearch_test.cc"
//#include "cellextractionfromcorners_test.cc"
//#include "hexmeshconversion_test.cc"
#include "performance_test.cc"
//#include "markasdeleted_test.cc"
//#include "gridisomorphism_test.cc"
//#include "randomization_test.cc"



int main(int _argc, char** _argv) {

    testing::InitGoogleTest(&_argc, _argv);
    return RUN_ALL_TESTS();
}
 
