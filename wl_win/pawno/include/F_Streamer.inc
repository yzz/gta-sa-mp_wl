                                       //////////////////////
                                       ////Object Streamer///
                                       //////Created by://///
                                       //////°Fallout°///////
                                       //////////////////////


#include <a_samp>

//Natives/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
native F_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);  //creates an object.
native F_DestroyObject(objectid);                                                         //destroys an object.
native F_PlayerObjectUpdate(playerid, Float:x, Float:y, Float:z);                         //update objects for a player in a certain position.
native F_MoveObject(objectid, Float:x, Float:y, Float:z, Float:speed);                    //moves an object.
native F_StopObject(objectid);                                                            //stops an object from moving.
native F_IsValidObject(objectid);                                                         //returns 1 if object is valid, returns 0 if object is invalid.
native F_SetObjectPos(objectid, Float:x, Float:y, Float:z);                               //sets the position of an object.
native F_GetObjectPos(objectid, &Float:x, &Float:y, &Float:z);                            //gets the position of an object in x, y and z.
native F_SetObjectRot(objectid, Float:rx, Float:ry, Float:rz);                            //sets the rotation of an object.
native F_GetObjectRot(objectid, &Float:rx, &Float:ry, &Float:rz);                         //gets the rotation of an object in rx, ry and rz.
native F_RefreshObjects(playerid);                                                        //recreates (refreshes) a certain player's objects. (useful to recreate broken objects like glass, boxes, barrels, ...)
*/

//Configuration///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define F_MAX_OBJECTS    3000   //the maximum amount of objects the streamer can create.
#define UpdateTime       500   //the update time in ms (milliseconds).
#define ObjectsToStream  240    //the maximum number of objects that will be streamed for a player. (maximum = 254)
#define StreamRange      220.0  //the player's object view range, doesn't need to be changed.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

forward F_ObjectUpdate();
forward F_StartUpdate();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#pragma dynamic 30000
//#pragma dynamic 40000

enum OInfo
{
	ModelID,
	ObjectID[MAX_PLAYERS],
	Float:ox,
	Float:oy,
	Float:oz,
	Float:orx,
	Float:ory,
	Float:orz,
	bool:ObjectCreated[MAX_PLAYERS],
}

