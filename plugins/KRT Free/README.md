# KRT Free (Electronics Inside 4 by 4 Pack)

There are 4 developing modules.

  * VCF - A Sallen-Key filter, with various 2, 3 and 4 pole basics, feedback rez with low and band pass inputs.
  * PLL - A dual PLL interpolation VCO, full multipliers and independant channel filters, plus VCO FM.
  * PM - A phase modulator through zero and DC sub flip. Various insert points with feedback.
  * DST - A distrotion unit, with 3 algorithms and a summed out.

# KRT Free (Electronics Inside 1 in 3 Pack)

There are 4 developing modules.

  * VCO - A 3 output shaped oscillator, as 2 sub octaves and independant shapes.
  * LFO - An LFO with three sine phases. The in is a beat rate trigger.
  * CHD - A 3 note chord quantizer. With drift tuning.
  * PHY - A complex physical modelled 4 output wave source.

# Source DSL (All-in-one DSP.hpp edits)

The source has a domain specific language to compile modules. Current syntax includes

  * BEGIN(classname, "readable name") ... cpp inards of step ... END
  * IN, OUT, PARA, LIGHT for all those easy controls used in DSP
  * LIBINIT ... global ... GENERIC ... local ... STEP ... tick ... SHOW(size) ... gui ... LIBEND
  * INPUT, OUTPUT, CTRL, LED to place things on the show
  * IS(classname) used in gui for specific design
  * libs.hpp place to put all your library includes
  * a standardized co-ordinate system based on size 5 multiples, 4 centred knobs, 6 sockets in 2 columns and 2 leds per size 5
  * a .svg standard path in /res based on classname
  * TYPE ... type expression ... DEF ... func name and args ... SUB ... code ... RETURN for generic functions
  * TYPE ... type expression ... DEF ... var name (and array) ... VAR for generic variables

  