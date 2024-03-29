
#import "CPLayer.h"
#import "CPDefinitions.h"

@class CPAxisSet;
@class CPPlotRange;

extern NSString * const CPPlotSpaceCoordinateMappingDidChangeNotification;

@interface CPPlotSpace : CPLayer {
	id <NSCopying, NSObject> identifier;
}

@property (nonatomic, readwrite, copy) id <NSCopying, NSObject> identifier;

@end

@interface CPPlotSpace (AbstractMethods)

-(CGPoint)viewPointForPlotPoint:(NSDecimalNumber **)decimalNumbers;
-(void)plotPoint:(NSDecimalNumber **)plotPoint forViewPoint:(CGPoint)point;

-(CPPlotRange *)plotRangeForCoordinate:(CPCoordinate)coordinate;

@end
