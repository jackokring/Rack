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
#define PARACV(X,S) exp(log(2.0) * S * (2.0 * params[X] - 1.0))
#define IN(X,Y) getf(inputs[X],Y)
#define INCV(X) exp(log(2.0) * inputs[X])
//Auto VCA linear
#define OUT(X,Y) setf(outputs[X], Y * getf(inputs[VCA_INPUT], 10.0) * 0.1)
#define OUTCV(X,Y,M) setf(outputs[X], Y + (M - 0.5) * getf(inputs[VCA_INPUT], 0.0) * 0.1)
#define CHAINEDIN(X) getf(_g.inputs[X])
#define CHAINEDOUTIN(X) getf(_g.outputs[X]) /* maybe a sample behind */
#define CHAINEDOUT(X,Y,OLD) setf(_g.outputs[X], getf(_g.outputs[X]) - OLD + Y); OLD = Y
#define MERGEDOUT(X,Y,OLD) setf(outputs[X], getf(outputs[X]) - OLD + Y); OLD = Y
#define LIGHT(X) lights = X
//IS only works in SHOW section
#define IS(X) (module.fn == X::fn)
//Graphics scaling
#define _SD(Y) (Y % 2)
#define _CX(X,Y) 4 + 60 * X + _SD(Y) * 16 
#define _CY(Y) 30 + 51 * Y
#define _SX(X,Y) 4 + 30 * X - _SD(Y) * 8 
#define _SY(Y) 240 + 38 * Y + _SD(Y) * 19
#define _SC(Y) 15 + 60 * Y
#define _LX(X) 5 + 10 * X
//Easy port definition
#define OUTPUT(X,Y,Z) addOutput(createOutput<PJ3410Port>(Vec(_SX(X,Y), _SY(Y)), module, Generic::Z))
#define INPUT(X,Y,Z) addInput(createInput<PJ3410Port>(Vec(_SX(X,Y), _SY(Y)), module, Generic::Z))
//LEDs
#define LED(Y,Z) addChild(createValueLight<TinyLight<GreenRedPolarityLight>>(Vec(_LX(X), 20), &module->Z))
//Screws
#define _SCREW(X,Y) addChild(createScrew<ScrewBlack>(Vec(_SC(X), Y)))
#define SCREWS(X) _SCREW(X, 0);_SCREW(X, 365)
//Control knobs
#define CTRL(X,Y,Z) addParam(createParam<Davies1900hWhiteKnob>(Vec(_CX(X, Y), _CY(Y)), module, Generic::Z, 0.0, 1.0, 0.0))
//DON'T USE ANYTHING WITH A _ BEFORE IT. E.G. _PANEL IS USED BY THE SHOW MACRO
#define _PANEL(X) setModule(new Generic(this)); box.size = Vec(15*X, 380); {\
	Panel *panel = new DarkPanel(); panel->box.size = box.size;\
	panel->backgroundImage = Image::load(k.slug()); addChild(panel); }

#define s2s(a,b) { (b / a), 1. / b }
#define s1s(b) { 0., 1. / b }
#define pair(r,i) { (r * r + i * i), (r * r + i * i) / (-2. * r) }
#define real(r) pair(r, 0.)

#define phi(N) exp(log((1. + sqrt(5)) / 2.) / N)
#define rmul(N) ((phi(N) * phi(N) - 1.) / (2. * phi(N)))
#define imul(N) ((phi(N) * phi(N) + 1.) / (2. * phi(N)))
#define pick(k,N) (2. * k - 1.) * pi / 2. / N
#define cheb(k,N) pair(-sin(pick(k,N)) * rmul(N), cos(pick(k,N)) * imul(N))
//===================================================================================================
//========================================================================================= FUNCTIONS
//NOTES ON GETTING OTHER VARIABLES INTO JUST A SPECIFIC CLASS
//A static type VAR will persist across the whole plugin.
//A static declaration in a function will persist across any instances using that function.
//A static declaration in a BEGIN ... END section will persist across all instances of the one module kind.
//

//TYPE int DEF x[100] VAR //Use GENERIC to initialize
TYPE float DEF v[4] VAR
TYPE float DEF vo[4] VAR


TYPE float DEF quant(float arg) SUB
	//C++ function here minus the {} outer brackets
	int x = (int)(arg * 12.0 + 0.5);
	return (float)x / 12.0;
RETURN

TYPE float DEF Freq(float in, float invSample) SUB
	if(in == 0.) return 1.;
	return in * invSample / (3. * in * invSample + 2.);//alpha
RETURN

TYPE float DEF SK(float in, float f1, float f2, float *b1, float *b2, float *x, float bp, float rez) SUB
	//ZDF
	float pf1 = f1;// / (2. + f1);
	float pf2 = f2;// / (2. + f2);
	float b = *b2 * (1.0 + rez) + bp;
	float dy1 = pf1 * (*x + in - 2. * (*b1 + b));
	float dyb = pf2 * (2. * (*b1 - b) + dy1) / (1. + pf2);
	dy1 -= dyb;
	dyb /= pf1 - 1.;
	*x = in;
	*b1 += dy1;
	return *b2 = dyb;//lpf
RETURN

