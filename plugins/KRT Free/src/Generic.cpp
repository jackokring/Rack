#include "KRTFree.hpp"

#define IMAGE(X) "plugins/KRTFree/res/" #X ".svg"
#define KRTRES(X) void (*(X::fn()))(Generic) { return X::stepI; } char* X::slug() { return IMAGE(X); }
#define KRTRUN(X) (*(_k.fn()))(X)
#define IS(X) (module.fn == X::fn)
#define _CX(X) 20 + 75 * X
#define _CY(Y) 32 + 51 * Y
#define _SX(X) 4 + 75 * X / 2
#define _SY(Y) 240 + 40 * Y
#define _SC(Y) 15 + 75 * Y
#define _LY(Y) 309 + 20 * Y
#define OUTPUT(X,Y,Z) addOutput(createOutput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
#define INPUT(X,Y,Z) addInput(createInput<PJ3410Port>(Vec(_SX(X), _SY(Y)), module, Generic::Z))
#define LED(Y,Z) addChild(createValueLight<MediumLight<GreenRedPolarityLight>>(Vec(31, _LY(Y)), &module->Z))
#define _SCREW(X,Y) addChild(createScrew<ScrewBlack>(Vec(_SC(X), Y)))
#define CTRL(X,Y,Z) addParam(createParam<Davies1900hWhiteKnob>(Vec(_CX(X), _CY(Y)), module, Generic::Z, 0.0, 1.0, 0.0))
#define SCREWS(X) _SCREW(X, 0);_SCREW(X, 365)
#define _PANEL(X) setModule(new Generic(this)); box.size = Vec(15*X, 380); {\
	Panel *panel = new DarkPanel(); panel->box.size = box.size;\
	panel->backgroundImage = Image::load(k.slug()); addChild(panel); }
#define LIBINIT void KRTInit() {
#define GENERIC } Generic::Generic(KRTWidget _x) { _k = _x; params.resize(NUM_PARAMS); inputs.resize(NUM_INPUTS);\
	 outputs.resize(NUM_OUTPUTS);
#define STEP } void Generic::step() {
#define SHOW(X) } KRTWidget::KRTWidget() { _PANEL(X)
#define LIBEND }

#define COMPILING 1
#define BEGIN(X,Y) KRTRES(X); / ## *
#define END * ## /

//NEW MODULES NEED:
//CODE IN DSP.hpp
#include "DSP.hpp"