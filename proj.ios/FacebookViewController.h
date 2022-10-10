//
//  FacebookViewController.h
//  HiHigh
//
//  Created by geek on 2014. 7. 16..
//
//

#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>
#import <Social/Social.h>
#import <Accounts/Accounts.h>
#import "AppController.h"

@interface FacebookViewController : NSObject


//Session

- (void)openSession;

//Request
- (void)login;
- (void)logout;
- (void)friends;
- (void)publishFeed:(NSString*)score;
- (void)inviteFriends;

- (NSString*)sessionStateChanged:(FBSession *)session state:(FBSessionState) state error:(NSError *)error;

//Singleton instance
+ (FacebookViewController*)sharedFacebook;

@property (readonly) BOOL isLogined;

@end
