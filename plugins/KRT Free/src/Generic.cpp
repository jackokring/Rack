#include "KRTFree.hpp"

#define IMAGE(X) "plugins/" SLUGGENERIC "/res/" #X ".svg"
#define KRTRES(X) void (*(X::fn()))(Generic) { return X::stepI; } char* X::slug() { return IMAGE(X); }
#define KRTRUN(X) (*(_k.fn()))(X)

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