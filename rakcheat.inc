#if defined _rakcheat_included
    #endinput
#endif
#define _rakcheat_included

#include <a_samp>

#if !defined PAWNRAKNET_INC_
    #error You must have Pawn.Raknet include in order to use this one.
#endif

#if !defined DEBUG
    #define DEBUG
#endif

#define ID_PLAYER_SYNC 207
#define ID_VEHICLE_SYNC 200
#define ID_UNOCCUPIED_SYNC 209
#define ID_AIM_SYNC 203

IPacket:ID_PLAYER_SYNC(playerid, BitStream:bs)
{
    new onFootData[PR_OnFootSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadOnFootSync(bs, onFootData);

    if(floatcmp(onFootData[PR_quaternion][0], onFootData[PR_quaternion][0]) != 0 || floatcmp(onFootData[PR_quaternion][1], onFootData[PR_quaternion][1]) != 0 ||
	floatcmp(onFootData[PR_quaternion][2], onFootData[PR_quaternion][2]) != 0 || floatcmp(onFootData[PR_quaternion][3], onFootData[PR_quaternion][3]) != 0)
	{
		return 0;
	}

	if(floatcmp(onFootData[PR_velocity][0], onFootData[PR_velocity][0]) != 0 || floatcmp(onFootData[PR_velocity][1], onFootData[PR_velocity][1]) != 0 ||
	floatcmp(onFootData[PR_velocity][2], onFootData[PR_velocity][2]) != 0)
	{
		return 0;
	}

	if(onFootData[PR_surfingVehicleId] != 0 && onFootData[PR_surfingVehicleId] != INVALID_VEHICLE_ID)
	{
		if(floatabs(onFootData[PR_surfingOffsets][0]) >= 25.0 || floatabs(onFootData[PR_surfingOffsets][1]) >= 25.0 ||
		floatabs(onFootData[PR_surfingOffsets][2]) >= 25.0)
		{
			return 0;
		}
	}

	if(onFootData[PR_animationFlags] == 0)
	{
		return 0;
	}
	return 1;
}

IPacket:ID_VEHICLE_SYNC(playerid, BitStream:bs)
{
    new inCarData[PR_InCarSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadInCarSync(bs, inCarData);

    if(floatcmp(inCarData[PR_quaternion][0], inCarData[PR_quaternion][0]) != 0 || floatcmp(inCarData[PR_quaternion][1], inCarData[PR_quaternion][1]) != 0 ||
	floatcmp(inCarData[PR_quaternion][2], inCarData[PR_quaternion][2]) != 0 || floatcmp(inCarData[PR_quaternion][3], inCarData[PR_quaternion][3]) != 0)
	{
		return 0;
	}

	if(floatcmp(inCarData[PR_velocity][0], inCarData[PR_velocity][0]) != 0 || floatcmp(inCarData[PR_velocity][1], inCarData[PR_velocity][1]) != 0 ||
	floatcmp(inCarData[PR_velocity][2], inCarData[PR_velocity][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(inCarData[PR_vehicleHealth], inCarData[PR_vehicleHealth]) != 0)
	{
		return 0;
	}

	if(floatcmp(inCarData[PR_trainSpeed], inCarData[PR_trainSpeed]) != 0)
	{
		return 0;
	}
	return 1;
}

IPacket:ID_UNOCCUPIED_SYNC(playerid, BitStream:bs)
{
    new unoccupiedData[PR_UnoccupiedSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadUnoccupiedSync(bs, unoccupiedData);

	if(floatcmp(unoccupiedData[PR_roll][0], unoccupiedData[PR_roll][0]) != 0 || floatcmp(unoccupiedData[PR_roll][1], unoccupiedData[PR_roll][1]) != 0 ||
	floatcmp(unoccupiedData[PR_roll][2], unoccupiedData[PR_roll][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(unoccupiedData[PR_direction][0], unoccupiedData[PR_direction][0]) != 0 ||
	floatcmp(unoccupiedData[PR_direction][1], unoccupiedData[PR_direction][1]) != 0 ||
	floatcmp(unoccupiedData[PR_direction][2], unoccupiedData[PR_direction][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(unoccupiedData[PR_position][0], unoccupiedData[PR_position][0]) != 0 || floatcmp(unoccupiedData[PR_position][1], unoccupiedData[PR_position][1]) != 0 ||
	floatcmp(unoccupiedData[PR_position][2], unoccupiedData[PR_position][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(unoccupiedData[PR_velocity][0], unoccupiedData[PR_velocity][0]) != 0 || floatcmp(unoccupiedData[PR_velocity][1], unoccupiedData[PR_velocity][1]) != 0 ||
	floatcmp(unoccupiedData[PR_velocity][2], unoccupiedData[PR_velocity][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(unoccupiedData[PR_angularVelocity][0], unoccupiedData[PR_angularVelocity][0]) != 0 ||
	floatcmp(unoccupiedData[PR_angularVelocity][1], unoccupiedData[PR_angularVelocity][1]) != 0 ||
	floatcmp(unoccupiedData[PR_angularVelocity][2], unoccupiedData[PR_angularVelocity][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(unoccupiedData[PR_vehicleHealth], unoccupiedData[PR_vehicleHealth]) != 0)
	{
		return 0;
	}
	return 1;
}

IPacket:ID_AIM_SYNC(playerid, BitStream:bs)
{
    new aimData[PR_AimSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadAimSync(bs, aimData);

	if(floatcmp(aimData[PR_camFrontVec][0], aimData[PR_camFrontVec][0]) != 0 || floatcmp(aimData[PR_camFrontVec][1], aimData[PR_camFrontVec][1]) != 0 ||
	floatcmp(aimData[PR_camFrontVec][2], aimData[PR_camFrontVec][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(aimData[PR_camPos][0], aimData[PR_camPos][0]) != 0 || floatcmp(aimData[PR_camPos][1], aimData[PR_camPos][1]) != 0 ||
	floatcmp(aimData[PR_camPos][2], aimData[PR_camPos][2]) != 0)
	{
		return 0;
	}

	if(floatcmp(aimData[PR_aimZ], aimData[PR_aimZ]) != 0)
	{
		return 0;
	}
	return 1;
}
