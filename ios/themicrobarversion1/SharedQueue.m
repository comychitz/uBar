#import <Foundation/Foundation.h>
#import "SharedQueue.h"

@implementation SharedQueue: NSObject{

}

-(id)init{

	self = [super init];

	if(self){
		queue = [[NSMutableArray alloc] init];
		numItems = 0;
		mutex = [[NSLock alloc] init];
	}

	return self;
}

-(void)enqueue: (id)data{

	[mutex lock];

	[queue addObject:data];
	numItems++;

	[mutex unlock];
}

-(id)dequeue{

	[mutex lock];

	/* empty */
	if(numItems == 0)
		return nil;

	id toReturn = [queue objectAtIndex:0];
	[queue removeObject:toReturn];

	numItems--;
	
	[mutex unlock];

	return toReturn;
}

-(NSUInteger) getNumItems{

	NSUInteger toReturn;

	[mutex lock];

	toReturn = numItems;

	[mutex unlock];

	return toReturn;
}

@end
