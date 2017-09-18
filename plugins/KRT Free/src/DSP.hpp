//========================================================================================
//========================================================================= FOR THE EDITOR
#ifndef COMPILING
#include "KRTFree.hpp"
#endif
//========================================================================================
//================================================================================= CONFIG
//Make this your plugin directory name
#define SLUGGENERIC "KRTFree"
//Make this the module set name
#define PLUGNAME "KRT Free (EI Series)"
//=========================================================================================
//============================================================================= DO NOT EDIT
//BASIC MACROS FOR EASY CODE
#define PARA(X) (_g.params[X])
#define IN(X) getf(_g.inputs[X])
#define OUT(X,Y) setf(_g.outputs[X], Y)
#define LIGHT(X) (_g.lights = X)
//IS only works in SHOW section
#define IS(X) (module.fn == X::fn)
//Graphics scaling
#define _CX(X) 20 + 75 * X
#define _CY(Y) 32 + 51 * Y
#define _SX(X) 4 + 75 * X / 2
#define _SY(Y) 240 + 40 * Y
#define _SC(Y) 15 + 75 * Y
#define _LY(Y) 309 + 20 * Y
//Easy port definition
#define OUTPUT(X,Y,Z) addOutput(createOutput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
#define INPUT(X,Y,Z) addInput(createInput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
//LEDs
#define LED(Y,Z) addChild(createValueLight<MediumLight<GreenRedPolarityLight>>(Vec(31, _LY(Y)), &module->Z))
//Screws
#define _SCREW(X,Y) addChild(createScrew<ScrewBlack>(Vec(_SC(X), Y)))
#define SCREWS(X) _SCREW(X, 0);_SCREW(X, 365)
//Control knobs
#define CTRL(X,Y,Z) addParam(createParam<Davies1900hWhiteKnob>(Vec(_CX(X), _CY(Y)), module, Generic::Z, 0.0, 1.0, 0.0))
//DON'T USE ANYTHING WITH A _ BEFORE IT. E.G. _PANEL IS USED BY THE SHOW MACRO
#define _PANEL(X) setModule(new Generic(this)); box.size = Vec(15*X, 380); {\
	Panel *panel = new DarkPanel(); panel->box.size = box.size;\
	panel->backgroundImage = Image::load(k.slug()); addChild(panel); }
//===================================================================================================
//========================================================================================= FUNCTIONS

TYPE int DEF x[100] VAR //Use GENERIC to initialize

TYPE void DEF func(int arg) SUB

RETURN

//===================================================================================================
//=============================================================================================== DSP
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

//========================================================================================================
//=========================================================================================== INIT AND GUI

LIBINIT
	//gloal plugin initializer
GENERIC
	lights = 0.0;
STEP
	KRTRUN(this);//Can also apply it to other instances to share IO
SHOW(5)

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
//===================================================================================================