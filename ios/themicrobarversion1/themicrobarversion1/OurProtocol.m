//
//  Message.m
//  nextlevelgaragedoor
//
//  Created by comy chitz on 3/6/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import "OurProtocol.h"

@implementation OurProtocol

@synthesize messageLength;
@synthesize messageType;
@synthesize messageName;

- (id) init: (NSInteger )messageType_ messageL:(NSInteger)messageLength_ messageN:(NSString *)messageName_;
{
    
    
    self = [super init];
    
    if(self){
        messageType = messageType_;
        messageLength = messageLength_;
        messageName = messageName_;
    }
    
    return self;
}

@end

