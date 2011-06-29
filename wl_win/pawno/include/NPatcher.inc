


stock GetPlayerName_prefixed(playerid, name[], len)
{
        new ret = GetPlayerName( playerid, name, len );
        for( new i=0; name[i]!=0; i++ )
                if( name[i]<0 ) name[i] += 256;
        return ret;
}
#define GetPlayerName(%1) GetPlayerName_prefixed(%1)