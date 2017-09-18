All the edits are to be done in DSP.hpp
=======================================

See notes in Generic of other minor edits on new module add.

This is a DSL adaptation to includes, which makes for one file compiling in different ways depending on inlusion location.
If the rules of the DSL are followed, compile is easy with no fiddling with many files. If an error is introduced, compiling will fail, and the error might not be too helpful, but could be, depending on experience.