new ObjectInfo[F_MAX_OBJECTS][OInfo];
new bool:ObjectUpdatetRunning;
new bool:CantCreateMore;
new bool:RefreshObjects[MAX_PLAYERS];
new Float:OldX[MAX_PLAYERS], Float:OldY[MAX_PLAYERS], Float:OldZ[MAX_PLAYERS];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public F_StartUpdate()
{
    SetTimer("F_ObjectUpdate", UpdateTime, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(ObjectUpdatetRunning == false)
	{
	    SetTimer("F_StartUpdate", F_MAX_OBJECTS/2, 0);
	    ObjectUpdatetRunning = true;
    }

	new objectid;

	if(CantCreateMore == false)
	{
		for(new i; i<F_MAX_OBJECTS; i++)
		{
		    if(i == F_MAX_OBJECTS-1)
		    {
		        printf("Only the first %i objects could be created - object limit exceeded.", F_MAX_OBJECTS);
				CantCreateMore = true;
		    }
		    if(ObjectInfo[i][ModelID] == 0)
		    {
		        objectid = i;
		        break;
		    }
		}
	}
	else
	{
	    return -1;
	}

	if(modelid == 0)
	{
	    printf("Invalid modelid for object %i", objectid);
	    return -1;
	}

    ObjectInfo[objectid][ModelID] = modelid;
    ObjectInfo[objectid][ox] = x;
    ObjectInfo[objectid][oy] = y;
    ObjectInfo[objectid][oz] = z;
    ObjectInfo[objectid][orx] = rx;
    ObjectInfo[objectid][ory] = ry;
    ObjectInfo[objectid][orz] = rz;
	return objectid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_IsValidObject(objectid)
{
	if(ObjectInfo[objectid][ModelID] == 0 || objectid == -1)
	{
	    return 0;
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_DestroyObject(objectid)
{
	if(F_IsValidObject(objectid))
	{
		for(new playerid; playerid<MAX_PLAYERS; playerid++)
		{
		    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid) && ObjectInfo[objectid][ObjectCreated][playerid] == true)
		    {
				DestroyPlayerObject(playerid, ObjectInfo[objectid][ObjectID][playerid]);
				ObjectInfo[objectid][ObjectCreated][playerid] = false;
			}
		}
		ObjectInfo[objectid][ModelID] = 0;
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_MoveObject(objectid, Float:x, Float:y, Float:z, Float:speed)
{
	if(F_IsValidObject(objectid))
	{
		new time;
		for(new playerid; playerid<MAX_PLAYERS; playerid++)
		{
		    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid) && ObjectInfo[objectid][ObjectCreated][playerid] == true)
		    {
				time = MovePlayerObject(playerid, ObjectInfo[objectid][ObjectID][playerid], x, y, z, speed);
			}
		}
		return time;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_StopObject(objectid)
{
	if(F_IsValidObject(objectid))
	{
		for(new playerid; playerid<MAX_PLAYERS; playerid++)
		{
		    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid) && ObjectInfo[objectid][ObjectCreated][playerid] == true)
		    {
		        StopPlayerObject(playerid,  ObjectInfo[objectid][ObjectID][playerid]);
			}
		}
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_SetObjectPos(objectid, Float:x, Float:y, Float:z)
{
	if(F_IsValidObject(objectid))
	{
	    ObjectInfo[objectid][ox] = x;
	    ObjectInfo[objectid][oy] = y;
	    ObjectInfo[objectid][oz] = z;
		for(new playerid; playerid<MAX_PLAYERS; playerid++)
		{
		    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid) && ObjectInfo[objectid][ObjectCreated][playerid] == true)
		    {
				SetPlayerObjectPos(playerid, ObjectInfo[objectid][ObjectID][playerid], x, y, z);
			}
		}
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_GetObjectPos(objectid, &Float:x, &Float:y, &Float:z)
{
	if(F_IsValidObject(objectid))
	{
	    x = ObjectInfo[objectid][ox];
	    y = ObjectInfo[objectid][oy];
	    z = ObjectInfo[objectid][oz];
	    return 1;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_SetObjectRot(objectid, Float:rx, Float:ry, Float:rz)
{
	if(F_IsValidObject(objectid))
	{
	    ObjectInfo[objectid][orx] = rx;
	    ObjectInfo[objectid][ory] = ry;
	    ObjectInfo[objectid][orz] = rz;
		for(new playerid; playerid<MAX_PLAYERS; playerid++)
		{
		    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid) && ObjectInfo[objectid][ObjectCreated][playerid] == true)
		    {
				SetPlayerObjectRot(playerid, ObjectInfo[objectid][ObjectID][playerid], rx, ry, rz);
			}
		}
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_GetObjectRot(objectid, &Float:rx, &Float:ry, &Float:rz)
{
	if(F_IsValidObject(objectid))
	{
	    rx = ObjectInfo[objectid][orx];
	    ry = ObjectInfo[objectid][ory];
	    rz = ObjectInfo[objectid][orz];
	    return 1;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_RefreshObjects(playerid)
{
	if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid))
	{
		RefreshObjects[playerid] = true;
		new Float:x, Float:y, Float:z;
		GetPlayerCameraPos(playerid, x, y, z);
		F_PlayerObjectUpdate(playerid, x, y, z);
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_Streamer_OnPlayerConnect(playerid)
{
	for(new objectid; objectid<F_MAX_OBJECTS; objectid++)
	{
    	ObjectInfo[objectid][ObjectCreated][playerid] = false;
	}
	OldX[playerid] = 999999999.99;
	OldY[playerid] = 999999999.99;
	OldZ[playerid] = 999999999.99;
	RefreshObjects[playerid] = false;
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public F_ObjectUpdate()
{
	static Float:F_ObjectUpdate_ObjDistance[F_MAX_OBJECTS];
	static F_ObjectUpdate_Closest[ObjectsToStream];
	static F_ObjectUpdate_ObjectArr[F_MAX_OBJECTS];
	static bool:F_ObjectUpdate_DontDestroy[F_MAX_OBJECTS];
	new 
		nr,
		bool:Firstloop;

	for(new playerid; playerid<MAX_PLAYERS; playerid++)
	{
	    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid))
	    {
	        if(!IsPlayerInRangeOfPoint(playerid, 1.0, OldX[playerid], OldY[playerid], OldZ[playerid]))
			{
	        	GetPlayerCameraPos(playerid, OldX[playerid], OldY[playerid], OldZ[playerid]);

				nr = 0;
		        for(new objectid; objectid<F_MAX_OBJECTS; objectid++)
		        {
		            if(F_IsValidObject(objectid))
		            {
		                F_ObjectUpdate_ObjDistance[objectid] = floatsqroot(floatpower(floatsub(ObjectInfo[objectid][ox],OldX[playerid]),2)+floatpower(floatsub(ObjectInfo[objectid][oy],OldY[playerid]),2)+floatpower(floatsub(ObjectInfo[objectid][oz],OldZ[playerid]),2));
						if(floatcmp(F_ObjectUpdate_ObjDistance[objectid], StreamRange) == -1)
						{
						    F_ObjectUpdate_ObjectArr[nr] = objectid;
						    nr++;
						}
					}
				}

                F_ObjectUpdate_Closest = "";

				if(nr > ObjectsToStream)
				{
			        for(new loop; loop<ObjectsToStream; loop++)
			        {
			            Firstloop = true;
			            for(new objectid; objectid<nr; objectid++)
			            {
			                if((F_ObjectUpdate_ObjDistance[F_ObjectUpdate_ObjectArr[objectid]] != 999999999.99) && ((floatcmp(F_ObjectUpdate_ObjDistance[F_ObjectUpdate_ObjectArr[objectid]], F_ObjectUpdate_ObjDistance[F_ObjectUpdate_Closest[loop]]) == -1) || Firstloop))
			                {
			            		Firstloop = false;
			                    F_ObjectUpdate_Closest[loop] = F_ObjectUpdate_ObjectArr[objectid];
			                }
			            }
			            F_ObjectUpdate_ObjDistance[F_ObjectUpdate_Closest[loop]] = 999999999.99;
			        }
				}
				else
				{
			        for(new objectid; objectid<nr; objectid++)
			        {
						F_ObjectUpdate_Closest[objectid] = F_ObjectUpdate_ObjectArr[objectid];
			        }
				}

	            for(new objectid; objectid<F_MAX_OBJECTS; objectid++) { F_ObjectUpdate_DontDestroy[objectid] = false; }
				for(new objectid; objectid<ObjectsToStream && objectid<nr; objectid++)
				{
					F_ObjectUpdate_DontDestroy[F_ObjectUpdate_Closest[objectid]] = true;
				}

	            for(new objectid; objectid<F_MAX_OBJECTS; objectid++)
	            {
				    if(ObjectInfo[objectid][ObjectCreated][playerid] == true && F_ObjectUpdate_DontDestroy[objectid] == false)
				    {
				        DestroyPlayerObject(playerid, ObjectInfo[objectid][ObjectID][playerid]);
						ObjectInfo[objectid][ObjectCreated][playerid] = false;
				    }
				}

				for(new loop; loop<ObjectsToStream && loop<nr; loop++)
				{
				    if(ObjectInfo[F_ObjectUpdate_Closest[loop]][ObjectCreated][playerid] == false)
				    {
						ObjectInfo[F_ObjectUpdate_Closest[loop]][ObjectID][playerid] = CreatePlayerObject(playerid, ObjectInfo[F_ObjectUpdate_Closest[loop]][ModelID], ObjectInfo[F_ObjectUpdate_Closest[loop]][ox], ObjectInfo[F_ObjectUpdate_Closest[loop]][oy], ObjectInfo[F_ObjectUpdate_Closest[loop]][oz], ObjectInfo[F_ObjectUpdate_Closest[loop]][orx], ObjectInfo[F_ObjectUpdate_Closest[loop]][ory], ObjectInfo[F_ObjectUpdate_Closest[loop]][orz]);
						ObjectInfo[F_ObjectUpdate_Closest[loop]][ObjectCreated][playerid] = true;
				    }
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_PlayerObjectUpdate(playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid))
    {
		OldX[playerid] = x;
		OldY[playerid] = y;
		OldZ[playerid] = z;

		new nr;
		static Float:PObjectUpdate_ObjDistance[F_MAX_OBJECTS];
		static PObjectUpdate_ObjectArr[F_MAX_OBJECTS];
        for(new objectid; objectid<F_MAX_OBJECTS; objectid++)
        {
			if(F_IsValidObject(objectid))
            {
                PObjectUpdate_ObjDistance[objectid] = floatsqroot(floatpower(floatsub(ObjectInfo[objectid][ox],x),2)+floatpower(floatsub(ObjectInfo[objectid][oy],y),2)+floatpower(floatsub(ObjectInfo[objectid][oz],z),2));
				if(floatcmp(PObjectUpdate_ObjDistance[objectid], StreamRange) == -1)
				{
				    PObjectUpdate_ObjectArr[nr] = objectid;
				    nr++;
				}
			}
		}

		new Closest[ObjectsToStream];

		if(nr > ObjectsToStream)
		{
	        for(new loop; loop<ObjectsToStream; loop++)
	        {
				new bool:Firstloop = true;
				for(new objectid; objectid<nr; objectid++)
				{
					if((PObjectUpdate_ObjDistance[PObjectUpdate_ObjectArr[objectid]] != 999999999.99) && ((floatcmp(PObjectUpdate_ObjDistance[PObjectUpdate_ObjectArr[objectid]], PObjectUpdate_ObjDistance[Closest[loop]]) == -1) || Firstloop))
	                {
	            		Firstloop = false;
	                    Closest[loop] = PObjectUpdate_ObjectArr[objectid];
	                }
	            }
	            PObjectUpdate_ObjDistance[Closest[loop]] = 999999999.99;
	        }
		}
		else
		{
	        for(new objectid; objectid<nr; objectid++)
	        {
				Closest[objectid] = PObjectUpdate_ObjectArr[objectid];
	        }
		}

		new bool:F_ObjectUpdate_DontDestroy[F_MAX_OBJECTS];
		for(new objectid; objectid<ObjectsToStream && objectid<nr; objectid++)
		{
			F_ObjectUpdate_DontDestroy[Closest[objectid]] = true;
		}

		for(new objectid; objectid<F_MAX_OBJECTS; objectid++)
		{
		    if(ObjectInfo[objectid][ObjectCreated][playerid] == true && (F_ObjectUpdate_DontDestroy[objectid] == false || RefreshObjects[playerid] == true))
		    {
		        DestroyPlayerObject(playerid, ObjectInfo[objectid][ObjectID][playerid]);
				ObjectInfo[objectid][ObjectCreated][playerid] = false;
		    }
		}
		RefreshObjects[playerid] = false;

		for(new loop; loop<ObjectsToStream && loop<nr; loop++)
		{
		    if(ObjectInfo[Closest[loop]][ObjectCreated][playerid] == false)
		    {
				ObjectInfo[Closest[loop]][ObjectID][playerid] = CreatePlayerObject(playerid, ObjectInfo[Closest[loop]][ModelID], ObjectInfo[Closest[loop]][ox], ObjectInfo[Closest[loop]][oy], ObjectInfo[Closest[loop]][oz], ObjectInfo[Closest[loop]][orx], ObjectInfo[Closest[loop]][ory], ObjectInfo[Closest[loop]][orz]);
				ObjectInfo[Closest[loop]][ObjectCreated][playerid] = true;
		    }
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock F_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	F_PlayerObjectUpdate(playerid, x, y, z);
	SetPlayerPos(playerid, x, y, z);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SetPlayerPos F_SetPlayerPos

//EOF/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

