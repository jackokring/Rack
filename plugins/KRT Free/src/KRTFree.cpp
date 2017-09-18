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
		slug = SLUGGENERIC;
		name = PLUGNAME;
#define TYPE / ## *		
#define DEF
#define SUB
#define RETURN * ## /
#define VAR * ## /
#include "DSP.hpp"
	}
};

#define BEGIN(X,Y) void X::stepI(Generic _g) {
#define END }
#define TYPE 
#define DEF Generic::
#define SUB {
#define RETURN }
#include "DSP.hpp"

Plugin *init() {
	KRTInit();
	return new KRTFreePlugin();
}
