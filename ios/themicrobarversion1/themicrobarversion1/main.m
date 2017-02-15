//
//  main.m
//  themicrobarversion1
//
//  Created by comy chitz on 2/23/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "COMAppDelegate.h"
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "NeXTGarageClient.h"
#import "NextGarageApp.h"
#import "COMAppDelegate.h"
#import "NextGarageApp.h"

int main(int argc, char * argv[])
{
    @autoreleasepool {
        return UIApplicationMain(argc, argv, NSStringFromClass([NextGarageApp class]), NSStringFromClass([COMAppDelegate class]));
    }
}
