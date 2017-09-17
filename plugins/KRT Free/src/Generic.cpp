#include "KRTFree.hpp"

#define KRTRES(X) void (*(X::fn()))(Generic) { return X::stepI; } char* X::slug() { return #X; }
#define IMAGE(X) "plugins/KRTFree/res/" #X ".png"
#define KRTRUN(X,Y) (*(X()))(Y)
#define IS(X) (module.fn == X::fn)
#define OUTPUT(X,Y,Z) addOutput(createOutput<PJ3410Port>(Vec(X, Y), module, Generic::Z))
#define INPUT(X,Y,Z) addInput(createInput<PJ3410Port>(Vec(X, Y), module, Generic::Z))
#define LED(X,Y,Z) addChild(createValueLight<MediumLight<GreenRedPolarityLight>>(Vec(X, Y), &module->Z))
#define SCREW(X,Y) addChild(createScrew<ScrewBlack>(Vec(X, Y)))
#define CTRL(X,Y,Z) addParam(createParam<Davies1900hWhiteKnob>(Vec(X, Y), module, Generic::Z, 0.0, 1.0, 0.0))
#define PANEL(X) box.size = Vec(15*X, 380); { Panel *panel = new DarkPanel(); panel->box.size = box.size;\
	panel->backgroundImage = Image::load(IMAGE(k.slug())); addChild(panel); }

//EI 4 by 4
KRTRES(PMKRTWidget);
KRTRES(PLLKRTWidge);
KRTRES(VCFKRTWidge);
KRTRES(DSTKRTWidge);

//EI 1 in 3
KRTRES(VCOKRTWidget);
KRTRES(LFOKRTWidget);
KRTRES(CHDKRTWidget);
KRTRES(PHYKRTWidget);

Generic::Generic(KRTWidget x) {
	k = x;
	lights = 0.0;
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

void Generic::step() {
	KRTRUN(k.fn, this);//Can also apply it to other instances to share IO
}

KRTWidget::KRTWidget() {
	setModule(new Generic(this));
	PANEL(5);

	SCREW(15, 0);
	SCREW(15, 365);

	CTRL(19, 32, CH1_PARAM);
	CTRL(19, 85, CH2_PARAM);
	CTRL(19, 137, CH3_PARAM);
	CTRL(19, 190, CH4_PARAM);

	if(IS(PHYKRTWidget))
		OUTPUT(4, 239, OUT1_OUTPUT);
	else
		INPUT(4, 239, IN1_INPUT);

	if(IS(VCOKRTWidget) || IS(LFOKRTWidget) || IS(CHDKRTWidget)) {
		OUTPUT(40, 239, OUT2_OUTPUT);
		OUTPUT(4, 278, OUT3_OUTPUT);
	} else {
		INPUT(40, 239, IN2_INPUT);
		INPUT(4, 278, IN3_INPUT);
	}

	OUTPUT(40, 278, OUT4_OUTPUT);

	LED(31, 309, lights);
}
