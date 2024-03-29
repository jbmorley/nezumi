
#import <Foundation/Foundation.h>

@interface CPAnimationKeyFrame : NSObject {
    id <NSCopying> identifier;
    BOOL isInitialFrame;
    NSTimeInterval duration;
}

@property (nonatomic, readwrite, copy) id <NSCopying> identifier;
@property (nonatomic, readwrite, assign) NSTimeInterval duration;

-(id)initAsInitialFrame:(BOOL)isFirst;

@end
