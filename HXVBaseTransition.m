//
//  HXVBaseTransition.m
//  TransitionTest
//
//  Created by Wuyutie on 2017/11/2.
//  Copyright © 2017年 Wuyutie. All rights reserved.
//


#define HXVMethodNotImplemented() \
@throw [NSException exceptionWithName:NSInternalInconsistencyException \
reason:[NSString stringWithFormat:@"You must override %@ in a subclass.", NSStringFromSelector(_cmd)] \
userInfo:nil]

#import "HXVBaseTransition.h"

@implementation HXVBaseTransition


- (instancetype)init {
    if (self = [super init]) {
        self.duration = 0.5;
        self.transitionMode = HXVTransitionModePresent;
        self.damp = 0.5;
        self.initialSpringVelocity = 1.0 / 0.5;
        self.animatedWithSpring = NO;
    }
    
    return self;
}

- (instancetype)initWithPresented:(HXVTransitionPresented)presentedCallback
                        dismissed:(HXVTransitionDismiss)dismissCallback {
    if (self = [self init]) {
        self.animationDismissCallback = dismissCallback;
        self.animationPresentedCallback = presentedCallback;
    }
    
    return self;
}

- (instancetype)initWithPushed:(HXVTransitionPush)pushCallback
                         poped:(HXVTransitionPop)popCallback {
    if (self = [self init]) {
        self.animationPopedCallback = popCallback;
        self.animationPushedCallback = pushCallback;
    }
    
    return self;
}

#pragma mark - UIViewControllerAnimatedTransitioning

// Required by UIViewControllerAnimatedTransitioning protocol
// You can override it if you must. Usually normally you don't need to override it,
// just set ther property duration and it will works well.
- (NSTimeInterval)transitionDuration:(id<UIViewControllerContextTransitioning>)transitionContext {
    return self.duration;
}

// Required by UIViewControllerAnimatedTransitioning protocol.
// Subclass must override it to add animation for controller.
- (void)animateTransition:(id<UIViewControllerContextTransitioning>)transitionContext {
    HXVMethodNotImplemented();
}

// Usually you don't need to override it.
// Unless that you need to do something after animation is finished.
- (void)animationEnded:(BOOL)transitionCompleted {
    // Now just do nothing.
}

#pragma mark - UIViewControllerTransitioningDelegate
- (id<UIViewControllerAnimatedTransitioning>)animationControllerForPresentedController:(UIViewController *)presented presentingController:(UIViewController *)presenting sourceController:(UIViewController *)source {
    self.transitionMode = HXVTransitionModePresent;
    
    if (self.animationPresentedCallback) {
        self.animationPresentedCallback(presented, presenting, source, self);
    }
    
    return self;
}

- (id<UIViewControllerAnimatedTransitioning>)animationControllerForDismissedController:(UIViewController *)dismissed {
    self.transitionMode = HXVTransitionModeDismiss;
    
    if (self.animationDismissCallback) {
        self.animationDismissCallback(dismissed, self);
    }
    
    return self;
}

#pragma mark - UINavigationControllerDelegate
- (id<UIViewControllerAnimatedTransitioning>)navigationController:(UINavigationController *)navigationController animationControllerForOperation:(UINavigationControllerOperation)operation fromViewController:(UIViewController *)fromVC toViewController:(UIViewController *)toVC {
    
    if (UINavigationControllerOperationPush == operation) {
        self.transitionMode = HXVTransitionModePush;
        
        if (self.animationPushedCallback) {
            self.animationPushedCallback(fromVC, toVC, self);
        }
    } else if (operation == UINavigationControllerOperationPop) {
        self.transitionMode = HXVTransitionModePop;
        
        toVC.navigationController.delegate = nil;
        
        if (self.animationPopedCallback) {
            self.animationPopedCallback(fromVC, toVC, self);
        }
    }
    
    return self;
}

- (UIView *)toView:(id<UIViewControllerContextTransitioning>)transitionContext {
    UIView *toView = nil;
    
    UIViewController *toVC = [transitionContext viewControllerForKey:UITransitionContextToViewControllerKey];
    
    if ([transitionContext respondsToSelector:@selector(viewForKey:)]) {
        toView = [transitionContext viewForKey:UITransitionContextToViewKey];
    } else {
        toView = toVC.view;
    }
    
    toView.frame = [transitionContext finalFrameForViewController:toVC];
    
    return toView;
}

- (UIView *)fromView:(id<UIViewControllerContextTransitioning>)transitionContext {
    
    UIView *fromView = nil;
    
    UIViewController *fromVC = [transitionContext viewControllerForKey:UITransitionContextFromViewControllerKey];
    
    if ([transitionContext respondsToSelector:@selector(viewForKey:)]) {
        fromView = [transitionContext viewForKey:UITransitionContextFromViewKey];
    } else {
        fromView = fromVC.view;
    }
    
    fromView.frame = [transitionContext initialFrameForViewController:fromVC];
    
    return fromView;
}

@end
