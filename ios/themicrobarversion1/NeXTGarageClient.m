#import "NeXTGarageClient.h"
#import "OurProtocol.h"
#import "SharedQueue.h"
#import "Task.h"
#import <CommonCrypto/CommonDigest.h>


@implementation NeXTGarageClient: NSObject{
}

-(id)init:(NSString *)ip_ port:(NSUInteger)port_{

	self = [super init];

	if(self){
		ip = ip_;
		port = port_;
        
        resultsQueue = [[SharedQueue alloc] init];
		threadInterrupt = [[NSLock alloc] init];
		workQueue = [[SharedQueue alloc] init];
	}
    
    CFReadStreamRef r = NULL;
    CFWriteStreamRef w = NULL;
    
    CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef)ip, (UInt32)port, &r, &w);
    readStream = (__bridge_transfer NSInputStream *)r;
    writeStream = (__bridge_transfer NSOutputStream *)w;
   
    protocolArray = [[NSMutableArray alloc] init];
   
    [self fillProtocolArray];
    
	return self;
}

/* open TCP connection, start up thread */
-(void)connect{
    
    [readStream open];
    [writeStream open];
    
    workThread = [[NSThread alloc]	initWithTarget:self
                                         selector:@selector(doWork)
                                           object:nil];
    [workThread start];

}


/* kill thread and close TCP connection */
-(void)disconnect{

	/*	acquire the interrupt lock, causing the
		thread to exit */
    
	[threadInterrupt lock];
    [threadInterrupt unlock];
    
    [readStream close];
    [writeStream close];
    
    readStream = nil;
    writeStream = nil;

}

/* dont call with an invalid msgName */
-(void)sendMessage:(NSString *)msgName d:(uint8_t *)data_
{
    OurProtocol *msgToSend;
    
    int i;
    
    for(i = 0; i < [protocolArray count]; i++){
        msgToSend = [protocolArray objectAtIndex:i];
        if([msgName isEqualToString:msgToSend.messageName]){
            break;
        }
    }
    
    uint8_t *toSendBuffer = malloc(3 + msgToSend.messageLength);
    
    toSendBuffer[0] = msgToSend.messageType;
    toSendBuffer[1] = (msgToSend.messageLength & 0xFF00) >> 8;
    toSendBuffer[2] = (msgToSend.messageLength & 0xFF);
    
    NSInteger totalMessageLen = 3 + msgToSend.messageLength;
    
    if(data_ != NULL)
        memcpy(&(toSendBuffer[3]), data_, msgToSend.messageLength);
    
    [workQueue enqueue:[[Task alloc]init:toSendBuffer l:totalMessageLen RW:1]];
    
    free(toSendBuffer);
}

-(void) queueReadMessage
{
    [workQueue enqueue:[[Task alloc]init:NULL l:0 RW: 0]];

}

-(NSInteger ) checkResultsQueue: (uint8_t *)buf_
{
    Task *t;
    usleep(1000000);
    if([resultsQueue getNumItems])
    {
        t = [resultsQueue dequeue];
        memcpy(buf_, [t getBuf], t.len);
        return t.len;
    }
    return 0;
}

-(void)doWork{

	Task *task;
    uint8_t buf[128];
    NSInteger bytesRead;
    
    
	while(true){

		if(![threadInterrupt tryLock]){
			NSLog(@"Interrupted\n");
			break;
		}

		/*	check if anything is in work queue,
			if so, handle the request */
        if([workQueue getNumItems])
        {
            task = [workQueue dequeue];
            
            /* writing */
            if(task.rw){
                [writeStream write:[task getBuf] maxLength:task.len];
                
            } else { /* reading */
                
                bytesRead = [readStream read:buf maxLength:128];
                [resultsQueue enqueue:[[Task alloc]init:buf l:bytesRead RW: 0]];
            
            }
        }

		[threadInterrupt unlock];

	}

}

- (void) fillProtocolArray
{
  
    [protocolArray addObject:[[OurProtocol alloc] init:0 messageL:(1) messageN:@"makeDrink"]];

}

+ (void) computeResponse:(uint8_t *)challenge_ pw:(NSString *)password_
{
    uint8_t hashedChars[32];
    uint8_t attemptedResponse[64];
    
    NSData * inputData = [password_ dataUsingEncoding:NSUTF8StringEncoding];
    CC_SHA256(inputData.bytes, (CC_LONG)inputData.length, hashedChars);
    memcpy(attemptedResponse, hashedChars, 32);
    memcpy(&(attemptedResponse[32]), challenge_, 32);
    CC_SHA256(attemptedResponse, (CC_LONG)64, challenge_);
    
    
}

@end
