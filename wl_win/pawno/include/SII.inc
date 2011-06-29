//======================================================
// Slick's INI Include 2.0.6
//
// (c) Copyright 2008-2009, [DRuG]Slick
// This file is provided as is (no warranties).
//======================================================


//#pragma dynamic 25000 // Change accordingly!!

/*
#if defined MAX_STRING
	#define INI_MAX_VALUE MAX_STRING
#else
	#define INI_MAX_VALUE 128
#endif
*/
#define INI_MAX_VALUE		(256)
#define INI_MAX_KEY 32
#define INI_MAX_LINE (INI_MAX_KEY + INI_MAX_VALUE + 3)
#define INI_MAX_FILENAME 128
#define INI_MAX_LINES 2000


enum E_CACHE
{
	E_KEY[INI_MAX_KEY],
	E_VALUE[INI_MAX_VALUE]
}

enum E_FILE
{
	E_FILENAME[INI_MAX_FILENAME],
	bool: E_OPEN
}

static gCache[INI_MAX_LINES][E_CACHE];
static gEmptyCache[E_CACHE];
static gFile[E_FILE];
static gNoFile[E_FILE];


#define INI_Exist fexist


stock INI_Open(const filename[]){
	if (!filename[0]) return false;
	if(!INI_Exist(filename)){
		printf "File '%s' doesn't exist,server crash",filename
		SendClientMessageToAll(0,"");
	}
	if (gFile[E_OPEN])
	{
		if (!strcmp(gFile[E_FILENAME], filename, true)) return true;
		return false;
	}
	new File: h;
	h = fopen(filename, io_readwrite);
	if (h)
	{
		//format(gFile[E_FileName],)
		INI_strcpy(gFile[E_FILENAME], filename, INI_MAX_FILENAME, INI_MAX_FILENAME);
		new line[INI_MAX_LINE];
		new ln = -1;
		new separator;
		while (((ln + 1) < INI_MAX_LINES) && (fread(h, line)))
		{
			ln ++;
			if(ln > 0 && gCache[ln-1][E_KEY][0]== ';')printf "%s|%s",gCache[ln-1][E_VALUE],gCache[ln-1][E_KEY]

			INI_StripLine(line);
			separator = strfind(line, "=", false);
			if ((line[0] == ';') || (line[0] == '[') || (line[0] == '=') || (separator == -1) || (separator > INI_MAX_KEY))
			{
				if (line[0] == ';' || line[0] == '[')
				{
					//printf "|%s|",line
					INI_strcpy(gCache[ln][E_VALUE], line, INI_MAX_VALUE, INI_MAX_VALUE);
					gCache[ln][E_KEY][0] = '[';
				}
				else
				{
					//printf "|%s|",line
					INI_strcpy(gCache[ln][E_VALUE][1], line, INI_MAX_VALUE, INI_MAX_VALUE);
					gCache[ln][E_VALUE][0] = ';';
					gCache[ln][E_KEY][0] = '[';
				}
				continue;
			}
			//printf "|%s|",line
			INI_strcpy(gCache[ln][E_KEY], line, separator, INI_MAX_KEY);
			INI_strcpy(gCache[ln][E_VALUE], line[separator + 1], INI_MAX_VALUE, INI_MAX_VALUE);
			if (!gCache[ln][E_VALUE][0]) gCache[ln][E_VALUE][0] = ' ';
		}
		fclose(h);
		gFile[E_OPEN] = true;
		//for(new k;k < ln;k++) printf "%s,%s",gCache[k][E_KEY], gCache[k][E_VALUE]
		return 1;
	}
	
	return 0;
}
/*
	48-57
	65-90
	100-122
*/
stock INI_Save(){
	if (!gFile[E_OPEN]) return false;
	new File: h;
	h = fopen(gFile[E_FILENAME], io_write);
	if (h)
	{
		new line[INI_MAX_LINE];
		new ln = -1;
		while (((ln + 1) < INI_MAX_LINES) && (gCache[ln + 1][E_VALUE][0]))
		{
			ln ++;
			if ((gCache[ln][E_VALUE][0] == ';' || gCache[ln][E_VALUE][0] == '[') && gCache[ln][E_KEY][0] == '[')
			{
				//printf "%d",(gCache[ln][E_KEY][0] == ';')
				if (gCache[ln][E_VALUE][1])
				{
					format(line, sizeof(line), "%s\r\n", gCache[ln][E_VALUE]);
					//printf "|%s|",line
					fwrite(h, line);
					continue;
				}
				fwrite(h, "\r\n");
				continue;
			}
			if(gCache[ln][E_KEY][0] != ';' && gCache[ln][E_KEY][0] != '['){
				format(line, sizeof(line), "%s=%s\r\n", gCache[ln][E_KEY], gCache[ln][E_VALUE]);
				//printf "|%s|",line
				fwrite(h, line);
			}
		}
		fclose(h);
		return true;
	}
	return false;
}


