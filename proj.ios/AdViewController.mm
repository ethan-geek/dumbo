//
//  AdViewController.m
//  HiHigh
//
//  Created by insanity on 2014. 6. 25..
//
//

#import "AdViewController.h"

#define kBannerUnitID           @"ca-app-pub-2616510431071196/7591235061"

@implementation AdViewController
//@synthesize banner, interstitial;
@synthesize iAdView;


+ (AdViewController*)sharedInstance
{
    static AdViewController * instance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[AdViewController alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if (self) {

    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
  
}

- (void)viewDidUnload
{
    [[NSNotificationCenter defaultCenter] removeObserver:nil];
    [super viewDidUnload];
}

- (void)loadAdView
{
    if ([ADBannerView instancesRespondToSelector:@selector(initWithAdType:)]) {
        self.iAdView = [[ADBannerView alloc] initWithAdType:ADAdTypeBanner];
    } else {
        self.iAdView = [[ADBannerView alloc] init];
    }
    self.iAdView.delegate = self;
    self.isShown = NO;
}

- (void)showBanner
{
    
    // AdMob
//    self.banner = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerPortrait];
//    [self.banner setDelegate:self];
//    
//    self.banner.adUnitID = kBannerUnitID;
//    self.banner.rootViewController = self;
//    
//    [self.banner loadRequest:[GADRequest request]];

    if (self.iAdView == nil) {
        [self loadAdView];
    }
    self.isShown = YES;
    [self layoutAnimated:YES];
}

- (void)removeBanner
{
//    [self.banner removeFromSuperview];
//    self.banner = nil;
    
    self.isShown = NO;
    [self layoutAnimated:NO];
}



- (void)layoutAnimated:(BOOL)animated
{
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    CGRect bannerFrame = self.iAdView.frame;
    
    if (self.isShown) {
        bannerFrame = CGRectMake(0, activeController.view.frame.size.height - 50, bannerFrame.size.width, bannerFrame.size.height);
    } else {
        bannerFrame = CGRectMake(0, activeController.view.frame.size.height, bannerFrame.size.width, bannerFrame.size.height);
    }
    
    [UIView animateWithDuration:animated ? 0.1: 0.0 animations:^{
        self.iAdView.frame = bannerFrame;
    }];
}


#pragma iAD delegate
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    NSLog(@"### bannerViewDidLoadAd");
    
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    [self.iAdView setFrame:CGRectMake(0, activeController.view.frame.size.height, iAdView.frame.size.width, iAdView.frame.size.height)];
    [activeController.view addSubview:self.iAdView];
    
    NSNotificationCenter *notiCenter = [NSNotificationCenter defaultCenter];
    [notiCenter addObserver:self selector:@selector(showBanner) name:@"showBannerNotification" object:nil];
    [notiCenter addObserver:self selector:@selector(removeBanner) name:@"removeBannerNotification" object:nil];
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    NSLog(@"### didFailToReceiveAdWithError :%@", error.localizedDescription);
}

- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    return YES;
}

- (void)bannerViewActionDidFinish:(ADBannerView *)banner {}



/*
- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    self.banner.frame = CGRectMake(0, activeController.view.frame.size.height + self.banner.frame.size.height, self.banner.frame.size.width, self.banner.frame.size.height);
    [activeController.view addSubview:self.banner];
    
    [UIView beginAnimations:@"BannerSlide" context:nil];
    self.banner.frame = CGRectMake(0.0,
                                   activeController.view.frame.size.height -
                                   banner.frame.size.height,
                                   banner.frame.size.width,
                                   banner.frame.size.height);
    [UIView commitAnimations];
}

- (void)adView:(GADBannerView *)bannerView didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"adView:didFailToReceiveAdWithError:%@", [error localizedDescription]);
}


//전면 광고
- (void)showAdvertisement
{
    self.interstitial = [[GADInterstitial alloc] init];
    self.interstitial.delegate = self;
    
    self.interstitial.adUnitID = kInterstitialUnitID;
    GADRequest *request = [GADRequest request];
    request.testDevices = @[ @"ed0804096bf358214df89709d630072e" ];
    
    [self.interstitial loadRequest:request];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)interstitial {
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    [self.interstitial presentFromRootViewController:activeController];
    
}

- (void)interstitial:(GADInterstitial *)interstitial didFailToReceiveAdWithError:(GADRequestError *)error {
    
}
*/
@end
