//
//  FLDownload.h
//  DownloadIOS7
//
//  Created by Lombardo on 10/11/13.
//  Copyright (c) 2013 Lombardo. All rights reserved.
//
//  This object manage background downloads using NSURLSession.
//  Supported only on iOS 7.0 and above.

#import <Foundation/Foundation.h>

@interface FLDownload : NSObject <NSURLSessionDelegate, NSURLSessionDownloadDelegate>

/**
 A dictionary of FLDownload objects
 */
+(NSDictionary *)downloads;

/**
 Returns a download object that supports background on iOS 7. You must start the download sending "start".
 */
-(id)initBackgroundDownloadWithURL:(NSURL *)url completion:(void (^)(BOOL success, NSError *error))completion NS_AVAILABLE_IOS(7_0);

/**
 Must by called by:
 - (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler
 When the app is suspended and a Download is finished, system calls the above AppDelegate method. If the app was suspended, the below method does nothing, since all objects are created and configured. The delegate method of NSURLSession are called and the file moved to the final path.
 When the app was previously killed, the above method is called, and then the below method recreates the NSURLSession object with the passed session id (the complete URL is used as session id). No need to create again the download, the session is resumed automatically and the delegate methods called
 To support resuming from the background, use this implementation in your AppDelegate (copy&paste):
 
 - (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler
 {
    NSURL *url = [NSURL URLWithString:identifier];
    [FLDownload resumeDownloadForSession:url];
    completionHandler();
 }
 */
+(void)resumeDownloadForSession:(NSURL *)session NS_AVAILABLE_IOS(7_0);

/**
 Set the completion block
 */
@property (copy, nonatomic) void (^completionBlock)(BOOL success, NSError *error);

/**
 Set the download url
 */
@property (strong, nonatomic) NSURL *url;

/**
 Set the destination directory for the file. Defaults: documents directory
 */
@property (copy, nonatomic) NSString *destinationDirectory;

/**
 Start the download. The FLDownload object is retained by the system until the download ends or fail (then the completion block is called and the object disposed)
 */
-(void)start NS_AVAILABLE_IOS(7_0);

/**
 Set the progress update block - optional
 */
@property (copy, nonatomic) void (^progressBlock)(int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite);
-(void)setProgressBlock:(void (^)(int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite))progressBlock;

/**
 The name of the file that it's being downloaded
 */
@property (copy, nonatomic, readonly) NSString *fileName;




@end