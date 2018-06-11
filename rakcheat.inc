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

static const ID_PLAYER_SYNC = 207;
static const ID_VEHICLE_SYNC = 200;
static const ID_PASSENGER_SYNC = 211;
static const ID_UNOCCUPIED_SYNC = 209;
static const ID_TRAILER_SYNC = 210;
static const ID_SPECTATOR_SYNC = 212;
static const ID_BULLET_SYNC = 206;
static const ID_AIM_SYNC = 203;

static CheckValidityData(Float:data)
{
    if(floatcmp(data, data) != 0)
	{
		return 0;
	}
	new check[20];
	format(check, sizeof check, "%f", data);
    if(strcmp(check, "NaN", false) == 0 || strcmp(check, "./,),(-*,(.((((((", false) == 0 || strcmp(check, "-./,),(-*,(.((((((", false) == 0)
	{
		return 0;
	}
	return 1;
}

IPacket:ID_PLAYER_SYNC(playerid, BitStream:bs)
{
    new onFootData[PR_OnFootSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadOnFootSync(bs, onFootData);

	if(CheckValidityData(onFootData[PR_position][0]) != 1 || CheckValidityData(onFootData[PR_position][1]) != 1 ||
	CheckValidityData(onFootData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Position x, y, z: %f, %f, %f",
		    onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}

    if(CheckValidityData(onFootData[PR_quaternion][0]) != 1 || CheckValidityData(onFootData[PR_quaternion][1]) != 1 ||
	CheckValidityData(onFootData[PR_quaternion][2]) != 1 || CheckValidityData(onFootData[PR_quaternion][3]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
		    onFootData[PR_quaternion][0], onFootData[PR_quaternion][1], onFootData[PR_quaternion][2], onFootData[PR_quaternion][3]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(onFootData[PR_velocity][0]) != 1 || CheckValidityData(onFootData[PR_velocity][1]) != 1 ||
	CheckValidityData(onFootData[PR_velocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Velocity x, y, z: %f, %f, %f",
		    onFootData[PR_velocity][0], onFootData[PR_velocity][1], onFootData[PR_velocity][2]);
        #endif
        Kick(playerid);
        return 0;
	}

	if(CheckValidityData(onFootData[PR_surfingOffsets][0]) != 1 ||
	CheckValidityData(onFootData[PR_surfingOffsets][1]) != 1 ||
	CheckValidityData(onFootData[PR_surfingOffsets][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Surfing offsets x, y, z: %f, %f, %f",
		    onFootData[PR_surfingOffsets][0], onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2]);
        #endif
        Kick(playerid);
        return 0;
	}

	if(onFootData[PR_surfingVehicleId] != 0)
	{
	    if(0 < onFootData[PR_surfingVehicleId] < MAX_VEHICLES)
		{
		    new ac_model = GetVehicleModel(onFootData[PR_surfingVehicleId]);
		    if(ac_model == 0)
			{
			    #if defined DEBUG
				    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Veh model: %d, vehicleid: %d",
				    ac_model, onFootData[PR_surfingVehicleId]);
		        #endif
		        Kick(playerid);
		        return 0;
			}
			else
			{
			    if(floatabs(onFootData[PR_surfingOffsets][0]) >= 25.0 || floatabs(onFootData[PR_surfingOffsets][1]) >= 25.0 ||
			    floatabs(onFootData[PR_surfingOffsets][2]) >= 25.0)
				{
				    #if defined DEBUG
					    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Veh model: %d, vehicleid: %d, surfing offsets x, y, z: %f, %f, %f",
					    ac_model, onFootData[PR_surfingVehicleId], onFootData[PR_surfingOffsets][0], onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2]);
			        #endif
			        Kick(playerid);
			        return 0;
				}
			}
		}
		else if(MAX_VEHICLES <= onFootData[PR_surfingVehicleId] < MAX_OBJECTS)
		{
		    new ac_object = IsValidObject(onFootData[PR_surfingVehicleId]);
		    if(ac_object == 0)
			{
			    #if defined DEBUG
				    printf("[Rakcheat debug] [ID_PLAYER_SYNC] IsValidObject: %d, objectid: %d",
				    ac_object, onFootData[PR_surfingVehicleId]);
		        #endif
		        Kick(playerid);
		        return 0;
			}
			else
			{
			    if(floatabs(onFootData[PR_surfingOffsets][0]) >= 101.0 || floatabs(onFootData[PR_surfingOffsets][1]) >= 101.0 ||
			    floatabs(onFootData[PR_surfingOffsets][2]) >= 101.0)
				{
				    #if defined DEBUG
					    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Object modelid: %d, objectid: %d, surfing offsets x, y, z: %f, %f, %f",
					    GetObjectModel(onFootData[PR_surfingVehicleId]), onFootData[PR_surfingVehicleId], onFootData[PR_surfingOffsets][0],
					    onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2]);
			        #endif
			        Kick(playerid);
			        return 0;
				}
			}
		}
		else
		{
		    if(onFootData[PR_surfingVehicleId] != INVALID_VEHICLE_ID)
			{
			    #if defined DEBUG
				    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Surfing: %d",
				    onFootData[PR_surfingVehicleId]);
		        #endif
		        Kick(playerid);
		        return 0;
			}
		}
	}

	if(onFootData[PR_animationFlags] == 0)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PLAYER_SYNC] Animation flags: %d",
		    onFootData[PR_animationFlags]);
        #endif
        Kick(playerid);
        return 0;
	}
	return 1;
}

