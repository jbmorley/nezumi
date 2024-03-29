
#import "CPGraph.h"
#import "CPExceptions.h"
#import "CPPlot.h"
#import "CPPlotArea.h"
#import "CPPlotSpace.h"
#import "CPFill.h"
#import "CPAxisSet.h"
#import "CPAxis.h"

@interface CPGraph()

@property (nonatomic, readwrite, retain) NSMutableArray *plots;
@property (nonatomic, readwrite, retain) NSMutableArray *plotSpaces;

-(void)plotSpaceMappingDidChange:(NSNotification *)notif;

@end

@implementation CPGraph

@synthesize axisSet;
@synthesize plotArea;
@synthesize fill;
@synthesize plots;
@synthesize plotSpaces;

#pragma mark -
#pragma mark Init/Dealloc

-(id)initWithFrame:(CGRect)newFrame
{
	if ( self = [super initWithFrame:newFrame] ) {
 		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		self.fill = nil;
		self.plots = [[NSMutableArray alloc] init];
        
        // Plot area
        self.plotArea = [[CPPlotArea alloc] initWithFrame:self.bounds];
        [self addSublayer:self.plotArea];
		
        // Plot spaces
		self.plotSpaces = [[NSMutableArray alloc] init];
        CPPlotSpace *newPlotSpace = [self newPlotSpace];
        [self addPlotSpace:newPlotSpace];
        [newPlotSpace release];
        
        // Axis set
        CPAxisSet *newAxisSet = [self newAxisSet];
        self.axisSet = newAxisSet;
        [newAxisSet release];
        
		[CATransaction commit];
		
		self.needsDisplayOnBoundsChange = YES;
	}
	return self;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
	[axisSet release];
	[plotArea release];
    self.fill = nil;
	self.plots = nil;
	self.plotSpaces = nil;
	[super dealloc];
}

#pragma mark -
#pragma mark Retrieving Plots

-(void)reloadData
{
    [[self allPlots] makeObjectsPerformSelector:@selector(reloadData)];
}

-(NSArray *)allPlots 
{    
	return [NSArray arrayWithArray:self.plots];
}

-(CPPlot *)plotAtIndex:(NSUInteger)index
{
    return [self.plots objectAtIndex:index];
}

-(CPPlot *)plotWithIdentifier:(id <NSCopying>)identifier 
{
	for (CPPlot *plot in self.plots) {
        if ( [[plot identifier] isEqual:identifier] ) return plot;
	}
    return nil;
}

#pragma mark -
#pragma mark Organizing Plots

-(void)addPlot:(CPPlot *)plot
{
	[self addPlot:plot toPlotSpace:self.defaultPlotSpace];
}

-(void)addPlot:(CPPlot *)plot toPlotSpace:(CPPlotSpace *)space
{
	if (plot) {
		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[self.plots addObject:plot];
		plot.plotSpace = space;
		[space addSublayer:plot];
		
		[CATransaction commit];
		
		[self setNeedsDisplay];
	}
}

-(void)removePlot:(CPPlot *)plot
{
    if ( [self.plots containsObject:plot] ) {
 		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[self.plots removeObject:plot];
        plot.plotSpace = nil;
        [plot removeFromSuperlayer];
		
		[CATransaction commit];
		
		[self setNeedsDisplay];
    }
    else {
        [NSException raise:CPException format:@"Tried to remove CPPlot which did not exist."];
    }
}

-(void)insertPlot:(CPPlot* )plot atIndex:(NSUInteger)index 
{
	[self insertPlot:plot atIndex:index intoPlotSpace:self.defaultPlotSpace];
}

-(void)insertPlot:(CPPlot* )plot atIndex:(NSUInteger)index intoPlotSpace:(CPPlotSpace *)space
{
	if (plot) {
		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[self.plots insertObject:plot atIndex:index];
		plot.plotSpace = space;
		[space addSublayer:plot];
		
		[CATransaction commit];
		
		[self setNeedsDisplay];
	}
}

