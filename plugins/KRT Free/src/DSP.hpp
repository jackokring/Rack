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
#define PARA(X) params[X]
#define IN(X) getf(inputs[X])
#define OUT(X,Y) setf(outputs[X], Y)
#define CHAINEDIN(X) getf(_g.inputs[X])
#define CHAINEDOUTIN(X) getf(_g.outputs[X]) /* maybe a sample behind */
#define CHAINEDOUT(X,Y,OLD) setf(_g.outputs[X], getf(_g.outputs[X]) - OLD + Y); OLD = Y
#define MERGEDOUT(X,Y,OLD) setf(outputs[X], getf(outputs[X]) - OLD + Y); OLD = Y
#define LIGHT(X) lights = X
//IS only works in SHOW section
#define IS(X) (module.fn == X::fn)
//Graphics scaling
#define _CX(X) 19 + 75 * X
#define _CY(Y) 30 + 51 * Y
#define _SX(X) 4 + 38 * X
#define _SY(Y) 240 + 38 * Y
#define _SC(Y) 15 + 75 * Y
#define _LY(Y) 272 + 38 * Y
//Easy port definition
#define OUTPUT(X,Y,Z) addOutput(createOutput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
#define INPUT(X,Y,Z) addInput(createInput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
//LEDs
#define LED(Y,Z) addChild(createValueLight<TinyLight<GreenRedPolarityLight>>(Vec(30, _LY(Y)), &module->Z))
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
//NOTES ON GETTING OTHER VARIABLES INTO JUST A SPECIFIC CLASS
//A static type VAR will persist across the whole plugin.
//A static declaration in a function will persist across any instances using that function.
//A static declaration in a BEGIN ... END section will persist across all instances of the one module kind.
//

TYPE int DEF x[100] VAR //Use GENERIC to initialize

TYPE void DEF func(int arg) SUB
	//C++ function here minus the {} outer brackets
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
	light = 0.0;
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

	//A BUILT IN VCA OPTION?
	INPUT(0, 2, VCA_INPUT);
	//A SECOND VCA TO ASSIST IN ADDATIVE HARMONICS
	INPUT(1, 2, CUBE_INPUT);

	LED(0, light);
LIBEND
//===================================================================================================