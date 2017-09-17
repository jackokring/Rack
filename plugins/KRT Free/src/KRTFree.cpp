#include "KRTFree.hpp"
#define KRTMOD(X,Y) createModel<X>(this, ""X"", Y) 

struct KRTFreePlugin : Plugin {
	KRTFreePlugin() {
		slug = "KRTFree";
		name = "KRT EI";
		KRTMOD(PMKRTWidget, "PM Phase Modulator");
		KRTMOD(PLLKRTWidget, "PLL Phase Locked Loop");
		KRTMOD(VCFKRTWidget, "VCF SK Filter");
		KRTMOD(DSTKRTWidget, "DST Distortion");
		//
		KRTMOD(VCOKRTWidget, "VCO 2 Subs");
		KRTMOD(LFOKRTWidget, "LFO Gate Synced");
		KRTMOD(CHDKRTWidget, "CHD Chord Quantizer");
		KRTMOD(PHYKRTWidget, "PHY Physical Model");
	}
};


Plugin *init() {
	KRTInit();
	return new KRTFreePlugin();
}
