//
//  COMFirstViewController.h
//  themicrobarversion1
//
//  Created by comy chitz on 2/23/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "NeXTGarageClient.h"
#import "COMAppDelegate.h"
#import "AsyncSocket.h"

@interface COMFirstViewController : UIViewController
{
    AsyncSocket *socket;
    
}

@property (nonatomic, retain) NeXTGarageClient *a;

@end