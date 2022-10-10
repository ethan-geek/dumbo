//
//  FacebookViewController.m
//  HiHigh
//
//  Created by geek on 2014. 7. 16..
//
//

#import "FacebookViewController.h"
#import "../Classes/fb/FacebookInterfaceiOS.h"

@implementation FacebookViewController
@synthesize isLogined = _isLogined;

//Singleton instance
+ (FacebookViewController *)sharedFacebook
{
    static FacebookViewController *sharedSingleton;
    
    @synchronized(self)
    {
        if (!sharedSingleton)
        {
            sharedSingleton = [[FacebookViewController alloc] init];
		}
        
        return sharedSingleton;
    }
}

- (id)init
{
	self = [super init];
	
	if (self) {
		[self openSession];
		
	}
	
	return self;
}

- (void)openSession
{
	if (FBSession.activeSession.state == FBSessionStateCreatedTokenLoaded) {
		NSLog(@"Found a cached session");
		
		FBSession* activeSession = [FBSession activeSession];
		
		[activeSession openWithCompletionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
			
			NSString* message = [self sessionStateChanged:session state:status error:error];
			[FBSession setActiveSession:session];
			
		 if (message != nil) {
			 const char* res = [message UTF8String];
				
			 FacebookInterfaceiOS::sharedFacebookiOS().setIndex(Facebook::LOGIN_REQUEST);
			 FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
			 return;
		 }

			
			[[FBRequest requestForMe] startWithCompletionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
				if (!error && result) {
					NSData* jsonData = [NSJSONSerialization dataWithJSONObject:result options:0 error:nil];
					NSString* jsonString = [[NSString alloc] initWithBytes:[jsonData bytes] length:[jsonData length] encoding:NSUTF8StringEncoding];
					
					const char* res = [jsonString UTF8String];
					
					FacebookInterfaceiOS::sharedFacebookiOS().setIndex(Facebook::LOGIN_REQUEST);
					FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
				}
			}];
			
		}];
		
	}else{
		_isLogined = false;
	}
	
}
- (void)login
{

	
	NSArray* permissions = [[NSArray alloc] initWithObjects:
							@"public_profile",
							@"email",
							@"user_friends",
							@"publish_actions",
							nil];
	
	[FBSession openActiveSessionWithPublishPermissions:permissions
									   defaultAudience:FBSessionDefaultAudienceEveryone
										  allowLoginUI:true
									 completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
										 NSString* message = [self sessionStateChanged:session state:status error:error];
										 [FBSession setActiveSession:session];
										 
										 if (message != nil) {
											 const char* res = [message UTF8String];
											 
											 FacebookInterfaceiOS::sharedFacebookiOS().setIndex(Facebook::LOGIN_REQUEST);
											 FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
											 return;
										 }
										 
										 if (FBSession.activeSession.isOpen)
										 {
											 [[FBRequest requestForMe]startWithCompletionHandler:^(FBRequestConnection *connection, NSDictionary<FBGraphUser> *result, NSError *error) {
												 if (nil == error && nil != result) {
													 NSData* jsonData = [NSJSONSerialization dataWithJSONObject:result options:0 error:nil];
													 NSString* jsonString = [[NSString alloc] initWithBytes:[jsonData bytes] length:[jsonData length] encoding:NSUTF8StringEncoding];
													 
													 const char* res = [jsonString UTF8String];
													 
													 [self sessionStateChanged:session state:status error:error];
													 //				FacebookInterfaceiOS::sharedFacebookiOS().setIndex(Facebook::LOGIN_REQUEST);
													 FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
												 }else if (error != nil){
													 NSString* message = [self sessionStateChanged:session state:status error:error];
													 const char* res = [message UTF8String];
													 
													 FacebookInterfaceiOS::sharedFacebookiOS().setIndex(Facebook::LOGIN_REQUEST);
													 FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
												 

												 }
											 }];
										 }
									 }];
}

- (void)logout
{
	if (FBSession.activeSession.state == FBSessionStateOpen
		|| FBSession.activeSession.state == FBSessionStateOpenTokenExtended) {
		
		[[FBSession activeSession] closeAndClearTokenInformation];
		[FBSession setActiveSession:nil];
		NSString* str = @"Logout";
		const char* res = [str UTF8String];
		
//		[self sessionStateChanged:[FBSession activeSession] state:FBSession.activeSession.state error:nil];
		
		FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
	}
	

	
}

//- (void)friends
//{
//	NSString* fqlStr =
//			@"SELECT uid, name "
//			@" FROM user "
//			@" WHERE uid IN "
//			@"(SELECT uid2 FROM friend WHERE uid1=me())";
//	NSLog(@"fqlStr = %@",fqlStr);
//	
//	NSDictionary* queryParam = @{@"q":fqlStr};
//	
//	if (FBSession.activeSession.isOpen) {
//		[FBRequestConnection startWithGraphPath:@"/fql"
//									 parameters:queryParam
//									 HTTPMethod:@"GET"
//							  completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
//								  if (error) {
//									  NSLog(@"Error: %@", [error localizedDescription]);
//									  NSString* message = [self sessionStateChanged:[FBSession activeSession] state:FBSession.activeSession.state error:error];
//									  const char* res = [message UTF8String];
//									  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
//								  }else{
//									  
//									  NSError *writeError = nil;
//									  
//									  NSData *jsonData = [NSJSONSerialization dataWithJSONObject:result options:NSJSONWritingPrettyPrinted error:&writeError];
//									  NSString *result1= [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
//									  
//									  
//									  NSLog(@"Result: %@", result1);
//									  
//									  const char* res = [result1 UTF8String];
//									  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
//									  
//								  }
//							  }];
//	}
//	
//}

