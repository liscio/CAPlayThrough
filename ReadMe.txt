### CAPlayThrough ###

===========================================================================
DESCRIPTION:

The CAPlayThrough example project provides a Cocoa based sample application for obtaining all possible input and output devices on the system, setting the default device for input and/or output, and playing through audio from the input device to the output. The application uses two instances of the AUHAL audio unit (one for input, one for output) and a varispeed unit in between to compensate for minor sample rate drift. The app also uses a ring buffer to store the captured audio data from input and access it as needed by the output unit.

===========================================================================
BUILD REQUIREMENTS:

Mac OS X v10.6 or later

===========================================================================
RUNTIME REQUIREMENTS:

Mac OS X v10.6 or later

===========================================================================
PACKAGING LIST:

CAPlayThroughController.h
CAPlayThroughController.mm
- Controller class for managing PlayThrough objects. Handles building the available devices menu, resetting the PlayThrough objects, and starting and stopping the audio feed.

CAPlayThrough.h
CAPlayThough.cpp
- The CAPlayThrough class. Handles capturing data from input, storing to the ring buffer, and retreiving it for use by the output unit. Also performs the setup for the ring buffer, two AUHAL units and varispeed unit.

===========================================================================
CHANGES FROM PREVIOUS VERSIONS:

Version 1.0
- First version.

===========================================================================
Copyright (C) 2009 Apple Inc. All rights reserved.
