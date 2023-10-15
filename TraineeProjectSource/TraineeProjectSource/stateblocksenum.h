#pragma once
enum stateblocksenum {
	BlockReadyToWork =0 , BlockFault = 1, BlockDisable = 2, BlockAtWork = 3, BlockAtInitializaiton = 4
};

enum AimingStateEnum {
	SpotNoFoundState, AimingInFullImage, AimingInStrob, NotAiming
};
