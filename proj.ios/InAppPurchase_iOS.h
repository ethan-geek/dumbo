//
//  InAppPurchase_iOS.m
//  HiHigh
//
//  Created by Insanity on 2014. 11. 18..
//
//


#include "../Classes/common/DefaultHeader.h"
#ifdef __OBJC__


#import <StoreKit/StoreKit.h>
#import <UIKit/UIKit.h>


@interface InAppPurchase_iOS : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>

+ (InAppPurchase_iOS*)sharedInstance;
- (BOOL)initIAP;
- (void)requestProductData;

- (void)buyProduct:(SKProduct *)product;

- (void)completeTransaction:(SKPaymentTransaction*)transaction;
- (void)restoreTransaction:(SKPaymentTransaction*)transaction;
- (void)failedTransaction:(SKPaymentTransaction*)transaction;

@end

#endif