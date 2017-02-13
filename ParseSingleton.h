//
//  ParseSingleton.h
//  ramonparse
//
//  Created by Ramon Calimbas.
//
//

#import <Foundation/Foundation.h>
#import <Parse/Parse.h>

@interface ParseSingleton : NSObject

typedef void (^CallbackBlock)(id object, NSError *error);
typedef void (^CallbackBlockWithExtra)(id extra, id object, NSError *error);
typedef void (^SimpleCallbackBlock)(BOOL completed);

+(ParseSingleton *)sharedParseSingleton;
-(void)setApplicationId:(NSString *)appId clientKey:(NSString *)clientKey;

// PFObject
-(void)createObjectWithClassName:(NSString *)className andProperties:(NSDictionary *)properties andCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;
-(void)fetchObjectOfClassName:(NSString *)className andObjectId:(NSString *)objectId andCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;
-(void)findObjectsOfClassName:(NSString *)className withCriteria:(NSArray *)criteria andCallback:(void(^)(NSArray *, NSError *))callbackBlock;
-(void)updateObject:(NSDictionary *)object withCallback:(void(^)(BOOL, NSError *))callbackBlock;
-(void)deleteObjectWithClassName:(NSString *)className andObjectId:(NSString *)objectId andCallback:(void(^)(BOOL, NSError *))callbackBlock;
-(void)deleteObject:(NSDictionary *)object withCallback:(void(^)(BOOL, NSError *))callbackBlock;
-(void)saveAllObjects:(NSArray *)objects withCallback:(void(^)(BOOL, NSError *))callbackBlock;

// PFFile
-(void)createFileWithName:(NSString *)name andData:(NSData *)data andAttachmentInfo:(NSDictionary *)attachmentInfo withCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;

// PFUser
-(void)signupUserWithUsername:(NSString *)username andPassword:(NSString *)password andEmail:(NSString *)email andCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;
-(void)signupUserWithUsername:(NSString *)username andPassword:(NSString *)password andCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;
-(void)loginWithUsername:(NSString *)username andPassword:(NSString *)password andCallback:(void(^)(NSDictionary *, NSError *))callbackBlock;
-(void)requestPasswordResetForEmail:(NSString *)email;
-(NSDictionary *)currentUser;
-(void)refreshCurrentUser;
-(void)logout;

// PFCloud
-(void)callCloudFunction:(NSString *)functionName withParameters:(NSDictionary *)parameters andCallback:(void(^)(id object, NSError *error))callbackBlock;

// PFPush
- (void)registerForPushWithDeviceToken:(NSString *)deviceToken andSubscribeToChannel:(NSString *)channel withCallback:(void(^)(BOOL, NSError *))callbackBlock;
- (void)unsubscribeFromPushChannel:(NSString *)channel withCallback:(void(^)(BOOL, NSError *))callbackBlock;
- (void)subscribeFromPushChannel:(NSString *)channel withCallback:(void (^)(BOOL, NSError *))callbackBlock;
- (void)clearBadge;

@end
