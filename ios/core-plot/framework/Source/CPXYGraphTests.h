
#import "CPDataSourceTestCase.h"
#import "CPXYGraph.h"

@interface CPXYGraphTests : CPDataSourceTestCase {
    CPXYGraph *graph;

}

@property (retain,readwrite) CPXYGraph *graph;

- (void)addScatterPlot;
@end