- (void)friends
{
//	NSString* friendsRequest = @"/me/friends";
//	NSDictionary* queryParam = @{@"q":friendsRequest};
	NSString* friendsRequest = [NSString stringWithFormat:@"/me/friends?limit=%d&offset=0", 500];
	NSLog(@"friendsRequest = %@",friendsRequest);
	
	if (FBSession.activeSession.isOpen) {
		[FBRequestConnection startWithGraphPath:friendsRequest
									 parameters:nil
									 HTTPMethod:@"GET"
							  completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
								  if (error) {
									  NSLog(@"Error: %@", [error localizedDescription]);
									  NSString* message = [self sessionStateChanged:[FBSession activeSession] state:FBSession.activeSession.state error:error];
									  const char* res = [message UTF8String];
									  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
								  }else{
									  
									  NSError *writeError = nil;
									  
									  NSData *jsonData = [NSJSONSerialization dataWithJSONObject:result options:NSJSONWritingPrettyPrinted error:&writeError];
									  NSString *result1= [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
									  
									  
									  NSLog(@"Result: %@", result1);
									  
									  const char* res = [result1 UTF8String];
									  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
									  
								  }
							  }];
	}
	
}

- (void)publishFeed:(NSString*)score
{
	NSArray* paths = NSSearchPathForDirectoriesInDomains
	(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* documentsDirectory = [paths objectAtIndex:0];
	NSString* screenshotPath = [documentsDirectory
								stringByAppendingPathComponent:@"/screenshot.jpg"];
	
	NSData *data = [NSData dataWithContentsOfFile:screenshotPath];

	if ([SLComposeViewController isAvailableForServiceType:SLServiceTypeFacebook])
	{
		SLComposeViewController *fbPost = [SLComposeViewController
										   composeViewControllerForServiceType:SLServiceTypeFacebook];
		
		
		[fbPost setInitialText:@"https://hihigh.atgame.net"];
		
		[fbPost addImage:[UIImage imageWithData:data]];
		
		UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
		
		[activeController presentViewController:fbPost animated:YES completion:nil];
		
		[fbPost setCompletionHandler:^(SLComposeViewControllerResult result) {
			
			
			switch (result) {
				case SLComposeViewControllerResultCancelled:
				{
					NSString* message = @"Cancel";
					
					const char* res = [message UTF8String];
					FacebookInterfaceiOS& ios = FacebookInterfaceiOS::sharedFacebookiOS();
					ios.setIndex(Facebook::SHARED_CANCEL);
					
					FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
				}
					break;
				case SLComposeViewControllerResultDone:
				{
					NSLog(@"Post Sucessful");
					
					NSString* message = @"Sucessful";
					
					const char* res = [message UTF8String];

					FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
					
				}
					break;
				default:
					break;
			}
			
			[activeController dismissViewControllerAnimated:YES completion:nil];
			
		}];
	}
}

- (void)inviteFriends
{
	
	[FBWebDialogs presentRequestsDialogModallyWithSession:[FBSession activeSession]
												  message:[NSString stringWithFormat:@"I just Jump Score %d friends! Can you beat it?", 11000]
													title:@"Dumbo Jump"
											   parameters:nil
												  handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
													  if (error) {
														  // Case A: Error launching the dialog or sending request.
														  NSLog(@"Error sending request.");

														  NSString* message = [self sessionStateChanged:[FBSession activeSession] state:FBSession.activeSession.state error:error];
														  const char* res = [message UTF8String];
														  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookError(res);
													  } else {
														  if (result == FBWebDialogResultDialogNotCompleted) {
															  // Case B: User clicked the "x" icon
															  NSLog(@"User canceled request.");
														  } else {
															  NSLog(@"Request Sent.");
															  
															  NSString* message = @"Sucessful";
															  
															  const char* res = [message UTF8String];
															  
															  FacebookInterfaceiOS::sharedFacebookiOS().callbackFacebookiOS(res);
														  }
													  }}
  ];
}
//Session

- (NSString*)sessionStateChanged:(FBSession *)session state:(FBSessionState) state error:(NSError *)error
{
	NSString *retrunMessage = nil;
	// If the session was opened successfully
	if (!error && state == FBSessionStateOpen){
		NSLog(@"Session opened");
		// Show the user the logged-in UI
		_isLogined = true;
		
		return retrunMessage;
	}
	if (state == FBSessionStateClosed || state == FBSessionStateClosedLoginFailed){
		// If the session is closed
		NSLog(@"Session closed");
		// Show the user the logged-out UI
		_isLogined = false;
	}
	
	if (error){
		if ([FBErrorUtility shouldNotifyUserForError:error] == YES){
			// Error requires people using you app to make an action outside your app to recover
			retrunMessage = @"Something went wrong. Please make sure you're connected to the internet and try again.";
			
			
		} else {
			// You need to find more information to handle the error within your app
			if ([FBErrorUtility errorCategoryForError:error] == FBErrorCategoryUserCancelled) {
				//The user refused to log in into your app, either ignore or...
				retrunMessage = @"You need to login to access this part of the app";
				
				
			} else if ([FBErrorUtility errorCategoryForError:error] == FBErrorCategoryAuthenticationReopenSession){
				// We need to handle session closures that happen outside of the app
				
				retrunMessage = @"Your current session is no longer valid. Please log in again.";
				
				
			} else {
				// All other errors that can happen need retries
				// Show the user a generic error message
				retrunMessage = @"Please retry";
				
			}
		}
		
		// Clear this token
//		[FBSession.activeSession closeAndClearTokenInformation];
//		_isLogined = false;
	}
	
	return retrunMessage;

}
@end

