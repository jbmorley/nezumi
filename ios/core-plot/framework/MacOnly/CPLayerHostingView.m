#import "CPLayerHostingView.h"
#import "CPLayer.h"

@interface CPLayerHostingView()

@property (nonatomic, readwrite, assign) CPLayer *layerBeingClickedOn;

@end

@implementation CPLayerHostingView

@synthesize hostedLayer;
@synthesize layerBeingClickedOn;

-(id)initWithFrame:(NSRect)frame {
    if (self = [super initWithFrame:frame]) {
		hostedLayer = nil;
		layerBeingClickedOn = nil;
		CPLayer *mainLayer = [[CPLayer alloc] initWithFrame:NSRectToCGRect(frame)];
		self.layer = mainLayer;
		[mainLayer release];
		[self setWantsLayer:YES];
    }
    return self;
}

- (void)dealloc
{
	self.hostedLayer = nil;
	self.layerBeingClickedOn = nil;
	[super dealloc];
}

#pragma mark -
#pragma mark Mouse handling

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;
{
	return YES;
}

-(void)mouseDown:(NSEvent *)theEvent;
{
	CGPoint pointOfMouseDown = NSPointToCGPoint([self convertPoint:[theEvent locationInWindow] fromView:nil]);
	CALayer *hitLayer = [self.layer hitTest:pointOfMouseDown];
	
	if ( (hitLayer != nil) && [hitLayer isKindOfClass:[CPLayer class]]) {
		self.layerBeingClickedOn = (CPLayer *)hitLayer;
		[(CPLayer *)hitLayer mouseOrFingerDownAtPoint:pointOfMouseDown];
	}
}

-(void)mouseDragged:(NSEvent *)theEvent;
{
	if (self.layerBeingClickedOn == nil) {
		return;
	}
	
	CGPoint pointOfMouseDrag = NSPointToCGPoint([self convertPoint:[theEvent locationInWindow] fromView:nil]);
	
	[self.layerBeingClickedOn mouseOrFingerUpAtPoint:pointOfMouseDrag];
	self.layerBeingClickedOn = nil;	
}

-(void)mouseUp:(NSEvent *)theEvent;
{
	if (self.layerBeingClickedOn == nil) {
		return;		
	}
	
	CGPoint pointOfMouseUp = NSPointToCGPoint([self convertPoint:[theEvent locationInWindow] fromView:nil]);
	
	[self.layerBeingClickedOn mouseOrFingerUpAtPoint:pointOfMouseUp];
	self.layerBeingClickedOn = nil;	
}

#pragma mark -
#pragma mark Accessors

-(void)setHostedLayer:(CPLayer *)newLayer
{
	if (newLayer != hostedLayer) {
		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[hostedLayer removeFromSuperlayer];
		[hostedLayer release];
		hostedLayer = [newLayer retain];
		if (hostedLayer) {
			[self.layer addSublayer:hostedLayer];
		}
		
		[CATransaction commit];
	}
}

@end
