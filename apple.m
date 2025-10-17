#import <AppKit/AppKit.h>

int
bare__open(const char *app, const char *arg) {
  @autoreleasepool {
    NSURL *path = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%s", app]];

    NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];

    configuration.createsNewApplicationInstance = YES;

    if (arg) configuration.arguments = @[ [NSString stringWithFormat:@"%s", arg] ];

    __block NSError *error = nil;

    dispatch_semaphore_t sem = dispatch_semaphore_create(0);

    [[NSWorkspace sharedWorkspace]
      openApplicationAtURL:path
             configuration:configuration
         completionHandler:^(NSRunningApplication *app, NSError *err) {
           error = err;

           dispatch_semaphore_signal(sem);
         }];

    dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);

    dispatch_release(sem);

    if (error) return -1;
  }

  return 0;
}
