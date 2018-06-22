//
//  ZFAVPlayerManager.h
//  ZFPlayer
//
// Copyright (c) 2016年 任子丰 ( http://github.com/renzifeng )

#import <Foundation/Foundation.h>
#if __has_include(<ZFPlayer/ZFPlayer.h>)
#import <ZFPlayer/ZFPlayer.h>
#else
#import "ZFPlayer.h"
#endif

@interface ZFAVPlayerManager : NSObject <ZFPlayerMediaPlayback>

@end
