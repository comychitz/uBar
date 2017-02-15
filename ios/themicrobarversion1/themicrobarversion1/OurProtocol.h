//
//  Message.h
//  nextlevelgaragedoor
//
//  Created by comy chitz on 3/6/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OurProtocol : NSObject


@property (nonatomic)  NSInteger messageType;
@property (nonatomic) NSInteger messageLength;
@property (nonatomic, weak) NSString *messageName;

- (id) init: (NSInteger )messageType_ messageL:(NSInteger)messageLength_ messageN:(NSString *)messageName_;

@end

