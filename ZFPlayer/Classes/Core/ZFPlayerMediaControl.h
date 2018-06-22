//
//  ZFPlayerMediaControl.h
//  ZFPlayer
//
// Copyright (c) 2016年 任子丰 ( http://github.com/renzifeng )
//
// 控制层协议

#import <Foundation/Foundation.h>
#import "ZFPlayerMediaPlayback.h"
#import "ZFOrientationObserver.h"
#import "ZFPlayerGestureControl.h"
#import "ZFReachabilityManager.h"
@class ZFPlayerController;

NS_ASSUME_NONNULL_BEGIN

@protocol ZFPlayerMediaControl <NSObject>

@optional

#pragma mark - 视频状态相关

///  视频播放准备就绪
- (void)videoPlayer:(ZFPlayerController *)videoPlayer prepareToPlay:(NSURL *)assetURL;

///  视频播放状态改变
- (void)videoPlayer:(ZFPlayerController *)videoPlayer playStateChanged:(ZFPlayerPlaybackState)state;

///  视频加载状态改变
- (void)videoPlayer:(ZFPlayerController *)videoPlayer loadStateChanged:(ZFPlayerLoadState)state;


#pragma mark - 播放进度

///  视频播放时间进度
- (void)videoPlayer:(ZFPlayerController *)videoPlayer
        currentTime:(NSTimeInterval)currentTime
          totalTime:(NSTimeInterval)totalTime;

///  视频缓冲进度
- (void)videoPlayer:(ZFPlayerController *)videoPlayer
         bufferTime:(NSTimeInterval)bufferTime;

///  视频定位播放时间
- (void)videoPlayer:(ZFPlayerController *)videoPlayer
       draggingTime:(NSTimeInterval)seekTime
          totalTime:(NSTimeInterval)totalTime;

///  视频播放结束
- (void)videoPlayerPlayEnd:(ZFPlayerController *)videoPlayer;


#pragma mark - 锁屏

/// 设置播放器锁屏时的协议方法
- (void)lockedVideoPlayer:(ZFPlayerController *)videoPlayer lockedScreen:(BOOL)locked;

#pragma mark - 屏幕旋转

///  播放器全屏模式即将改变
- (void)videoPlayer:(ZFPlayerController *)videoPlayer orientationWillChange:(ZFOrientationObserver *)observer;

///  播放器全屏模式已经改变
- (void)videoPlayer:(ZFPlayerController *)videoPlayer orientationDidChanged:(ZFOrientationObserver *)observer;


#pragma mark - 当前网络状态发生变化

///  当前网络状态发生变化
- (void)videoPlayer:(ZFPlayerController *)videoPlayer reachabilityChanged:(ZFReachabilityStatus)status;

#pragma mark - 手势方法

///  相关手势设置
- (BOOL)gestureTriggerCondition:(ZFPlayerGestureControl *)gestureControl
                    gestureType:(ZFPlayerGestureType)gestureType
              gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer
                          touch:(UITouch *)touch;

///  单击
- (void)gestureSingleTapped:(ZFPlayerGestureControl *)gestureControl;

///  双击
- (void)gestureDoubleTapped:(ZFPlayerGestureControl *)gestureControl;

///  开始拖拽
- (void)gestureBeganPan:(ZFPlayerGestureControl *)gestureControl
           panDirection:(ZFPanDirection)direction
            panLocation:(ZFPanLocation)location;

///  拖拽中
- (void)gestureChangedPan:(ZFPlayerGestureControl *)gestureControl
             panDirection:(ZFPanDirection)direction
              panLocation:(ZFPanLocation)location
             withVelocity:(CGPoint)velocity;

///  拖拽结束
- (void)gestureEndedPan:(ZFPlayerGestureControl *)gestureControl
           panDirection:(ZFPanDirection)direction
            panLocation:(ZFPanLocation)location;

///  捏合手势变化
- (void)gesturePinched:(ZFPlayerGestureControl *)gestureControl
                 scale:(float)scale;


#pragma mark - scrollView上的播放器视图方法

/// scrollView中的播放器视图已经出现（包括tableView或collectionView）
- (void)playerDidAppearInScrollView:(ZFPlayerController *)videoPlayer;

///  scrollView中的播放器视图即将消失（包括tableView或collectionView）
- (void)playerWillDisappearInScrollView:(ZFPlayerController *)videoPlayer;

///  scrollView中的播放器视图消失过半（包括tableView或collectionView）
- (void)playerDisappearHalfInScrollView:(ZFPlayerController *)videoPlayer;

/// scrollView中的播放器视图已经消失（包括tableView或collectionView）
- (void)playerDidDisappearInScrollView:(ZFPlayerController *)videoPlayer;


@end

NS_ASSUME_NONNULL_END

