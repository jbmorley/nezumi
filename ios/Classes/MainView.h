//
//  MainView.h
//  nezumi
//
//  Created by Jason Morley on 25/01/2012.
//  Copyright (c) 2012 InSeven Limited. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DINezAnimationView.h"

@interface MainView : UIView {
  
  UIButton *_timeButton;
  UIButton *_cheeseButton;
  DINezAnimationView *_animationView;
  
}

@property (nonatomic, retain) IBOutlet UIButton *timeButton;
@property (nonatomic, retain) IBOutlet UIButton *cheeseButton;
@property (nonatomic, retain) IBOutlet DINezAnimationView *animationView;

- (IBAction) timeClicked:(id)sender;
- (IBAction) cheeseClicked:(id)sender;

@end
