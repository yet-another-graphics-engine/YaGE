#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include "macosx.h"

#include <string>

namespace yage {
namespace platform {

OSXPlayer::OSXPlayer(std::string url) : Player() {
    url_ = url;
    NSURL *nsurl = [NSURL fileURLWithPath:[NSString stringWithCString:url.c_str() encoding:[NSString defaultCStringEncoding]]];
    NSError *e= nil;
    player_ = [[AVAudioPlayer alloc] initWithContentsOfURL:nsurl error:&e];
    if (e) {
        NSLog(@"%@", [e localizedDescription]);
    }
}

bool OSXPlayer::play(void) {
    return [player_ play];
}

void OSXPlayer::pause(void) {
    [player_ pause];
}

void OSXPlayer::stop(void) {
    [player_ stop];
}

bool OSXPlayer::is_playing(void) {
    return player_.playing;
}

}
}

