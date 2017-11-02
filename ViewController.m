//
//  ViewController.m
//  TransitionTest
//
//  Created by Wuyutie on 2017/11/2.
//  Copyright © 2017年 Wuyutie. All rights reserved.
//

#import "ViewController.h"
#import "DetailViewController.h"
#import "HXVMoveTransition.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (nonatomic, strong) HXVMoveTransition *transition;

@end

@implementation ViewController


- (IBAction)action:(id)sender {
    id navigationDelegate = self.navigationController.delegate;
    DetailViewController *vc = [[DetailViewController alloc] init];
    self.transition = [[HXVMoveTransition alloc] initWithPushed:^(UIViewController *fromVC, UIViewController *toVC, HXVBaseTransition *transition) {
        HXVMoveTransition *move = (HXVMoveTransition *)transition;
        move.targetClickedView = self.imageView;
        move.animatedWithSpring = YES;
    } poped:^(UIViewController *fromVC, UIViewController *toVC, HXVBaseTransition *transition) {
        // Do nothing, unless you really need to.
        // If you need to recode navigation controller delegate, you should add this.
        toVC.navigationController.delegate = navigationDelegate;
    }];
    self.navigationController.delegate = self.transition;
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
}



@end
