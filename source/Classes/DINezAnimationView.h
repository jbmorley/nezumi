//
//  DINezScreen.h
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright 2009 In7. All rights reserved.
//

#import <UIKit/UIKit.h>

enum {
	STATE_BLINK,
	STATE_BEGIN_STROKE,
	STATE_STROKE,
	STATE_END_STROKE
};

@interface DINezAnimationView : UIView {

	IBOutlet UIImageView *image;	

	int _frameIndex;
	
	NSArray *_activeSet;	
	NSArray *_blinkSet;
	NSArray *_beginStrokeSet;
	NSArray *_strokeSet;
	NSArray *_endStrokeSet;
	
	BOOL _stroking;
	
	int _state;
	
}

@property(nonatomic, retain) IBOutlet UIImageView *image;

@end