stock INI_Close(){
	if (!gFile[E_OPEN]) return false;
	for (new ln; ln < INI_MAX_LINES; ln++) gCache[ln] = gEmptyCache;
	gFile = gNoFile;
	for (new ln; ln < INI_MAX_LINES; ln++) gCache[ln][E_KEY][0] = ' '
	return true;
}


stock INI_ReadString(dest[], const key[], maxlength = sizeof(dest)){
	if ((!gFile[E_OPEN]) || (!key[0])) return false;
	new ln = -1;
	while (((ln + 1) < INI_MAX_LINES) && (gCache[ln + 1][E_VALUE][0]))
	{
		ln ++;
		if ((gCache[ln][E_VALUE][0] == ';' || gCache[ln][E_VALUE][0] == '[') && gCache[ln][E_KEY][0] == '[') continue;
		if (!strcmp(gCache[ln][E_KEY], key, false))
		{
			INI_strcpy(dest, gCache[ln][E_VALUE], INI_MAX_VALUE, maxlength);
			return true;
		}
	}
	return false;
}


stock INI_ReadInt(const key[]){
	new dest[11];
	if (INI_ReadString(dest, key)) return strval(dest);
	return false;
}


stock Float: INI_ReadFloat(const key[]){
	new dest[11];
	if (INI_ReadString(dest, key)) return floatstr(dest);
	return 0.0;
}


stock INI_WriteString(const key[], const value[]){
	if ((
		!gFile[E_OPEN]) || 
		(!key[0]) || 
		(key[0] == ';') || 
		(key[0] == '[') ||
		(strfind(key, "=", false) != -1)) return false;
	new ln = -1;
	while (((ln + 1) < INI_MAX_LINES) && (gCache[ln + 1][E_VALUE][0]))
	{
		ln ++;
		if ((gCache[ln][E_VALUE][0] == ';' || gCache[ln][E_VALUE][0] == '[')  && gCache[ln][E_KEY][0] == '[') continue;
		if (!strcmp(gCache[ln][E_KEY], key, false))
		{
			INI_strcpy(gCache[ln][E_VALUE], value, INI_MAX_VALUE, INI_MAX_VALUE);
			return true;
		}
	}
	ln ++;
	if (ln < INI_MAX_LINES)
	{
		INI_strcpy(gCache[ln][E_KEY], key, INI_MAX_KEY, INI_MAX_KEY);
		INI_strcpy(gCache[ln][E_VALUE], value, INI_MAX_VALUE, INI_MAX_VALUE);
		return true;
	}
	return false;
}


stock INI_WriteInt(const key[], value){
	new dest[11];
	format(dest, sizeof(dest), "%i", value);
	return INI_WriteString(key, dest);
}


stock INI_WriteFloat(const key[], Float: value){
	new dest[11];
	format(dest, sizeof(dest), "%f", value);
	return INI_WriteString(key, dest);
}


