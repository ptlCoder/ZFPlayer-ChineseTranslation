//
//  ZFMediaPlayback.h
//  ZFPlayer
//
// Copyright (c) 2016年 任子丰 ( http://github.com/renzifeng )
//
// 自定义播放器

#import <Foundation/Foundation.h>
#import "ZFPlayerView.h"

NS_ASSUME_NONNULL_BEGIN
///  播放状态：未知、播放中、暂停、失败、停止
typedef NS_ENUM(NSUInteger, ZFPlayerPlaybackState) {
    ZFPlayerPlayStateUnknown = 0,
    ZFPlayerPlayStatePlaying,
    ZFPlayerPlayStatePaused,
    ZFPlayerPlayStatePlayFailed,
    ZFPlayerPlayStatePlayStopped
};
///  加载状态：未知、就绪、可以播放、自动播放、播放暂停
typedef NS_OPTIONS(NSUInteger, ZFPlayerLoadState) {
    ZFPlayerLoadStateUnknown        = 0,
    ZFPlayerLoadStatePrepare        = 1 << 0,
    ZFPlayerLoadStatePlayable       = 1 << 1,
    ZFPlayerLoadStatePlaythroughOK  = 1 << 2, // Playback will be automatically started.
    ZFPlayerLoadStateStalled        = 1 << 3, // Playback will be automatically paused in this state, if started.
};
///  播放画面拉伸模式：无拉伸、等比例拉伸不裁剪、部分内容裁剪按比例填充、非等比例填满
typedef NS_ENUM(NSInteger, ZFPlayerScalingMode) {
    ZFPlayerScalingModeNone,       // No scaling.
    ZFPlayerScalingModeAspectFit,  // Uniform scale until one dimension fits.
    ZFPlayerScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents.
    ZFPlayerScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds.
};

@protocol ZFPlayerMediaPlayback <NSObject>

@required
///  播放器视图继承于ZFPlayerView，处理一些手势冲突
@property (nonatomic) ZFPlayerView *view;

///  0...1.0，播放器音量，不影响设备的音量大小
@property (nonatomic) float volume;

///  播放器是否静音，不影响设备静音
@property (nonatomic, getter=isMuted) BOOL muted;

///  0.5...2，播放速率，正常速率为 1
@property (nonatomic) float rate;

///  当前播放时间
@property (nonatomic, readonly) NSTimeInterval currentTime;

///  播放总时间
@property (nonatomic, readonly) NSTimeInterval totalTime;

///  缓冲时间
@property (nonatomic, readonly) NSTimeInterval bufferTime;

///  视频播放定位时间
@property (nonatomic) NSTimeInterval seekTime;

///  视频是否正在播放中
@property (nonatomic, readonly) BOOL isPlaying;

///  视频播放视图的填充模式，默认不做任何拉伸
@property (nonatomic) ZFPlayerScalingMode scalingMode;

///  检查视频播放是否准备就绪，返回YES，调用play方法直接播放视频；返回NO，调用play方法内部自动调用prepareToPlay方法进行视频播放准备工作
@property (nonatomic, readonly) BOOL isPreparedToPlay;

///  媒体播放资源URL
@property (nonatomic) NSURL *assetURL;

///  视频的尺寸
@property (nonatomic, readonly) CGSize presentationSize;

///  视频播放状态
@property (nonatomic, readonly) ZFPlayerPlaybackState playState;

///  视频的加载状态
@property (nonatomic, readonly) ZFPlayerLoadState loadState;

///  准备播放
@property (nonatomic, copy, nullable) void(^playerPrepareToPlay)(id<ZFPlayerMediaPlayback> asset, NSURL *assetURL);

///  播放进度改变
@property (nonatomic, copy, nullable) void(^playerPlayTimeChanged)(id<ZFPlayerMediaPlayback> asset, NSTimeInterval currentTime, NSTimeInterval duration);

///  视频缓冲进度改变
@property (nonatomic, copy, nullable) void(^playerBufferTimeChanged)(id<ZFPlayerMediaPlayback> asset, NSTimeInterval bufferTime);

///  视频播放状态改变
@property (nonatomic, copy, nullable) void(^playerPlayStatChanged)(id<ZFPlayerMediaPlayback> asset, ZFPlayerPlaybackState playState);

///  视频加载状态改变
@property (nonatomic, copy, nullable) void(^playerLoadStatChanged)(id<ZFPlayerMediaPlayback> asset, ZFPlayerLoadState loadState);

///  视频播放已经结束
@property (nonatomic, copy, nullable) void(^playerDidToEnd)(id<ZFPlayerMediaPlayback> asset);


///  视频播放准备，中断除non-mixible之外的任何音频会话
- (void)prepareToPlay;

///  重新进行视频播放准备
- (void)reloadPlayer;

///  视频播放
- (void)play;

///  视频暂停
- (void)pause;

///  视频重新播放
- (void)replay;

///  视频播放停止
- (void)stop;

///  视频播放当前时间的画面截图
- (UIImage *)thumbnailImageAtCurrentTime;

///  替换当前媒体资源地址
- (void)replaceCurrentAssetURL:(NSURL *)assetURL;

///  调节播放进度
- (void)seekToTime:(NSTimeInterval)time completionHandler:(void (^ __nullable)(BOOL finished))completionHandler;


@end

NS_ASSUME_NONNULL_END
