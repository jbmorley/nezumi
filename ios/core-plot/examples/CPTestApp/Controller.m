
#import "Controller.h"
#import <CorePlot/CorePlot.h>

@implementation Controller

+(void)initialize {
    [NSValueTransformer setValueTransformer:[CPDecimalNumberValueTransformer new] forName:@"CPDecimalNumberValueTransformer"];
}

-(void)dealloc 
{
    [graph release];
    [super dealloc];
}

-(void)awakeFromNib {
    [super awakeFromNib];

    // Create graph from theme
	CPTheme *theme = [CPTheme themeNamed:kCPDarkGradientTheme];
	graph = [theme newGraph];
	hostView.hostedLayer = graph;
    
    // Setup scatter plot space
    CPXYPlotSpace *plotSpace = (CPXYPlotSpace *)graph.defaultPlotSpace;
    plotSpace.xRange = [CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(1.0) length:CPDecimalFromFloat(2.0)];
    plotSpace.yRange = [CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(1.0) length:CPDecimalFromFloat(3.0)];

    // Axes
	CPXYAxisSet *axisSet = (CPXYAxisSet *)graph.axisSet;
    CPXYAxis *x = axisSet.xAxis;
    x.majorIntervalLength = [NSDecimalNumber decimalNumberWithString:@"0.5"];
    x.constantCoordinateValue = [NSDecimalNumber decimalNumberWithString:@"2"];
    x.minorTicksPerInterval = 2;
	NSArray *exclusionRanges = [NSArray arrayWithObjects:
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(1.99) length:CPDecimalFromFloat(0.02)], 
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(0.99) length:CPDecimalFromFloat(0.02)],
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(2.99) length:CPDecimalFromFloat(0.02)],
		nil];
	x.labelExclusionRanges = exclusionRanges;

    CPXYAxis *y = axisSet.yAxis;
    y.majorIntervalLength = [NSDecimalNumber decimalNumberWithString:@"0.5"];
    y.minorTicksPerInterval = 5;
    y.constantCoordinateValue = [NSDecimalNumber decimalNumberWithString:@"2"];
	exclusionRanges = [NSArray arrayWithObjects:
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(1.99) length:CPDecimalFromFloat(0.02)], 
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(0.99) length:CPDecimalFromFloat(0.02)],
		[CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(3.99) length:CPDecimalFromFloat(0.02)],
		nil];
	y.labelExclusionRanges = exclusionRanges;
    
    // Create one plot that uses bindings
	CPScatterPlot *boundLinePlot = [[[CPScatterPlot alloc] init] autorelease];
    boundLinePlot.identifier = @"Bindings Plot";
	boundLinePlot.dataLineStyle.miterLimit = 1.f;
	boundLinePlot.dataLineStyle.lineWidth = 3.f;
	boundLinePlot.dataLineStyle.lineColor = [CPColor blueColor];
    [graph addPlot:boundLinePlot];
	[boundLinePlot bind:CPScatterPlotBindingXValues toObject:self withKeyPath:@"arrangedObjects.x" options:nil];
	[boundLinePlot bind:CPScatterPlotBindingYValues toObject:self withKeyPath:@"arrangedObjects.y" options:nil];
    
    // Put an area gradient under the plot above
    NSString *pathToFillImage = [[NSBundle mainBundle] pathForResource:@"BlueTexture" ofType:@"png"];
    CPImage *fillImage = [CPImage imageForPNGFile:pathToFillImage];
    fillImage.tiled = YES;
    CPFill *areaGradientFill = [CPFill fillWithImage:fillImage];
    boundLinePlot.areaFill = areaGradientFill;
    boundLinePlot.areaBaseValue = [NSDecimalNumber zero];
    
	// Add plot symbols
	CPLineStyle *symbolLineStyle = [CPLineStyle lineStyle];
	symbolLineStyle.lineColor = [CPColor blackColor];
	CPPlotSymbol *plotSymbol = [CPPlotSymbol ellipsePlotSymbol];
	plotSymbol.fill = [CPFill fillWithColor:[CPColor blueColor]];
	plotSymbol.lineStyle = symbolLineStyle;
    plotSymbol.size = CGSizeMake(10.0, 10.0);
    boundLinePlot.plotSymbol = plotSymbol;
    
    // Create a second plot that uses the data source method
	CPScatterPlot *dataSourceLinePlot = [[[CPScatterPlot alloc] init] autorelease];
    dataSourceLinePlot.identifier = @"Data Source Plot";
	dataSourceLinePlot.dataLineStyle.lineWidth = 3.f;
    dataSourceLinePlot.dataLineStyle.lineColor = [CPColor greenColor];
    dataSourceLinePlot.dataSource = self;
    [graph addPlot:dataSourceLinePlot];
    
    // Put an area gradient under the plot above
    CPColor *areaColor = [CPColor colorWithComponentRed:0.3 green:1.0 blue:0.3 alpha:0.8];
    CPGradient *areaGradient = [CPGradient gradientWithBeginningColor:areaColor endingColor:[CPColor clearColor]];
    areaGradient.angle = -90.0f;
    areaGradientFill = [CPFill fillWithGradient:areaGradient];
    dataSourceLinePlot.areaFill = areaGradientFill;
    dataSourceLinePlot.areaBaseValue = [NSDecimalNumber decimalNumberWithString:@"1.75"];    
	
    // Add some initial data
	NSMutableArray *contentArray = [NSMutableArray arrayWithCapacity:100];
	NSUInteger i;
	for ( i = 0; i < 60; i++ ) {
		id x = [NSDecimalNumber numberWithFloat:1+i*0.05];
		id y = [NSDecimalNumber numberWithFloat:1.2*rand()/(float)RAND_MAX + 1.2];
		[contentArray addObject:[NSMutableDictionary dictionaryWithObjectsAndKeys:x, @"x", y, @"y", nil]];
	}
	self.content = contentArray;
    
    // Add plot space for horizontal bar charts
    CPXYPlotSpace *barPlotSpace = [[CPXYPlotSpace alloc] init];
    barPlotSpace.xRange = [CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(-20.0f) length:CPDecimalFromFloat(200.0f)];
    barPlotSpace.yRange = [CPPlotRange plotRangeWithLocation:CPDecimalFromFloat(-7.0f) length:CPDecimalFromFloat(15.0f)];
    [graph addPlotSpace:barPlotSpace];
    [barPlotSpace release];
    
    // First bar plot
    CPBarPlot *barPlot = [CPBarPlot tubularBarPlotWithColor:[CPColor darkGrayColor] horizontalBars:YES];
    barPlot.baseValue = [NSDecimalNumber decimalNumberWithString:@"20"];
    barPlot.dataSource = self;
    barPlot.barOffset = -0.25f;
    barPlot.identifier = @"Bar Plot 1";
    [graph addPlot:barPlot toPlotSpace:barPlotSpace];
    
    // Second bar plot
    barPlot = [CPBarPlot tubularBarPlotWithColor:[CPColor blueColor] horizontalBars:YES];
    barPlot.dataSource = self;
    barPlot.baseValue = [NSDecimalNumber decimalNumberWithString:@"20"];
    barPlot.barOffset = 0.25f;
    barPlot.cornerRadius = 2.0f;
    barPlot.identifier = @"Bar Plot 2";
    [graph addPlot:barPlot toPlotSpace:barPlotSpace];
}

