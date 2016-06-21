//
//  ModuleCapability.h
//  Common
//
//  Created by 黄磊 on 16/4/14.
//  Copyright © 2016年 Musjoy. All rights reserved.
//

#ifndef ModuleCapability_h
#define ModuleCapability_h

//######################################
/// 常用函数
//######################################
// 字符串拼接
#define combine(x, y)   [(x) stringByAppendingString:(y)]
// 字符串长度获取
#define textSizeWithFont(text, font) ([text length] > 0 ? [text sizeWithAttributes:@{NSFontAttributeName:font}] : CGSizeZero);
#define multilineTextSize(text, font, maxSize) ([text length] > 0 ? \
[text boundingRectWithSize:maxSize \
options:(NSStringDrawingUsesFontLeading | NSStringDrawingUsesLineFragmentOrigin) \
attributes:@{NSFontAttributeName:font} \
context:nil].size : CGSizeZero);


//######################################
/// 用户自定义常量导入
//######################################
#ifdef MODULE_USER_CONSTANT
#import "Constant.h"
#endif

//######################################
// 部分常量定义
//######################################
// 公开版本号。eg：1.0
#define kClientVersionShort [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]
// 内部版本号。eg：1.0.1
#define kClientVersion [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]
// App Store
#ifndef kAppID
#define kAppID   @"unknown"
#endif
#define kAppLookUpUrl    combine(@"http://itunes.apple.com/lookup?id=", kAppID)
#define kAppDownload     combine(@"http://itunes.apple.com/app/id", kAppID)
#define kAppComment      combine(combine(@"itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?id=", kAppID), @"&pageNumber=0&sortOrdering=2&type=Purple+Software&mt=8")
// 当前iOS版本
#define __CUR_IOS_VERSION ([[[UIDevice currentDevice] systemVersion] floatValue] * 10000)
// 屏幕高度
#define kScreenHeight [UIScreen mainScreen].bounds.size.height
// 屏幕宽度
#define kScreenWidth  [UIScreen mainScreen].bounds.size.width

//######################################
/// 常量默认值
//######################################
/** 默认动画持续时间 */
#ifndef DEFAULT_ANIMATE_DURATION
#define DEFAULT_ANIMATE_DURATION 0.3
#endif

//######################################
/// Logging配置
//######################################
#ifndef IS_LOGGING_IN_USE
#ifdef DEBUG
// TRACE CONFIG
#define LOGGING_ENABLED 1
#define LOGGING_INCLUDE_CODE_LOCATION 1
#define LOGGING_LEVEL_INFO 1
// FILE LOGGING
#define LOGGING_TO_FILE
// 开发时使用，发版本时应去掉
#undef LOGGING_TO_FILE
#endif
#endif
#import "Logging.h"

//######################################
/// 高级函数
//######################################
#ifdef MODULE_DB_MODEL
#define objectFromString(str, err) [DBModel objectFromJSONString:str error:err]
#else
#define objectFromString(str, err) ({       \
    id aNil = nil;                          \
    id obj = aNil;                          \
    NSData *data = [str dataUsingEncoding:NSUTF8StringEncoding];            \
    if (data) {                             \
        NSError *initError = aNil;          \
        @try {                              \
            obj = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&initError];   \
        } @catch (NSException *exception) { \
            obj = aNil;                     \
        }                                   \
    }                                       \
    obj;                                    \
})
#endif





//######################################
/// 友盟分析模块
//######################################
#ifdef MODULE_UM_ANALYSE
#define HEADER_UM_ANALYSE <UMMobClick/MobClick.h>
#define triggerEventStr(eventId, evenDesc) [MobClick event:eventId attributes:@{@"name":evenDesc}];
#define triggerEvent(eventId, attrs) [MobClick event:eventId attributes:attrs];
#define triggerBeginPage(className) [MobClick beginLogPageView:className];
#define triggerEndPage(className) [MobClick endLogPageView:className];
#else
#define triggerEventStr(eventId, evenDesc) NSLog(@"%@", evenDesc)
#define triggerEvent(eventId, attrs) NSLog(@"%@", attrs)
#define triggerBeginPage(className) NSLog(@"%@", className)
#define triggerEndPage(className) NSLog(@"%@", className)
#endif
/// 对应通用统计事件定义
#ifndef stat_Error
#define stat_Error      @"Error"
#endif

//######################################
/// FileSource
//######################################
#ifdef MODULE_FILE_SOURCE
#define getPlistFileData(aPlistName) [FileSource dataWithPlistName:aPlistName];
#else
#define getPlistFileData(aPlistName) ({ \
    NSString *fileName = [aPlistName stringByAppendingString:@".plist"]; \
    NSString *fileBundle = [[NSBundle mainBundle] resourcePath]; \
    NSString *filePath = [fileBundle stringByAppendingPathComponent:fileName]; \
    NSDictionary *aDic = [[NSDictionary alloc] initWithContentsOfFile:filePath]; \
    aDic[@"body"]; \
})
#endif

//######################################
/// ControllerManager
//######################################
// BaseViewController
#ifdef MODULE_SUB_BASE_VIEW_CONTROLLER
#define HEADER_BASE_VIEW_CONTROLLER "BaseViewController.h"
#define THEBaseViewController       BaseViewController
#elif (defined(MODULE_CONTROLLER_MANAGER) || __has_include("MJBaseViewController.h"))
#define HEADER_BASE_VIEW_CONTROLLER "MJBaseViewController.h"
#define THEBaseViewController       MJBaseViewController
#else
#define HEADER_BASE_VIEW_CONTROLLER <UIKit/UIKit.h>
#define THEBaseViewController       UIViewController
#endif
// NavigationController
#ifdef MODULE_SUB_NAVIGATION_CONTROLLER
#define HEADER_NAVIGATION_CONTROLLER    "NavigationController.h"
#define THENavigationController         NavigationController
#elif (defined(MODULE_CONTROLLER_MANAGER) || __has_include("MJNavigationController.h"))
#define HEADER_NAVIGATION_CONTROLLER    "MJNavigationController.h"
#define THENavigationController         MJNavigationController
#else
#define HEADER_NAVIGATION_CONTROLLER    <UIKit/UINavigationController.h>
#define THENavigationController         UINavigationController
#endif
// ControllerManager
#ifdef MODULE_SUB_CONTROLLER_MANAGER
#define HEADER_CONTROLLER_MANAGER   "ControllerManager.h"
#define THEControllerManager        ControllerManager
#elif (defined(MODULE_CONTROLLER_MANAGER) || __has_include("MJControllerManager.h"))
#define HEADER_CONTROLLER_MANAGER   "MJControllerManager.h"
#define THEControllerManager        MJControllerManager
#endif

#endif /* ModuleCapability_h */
