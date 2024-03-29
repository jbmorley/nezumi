#import "CPPlotArea.h"
#import "CPPlotSpace.h"
#import "CPFill.h"

@implementation CPPlotArea

@synthesize fill;

#pragma mark -
#pragma mark Init/Dealloc

-(id)initWithFrame:(CGRect)newFrame
{
	if ( self = [super initWithFrame:newFrame] ) {
		self.needsDisplayOnBoundsChange = YES;
		
		self.fill = nil;
	}
	return self;
}

-(void)dealloc
{
	self.fill = nil;
	[super dealloc];
}

#pragma mark -
#pragma mark Drawing

-(void)renderAsVectorInContext:(CGContextRef)theContext
{
	[self.fill fillRect:self.bounds inContext:theContext];
}

#pragma mark -
#pragma mark Layout

+(CGFloat)defaultZPosition 
{
	return CPDefaultZPositionPlotArea;
}

#pragma mark -
#pragma mark Accessors

-(void)setFill:(CPFill *)newFill;
{
	if (newFill != fill) {
		[fill release];
		fill = [newFill retain];
		[self setNeedsDisplay];
	}
}

@end
