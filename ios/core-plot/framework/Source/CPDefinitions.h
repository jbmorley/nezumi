
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

typedef NSInteger CPInteger;
typedef CGFloat   CPFloat;
typedef double    CPDouble;

extern NSTimeInterval kCPIndefiniteDuration;

typedef enum  _CPNumericType {
    CPNumericTypeInteger,
    CPNumericTypeFloat,
    CPNumericTypeDouble
} CPNumericType;

typedef enum _CPErrorBarType {
    CPErrorBarTypeCustom,
    CPErrorBarTypeConstantRatio,
    CPErrorBarTypeConstantValue
} CPErrorBarType;

typedef enum _CPScaleType {
    CPScaleTypeLinear,
    CPScaleTypeLogN,
    CPScaleTypeLog10,
    CPScaleTypeAngular,
	CPScaleTypeDateTime,
	CPScaleTypeCategory
} CPScaleType;

typedef enum _CPCoordinate {
    CPCoordinateX = 0,
    CPCoordinateY = 1,
    CPCoordinateZ = 2
} CPCoordinate;

typedef struct _CPRGBAColor {
	float red, green, blue, alpha;
} CPRGBAColor;

typedef enum _CPSign {
	CPSignNone,
	CPSignPositive,
	CPSignNegative
} CPSign;

extern const CGFloat CPDefaultZPositionGraph;
extern const CGFloat CPDefaultZPositionPlotArea; 
extern const CGFloat CPDefaultZPositionAxisSet;
extern const CGFloat CPDefaultZPositionAxis;
extern const CGFloat CPDefaultZPositionPlotSpace;
extern const CGFloat CPDefaultZPositionPlot;
extern const CGFloat CPDefaultZPositionAxisSetOverlay;


