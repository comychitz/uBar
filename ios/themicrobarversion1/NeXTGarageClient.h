#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import "SharedQueue.h"


@interface NeXTGarageClient: NSObject{

	@private
	NSString *ip;
	NSUInteger port;

//	CFHost *host;
    NSInputStream *readStream;
    NSOutputStream *writeStream;
    
    CFSocketRef *socket;
    
	NSThread *workThread;
	/*	if thread cannot acquire this lock,
		it should exit */
	NSLock *threadInterrupt;
	SharedQueue *workQueue;
    SharedQueue *resultsQueue;
    
    NSMutableArray *protocolArray;
	
}

-(id)init:(NSString *)ip_ port:(NSUInteger)port_;
-(void)connect;
-(void)disconnect;
-(void)sendMessage:(NSString*)msgName d:(uint8_t *)data_;
-(NSInteger)checkResultsQueue:(uint8_t *)buf_;
-(void) queueReadMessage;
+(void) computeResponse:(uint8_t *)challenge_ pw:(NSString *)password_;
@end


