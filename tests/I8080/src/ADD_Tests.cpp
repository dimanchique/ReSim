#include "I8080_TestingSuite.h"

class I8080_ADDFixture : public I8080_TestFixture {
public:
    // fixture class placeholder
    // use if you see repetitive functions
    // for example see MOS6502 ADC_Tests
};

// test placeholder
TEST_F(I8080_ADDFixture, ADD_A_TestName) {
    // given:
    // setup

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    // check
}