stock INI_RemoveEntry(const key[]){
	if ((!gFile[E_OPEN]) || (!key[0]) || (strfind(key, "=", false) != -1)) return false;
	new ln = -1;
	while (((ln + 1) < INI_MAX_LINES) && (gCache[ln + 1][E_VALUE][0]))
	{
		ln ++;
		if ((gCache[ln][E_VALUE][0] == ';' || (gCache[ln][E_VALUE][0] == '[') && gCache[ln][E_KEY][0] == '[') continue;
		if (!strcmp(gCache[ln][E_KEY], key, false))
		{
			for (; ln < (INI_MAX_LINES - 1); ln ++)
			{
				INI_strcpy(gCache[ln][E_KEY], gCache[ln + 1][E_KEY], INI_MAX_KEY, INI_MAX_KEY);
				INI_strcpy(gCache[ln][E_VALUE], gCache[ln + 1][E_VALUE], INI_MAX_VALUE, INI_MAX_VALUE);
			}
			return true;
		}
	}
	return false;
}


stock INI_Remove(const filename[]){
	if (!filename[0]) return false;
	if ((gFile[E_OPEN]) && (!strcmp(gFile[E_FILENAME], filename, true))) gFile = gNoFile;
	return fremove(filename);
}


stock INI_strcpy(dest[], const source[], numcells = sizeof(source), maxlength = sizeof(dest)){
	//printf "source:|%s|",source
	//if(source[0]){
	//	format(dest,256,"%s",source);
	//	dest[strlen(dest)]
	//}
	//printf "dest:|%s|",dest
	//dest[strlen(source)] = '\0';
	new i;
	for(i=0;source[i] && i<numcells && i<maxlength;i++) dest[i] = source[i];
	//new i;
	//while ((source[i]) && (i < numcells) && (i < maxlength))
	//{
	//	dest[i] = source[i];
	//	i ++;
	//}
	dest[(i == maxlength) ? (i - 1) : (i)] = '\0';
}


stock INI_StripLine(string[]){
	new l;
	l = strlen(string);
	if (string[l - 2] == '\r') string[l - 2] = '\0';
	if (string[l - 1] == '\n') string[l - 1] = '\0';
}

//==================================================================
/*
stock INI_FindItem(const itemname[],maxlength = sizeof(itemname)){
	if(!gFile[E_OPEN] || !itemname[0])return -1;
	new
		ln = -1;
	while(ln+1 < INI_MAX_LINES && gCache[ln+1][E_VALUE][0]){
		ln++;
		if(gCache[ln][E_VALUE][0] == '[')
			if(!strcmp(itemname,gCache[ln][E_VALUE],false)
				return ln;
	}
	return -1;
}
*/
/**
* Gcs Team edited:
* INI_Write(const filename[],{Float,_}:...)
* Write ini data with one function
* eg:
* writeini("test.ini","key1","str","key2","50.0","key3","5");
* Note:All write to string
*/
stock INI_Write(const filename[],{Float,_}:...){
	new
		argAmount = numargs();
	if(argAmount == 1 || !INI_Open(filename))return false;
	
	new	
		pos=1,
		argPos,
		Key[INI_MAX_KEY],
		Value[INI_MAX_VALUE];
	while(pos < argAmount){
		getargAsString(Key,pos,argPos);pos++;
		getargAsString(Value,pos,argPos);pos++;
		if(!INI_WriteString(Key,Value)){
			INI_Close();
			return false;
		}
		//printf "pos:%d,Key:%s,Value:%s",pos,Key,Value
	}
	INI_Save();
	return INI_Close();
}
#define writeini INI_Write 
/**
* Gcs Team edited:
* INI_Read(const filename[],{Float,_}:...)
* Read ini data with one function
* eg:
* new
* 	a[128],
*	b[128],
*	c[128];
* readini("test.ini","key1",a,"key2",b,"key3",c);
* Note:All read to string
*/
stock INI_Read(const filename[],{Float,_}:...){
	new
		argAmount = numargs();
	if(argAmount == 1 || !INI_Open(filename))return false;
	new
		pos = 1,
		argPos,
		Key[INI_MAX_KEY],
		Value[INI_MAX_VALUE];
	while(pos < argAmount){
		getargAsString(Key,pos,argPos);pos++;
		if(INI_ReadString(Value,Key)){
			setargAsString(Value,pos,argPos);pos++;
			//printf("Key:%s,Value:%s",Key,Value);
		}else{
			INI_Close();
			return false;
		}
	}
	INI_Save();
	return INI_Close();
}
#define readini INI_Read