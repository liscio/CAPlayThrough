/*	Copyright © 2007 Apple Inc. All Rights Reserved.
	
	Disclaimer: IMPORTANT:  This Apple software is supplied to you by 
			Apple Inc. ("Apple") in consideration of your agreement to the
			following terms, and your use, installation, modification or
			redistribution of this Apple software constitutes acceptance of these
			terms.  If you do not agree with these terms, please do not use,
			install, modify or redistribute this Apple software.
			
			In consideration of your agreement to abide by the following terms, and
			subject to these terms, Apple grants you a personal, non-exclusive
			license, under Apple's copyrights in this original Apple software (the
			"Apple Software"), to use, reproduce, modify and redistribute the Apple
			Software, with or without modifications, in source and/or binary forms;
			provided that if you redistribute the Apple Software in its entirety and
			without modifications, you must retain this notice and the following
			text and disclaimers in all such redistributions of the Apple Software. 
			Neither the name, trademarks, service marks or logos of Apple Inc. 
			may be used to endorse or promote products derived from the Apple
			Software without specific prior written permission from Apple.  Except
			as expressly stated in this notice, no other rights or licenses, express
			or implied, are granted by Apple herein, including but not limited to
			any patent rights that may be infringed by your derivative works or by
			other works in which the Apple Software may be incorporated.
			
			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
			MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
			THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
			FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
			OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
			
			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
			OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
			SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
			INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
			MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
			AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
			STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
			POSSIBILITY OF SUCH DAMAGE.
*/
/*=============================================================================
	AudioDevice.cpp
	
=============================================================================*/

#include "AudioDevice.h"

void	AudioDevice::Init(AudioDeviceID devid, bool isInput)
{
	mID = devid;
	mIsInput = isInput;
	if (mID == kAudioDeviceUnknown) return;
	
	UInt32 propsize;
	AudioObjectPropertyAddress aopa;
    
	propsize = sizeof(UInt32);
    aopa.mSelector = kAudioDevicePropertySafetyOffset;
    aopa.mScope = kAudioObjectPropertyScopeGlobal;
    aopa.mElement = kAudioObjectPropertyElementMaster;    
    verify_noerr(AudioObjectGetPropertyData( mID, &aopa, 0, NULL, &propsize, &mSafetyOffset ));
	
	propsize = sizeof(UInt32);
    aopa.mSelector = kAudioDevicePropertyBufferFrameSize;
    verify_noerr(AudioObjectGetPropertyData( mID, &aopa, 0, NULL, &propsize, &mBufferSizeFrames ));
	
	propsize = sizeof(AudioStreamBasicDescription);
    aopa.mSelector = kAudioDevicePropertyStreamFormat;
    aopa.mScope = mIsInput ? kAudioDevicePropertyScopeInput : kAudioDevicePropertyScopeOutput;
    verify_noerr(AudioObjectGetPropertyData( mID, &aopa, 0, NULL, &propsize, &mFormat ));
}

void	AudioDevice::SetBufferSize(UInt32 size)
{
	UInt32 propsize = sizeof(UInt32);
	AudioObjectPropertyAddress aopa;
    
    aopa.mSelector = kAudioDevicePropertyBufferFrameSize;
    aopa.mScope = mIsInput ? kAudioDevicePropertyScopeInput : kAudioDevicePropertyScopeOutput;
    aopa.mElement = kAudioObjectPropertyElementMaster;
    verify_noerr(AudioObjectSetPropertyData( mID, &aopa, 0, NULL, propsize, &size ) );

	propsize = sizeof(UInt32);
    verify_noerr(AudioObjectGetPropertyData( mID, &aopa, 0, NULL, &propsize, &mBufferSizeFrames ));    
}

int		AudioDevice::CountChannels()
{
	OSStatus err;
	UInt32 propSize;
	AudioObjectPropertyAddress aopa;    
	int result = 0;
	
    aopa.mSelector = kAudioDevicePropertyStreamConfiguration;
    aopa.mScope = mIsInput ? kAudioDevicePropertyScopeInput : kAudioDevicePropertyScopeOutput;
    aopa.mElement = kAudioObjectPropertyElementMaster;
    err = AudioObjectGetPropertyDataSize(mID, &aopa, 0, NULL, &propSize );
	if (err) return 0;

	AudioBufferList *buflist = (AudioBufferList *)malloc(propSize);
    err = AudioObjectGetPropertyData(mID, &aopa, 0, NULL, &propSize, buflist );
	if (!err) {
		for (UInt32 i = 0; i < buflist->mNumberBuffers; ++i) {
			result += buflist->mBuffers[i].mNumberChannels;
		}
	}
	free(buflist);
	return result;
}

char *	AudioDevice::GetName(char *buf, UInt32 maxlen)
{
	AudioObjectPropertyAddress aopa;
    aopa.mSelector = kAudioDevicePropertyDeviceName;
    aopa.mScope = kAudioObjectPropertyScopeGlobal;
    aopa.mElement = kAudioObjectPropertyElementMaster;
    verify_noerr(AudioObjectGetPropertyData(mID, &aopa, 0, NULL, &maxlen, buf));
	return buf;
}
