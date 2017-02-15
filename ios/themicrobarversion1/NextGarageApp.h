//
//  NextGarageApp.h
//  nextlevelgaragedoor
//
//  Created by comy chitz on 3/6/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NeXTGarageClient.h"


@interface NextGarageApp : UIApplication

@property (nonatomic, retain) NeXTGarageClient *connection;

@end
