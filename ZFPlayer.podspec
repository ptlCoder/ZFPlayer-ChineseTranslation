#
# Be sure to run `pod lib lint ZFPlayer.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'ZFPlayer'
  s.version          = '3.0.4'
  s.summary          = 'A good player made by renzifeng'
  s.homepage         = 'https://github.com/renzifeng/ZFPlayer'
  s.screenshots      = 'https://upload-images.jianshu.io/upload_images/635942-b7498fe39e788604.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240', 'https://upload-images.jianshu.io/upload_images/635942-1ba16bde9d12acbe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'renzifeng' => 'zifeng1300@gmail.com' }
  s.source           = { :git => 'https://github.com/renzifeng/ZFPlayer.git', :tag => s.version.to_s }
  s.social_media_url = 'http://weibo.com/zifeng1300'
  s.ios.deployment_target = '7.0'
  s.requires_arc = true

  s.default_subspec = 'Core'
  
  s.subspec 'Core' do |core|
      core.source_files = 'ZFPlayer/Classes/Core/**/*'
      core.public_header_files = 'ZFPlayer/Classes/Core/**/*.h'
      core.frameworks = 'UIKit', 'MediaPlayer', 'AVFoundation'
  end
  
  s.subspec 'ControlView' do |controlView|
      controlView.source_files = 'ZFPlayer/Classes/ControlView/**/*.{h,m}'
      controlView.public_header_files = 'ZFPlayer/Classes/ControlView/**/*.h'
      controlView.resource = 'ZFPlayer/Classes/ControlView/ZFPlayer.bundle'
      controlView.dependency 'ZFPlayer/Core'
  end
  
  s.subspec 'AVPlayer' do |avPlayer|
      avPlayer.source_files = 'ZFPlayer/Classes/AVPlayer/**/*.{h,m}'
      avPlayer.public_header_files = 'ZFPlayer/Classes/AVPlayer/**/*.h'
      avPlayer.dependency 'ZFPlayer/Core'
  end
  
  s.subspec 'KSYMediaPlayer' do |ksyMediaPlayer|
      ksyMediaPlayer.source_files = 'ZFPlayer/Classes/KSYMediaPlayer/*.{h,m}'
      ksyMediaPlayer.public_header_files = 'ZFPlayer/Classes/KSYMediaPlayer/*.h'
      ksyMediaPlayer.vendored_frameworks = 'ZFPlayer/Classes/KSYMediaPlayer/Frameworks/*.framework'
      ksyMediaPlayer.frameworks   = 'VideoToolbox'
      ksyMediaPlayer.ios.library = 'z', 'iconv', 'stdc++.6', 'bz2'
      ksyMediaPlayer.dependency 'ZFPlayer/Core'
  end

end
