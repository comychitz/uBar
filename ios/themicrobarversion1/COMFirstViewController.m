//
//  COMFirstViewController.m
//  themicrobarversion1
//
//  Created by comy chitz on 2/23/14.
//  Copyright (c) 2014 Cameron Chitsaz. All rights reserved.
//

#import "COMFirstViewController.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "NeXTGarageClient.h"
#import "COMAppDelegate.h"
#import "AsyncSocket.h"
#import "NextGarageApp.h"

@interface COMFirstViewController ()

@property (weak, nonatomic) IBOutlet UISwitch *drank1switch;
@property (weak, nonatomic) IBOutlet UISwitch *drank2switch;
@property (weak, nonatomic) IBOutlet UISwitch *drank3switch;
@property (weak, nonatomic) IBOutlet UISwitch *drank4switch;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinWheel;
@property (weak, nonatomic) IBOutlet UIButton *makeButton;

@end


@implementation COMFirstViewController

/*--------- Actions to perform when makeButton is pressed -----------*/
- (IBAction)makeDrink:(id)sender {

    if (![self drank1switch].isOn && ![self drank2switch].isOn && ![self drank3switch].isOn && ![self drank4switch].isOn)
    {
        NSLog(@"None of the switches are on!");
    }
    else
    {
        NextGarageApp * app =  (NextGarageApp *) [UIApplication sharedApplication];
        app.connection = [[NeXTGarageClient alloc] init:@"192.168.2.2" port:2018];
        [app.connection connect];
        [self performSelectorInBackground:@selector(startAnimation) withObject:nil];
        uint8_t *data = malloc(1);
        *data = 0;
        
        
        if ([self drank1switch].isOn)
        {
            *data += 1;
        }
        if ([self drank2switch].isOn)
        {
            *data+=5;
        }
        if ([self drank3switch].isOn)
        {
            *data+=9;
        }
        if ([self drank4switch].isOn)
        {
            *data+=17;
        }
        
        [app.connection sendMessage:@"makeDrink" d:data];
        
        free(data);
        
        [[self drank1switch] setOn:NO animated:YES];
        [[self drank2switch] setOn:NO animated:YES];
        [[self drank3switch] setOn:NO animated:YES];
        [[self drank4switch] setOn:NO animated:YES];
        
        sleep(5);
        [self stopAnimation];
        [app.connection disconnect];
        app.connection = nil;
    }
}




- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


/* ------------- To Do when page is opened --------------------*/
- (void)viewDidLoad
{
    [super viewDidLoad];
    [[self drank1switch] setOn:NO animated:YES];
    [[self drank2switch] setOn:NO animated:YES];
    [[self drank3switch] setOn:NO animated:YES];
    [[self drank4switch] setOn:NO animated:YES];
    [self spinWheel].hidden = YES;
    [self makeButton].hidden = NO;
}


/* -------------- Methods for animation/aesthetic purposes ------------ */
- (void) startAnimation
{
    [self spinWheel].hidden = NO;
    [[self spinWheel] startAnimating];
}
- (void) stopAnimation
{
    [self spinWheel].hidden = YES;
    [[self spinWheel] stopAnimating];
}

@end
