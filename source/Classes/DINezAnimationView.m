//
//  DINezScreen.m
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright 2009 In7. All rights reserved.
//

#import "DINezAnimationView.h"

@interface DINezAnimationView (Private)

- (UIImage *)nextFrame;
- (NSDictionary *)set:(NSString *)set;
- (NSString *)nextSet;
- (NSArray *)frames:(NSString *)set;

- (UIImage *) imageForFrame:(NSUInteger)index;

@property (nonatomic, readonly) NSArray *activeFrames;

@end


@implementation DINezAnimationView

@synthesize image;
@synthesize activeSet = _activeSet;
@synthesize sets = _sets;
@synthesize activeIndex = _activeIndex;
@synthesize interactionState = _interactionState;


- (id)initWithFrame:(CGRect)frame
{
  if (self = [super initWithFrame:frame]) {
  }
  return self;
}

- (void)awakeFromNib
{	
  NSError *error = nil;
  NSString *file = [[NSBundle mainBundle] pathForResource:@"nezumi"
                                                   ofType:@"json"];
  NSData *data = [NSData dataWithContentsOfFile:file];
  NSDictionary *frame = [NSJSONSerialization JSONObjectWithData:data
                                                        options:kNilOptions
                                                          error:&error];
  if (error) {
    NSLog(@"Error: %@", error);    
  }

  self.sets = frame;
  self.activeSet = @"blink";
  self.activeIndex = 0;

	// Initialize the animation sets
	[NSTimer scheduledTimerWithTimeInterval:0.25
                                   target:self
                                 selector:@selector(onTick)
                                 userInfo:nil
                                  repeats:YES];
	
}

- (void)touchesBegan:(NSSet *)touches
           withEvent:(UIEvent *)event
{
  self.interactionState = StateStroke;
}

- (void)touchesEnded:(NSSet *)touches
           withEvent:(UIEvent *)event
{
  self.interactionState = StateDefault;
}

- (void)touchesCancelled:(NSSet *)touches
               withEvent:(UIEvent *)event
{
  self.interactionState = StateDefault;
}


- (void)onTick
{
	[image setImage:[self nextFrame]];	
}


- (void)drawRect:(CGRect)rect
{
}


- (void) dealloc
{
  self.activeSet = nil;
  self.sets = nil;
  [super dealloc];
}


@end

@implementation DINezAnimationView (Private)

- (UIImage *) nextFrame
{
  
  // Fetch the image.
  UIImage *frame = [self imageForFrame:self.activeIndex];
  
  // Transition the state.
  if (self.activeIndex < [self.activeFrames count]-1) {
    self.activeIndex++;
  } else {
    // TODO Transition the state and not just the frame.
    self.activeIndex = 0;
    self.activeSet = [self nextSet];
  }
  
  return frame;
}

/**
 * Returns the NSDictionary containing the parameters for a named set.
 */
- (NSDictionary *)set:(NSString *)set
{
  return [self.sets objectForKey:set];
}

/**
 * Returns the frames for a named set.
 */
- (NSArray *)frames:(NSString *)set
{
  return [[self set:set] objectForKey:@"frames"];
}

- (NSArray *)activeFrames
{
  return [self frames:self.activeSet];
}

- (UIImage *) imageForFrame:(NSUInteger)index
{
  NSDictionary *frame = [self.activeFrames objectAtIndex:index];
  NSString *file = [frame objectForKey:@"file"];
  return [UIImage imageNamed:file];
}


/**
 * Determines what the next set should be based on the current state of the
 * user interaction and the current state in the animation.
 */
- (NSString *)nextSet
{
  static NSString *kActionDefault  = @"default";
  static NSString *kActionStroke   = @"stroke";
  
  static NSString *kTypeTransition = @"transition";
  static NSString *kTransitionSet  = @"set";
  
  NSString *nextSet = self.activeSet;
  
  // TODO Work out what the next set should be.
  NSDictionary *set = [self set:self.activeSet];
  NSDictionary *actions = [set objectForKey:@"actions"];
  
  
  NSDictionary *action = nil;
  
  // Check to see if there is an action for the current interaction state.
  switch (self.interactionState) {
    case StateStroke:
      action = [actions objectForKey:kActionStroke];
      break;
    case StateDefault:
    default:
      action = [actions objectForKey:kActionDefault];
      break;
  }
  
  // If there is no specific action, then simply choose the default.
  if (action == nil) {
    action = [actions objectForKey:kActionDefault];
  }

  
  NSString *type = [action objectForKey:@"type"];
  if ([type isEqualToString:kTypeTransition]) {
    nextSet = [action objectForKey:kTransitionSet];
  }
  
  return nextSet;
}


@end