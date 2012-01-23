//
//  DINezScreen.m
//  Nezumi2
//
//  Created by Jason Barrie Morley on 01/07/2009.
//  Copyright 2009 In7. All rights reserved.
//

#import "DINezAnimationView.h"


@implementation DINezAnimationView

@synthesize image;


- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
    }
    return self;
}

- (void)awakeFromNib {
	
	_blinkSet = [[NSArray arrayWithObjects:@"nez-blink1.gif", @"nez-blink1.gif", @"nez-blink2.gif", @"nez-blink3.gif", @"nez-blink2.gif", nil] retain];
	
	_beginStrokeSet = [[NSArray arrayWithObjects:@"nez-pet1.gif", @"nez-pet2.gif", nil] retain];
	_strokeSet = [[NSArray arrayWithObjects:@"nez-pet3.gif", @"nez-pet4.gif", @"nez-pet5.gif", @"nez-pet4.gif", @"nez-pet3.gif", nil] retain];
	_endStrokeSet = [[NSArray arrayWithObjects:@"nez-pet2.gif", @"nez-pet1.gif", nil] retain];
	
	_activeSet = _blinkSet;
	_state = STATE_BLINK;
	
	// Initialize the animation sets
	_frameIndex = 0;
	[NSTimer scheduledTimerWithTimeInterval:0.25
                                   target:self
                                 selector:@selector(onTick)
                                 userInfo:nil
                                  repeats:YES];
	
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	_stroking = YES;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	_stroking = NO;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	_stroking = NO;
}


- (void)onTick {
	
	_frameIndex++;
	if (_frameIndex >= [_activeSet count]) {
	
		switch (_state) {
			case STATE_BLINK:
				if (_stroking) {
					_activeSet = _beginStrokeSet;
					_state = STATE_BEGIN_STROKE;
				}
				break;
			case STATE_BEGIN_STROKE:
				if (_stroking) {
					_activeSet = _strokeSet;
					_state = STATE_STROKE;
				} else {
					_activeSet = _endStrokeSet;
					_state = STATE_END_STROKE;
				}
				break;
			case STATE_STROKE:
				if (!_stroking) {
					_activeSet = _endStrokeSet;
					_state = STATE_END_STROKE;
				}
				break;
			case STATE_END_STROKE:
				if (!_stroking) {
					_activeSet = _blinkSet;
					_state = STATE_BLINK;
				} else {
					_activeSet = _beginStrokeSet;
					_state = STATE_BEGIN_STROKE;
				}
				break;
			default:
				NSLog(@"Unknown State");
		}		
	
		if (_stroking) {
			_activeSet = _strokeSet;
		} else {
			_activeSet = _blinkSet;
		}

		_frameIndex = 0;
	}
	
	[image setImage:[UIImage imageNamed:(NSString *)[_activeSet objectAtIndex:_frameIndex]]];
	
}


- (void)drawRect:(CGRect)rect {
    // Drawing code
}


- (void)dealloc {
	[_blinkSet release];
	[_beginStrokeSet release];
	[_strokeSet release];
	[_endStrokeSet release];
    [super dealloc];
}


@end
