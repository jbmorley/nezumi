
#import "CPFill.h"
#import "_CPFillColor.h"
#import "_CPFillGradient.h"
#import "_CPFillImage.h"
#import "CPColor.h"
#import "CPImage.h"

@implementation CPFill

#pragma mark -
#pragma mark init/dealloc

+(CPFill *)fillWithColor:(CPColor *)aColor 
{
	return [[(_CPFillColor *)[_CPFillColor alloc] initWithColor:aColor] autorelease];
}

+(CPFill *)fillWithGradient:(CPGradient *)aGradient 
{
	return [[[_CPFillGradient alloc] initWithGradient: aGradient] autorelease];
}

+(CPFill *)fillWithImage:(CPImage *)anImage 
{
	return [[(_CPFillImage *)[_CPFillImage alloc] initWithImage:anImage] autorelease];
}

-(id)initWithColor:(CPColor *)aColor 
{
	[self release];
	
	self = [(_CPFillColor *)[_CPFillColor alloc] initWithColor: aColor];
	
	return self;
}

-(id)initWithGradient:(CPGradient *)aGradient 
{
	[self release];
	
	self = [[_CPFillGradient alloc] initWithGradient: aGradient];
	
	return self;
}

-(id)initWithImage:(CPImage *)anImage 
{
	[self release];
	
	self = [(_CPFillImage *)[_CPFillImage alloc] initWithImage: anImage];
	
	return self;
}

#pragma mark -
#pragma mark Drawing

-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext
{
	// do nothing--subclasses override to do drawing here
}

-(void)fillPathInContext:(CGContextRef)theContext
{
	// do nothing--subclasses override to do drawing here
}

#pragma mark -
#pragma mark NSCopying methods

-(id)copyWithZone:(NSZone *)zone
{
	// do nothing--implemented in subclasses
	return nil;
}

@end
