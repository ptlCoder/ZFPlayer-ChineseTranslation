//
//  ZFPlayer.h
//  ZFPlayer
//
// Copyright (c) 2016年 任子丰 ( http://github.com/renzifeng )


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZFPlayerMediaPlayback.h"
#import "ZFOrientationObserver.h"
#import "ZFPlayerMediaControl.h"
#import "ZFPlayerGestureControl.h"
#import "ZFFloatView.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZFPlayerController : NSObject

/// 初始化时传递的容器视图，用来显示播放器view，和播放器view同等大小
@property (nonatomic, readonly) UIView *containerView;

/// 初始化时传递的播放器manager，必须遵守`ZFPlayerMediaPlayback`协议
@property (nonatomic, readonly) id<ZFPlayerMediaPlayback> currentPlayerManager;

/// 此属性是设置显示的控制层，自定义UIView遵守`ZFPlayerMediaControl`协议，实现相关协议就可以满足自定义控制层的目的。
@property (nonatomic, strong) UIView<ZFPlayerMediaControl> *controlView;


/// 普通播放的初始化
+ (instancetype)playerWithPlayerManager:(id<ZFPlayerMediaPlayback>)playerManager containerView:(UIView *)containerView;

/// 普通播放的初始化
- (instancetype)initWithPlayerManager:(id<ZFPlayerMediaPlayback>)playerManager containerView:(UIView *)containerView;

/// 列表播放的初始化
+ (instancetype)playerWithScrollView:(UIScrollView *)scrollView playerManager:(id<ZFPlayerMediaPlayback>)playerManager containerViewTag:(NSInteger)containerViewTag;

/// 列表播放的初始化
- (instancetype)initWithScrollView:(UIScrollView *)scrollView playerManager:(id<ZFPlayerMediaPlayback>)playerManager containerViewTag:(NSInteger)containerViewTag;


@end

@interface ZFPlayerController (ZFPlayerTimeControl)

/// 当前播放视频的时间，支持KVO
@property (nonatomic, readonly) NSTimeInterval currentTime;

/// 当前播放视频总时间，支持KVO
@property (nonatomic, readonly) NSTimeInterval totalTime;

/// 当前播放视频缓冲时间，支持KVO
@property (nonatomic, readonly) NSTimeInterval bufferTime;

/// 根据播放的时间和总时间，计算出当前播放的进度，取值范围0...1
@property (nonatomic, readonly) float progress;

/// 根据播放缓冲时间和总时间，计算出当前缓冲的进度，取值范围0...1
@property (nonatomic, readonly) float bufferProgress;

/// 调节播放进度
- (void)seekToTime:(NSTimeInterval)time completionHandler:(void (^ __nullable)(BOOL finished))completionHandler;

@end

@interface ZFPlayerController (ZFPlayerPlaybackControl)

/// 0...1.0,调节系统的声音，要是调节播放器声音可以使用播放器管理类设置
@property (nonatomic) float volume;

/// 系统静音，要是调节播放器静音可以使用播放器管理类设置
@property (nonatomic, getter=isMuted) BOOL muted;

// 0...1.0, 系统屏幕亮度
@property (nonatomic) float brightness;

/// 移动网络下自动播放, default is NO.
@property (nonatomic, getter=isWWANAutoPlay) BOOL WWANAutoPlay;

/// 当前播放的下标，只适用于设置了`assetURLs`
@property (nonatomic) NSInteger currentPlayIndex;

/// 当退到后台后是否暂停播放，前提是支持后台播放器模式，default is YES.
@property (nonatomic) BOOL pauseWhenAppResignActive;

/// 播放完的回调
@property (nonatomic, copy, nullable) void(^playerDidToEnd)(id asset);

/// 播放下一个，只适用于设置了`assetURLs`
- (void)playTheNext;

/// 播放上一个，只适用于设置了`assetURLs`
- (void)playThePrevious;

/// 播放某一个，只适用于设置了`assetURLs`
- (void)playTheIndex:(NSInteger)index;

/// 停止播放，并且把播放器view和相关通知移除
- (void)stop;

/// 切换当前的PlayerManager，适用场景：播放某一个视频时候使用特定的播放器管理类
- (void)replaceCurrentPlayerManager:(id<ZFPlayerMediaPlayback>)manager;


@end

