//
//  InAppPurchase_iOS.m
//  HiHigh
//
//  Created by Insanity on 2014. 11. 18..
//
//

#import "InAppPurchase_iOS.h"

@interface InAppPurchase_iOS()
{
    UIActivityIndicatorView *indicatorView;
}
@end

@implementation InAppPurchase_iOS

+ (InAppPurchase_iOS*)sharedInstance
{
    static InAppPurchase_iOS * instance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[InAppPurchase_iOS alloc] init];
    });
    return instance;
}

- (BOOL) initIAP
{
    if( [SKPaymentQueue canMakePayments] == NO )
        return NO;
    
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];

    return true;
}

///< 아이템 정보 요청
- (void) requestProductData
{
    [self startIndicator];
    NSSet* productIdentifiers = [NSSet setWithObjects:@"net.atgame.dumbo.iap.jewel01", @"net.atgame.dumbo.iap.jewel02", @"net.atgame.dumbo.iap.jewel03", @"net.atgame.dumbo.iap.jewel04", @"net.atgame.dumbo.iap.jewel05", @"net.atgame.dumbo.iap.jewel06", nil];
    SKProductsRequest* request = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    request.delegate = self;
    [request start];
}

///< 아이템 정보 요청 결과 callback
- (void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    [self stopIndicator];
    
    NSLog( @"InAppPurchase didReceiveResponse" );
    CCNotificationCenter *notificationCenter = CCNotificationCenter::sharedNotificationCenter();
    notificationCenter->postNotification("appleIapReadyToSaleNotification", (CCObject*)response);
    [request release];
}

- (void)buyProduct:(SKProduct *)product
{
    if(product == nil) return;
    
    NSLog(@"price %@", product.price);
    SKPayment *payment = [SKPayment paymentWithProduct:product];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}


- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    [self startIndicator];
    NSLog(@"%s", __FUNCTION__);
    
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
                ///< 서버에 거래 처리중
            case SKPaymentTransactionStatePurchasing:
                NSLog(@"InAppPurchase SKPaymentTransactionStatePurchasing");
                break;
                ///< 구매 완료
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
                ///< 거래 실패 또는 취소
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
                ///< 재구매
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
        }
    }
}

- (void) completeTransaction:(SKPaymentTransaction *)transaction
{
    [self stopIndicator];
    NSLog(@"InAppPurchase completeTransaction");
    NSLog(@"InAppPurchase Transaction Identifier : %@", transaction.transactionIdentifier );
    NSLog(@"InAppPurchase Transaction Data : %@", transaction.transactionDate );
    
    //다 사뜸
    NSLog(@"### PRODUCT ID : %@", transaction.payment.productIdentifier);
    CCNotificationCenter *notificationCenter = CCNotificationCenter::sharedNotificationCenter();
    notificationCenter->postNotification("appleIapCompleteNotification", (CCObject*)transaction);
    
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

- (void) restoreTransaction:(SKPaymentTransaction *)transaction
{
    [self stopIndicator];
    NSLog(@"InAppPurchase restoreTransaction");
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

- (void) failedTransaction:(SKPaymentTransaction *)transaction
{
    [self stopIndicator];
    CCLOG( "InAppPurchase failedTransaction." );
    CCString* pStrFailed = 0;
    if( transaction.error.code != SKErrorPaymentCancelled )
    {
        pStrFailed = ccs( "faileIAP" );
        CCLOG("InAppPurchase failedTransaction SKErrorDomain - %d", transaction.error.code );
    }
    else
    {
        pStrFailed = ccs( "cancelIAP" );
        CCLOG("InAppPurchase failedTransaction SKErrorPaymentCancelled");
    }

    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}


- (void)startIndicator
{
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    if (!indicatorView) {
        indicatorView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        [indicatorView setCenter:activeController.view.center];
        [activeController.view addSubview:indicatorView];
    }
    [activeController.view setUserInteractionEnabled:NO];
    [indicatorView startAnimating];
}

- (void)stopIndicator
{
    UIViewController *activeController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    [activeController.view setUserInteractionEnabled:YES];
    [indicatorView stopAnimating];
    [indicatorView removeFromSuperview];
    indicatorView = nil;
}

@end