-(id)newObject 
{
	NSDecimalNumber *x1 = [NSDecimalNumber decimalNumberWithString:@"1.0"];
	NSDecimalNumber *y1 = [NSDecimalNumber decimalNumberWithString:@"1.0"];
    return [NSMutableDictionary dictionaryWithObjectsAndKeys:x1, @"x", y1, @"y", nil];
}

#pragma mark -
#pragma mark Actions

-(IBAction)reloadDataSourcePlot:(id)sender {
    CPPlot *plot = [graph plotWithIdentifier:@"Data Source Plot"];
    [plot reloadData];
}

#pragma mark -
#pragma mark Plot Data Source Methods

-(NSUInteger)numberOfRecordsForPlot:(CPPlot *)plot {
    if ( [plot isKindOfClass:[CPBarPlot class]] ) 
        return 8;
    else
        return [self.arrangedObjects count];
}

-(NSNumber *)numberForPlot:(CPPlot *)plot field:(NSUInteger)fieldEnum recordIndex:(NSUInteger)index {
    NSDecimalNumber *num;
    if ( [plot isKindOfClass:[CPBarPlot class]] ) {
        num = (NSDecimalNumber *)[NSDecimalNumber numberWithInt:(index+1)*(index+1)];
        if ( [plot.identifier isEqual:@"Bar Plot 2"] ) 
            num = [num decimalNumberBySubtracting:[NSDecimalNumber decimalNumberWithString:@"10"]];
    }
    else {
        num = [[self.arrangedObjects objectAtIndex:index] valueForKey:(fieldEnum == CPScatterPlotFieldX ? @"x" : @"y")];
        if ( fieldEnum == CPScatterPlotFieldY ) num = [num decimalNumberByAdding:[NSDecimalNumber one]];
    }
    return num;
}

