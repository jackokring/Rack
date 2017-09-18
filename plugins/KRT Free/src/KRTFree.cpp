#include "KRTFree.hpp"
#define KRTMOD(X,Y) createModel<X>(this, #X, Y) 

#define COMPILING 1

//The overrides
#define BEGIN(X,Y) KRTMOD(X,Y); / ## *
#define END * ## /
#define LIBINIT / ## *
#define LIBEND * ## /


struct KRTFreePlugin : Plugin {
	KRTFreePlugin() {
		slug = "KRTFree";
		name = "KRT EI";
#include "DSP.hpp"
	}
};

#define BEGIN(X,Y) void X::stepI(Generic _g) {
#define END }
#include "DSP.hpp"

Plugin *init() {
	KRTInit();
	return new KRTFreePlugin();
}
