//
//  ByteBuffer.m
//  nextlevelgaragedoor
//
//  Created by comy chitz on 3/6/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import "Task.h"

@implementation Task

@synthesize len;
@synthesize rw;

/* maximum of 128 bytes! */
-(id) init:(uint8_t *)buf_ l:(NSInteger)len_ RW:(NSInteger)rw_
{
    
    if(len_ > 128)
        return nil;
    
    self = [super init];
    
    if(self){
        len = len_;
        rw = rw_;
        if(buf_ != NULL)
            memcpy(buf, buf_, 128);
    }
    
    return self;
    
}

-(uint8_t *) getBuf{
    return buf;
}

@end
