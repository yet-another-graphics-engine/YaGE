#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include "macosx.h"

#include <string>

namespace yage {
namespace platform {

OSXPlayer::OSXPlayer(std::string url) : Player() {
    url_ = url;
    NSURL *nsurl;
    NSString *nsurlstr = [NSString stringWithCString:url.c_str() encoding:[NSString defaultCStringEncoding]];
    nsurl = [NSURL URLWithString:nsurlstr];
    player_ = [AVPlayer playerWithURL:nsurl];
    [nsurlstr release];
    [nsurl release];
}

OSXPlayer::~OSXPlayer() {
    [player_ release];
}

bool OSXPlayer::play(void) {
    [player_ play];
    return is_playing();
}

void OSXPlayer::pause(void) {
    [player_ pause];
}

void OSXPlayer::stop(void) {
    [player_ pause];
    [player_ seekToTime:CMTimeMakeWithSeconds(1.0, 1)];
}

bool OSXPlayer::is_playing(void) {
    return player_.rate > 0 && !player_.error;
}

}
}

