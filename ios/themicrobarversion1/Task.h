//
//  ByteBuffer.h
//  nextlevelgaragedoor
//
//  Created by comy chitz on 3/6/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>

@interface Task : NSObject
{
    @private
    uint8_t buf[128];
    
}


@property (nonatomic) NSInteger len;
@property (nonatomic) NSInteger rw; /* 0 for read, 1 for write */

-(id) init:(uint8_t *)buf_ l:(NSInteger)len_ RW:(NSInteger)rw_;
-(uint8_t *) getBuf;


@end