//===================================================================================================
//=============================================================================================== DSP
//EI 4 by 4
BEGIN(PMKRTWidget, "PM Phase Modulator")
	float inv = 1.0 / gSampleRate;
	float a = Freq(440 * PARACV(POT1_PARAM, 4.0), inv);//lpf
	float b = PARA(POT2_PARAM);//depth
	float c = Freq(440 * PARACV(POT3_PARAM, 4.0), inv);//hpf
	float d = PARA(POT4_PARAM);//fb
	float t = IN(IN1_INPUT) + (2 * vo[2] - vo[3]) * (2.0 * d - 1.0);
	t = SK(t, 0.0, a, &v[0], &v[1], &v[2], 0.0, 0.0);
	t += IN(IN2_INPUT);
	t = t < 0 ? sin(-t * b * 4.0) : sin(t * b * 4.0);//sub
	t += IN(IN3_INPUT);
	vo[3] = vo[2];
	t -= SK(t, 0.0, c, &vo[0], &vo[1], &vo[2], 0.0, 0.0);
	OUT(OUT4_OUTPUT, t);
END

BEGIN(PLLKRTWidget, "PLL Phase Locked Loop")

END

BEGIN(VCFKRTWidget, "VCF SK Filter")

END

BEGIN(DSTKRTWidget, "DST Distortion")
	float a = IN(IN1_INPUT, 0.0);
	float b = IN(IN2_INPUT, 0.0);
	float c = IN(IN3_INPUT, 0.0);
	a *= exp(-1.0) * PARA(POT1_PARAM);
	b *= exp(1.0) * PARA(POT2_PARAM);
	c *= PARA(POT3_PARAM);
	//distort
	//everyone doing tanh, a bit different but not too far off
	b = b < 0 ? -exp(-a) - 1.0 : exp(a) - 1.0;
	//distort 2
	b = b < 0 ? -log(-b + 1.0) : log(b + 1.0);
	//distort 3
	c *= c < 0 ? -c : c;
	OUT(OUT4_OUTPUT, (a + b + c) * 2.0 * PARA(POT4_PARAM));
END

//EI 1 in 3
BEGIN(VCOKRTWidget, "VCO 2 Subs")

END

BEGIN(LFOKRTWidget, "LFO Gate Synced")
	float *ph = &v[3];//phase
	float f = Math::pi * 55.0 * PARACV(POT1_PARAM, 4.0);
	float tr = INCV(IN1_INPUT);
	float in = SK(tr, 0.0, Freq(f * 0.5, 1.0 / gSampleRate), &v[0], &v[1], &v[2], 0.0, 0.0);
	f *= in  / gSampleRate;//based on input sample
	*ph += f;
	if(absf(v[2] - tr) > 1.0 / 13.0) *ph = 0.0;//sync 
	if(*ph > 2.0 * Math::pi) *ph -= 2.0 * Math::pi;//wrap
	OUT(OUT2_OUTPUT, sin(*ph) * (2.0 * PARA(POT2_PARAM) - 1.0));
	OUT(OUT3_OUTPUT, sin(*ph + 2.0 * Math::pi / 3.0) * (2.0 * PARA(POT3_PARAM) - 1.0));
	OUT(OUT4_OUTPUT, sin(*ph - 2.0 * Math::pi / 3.0) * (2.0 * PARA(POT4_PARAM) - 1.0));
END

BEGIN(CHDKRTWidget, "CHD Chord Quantizer")
	float a = 2 * PARA(POT1_PARAM) - 1.0 + IN(IN1_INPUT, 0.0);
	float b = 2 * PARA(POT2_PARAM) - 1.0 + a;
	float c = 2 * PARA(POT3_PARAM) - 1.0 + b;
	float t = PARA(POT4_PARAM);
	OUTCV(OUT2_OUTPUT, quant(a), t);
	OUTCV(OUT3_OUTPUT, quant(b), t);
	OUTCV(OUT4_OUTPUT, quant(c), t);
END

BEGIN(PHYKRTWidget, "PHY Physical Model")
	float inv = 1.0 / gSampleRate;
	float d = v[0] * v[0] + 0.000000001;//checks no crash
	//float a = d * v[3];
	float b = -9 * v[0] * v[1] * v[2];
	float c = 12 * v[1] * v[1] * v[1];
	float e = PARACV(POT1_PARAM, 2.0);
	e *= (1 - d) * v[1] * d * e;
	vo[3] = v[3];
	v[3] = - (b + c + e);
	OUT(OUT1_OUTPUT, b);
	OUT(OUT2_OUTPUT, c);
	OUT(OUT3_OUTPUT, e);
	OUT(OUT4_OUTPUT, v[3]);
	v[3] /= d;//achieves uncertainty
	b = PARACV(POT2_PARAM, 3.0);//1 Hz centre
	c = PARACV(POT3_PARAM, 3.0);
	e = PARACV(POT4_PARAM, 3.0);
	vo[2] = v[2];
	v[2] = (1.0 - exp(-b * inv)) * (v[2] + (v[3] + vo[3]) * 0.5);//emmissive model
	vo[1] = v[1];
	v[1] = (1.0 - exp(-c * inv)) * (v[1] + (v[2] + vo[2]) * 0.5);
	v[0] = (1.0 - exp(-e * inv)) * (v[0] + (v[1] + vo[1]) * 0.5);
END

//========================================================================================================
//=========================================================================================== INIT AND GUI

LIBINIT
	//gloal plugin initializer
GENERIC
	light = 0.0;
	v[0] = v[1] = v[2] = v[3] = 0.0;
	vo[0] = vo[1] = vo[2] = vo[3] = 0.000000001;//startup
STEP
	KRTRUN(this);//Can also apply it to other instances to share IO
SHOW(4)

	SCREWS(1);

	CTRL(0, 0, POT1_PARAM);
	CTRL(0, 1, POT2_PARAM);
	CTRL(0, 2, POT3_PARAM);
	CTRL(0, 3, POT4_PARAM);

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
	//INPUT(1, 2, CUBE_INPUT);

	LED(0, light);
LIBEND
//===================================================================================================