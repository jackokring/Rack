#include "KRTFree.hpp"
#include "KRTFreeStep.cpp"

#define KRTRES(X,Y) void (*(X::fn()))() { return Y; } char* X::slug() { return ""X""; }
#define IMAGE(X) "plugins/KRTFree/res/"X".png"

void nop() {
	return;
}

//EI 4 by 4
KRTRES(PMKRTWidget, nop);
KRTRES(PLLKRTWidge, nop);
KRTRES(VCFKRTWidge, nop);
KRTRES(DSTKRTWidge, nop);

//EI 1 in 3
KRTRES(VCOKRTWidget, nop);
KRTRES(LFOKRTWidget, nop);
KRTRES(CHDKRTWidget, nop);
KRTRES(PHYKRTWidget, nop);

Generic::Generic(KRTWidget x) {
	k = x;
	lights = 0.0;
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

void Generic::step() {
	KRTPTR(k.fn);
}

KRTWidget::KRTWidget() {
	Generic *module = new Generic(this);
	setModule(module);
	box.size = Vec(15*5, 380);

	{
		Panel *panel = new DarkPanel();
		panel->box.size = box.size;
		panel->backgroundImage = Image::load(IMAGE(k.slug()));//KRTTag[]
		addChild(panel);
	}

	addChild(createScrew<ScrewBlack>(Vec(15, 0)));
	addChild(createScrew<ScrewBlack>(Vec(15, 365)));

	addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 32), module, Generic::CH1_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 85), module, Generic::CH2_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 137), module, Generic::CH3_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Davies1900hWhiteKnob>(Vec(19, 190), module, Generic::CH4_PARAM, 0.0, 1.0, 0.0));

	if(module.fn == PHYKRTWidget::fn)
		addOutput(createOutput<PJ3410Port>(Vec(4, 239), module, Generic::OUT1_OUTPUT));
	else
		addInput(createInput<PJ3410Port>(Vec(4, 239), module, Generic::IN1_INPUT));

	if(module.fn == VCOKRTWidget::fn || module.fn == LFOKRTWidget::fn || module.fn == CHDKRTWidget::fn) {
		addOutput(createOutput<PJ3410Port>(Vec(40, 239), module, Generic::OUT2_OUTPUT));
		addOutput(createOutput<PJ3410Port>(Vec(4, 278), module, Generic::OUT3_OUTPUT));
	} else {
		addInput(createInput<PJ3410Port>(Vec(40, 239), module, Generic::IN2_INPUT));
		addInput(createInput<PJ3410Port>(Vec(4, 278), module, Generic::IN3_INPUT));
	}

	addOutput(createOutput<PJ3410Port>(Vec(40, 278), module, Generic::OUT4_OUTPUT));

	addChild(createValueLight<MediumLight<GreenRedPolarityLight>>(Vec(31, 309), &module->lights));
}
