//
//  Nezumi2AppDelegate.m
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright In7 2009. All rights reserved.
//

#import "Nezumi2AppDelegate.h"


@implementation Nezumi2AppDelegate

@synthesize window;
@synthesize tabBarController;


- (void)applicationDidFinishLaunching:(UIApplication *)application
{
  [window addSubview:tabBarController.view];
}


- (void)dealloc
{
  [tabBarController release];
  [window release];
  [super dealloc];
}

@end

