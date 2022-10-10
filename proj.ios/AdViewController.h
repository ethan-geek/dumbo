//
//  AdViewController.h
//  HiHigh
//
//  Created by insanity on 2014. 6. 25..
//
//




#include "../Classes/common/DefaultHeader.h"
#ifdef __OBJC__
#import <UIKit/UIKit.h>

#import <iAd/iAd.h>


@interface AdViewController : UIViewController <ADBannerViewDelegate>


@property(nonatomic, strong) ADBannerView *iAdView;
@property(nonatomic) BOOL isShown;

- (void)loadAdView;
- (void)showBanner;
- (void)removeBanner;


+ (AdViewController*)sharedInstance;

@end
#endif
