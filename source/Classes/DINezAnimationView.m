//
//  DINezScreen.m
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright 2009 In7. All rights reserved.
//

#import "DINezAnimationView.h"

@interface DINezAnimationView (Private)

- (void) nextFrame;
- (NSDictionary *)set:(NSString *)set;
- (NSString *)nextSet;
- (NSArray *)frames:(NSString *)set;

- (UIImage *)imageForFrame:(NSUInteger)index;
- (CGFloat) durationForFrame:(NSUInteger)index;
- (InteractionState) state:(NSString *)state;

@property (nonatomic, readonly) NSArray *activeFrames;

@end


@implementation DINezAnimationView

@synthesize image;
@synthesize activeSet = _activeSet;
@synthesize sets = _sets;
@synthesize activeIndex = _activeIndex;
@synthesize interactionState = _interactionState;
@synthesize touchStart = _touchStart;

static NSTimeInterval kPokeThreshold = 0.1;

static NSString *kStateDefault  = @"default";
static NSString *kStateStroke   = @"stroke";
static NSString *kStatePoke     = @"poke";

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
  [self nextFrame];
}

- (void)touchesBegan:(NSSet *)touches
           withEvent:(UIEvent *)event
{
  self.touchStart = [NSDate date];
  self.interactionState = StateStroke;
}

- (void)touchesEnded:(NSSet *)touches
           withEvent:(UIEvent *)event
{
  NSTimeInterval duration = [self.touchStart timeIntervalSinceNow] * -1;
  if (duration < kPokeThreshold) {
    self.interactionState = StatePoke;
  } else {
    self.interactionState = StateDefault;
  }
}

- (void)touchesCancelled:(NSSet *)touches
               withEvent:(UIEvent *)event
{
  self.interactionState = StateDefault;
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

- (void) nextFrame
{
  
  // Fetch the image.
  UIImage *frame = [self imageForFrame:self.activeIndex];
  CGFloat duration = [self durationForFrame:self.activeIndex];
  
  // Schedule the next frame event.
  [self performSelector:@selector(nextFrame)
             withObject:nil
             afterDelay:duration];
  
  // Transition the state.
  if (self.activeIndex < [self.activeFrames count]-1) {
    self.activeIndex++;
  } else {
    self.activeIndex = 0;
    self.activeSet = [self nextSet];
  }
  
	[image setImage:frame];
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

- (CGFloat) durationForFrame:(NSUInteger)index
{
  NSDictionary *frame = [self.activeFrames objectAtIndex:index];
  return [[frame valueForKey:@"duration"] floatValue];
}

/**
 * Determines what the next set should be based on the current state of the
 * user interaction and the current state in the animation.
 */
- (NSString *)nextSet
{
  static NSString *kTypeTransition = @"transition";
  static NSString *kTypeState      = @"state";
  static NSString *kTransitionSet  = @"set";
  static NSString *kStateTarget    = @"target";
  
  NSString *nextSet = self.activeSet;
  
  // TODO Work out what the next set should be.
  NSDictionary *set = [self set:self.activeSet];
  NSDictionary *actions = [set objectForKey:@"actions"];
  
  
  NSArray *action = nil;
  
  // Check to see if there is an action for the current interaction state.
  switch (self.interactionState) {
    case StateStroke:
      action = [actions objectForKey:kStateStroke];
      break;
    case StatePoke:
      action = [actions objectForKey:kStatePoke];
      break;
    case StateDefault:
    default:
      action = [actions objectForKey:kStateDefault];
      break;
  }
  
  // If there is no specific action, then simply choose the default.
  if (action == nil) {
    action = [actions objectForKey:kStateDefault];
  }
  
  for (NSDictionary *act in action) {
    NSString *type = [act objectForKey:@"type"];
    if ([type isEqualToString:kTypeTransition]) {
      nextSet = [act objectForKey:kTransitionSet];
    } else if ([type isEqualToString:kTypeState]) {
      self.interactionState = [self state:[act objectForKey:kStateTarget]];
    }
    
  }

  return nextSet;
}

- (InteractionState) state:(NSString *)state
{
  if ([state isEqualToString:kStateDefault]) {
    return StateDefault;
  } else if ([state isEqualToString:kStatePoke]) {
    return StatePoke;
  } else if ([state isEqualToString:kStateStroke]) {
    return StateStroke;
  }
  return StateDefault;
}


@end