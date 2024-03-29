
#import <Foundation/Foundation.h>
#import "CPDefinitions.h"

@interface CPPlotRange : NSObject <NSCoding, NSCopying> {
	@private
	NSDecimalNumber *location;
	NSDecimalNumber *length;
}

@property (readwrite, copy) NSDecimalNumber *location;
@property (readwrite, copy) NSDecimalNumber *length;
@property (readonly) NSDecimalNumber *end;

+(CPPlotRange *)plotRangeWithLocation:(NSDecimal)loc length:(NSDecimal)len;

-(id)initWithLocation:(NSDecimal)loc length:(NSDecimal)len;

-(BOOL)contains:(NSDecimalNumber *)number;

@end
