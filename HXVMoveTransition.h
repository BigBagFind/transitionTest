//
//  HXVMoveTransition.h
//  TransitionTest
//
//  Created by Wuyutie on 2017/11/3.
//  Copyright © 2017年 Wuyutie. All rights reserved.
//

#import "HXVBaseTransition.h"

/*
 *    The move transition animation, it looks like the transition animation
 *  of KeyNote move transition.
 *
 *  When click a cell or a subview, then push to a view controller and you need
 *  animation from the clicked view to the destination controller.
 *
 *  @Note It only supports push and pop mode.
 */
@interface HXVMoveTransition : HXVBaseTransition

/**
 *    The view that is clicked at the pushing view controller.
 */
@property (nonatomic, strong, nonnull) UIView *targetClickedView;

@end

/*
 *
 * A category of UIViewController, for setting a target view,
 * so that it can handle to transition to which view.
 */
@interface UIViewController (HXVMoveTransition)

/**
 * Set a target view to show. When push, it will transition to
 * the target view. and when poped, it will pop from the target view.
 */
@property (nonatomic, strong, nonnull) UIView *hxv_toTargetView;

@end
