###Look! A version of CAPlayThrough that works...

...for the most part. Standard disclaimers apply, etc.

I've cobbled together improvements to CARingBuffer.cpp and CARingBuffer.h that were based on an older version of CARingBuffer that I found in an older version of the CoreAudio SDK (Thanks, Pacifist!)

There were many bugs in that class which caused havoc in the CAPlayThrough sample, especially when mixing devices that have varying sample rates (and drifting clocks.)

Please: if you find bugs, try and fix them yourself, and contribute back to this repo for the benefit of others. I don't have time to respond to bug reports.
