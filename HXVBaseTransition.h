//
//  HXVBaseTransition.h
//  TransitionTest
//
//  Created by Wuyutie on 2017/11/2.
//  Copyright © 2017年 Wuyutie. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@class HXVBaseTransition;

/**
 *    The block version of protocol, just see:
 *
 *  - (id<UIViewControllerAnimatedTransitioning>)animationControllerForPresentedController:(UIViewController *)presented presentingController:(UIViewController *)presenting sourceController:(UIViewController *)source
 *
 *    @param presented    The controller will be presented
 *    @param presenting    The controller to present the presented controller
 *    @param source        The source controller
 *  @param transition The object which implement UIViewControllerTransitioningDelegate protocol.
 *                    Just strongly cast it to the subclass type which was called.
 *
 *  @Note For more information, @see UIViewControllerTransitioningDelegate
 */
typedef void(^HXVTransitionPresented)(UIViewController *presented,
                                      UIViewController *presenting,
                                      UIViewController *source,
                                      HXVBaseTransition *transition);

/**
 *    The block version of protocol, just see:
 *
 *  - (nullable id <UIViewControllerAnimatedTransitioning>)animationControllerForDismissedController:(UIViewController *)dismissed;
 *
 *  @param dismissed  The controller will be dismissed.
 *    @param transition The object which implement UIViewControllerTransitioningDelegate protocol.
 *                    If you want to change, you can configure it. Usually, you don't need to
 *                    config anything, and it will works well. Cast it to the real subclass type.
 *
 *  @Note For more information, @see UIViewControllerTransitioningDelegate
 */
typedef void(^HXVTransitionDismiss)(UIViewController *dismissed, HXVBaseTransition *transition);

/**
 *    The call back for custom push transition animation.
 *
 *    @param fromVC            Push from view controller
 *    @param toVC                Push to view controller
 *    @param transition The object which implement UINavigationControllerDelegate for push/pop.
 *                    If you want to change, you can configure it. Usually, you don't need to
 *                    config anything, and it will works well. Cast it to the real subclass type.
 *
 *  @Note see UINavigationControllerDelegate
 */
typedef void(^HXVTransitionPush)(UIViewController *fromVC,
                                 UIViewController *toVC,
                                 HXVBaseTransition *transition);
// The pop same to the push
typedef HXVTransitionPush HXVTransitionPop;

/**
 * The transition mode. It's double pairs of mode.
 */
typedef NS_ENUM(NSUInteger, HXVTransitionMode) {
    HXVTransitionModeDismiss,   // Dismiss
    HXVTransitionModePresent,  // Present
    HXVTransitionModePush,     // Push
    HXVTransitionModePop       // Pop
};

/**
 *    Base class for transition animation.
 */
@interface HXVBaseTransition : NSObject <
UIViewControllerAnimatedTransitioning, // This is the required protocol.
UIViewControllerTransitioningDelegate, // for present and dismiss transition
UINavigationControllerDelegate // For push and pop transition
>

/**
 *    The duration of transition animations, for pairs of present/dissmis
 *  or push/pop. Default is 0.5s.
 */
@property (nonatomic, assign) NSTimeInterval duration;

/**
 * The transition mode, Only `Dismiss`、`Present`、`Push`、`Pop`.
 * Default is `kHYBTransitionPush`
 *
 * @see For more information, just see HYBTransitionMode.
 */
@property (nonatomic, assign) HXVTransitionMode transitionMode;

/**
 * The subclass can use it directly.
 * When presented, it will be invoked if it exsists.
 */
@property (nonatomic, copy) HXVTransitionPresented animationPresentedCallback;

/**
 * The subclass can use it directly.
 * When dismissed, it will be invoked if it exsists.
 */
@property (nonatomic, copy) HXVTransitionDismiss animationDismissCallback;

/**
 * The subclass can use it directly.
 * When pushed, it will be invoked if it exsists.
 */
@property (nonatomic, copy) HXVTransitionPush animationPushedCallback;

/**
 * The subclass can use it directly.
 * When poped, it will be invoked if it exsists.
 */
@property (nonatomic, copy) HXVTransitionPop animationPopedCallback;

/**
 *    Default is NO, if set to YES, it will be presented and dismissed with
 *  spring animation.
 */
@property (nonatomic, assign) BOOL animatedWithSpring;

/**
 * The initial Spring velocity, Only when animatedWithSpring is YES, it will take effect.
 * Default is 1.0 / 0.5. If you don't know, just use the default value.
 */
@property (nonatomic, assign) CGFloat initialSpringVelocity;

/**
 *    The Spring damp, Only when animatedWithSpring is YES, it will take effect.
 *
 *  Default is 0.5. If you don't know, just use the default value.
 */
@property (nonatomic, assign) CGFloat damp;

/**
 *  The designed-initializer for present/dismiss. Subclass can override it to initialize something.
 *    Call it to create bubble transition object, with double callbacks.
 *
 *    @param presentedCallback    When presented, it will be invoked.
 *    @param dismissCallback        When dissmissed, it will be invoked.
 *
 *    @return The transition object, usually it is no use. If you really need it to
 *          Do something, you can own it strongly.
 */
- (instancetype)initWithPresented:(HXVTransitionPresented)presentedCallback
                        dismissed:(HXVTransitionDismiss)dismissCallback;

/**
 *  The designed-initializer for push/pop. Subclass can override it to initialize something.
 *    Call it to create bubble transition object, with double callbacks.
 
 *
 *    @param pushCallback    When pushed, it will be invoked.
 *    @param popCallback    When poped, it will be invoked.
 *
 *    @return The transition object, usually it is no use. If you really need it to
 *          Do something, you can own it strongly.
 */
- (instancetype)initWithPushed:(HXVTransitionPush)pushCallback
                         poped:(HXVTransitionPop)popCallback;

- (UIView *)toView:(id<UIViewControllerContextTransitioning>)transitionContext ;
- (UIView *)fromView:(id<UIViewControllerContextTransitioning>)transitionContext ;

@end
