#import <Foundation/Foundation.h>

@interface SharedQueue: NSObject{

	@private
	NSMutableArray *queue;
	NSUInteger numItems;
	NSLock *mutex;
}

-(void) enqueue: (id) data;
-(id) dequeue;
-(NSUInteger) getNumItems;


@end