@interface ZFPlayerController (ZFPlayerOrientationRotation)
/// 屏幕旋转管理类
@property (nonatomic, readonly) ZFOrientationObserver *orientationObserver;

/// 是否是全屏状态，当ZFFullScreenMode == ZFFullScreenModeLandscape，当currentOrientation是LandscapeLeft或者LandscapeRight，这个值是YES
/// 当ZFFullScreenMode == ZFFullScreenModePortrait，当视频全屏后，这个值是YES
@property (nonatomic, readonly) BOOL isFullScreen;

/// 锁定当前的屏幕方向，目的是禁止设备自动旋转
@property (nonatomic, getter=isLockedScreen) BOOL lockedScreen;

/// 隐藏系统的状态栏
@property (nonatomic, getter=isStatusBarHidden) BOOL statusBarHidden;

/// 播放器view当前方向
@property (nonatomic, readonly) UIInterfaceOrientation currentOrientation;

/// 当即将全屏时候会调用
@property (nonatomic, copy, nullable) void(^orientationWillChange)(ZFPlayerController *player, BOOL isFullScreen);

/// 当已经全屏时候会调用
@property (nonatomic, copy, nullable) void(^orientationDidChanged)(ZFPlayerController *player, BOOL isFullScreen);

/// 添加设备方向的监听
- (void)addDeviceOrientationObserver;

/// 移除设备方向的监听
- (void)removeDeviceOrientationObserver;

/// 当 ZFFullScreenMode == ZFFullScreenModeLandscape使用此API设置全屏切换
- (void)enterLandscapeFullScreen:(UIInterfaceOrientation)orientation animated:(BOOL)animated;

/// 当 ZFFullScreenMode == ZFFullScreenModePortrait使用此API设置全屏切换
- (void)enterPortraitFullScreen:(BOOL)fullScreen animated:(BOOL)animated;

/// 内部根据ZFFullScreenMode的值来设置全屏切换
- (void)enterFullScreen:(BOOL)fullScreen animated:(BOOL)animated;


@end

@interface ZFPlayerController (ZFPlayerViewGesture)

/// 手势的管理类
@property (nonatomic, readonly) ZFPlayerGestureControl *gestureControl;

/// 禁用哪些手势，默认支持单击、双击、滑动、缩放手势
@property (nonatomic, assign) ZFPlayerDisableGestureTypes disableGestureTypes;


@end

@interface ZFPlayerController (ZFPlayerScrollView)

/// 初始化时候设置的scrollView
@property (nonatomic, readonly, nullable) UIScrollView *scrollView;

/// 列表播放时候是否自动播放,default is YES.
@property (nonatomic) BOOL shouldAutoPlay;

/// 列表播放的时小屏的悬浮窗，如果滑出屏幕后小窗播放，需要设置次view的默认frame，次view支持在屏幕可见范围内随意拖动。
@property (nonatomic, readonly, nullable) ZFFloatView *smallFloatView;

/// 当前播放的indexPath
@property (nonatomic, nullable) NSIndexPath *playingIndexPath;

/// 初始化时候设置的containerViewTag，根据此tag在cell上找到播放器view显示的位置
@property (nonatomic) NSInteger containerViewTag;

/// 滑出屏幕后是否停止播放，如果设置为NO，滑出屏幕后则会小窗播放，defalut is YES.
@property (nonatomic) BOOL stopWhileNotVisible;

/// 小屏悬浮窗是否正在显示
@property (nonatomic, readonly) BOOL isSmallFloatViewShow;

/// 如果列表播放时候有一个区或者普通播放时候，可以使用此API，此时 `playTheNext` `playThePrevious` `playTheIndex:`有效。
@property (nonatomic, copy, nullable) NSArray <NSURL *>*assetURLs;

/// 如果列表播放时候有多个区，使用此API
@property (nonatomic, copy, nullable) NSArray <NSArray <NSURL *>*>*sectionAssetURLs;

/// 在cell上停止当前正在播放的视频
- (void)stopCurrentPlayingCell;

//// 设置播放某indexPath，是否把当前播放indexPath滑动到UICollectionViewScrollPositionTop位置
- (void)playTheIndexPath:(NSIndexPath *)indexPath scrollToTop:(BOOL)scrollToTop;


@end

NS_ASSUME_NONNULL_END