-(void)removePlotWithIdentifier:(id <NSCopying>)identifier 
{
	CPPlot* plotToRemove = [self plotWithIdentifier:identifier];
	if (plotToRemove) {
		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		plotToRemove.plotSpace = nil;
		[plotToRemove removeFromSuperlayer];
		[self.plots removeObjectIdenticalTo:plotToRemove];
		
		[CATransaction commit];
		
		[self setNeedsDisplay];
	}
}

#pragma mark -
#pragma mark Retrieving Plot Spaces

-(CPPlotSpace *)defaultPlotSpace {
    return ( self.plotSpaces.count > 0 ? [self.plotSpaces objectAtIndex:0] : nil );
}

-(NSArray *)allPlotSpaces
{
	return [NSArray arrayWithArray:self.plotSpaces];
}

-(CPPlotSpace *)plotSpaceAtIndex:(NSUInteger)index
{
	return ( self.plotSpaces.count > index ? [self.plotSpaces objectAtIndex:index] : nil );
}

-(CPPlotSpace *)plotSpaceWithIdentifier:(id <NSCopying>)identifier
{
	for (CPPlotSpace *plotSpace in self.plotSpaces) {
        if ( [[plotSpace identifier] isEqual:identifier] ) return plotSpace;
	}
    return nil;	
}

#pragma mark -
#pragma mark Organizing Plot Spaces

-(void)addPlotSpace:(CPPlotSpace *)space
{
	[CATransaction begin];
	[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

	space.frame = self.plotArea.bounds;
	[self.plotSpaces addObject:space];
	[self.plotArea addSublayer:space];
	
	[CATransaction commit];
	
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(plotSpaceMappingDidChange:) name:CPPlotSpaceCoordinateMappingDidChangeNotification object:space];
}

-(void)removePlotSpace:(CPPlotSpace *)plotSpace
{
	if ( [self.plotSpaces containsObject:plotSpace] ) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:CPPlotSpaceCoordinateMappingDidChangeNotification object:plotSpace];
		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[self.plotSpaces removeObject:plotSpace];
        [plotSpace removeFromSuperlayer];
        for ( CPAxis *axis in self.axisSet.axes ) {
            if ( axis.plotSpace == plotSpace ) axis.plotSpace = nil;
        }
		
		[CATransaction commit];
    }
    else {
        [NSException raise:CPException format:@"Tried to remove CPPlotSpace which did not exist."];
    }
}


#pragma mark -
#pragma mark Coordinate Changes in Plot Spaces

-(void)plotSpaceMappingDidChange:(NSNotification *)notif 
{
    [self setNeedsLayout];
    [self.axisSet relabelAxes];
    for ( CPPlot *plot in self.plots ) {
        [plot setNeedsDisplay];
    }
}

#pragma mark -
#pragma mark Axis Set

-(void)setAxisSet:(CPAxisSet *)newSet
{
    if ( newSet != axisSet ) {
 		[CATransaction begin];
		[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];

		[axisSet removeFromSuperlayer];
		[newSet retain];
        [axisSet release];
        axisSet = newSet;
        if ( axisSet ) {
			axisSet.graph = self;
			[self addSublayer:axisSet];	
		}
		
		[CATransaction commit];
		
		[self setNeedsDisplay];
    }
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
	return CPDefaultZPositionGraph;
}

-(void)layoutSublayers 
{
	[super layoutSublayers];
	
    if ( self.axisSet ) {
        // Set the bounds so that the axis set coordinates coincide with the 
        // plot area drawing coordinates.
        CGRect axisSetBounds = self.bounds;
        axisSetBounds.origin = [self convertPoint:self.bounds.origin toLayer:self.plotArea];
		
		CPAxisSet *theAxisSet = self.axisSet;
        theAxisSet.bounds = axisSetBounds;
        theAxisSet.anchorPoint = CGPointZero;
        theAxisSet.position = self.bounds.origin;
    }
}

#pragma mark -
#pragma mark Accessors

-(void)setFill:(CPFill *)newFill 
{
    if ( newFill != fill ) {
		[newFill retain];
        [fill release];
        fill = newFill;
        [self setNeedsDisplay];
    }
}

@end
