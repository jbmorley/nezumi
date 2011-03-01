//
//  Nezumi2AppDelegate.h
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright In7 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Nezumi2AppDelegate : NSObject <UIApplicationDelegate, UITabBarControllerDelegate> {
    UIWindow *window;
    UITabBarController *tabBarController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UITabBarController *tabBarController;

@end
