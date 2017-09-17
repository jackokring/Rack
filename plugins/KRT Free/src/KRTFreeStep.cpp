#include "KRTFree.hpp"
#define BEGIN(X) void X::step(Generic _g) {
#define END ; return; }

#define FRONT(X) (_g.params[X])
#define IN(X) getf(_g.inputs[X])
#define OUT(X,Y) setf(_g.outputs[X], Y)
#define LIGHT(X) (_g.lights = X)

//EI 4 by 4
BEGIN(PMKRTWidget)

END

BEGIN(PLLKRTWidget)

END

BEGIN(VCFKRTWidget)

END

BEGIN(DSTKRTWidget)

END

//EI 1 in 3
BEGIN(VCOKRTWidget)

END

BEGIN(LFOKRTWidget)

END

BEGIN(CHDKRTWidget)

END

BEGIN(PHYKRTWidget)

END

/* float in1 = getf(inputs[IN1_INPUT]) * params[CH1_PARAM];
	float in2 = getf(inputs[IN2_INPUT]) * params[CH2_PARAM];
	float in3 = getf(inputs[IN3_INPUT]) * params[CH3_PARAM];
	float in4 = getf(inputs[IN4_INPUT]) * params[CH4_PARAM];

	float out = in1 + in2 + in3 + in4;
	setf(outputs[OUT1_OUTPUT], out);
	setf(outputs[OUT2_OUTPUT], -out);
	lights = out / 5.0; */