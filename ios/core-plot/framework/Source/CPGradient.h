
// Based on CTGradient (http://blog.oofn.net/2006/01/15/gradients-in-cocoa/)
// CTGradient is in public domain (Thanks Chad Weider!)

#import <Foundation/Foundation.h>
#import "CPDefinitions.h"

typedef struct _CPGradientElement {
	CPRGBAColor color;
	float position;
	
	struct _CPGradientElement *nextElement;
} CPGradientElement;

typedef enum _CPBlendingMode {
	CPLinearBlendingMode,
	CPChromaticBlendingMode,
	CPInverseChromaticBlendingMode
} CPGradientBlendingMode;

typedef enum _CPGradientType {
	CPGradientTypeAxial,
	CPGradientTypeRadial
} CPGradientType;

@class CPColorSpace;
@class CPColor;

@interface CPGradient : NSObject <NSCopying, NSCoding>  {
    @private
	CPColorSpace *colorspace;
	CPGradientElement *elementList;
	CPGradientBlendingMode blendingMode;
	CGFunctionRef gradientFunction;
    CGFloat angle;	// angle in degrees
	CPGradientType gradientType;
}

@property (assign, readonly) CPGradientBlendingMode blendingMode;
@property (assign) CGFloat angle;
@property (assign) CPGradientType gradientType;

+(CPGradient *)gradientWithBeginningColor:(CPColor *)begin endingColor:(CPColor *)end;

+(CPGradient *)aquaSelectedGradient;
+(CPGradient *)aquaNormalGradient;
+(CPGradient *)aquaPressedGradient;

+(CPGradient *)unifiedSelectedGradient;
+(CPGradient *)unifiedNormalGradient;
+(CPGradient *)unifiedPressedGradient;
+(CPGradient *)unifiedDarkGradient;

+(CPGradient *)sourceListSelectedGradient;
+(CPGradient *)sourceListUnselectedGradient;

+(CPGradient *)rainbowGradient;
+(CPGradient *)hydrogenSpectrumGradient;

-(CPGradient *)gradientWithAlphaComponent:(float)alpha;

-(CPGradient *)addColorStop:(CPColor *)color atPosition:(float)position;	// positions given relative to [0,1]
-(CPGradient *)removeColorStopAtIndex:(NSUInteger)index;
-(CPGradient *)removeColorStopAtPosition:(float)position;

-(CGColorRef)colorStopAtIndex:(NSUInteger)index;
-(CGColorRef)colorAtPosition:(float)position;

-(void)drawSwatchInRect:(CGRect)rect inContext:(CGContextRef)context;
-(void)fillRect:(CGRect)rect inContext:(CGContextRef)context;
-(void)fillPathInContext:(CGContextRef)context;

@end
