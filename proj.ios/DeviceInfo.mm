//
//  DeviceInfo.m
//  HiHigh
//
//  Created by Jackdaw on 2014. 8. 21..
//
//

#import "DeviceInfo.h"
#include "../Classes/common/DeviceInfoIOSBridge.h"
#include "../Classes/model/AGDeviceInfo.h"
#include <sys/sysctl.h>
#include <sys/utsname.h>

AGDeviceInfo getDeviceInfoIOS() {

    return [DeviceInfo getDeviceInfo];
}


@implementation DeviceInfo

+(AGDeviceInfo) getDeviceInfo {

    struct utsname systemInfo;
    uname(&systemInfo);
    NSString * version = [[UIDevice currentDevice] systemVersion];
    
    AGDeviceInfo f;
    f.deviceType = [[NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding] UTF8String];
    f.version = [version UTF8String];
    
    return f;
}

@end
