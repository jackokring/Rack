//FOR THE EDITOR
#ifndef COMPILING
#include "KRTFree.hpp"
#endif

//BASIC MACROS FOR EASY CODE
#define PARA(X) (_g.params[X])
#define IN(X) getf(_g.inputs[X])
#define OUT(X,Y) setf(_g.outputs[X], Y)
#define LIGHT(X) (_g.lights = X)

//EI 4 by 4
BEGIN(PMKRTWidget, "PM Phase Modulator")

END

BEGIN(PLLKRTWidget, "PLL Phase Locked Loop")

END

BEGIN(VCFKRTWidget, "VCF SK Filter")

END

BEGIN(DSTKRTWidget, "DST Distortion")

END

//EI 1 in 3
BEGIN(VCOKRTWidget, "VCO 2 Subs")

END

BEGIN(LFOKRTWidget, "LFO Gate Synced")

END

BEGIN(CHDKRTWidget, "CHD Chord Quantizer")

END

BEGIN(PHYKRTWidget, "PHY Physical Model")

END

LIBINIT
	//gloal plugin initializer
GENERIC
	lights = 0.0;
STEP
	KRTRUN(this);//Can also apply it to other instances to share IO
SHOW(5);

	SCREWS(1);

	CTRL(0, 0, CH1_PARAM);
	CTRL(0, 1, CH2_PARAM);
	CTRL(0, 2, CH3_PARAM);
	CTRL(0, 3, CH4_PARAM);

	if(IS(PHYKRTWidget))
		OUTPUT(0, 0, OUT1_OUTPUT);
	else
		INPUT(0, 0, IN1_INPUT);

	if(IS(VCOKRTWidget) || IS(LFOKRTWidget) || IS(CHDKRTWidget)) {
		OUTPUT(1, 0, OUT2_OUTPUT);
		OUTPUT(0, 1, OUT3_OUTPUT);
	} else {
		INPUT(1, 0, IN2_INPUT);
		INPUT(0, 1, IN3_INPUT);
	}

	OUTPUT(1, 1, OUT4_OUTPUT);

	LED(0, lights);
LIBEND
