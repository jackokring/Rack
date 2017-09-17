#include "rack.hpp"
#define KRTPTR(X) void (*(X()))()
#define KRTCHR(X) char* X()

using namespace rack;

void KRTInit();

//INDIRECT
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
struct PMKRTWidget : KRTWidget {
    using KRTWidget::KRTWidget;
};

struct PLLKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};

struct VCFKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};

struct DSTKRTWidget : KRTWidget {
    using KRTWidget::KRTWidget;
};

//EI 1 in 3
struct VCOKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};

struct LFOKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};

struct CHDKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};

struct PHYKRTWidget : KRTWidget {
	using KRTWidget::KRTWidget;
};
