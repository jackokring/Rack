#include "rack.hpp"
#define KRTPTR(X) void (*(X()))(struct Generic)
#define KRTCHR(X) char* X()
#define KRTWID(X) struct X : KRTWidget { using KRTWidget::KRTWidget; void step(Generic); }

using namespace rack;

void KRTInit();

//INDIRECT
struct Generic;

struct KRTWidget : ModuleWidget {
    KRTWidget();
    virtual KRTPTR(fn);//do it
    virtual KRTCHR(slug);
}

struct Generic : Module {
	enum ParamIds {
		CH1_PARAM,
		CH2_PARAM,
		CH3_PARAM,
		CH4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,//MAX 3 AS WOULD BE NO OUT
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		NUM_OUTPUTS
	};

	float lights;

	Generic(KRTWidget x);
	void step();
	KRTWidget k;
};

////////////////////
// module widgets
////////////////////

//EI 4 by 4
KRTWID(PMKRTWidget);
KRTWID(PLLKRTWidget)
KRTWID(VCFKRTWidget);
KRTWID(DSTKRTWidget);

//EI 1 in 3
KRTWID(VCOKRTWidget);
KRTWID(LFOKRTWidget);
KRTWID(CHDKRTWidget);
KRTWID(PHYKRTWidget);
