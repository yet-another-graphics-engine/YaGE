#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include "macosx.h"

#include <string>

namespace yage {
namespace platform {

OSXPlayer::OSXPlayer(std::string url) : Player() {
    url_ = url;
    NSURL *nsurl;
    NSError *err = nil;
    content_ = nil;

    NSString *nsurlstr = [NSString stringWithCString:url.c_str() encoding:[NSString defaultCStringEncoding]];
    if ([nsurlstr hasPrefix:@"http"] || [nsurlstr hasPrefix:@"ftp"]) {
        nsurl = [NSURL URLWithString:nsurlstr];
        content_ = [NSData dataWithContentsOfURL:nsurl];
        player_ = [[AVAudioPlayer alloc] initWithData:content_ error:&err];
    } else {
        nsurl = [NSURL fileURLWithPath:nsurlstr];
        player_ = [[AVAudioPlayer alloc] initWithContentsOfURL:nsurl error:&err];
    }
    [nsurlstr release];
    [nsurl release];
    if (err) {
        NSLog(@"%@", [err localizedDescription]);
        //[err release];
    }
}

OSXPlayer::~OSXPlayer() {
    [content_ release];
    [player_ release];
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

