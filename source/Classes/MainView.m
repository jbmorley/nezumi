//
//  MainView.m
//  nezumi
//
//  Created by Jason Morley on 25/01/2012.
//  Copyright (c) 2012 InSeven Limited. All rights reserved.
//

#import "MainView.h"

@implementation MainView

@synthesize timeButton = _timeButton;
@synthesize cheeseButton = _cheeseButton;
@synthesize animationView = _animationView;


- (id)initWithFrame:(CGRect)frame
{
  self = [super initWithFrame:frame];
  if (self) {
    // Initialization code
  }
  return self;
}

- (void) dealloc
{
  self.timeButton = nil;
  self.cheeseButton = nil;
  self.animationView = nil;
  [super dealloc];
}

- (IBAction) timeClicked:(id)sender
{
  NSLog(@"timeClicked");
  switch (self.animationView.timeState) {
    case StateDay:
      [self.timeButton setTitle:@"Day"
                       forState:UIControlStateNormal];
      self.animationView.timeState = StateNight;
      break;
    case StateNight:
      [self.timeButton setTitle:@"Night"
                       forState:UIControlStateNormal];
      self.animationView.timeState = StateDay;
      break;
  }
}

- (IBAction) cheeseClicked:(id)sender
{
  NSLog(@"cheeseClicked");
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/



@end