IPacket:ID_VEHICLE_SYNC(playerid, BitStream:bs)
{
    new inCarData[PR_InCarSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadInCarSync(bs, inCarData);

    if(CheckValidityData(inCarData[PR_quaternion][0]) != 1 || CheckValidityData(inCarData[PR_quaternion][1]) != 1 ||
	CheckValidityData(inCarData[PR_quaternion][2]) != 1 || CheckValidityData(inCarData[PR_quaternion][3]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
		    inCarData[PR_quaternion][0], inCarData[PR_quaternion][1], inCarData[PR_quaternion][2], inCarData[PR_quaternion][3]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(inCarData[PR_position][0]) != 1 || CheckValidityData(inCarData[PR_position][1]) != 1 ||
	CheckValidityData(inCarData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Position x, y, z: %f, %f, %f",
		    inCarData[PR_position][0], inCarData[PR_position][1], inCarData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(inCarData[PR_velocity][0]) != 1 || CheckValidityData(inCarData[PR_velocity][1]) != 1 ||
	CheckValidityData(inCarData[PR_velocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Velocity x, y, z: %f, %f, %f",
		    inCarData[PR_velocity][0], inCarData[PR_velocity][1], inCarData[PR_velocity][2]);
        #endif
        Kick(playerid);
        return 0;
	}

	if(CheckValidityData(inCarData[PR_vehicleHealth]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Veh health: %f",
		    inCarData[PR_vehicleHealth]);
        #endif
        Kick(playerid);
        return 0;
	}

	if(CheckValidityData(inCarData[PR_trainSpeed]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Train speed: %f",
		    inCarData[PR_trainSpeed]);
        #endif
        Kick(playerid);
        return 0;
	}
	return 1;
}

IPacket:ID_PASSENGER_SYNC(playerid, BitStream:bs)
{
    new passengerData[PR_PassengerSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadPassengerSync(bs, passengerData);

	if(CheckValidityData(passengerData[PR_position][0]) != 1 || CheckValidityData(passengerData[PR_position][1]) != 1 ||
	CheckValidityData(passengerData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_PASSENGER_SYNC] Position x, y, z: %f, %f, %f",
		    passengerData[PR_position][0], passengerData[PR_position][1], passengerData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}
	return 1;
}

IPacket:ID_UNOCCUPIED_SYNC(playerid, BitStream:bs)
{
    new unoccupiedData[PR_UnoccupiedSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadUnoccupiedSync(bs, unoccupiedData);

	if(CheckValidityData(unoccupiedData[PR_roll][0]) != 1 || CheckValidityData(unoccupiedData[PR_roll][1]) != 1 ||
	CheckValidityData(unoccupiedData[PR_roll][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Roll x, y, z: %f, %f, %f",
		    unoccupiedData[PR_roll][0], unoccupiedData[PR_roll][1], unoccupiedData[PR_roll][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(unoccupiedData[PR_direction][0]) != 1 ||
	CheckValidityData(unoccupiedData[PR_direction][1]) != 1 ||
	CheckValidityData(unoccupiedData[PR_direction][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Direction x, y, z: %f, %f, %f",
		    unoccupiedData[PR_direction][0], unoccupiedData[PR_direction][1], unoccupiedData[PR_direction][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(unoccupiedData[PR_position][0]) != 1 || CheckValidityData(unoccupiedData[PR_position][1]) != 1 ||
	CheckValidityData(unoccupiedData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Position x, y, z: %f, %f, %f",
		    unoccupiedData[PR_position][0], unoccupiedData[PR_position][1], unoccupiedData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(unoccupiedData[PR_velocity][0]) != 1 || CheckValidityData(unoccupiedData[PR_velocity][1]) != 1 ||
	CheckValidityData(unoccupiedData[PR_velocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Velocity x, y, z: %f, %f, %f",
		    unoccupiedData[PR_velocity][0], unoccupiedData[PR_velocity][1], unoccupiedData[PR_velocity][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(unoccupiedData[PR_angularVelocity][0]) != 1 ||
	CheckValidityData(unoccupiedData[PR_angularVelocity][1]) != 1 ||
	CheckValidityData(unoccupiedData[PR_angularVelocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Angular velocity x, y, z: %f, %f, %f",
		    unoccupiedData[PR_angularVelocity][0], unoccupiedData[PR_angularVelocity][1], unoccupiedData[PR_angularVelocity][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(unoccupiedData[PR_vehicleHealth]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Veh health: %f",
		    unoccupiedData[PR_vehicleHealth]);
        #endif
        Kick(playerid);
        return 0;
	}
	return 1;
}

IPacket:ID_TRAILER_SYNC(playerid, BitStream:bs)
{
    new trailerData[PR_TrailerSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadTrailerSync(bs, trailerData);

	if(CheckValidityData(trailerData[PR_position][0]) != 1 || CheckValidityData(trailerData[PR_position][1]) != 1 ||
	CheckValidityData(trailerData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_TRAILER_SYNC] Position x, y, z: %f, %f, %f",
		    trailerData[PR_position][0], trailerData[PR_position][1], trailerData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}

    if(CheckValidityData(trailerData[PR_quaternion][0]) != 1 || CheckValidityData(trailerData[PR_quaternion][1]) != 1 ||
	CheckValidityData(trailerData[PR_quaternion][2]) != 1 || CheckValidityData(trailerData[PR_quaternion][3]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_TRAILER_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
		    trailerData[PR_quaternion][0], trailerData[PR_quaternion][1], trailerData[PR_quaternion][2], trailerData[PR_quaternion][3]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(trailerData[PR_velocity][0]) != 1 || CheckValidityData(trailerData[PR_velocity][1]) != 1 ||
	CheckValidityData(trailerData[PR_velocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_TRAILER_SYNC] Velocity x, y, z: %f, %f, %f",
		    trailerData[PR_velocity][0], trailerData[PR_velocity][1], trailerData[PR_velocity][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(trailerData[PR_angularVelocity][0]) != 1 ||
	CheckValidityData(trailerData[PR_angularVelocity][1]) != 1 ||
	CheckValidityData(trailerData[PR_angularVelocity][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_TRAILER_SYNC] Angular velocity x, y, z: %f, %f, %f",
		    trailerData[PR_angularVelocity][0], trailerData[PR_angularVelocity][1], trailerData[PR_angularVelocity][2]);
        #endif
		Kick(playerid);
		return 0;
	}
	return 1;
}

IPacket:ID_SPECTATOR_SYNC(playerid, BitStream:bs)
{
    new spectatorData[PR_SpectatingSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadSpectatingSync(bs, spectatorData);

	if(CheckValidityData(spectatorData[PR_position][0]) != 1 || CheckValidityData(spectatorData[PR_position][1]) != 1 ||
	CheckValidityData(spectatorData[PR_position][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_SPECTATOR_SYNC] Position x, y, z: %f, %f, %f",
		    spectatorData[PR_position][0], spectatorData[PR_position][1], spectatorData[PR_position][2]);
        #endif
		Kick(playerid);
		return 0;
	}
	return 1;
}

IPacket:ID_BULLET_SYNC(playerid, BitStream:bs)
{
    new bulletData[PR_BulletSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadBulletSync(bs, bulletData);

	if(CheckValidityData(bulletData[PR_origin][0]) != 1 || CheckValidityData(bulletData[PR_origin][1]) != 1 ||
	CheckValidityData(bulletData[PR_origin][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_BULLET_SYNC] Origin x, y, z: %f, %f, %f",
		    bulletData[PR_origin][0], bulletData[PR_origin][1], bulletData[PR_origin][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(bulletData[PR_hitPos][0]) != 1 || CheckValidityData(bulletData[PR_hitPos][1]) != 1 ||
	CheckValidityData(bulletData[PR_hitPos][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_BULLET_SYNC] Hitpos x, y, z: %f, %f, %f",
		    bulletData[PR_hitPos][0], bulletData[PR_hitPos][1], bulletData[PR_hitPos][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(bulletData[PR_offsets][0]) != 1 || CheckValidityData(bulletData[PR_offsets][1]) != 1 ||
	CheckValidityData(bulletData[PR_offsets][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_BULLET_SYNC] Offsets x, y, z: %f, %f, %f",
		    bulletData[PR_offsets][0], bulletData[PR_offsets][1], bulletData[PR_offsets][2]);
        #endif
		Kick(playerid);
		return 0;
	}
	return 1;
}

IPacket:ID_AIM_SYNC(playerid, BitStream:bs)
{
    new aimData[PR_AimSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadAimSync(bs, aimData);

	if(CheckValidityData(aimData[PR_camFrontVec][0]) != 1 || CheckValidityData(aimData[PR_camFrontVec][1]) != 1 ||
	CheckValidityData(aimData[PR_camFrontVec][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_AIM_SYNC] Camfrontvec x, y, z: %f, %f, %f",
		    aimData[PR_camFrontVec][0], aimData[PR_camFrontVec][1], aimData[PR_camFrontVec][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(aimData[PR_camPos][0]) != 1 || CheckValidityData(aimData[PR_camPos][1]) != 1 ||
	CheckValidityData(aimData[PR_camPos][2]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_AIM_SYNC] Campos x, y, z: %f, %f, %f",
		    aimData[PR_camPos][0], aimData[PR_camPos][1], aimData[PR_camPos][2]);
        #endif
		Kick(playerid);
		return 0;
	}

	if(CheckValidityData(aimData[PR_aimZ]) != 1)
	{
	    #if defined DEBUG
		    printf("[Rakcheat debug] [ID_AIM_SYNC] Aimz: %f",
		    aimData[PR_aimZ]);
        #endif
        Kick(playerid);
        return 0;
	}
	return 1;
}
