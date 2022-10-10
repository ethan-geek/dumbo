#import <UIKit/UIKit.h>
#import <FacebookSDK/FacebookSDK.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

