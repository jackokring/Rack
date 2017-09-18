#include "rack.hpp"
//include lib headers
#include "libs.hpp"
#define KRTPTR(X) void (Generic::*(X()))(struct Generic)
#define KRTCHR(X) char* X()
#define KRTWID(X) struct X : KRTWidget { using KRTWidget::KRTWidget; }

#define COMPILING 1

using namespace rack;

void KRTInit();

//INDIRECT
struct Generic;

struct KRTWidget : ModuleWidget {
	KRTWidget();
	virtual void stepI(Generic);
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

	Generic(KRTWidget _x);
	void step();
	KRTWidget _k;
//The function template extension
//TODO:
#define TYPE
#define DEF
#define SUB ;
#define RETURN
#define VAR ;
//The overrides
#define BEGIN(X,Y) / ## *
#define END * ## /
#define LIBINIT / ## *
#define LIBEND * ## /
#include "DSP.hpp"
};

////////////////////
// module widgets
////////////////////

//The overrides
#define BEGIN(X,Y) KRTWID(X); / ## *
#define TYPE / ## *
#define DEF 
#define SUB
#define RETURN * ## /
#define VAR * ## /
#include "DSP.hpp"

