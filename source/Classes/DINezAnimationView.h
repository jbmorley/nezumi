//
//  DINezScreen.h
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright 2009 In7. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
  
  StateDefault,
  StateStroke,
  StatePoke,
  
} InteractionState;

@interface DINezAnimationView : UIView {

	IBOutlet UIImageView *image;	

  NSDictionary *_sets;
  NSString *_activeSet;
  NSUInteger _activeIndex;

  InteractionState _interactionState;
  
  NSDate *_touchStart;
	
}

@property(nonatomic, retain) IBOutlet UIImageView *image;
@property (nonatomic, retain) NSString *activeSet;
@property (nonatomic, retain) NSDictionary *sets;
@property (nonatomic, assign) NSUInteger activeIndex;
@property (nonatomic, assign) InteractionState interactionState;
@property (nonatomic, retain) NSDate *touchStart;

@end