#pragma mark -
#pragma mark PDF / image export

-(IBAction)exportToPDF:(id)sender;
{
	NSSavePanel *pdfSavingDialog = [NSSavePanel savePanel];
	[pdfSavingDialog setRequiredFileType:@"pdf"];
	
	if ( [pdfSavingDialog runModalForDirectory:nil file:nil] == NSOKButton )
	{
		NSData *dataForPDF = [graph dataForPDFRepresentationOfLayer];
		[dataForPDF writeToFile:[pdfSavingDialog filename] atomically:NO];
	}		
}

-(IBAction)exportToPNG:(id)sender;
{
	NSSavePanel *pngSavingDialog = [NSSavePanel savePanel];
	[pngSavingDialog setRequiredFileType:@"png"];
	
	if ( [pngSavingDialog runModalForDirectory:nil file:nil] == NSOKButton )
	{
		NSImage *image = [graph imageOfLayer];
        NSData *tiffData = [image TIFFRepresentation];
        NSBitmapImageRep *tiffRep = [NSBitmapImageRep imageRepWithData:tiffData];
        NSData *pngData = [tiffRep representationUsingType:NSPNGFileType properties:nil];
		[pngData writeToFile:[pngSavingDialog filename] atomically:NO];
	}		
}

#pragma mark -
#pragma mark Layer exploding for illustration

#define ZDISTANCEBETWEENLAYERS 20.0f
-(IBAction)explodeLayers:(id)sender;
{
	CATransform3D perspectiveRotation = CATransform3DMakeRotation(-40.0 * M_PI / 180.0, 0.0, 1.0, 0.0);
	
	perspectiveRotation = CATransform3DRotate(perspectiveRotation, -55.0 * M_PI / 180.0, perspectiveRotation.m11, perspectiveRotation.m21, perspectiveRotation.m31);
	
	perspectiveRotation = CATransform3DScale(perspectiveRotation, 0.7, 0.7, 0.7);
	graph.masksToBounds = NO;
	graph.superlayer.masksToBounds = NO;
	
	overlayRotationView = [[RotationView alloc] initWithFrame:hostView.frame];
	overlayRotationView.rotationDelegate = self;
	overlayRotationView.rotationTransform = perspectiveRotation;
	[[hostView superview] addSubview:overlayRotationView positioned:NSWindowAbove relativeTo:hostView];
	
	[CATransaction begin];
	[CATransaction setValue:[NSNumber numberWithFloat:1.0f] forKey:kCATransactionAnimationDuration];		

	[Controller recursivelySplitSublayersInZForLayer:graph depthLevel:0];
	graph.superlayer.sublayerTransform = perspectiveRotation;

	[CATransaction commit];
}

+(void)recursivelySplitSublayersInZForLayer:(CALayer *)layer depthLevel:(unsigned int)depthLevel;
{
	layer.zPosition = ZDISTANCEBETWEENLAYERS * (CGFloat)depthLevel;
	layer.borderColor = [[CPColor blueColor] cgColor];
	layer.borderWidth = 2.0;

	depthLevel++;
	for (CALayer *currentLayer in layer.sublayers) {
		[Controller recursivelySplitSublayersInZForLayer:currentLayer depthLevel:depthLevel];
	}
}

-(IBAction)reassembleLayers:(id)sender;
{
	[CATransaction begin];
	[CATransaction setValue:[NSNumber numberWithFloat:1.0f] forKey:kCATransactionAnimationDuration];		
	
	[Controller recursivelyAssembleSublayersInZForLayer:graph];
	graph.superlayer.sublayerTransform = CATransform3DIdentity;

	[CATransaction commit];
	
	[overlayRotationView removeFromSuperview];
	[overlayRotationView release];
	overlayRotationView = nil;
}

+(void)recursivelyAssembleSublayersInZForLayer:(CALayer *)layer;
{
	layer.zPosition = 0.0;
	layer.borderColor = [[CPColor clearColor] cgColor];
	layer.borderWidth = 0.0;
	for (CALayer *currentLayer in layer.sublayers) {
		[Controller recursivelyAssembleSublayersInZForLayer:currentLayer];
	}
}

#pragma mark -
#pragma mark CPRotationDelegate delegate method

-(void)rotateObjectUsingTransform:(CATransform3D)rotationTransform;
{
	[CATransaction begin];
	[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];	

	graph.superlayer.sublayerTransform = rotationTransform;
	
	[CATransaction commit];
}

@end
