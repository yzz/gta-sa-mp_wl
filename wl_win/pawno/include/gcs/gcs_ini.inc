/**====================================================================================
								GCS INI System	
								


Description:
	INI System

Legal:
	Copyright (C) 2009 ,GCS Team

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA 02110-1301, USA.

Version:

Changelog:

Bugs:

Functions:
	@public:
	@private:
			
		G private:
			
Callbacks:
	
Definitions:
	
Variables:
	Global:
	Static:





*/


#define INI_DEBUG			(false)
#define INI_SHOWVALUE		(false)
static const stock 
	bool:gini_true = true,
	bool:gini_false = false;

#if INI_DEBUG
#define INI_DEBUG_output(%1) \
	do{ \
		printf(%1); \
	}while(gini_false)
#else
#define INI_DEBUG_output(%1) \
	do{}while(gini_false)
#endif


stock gcs_ini_strcmp(const str1[],const str2[],bool:ignorecase = false,length = cellmax){
	if(!str1[0] && !str2[0])return 0;
	if(!str1[0])return 0-strlen(str2);
	if(!str2[0])return strlen(str1);
	return strcmp(str1,str2,ignorecase,length);
}


/*----------------------------------------------------------------------*\
Name:
	gini_delChar
Param(s):
	source[] - source string
	del_char - the char to delete
	start - start pos
	end - end pos
Return:
	deleted string
Description:
	Delete all of the char in a string
\*----------------------------------------------------------------------*/
stock gini_delChar(dest[],const source[],const del_char,start = 0,const end = sizeof(source)){
	INI_DEBUG_output("[debug_gini]gini_delChar(%s,%s,%d,%d,%d)",dest,source,del_char,start,end);
	new
		pos;
	while(start < end && source[start]){
		if(source[start] != del_char){
			dest[pos++] = source[start];
		}
		start++;
	}
	dest[pos] = '\0';
	return true;
}


/**
 *  Strips Newline from the end of a string.
 *  Idea: Y_Less, Bugfixing (when length=1) by DracoBlue
 *  @param   string
 */
stock gini_stripNewLine(string[]){
	new len = strlen(string);
	if (string[0]==0) return ;
	if ((string[len - 1] == '\n') || (string[len - 1] == '\r')) {
		string[len - 1] = 0;
		if (string[0]==0) return ;
		if ((string[len - 2] == '\n') || (string[len - 2] == '\r')) string[len - 2] = 0;
	}
}


#define MAX_INI_LINE_SPARE_LENGTH		(10)
#define MAX_INI_SPARE_LINES				(100)

#define MAX_INI_SECTION					(5)
#define MAX_INI_SECTION_LENGTH			(24+MAX_INI_LINE_SPARE_LENGTH)
#define MAX_INI_SECTION_SON				(1000)
#define INI_INVALID_SECTION_ID			(0)

#define MAX_INI_ENTRY					(1000)
#define MAX_INI_VALUE_LENGTH			(256+MAX_INI_LINE_SPARE_LENGTH)
#define MAX_INI_ENTRY_LENGTH			(24+MAX_INI_VALUE_LENGTH)


#define MAX_INI_COMMENT					(50)
#define MAX_INI_COMMENT_LENGTH			(256+MAX_INI_LINE_SPARE_LENGTH)


#define MAX_INI_LINES					(MAX_INI_SECTION+MAX_INI_ENTRY+MAX_INI_COMMENT+MAX_INI_SPARE_LINES)

#if (MAX_INI_ENTRY_LENGTH > MAX_INI_SECTION_LENGTH && MAX_INI_ENTRY_LENGTH > MAX_INI_COMMENT_LENGTH) 
	#define MAX_INI_LINE_LENGTH				(MAX_INI_ENTRY_LENGTH)
#elseif MAX_INI_COMMENT_LENGTH > MAX_INI_ENTRY_LENGTH
	#define MAX_INI_LINE_LENGTH				(MAX_INI_COMMENT_LENGTH)
#else
	#define MAX_INI_LINE_LENGTH				(MAX_INI_SECTION_LENGTH)
#endif

#define MAX_INI_FILE_NAME_LENGTH		(256)

#define INI_LINE_END					"\r\n"

//#define INI_BASED_LINE_POS				(10000)


enum {
	gini_file_section_type_none,
	gini_file_section_type_entry,
	gini_file_section_type_comment,
	gini_file_section_type_amount
}
enum E_gini_file_entry_data{
	E_gini_file_entry_sectionid,
	E_gini_file_entry_str[MAX_INI_ENTRY_LENGTH],
	E_gini_file_entry_split,
	//E_gini_file_entry_pos
};

enum E_gini_file_section_data{
	E_gini_file_section_str[MAX_INI_SECTION_LENGTH],
	E_gini_file_section_amount,
	E_gini_file_section_pos[MAX_INI_SECTION_SON],
	E_gini_file_section_pos_type[MAX_INI_SECTION_SON],
	E_gini_file_section_pos_amount
};

enum E_gini_file_comment_data{
	E_gini_file_comment_sectionid,
	E_gini_file_comment_str[MAX_INI_COMMENT_LENGTH],
	//E_gini_file_comment_pos
};

enum E_gini_file_data{
	E_gini_file_name[MAX_INI_FILE_NAME_LENGTH]
};

static stock
	gcs_s_gini_file_entry[MAX_INI_ENTRY][E_gini_file_entry_data],
	gcs_s_gini_file_entry_amount,
	
	gcs_s_gini_file_section[MAX_INI_SECTION][E_gini_file_section_data],
	gcs_s_gini_file_section_amount,
	
	gcs_s_gini_file_comment[MAX_INI_COMMENT][E_gini_file_comment_data],
	gcs_s_gini_file_comment_amount,
	
	gcs_s_gini_file[E_gini_file_data];

/*----------------------------------------------------------------------*\
Name:
	gini_opened
Param(s):
	-
Return:
	open or not
Description:
	Check if is opened a file
\*----------------------------------------------------------------------*/
#define gini_opened() \
	gcs_s_gini_file[E_gini_file_name][0]

/*----------------------------------------------------------------------*\
Name:
	gini_open
Param(s):
	filename[] - the filename
Return:
	open or not
Description:
	Open a file to handle
\*----------------------------------------------------------------------*/
stock bool:gini_open(const filename[]){
	INI_DEBUG_output("[debug_gini]gini_open(%s)",filename);
	if(!fexist(filename)){
		fclose(fopen(filename,io_write));
		printf "File '%s' doesn't exist.create it",filename
		//return false;
	}
	if(gini_opened()){
		return false;
	}
	
	format(gcs_s_gini_file[E_gini_file_name],MAX_INI_FILE_NAME_LENGTH,filename);
	new
		File:gcs_s_gini_handle = fopen(filename,io_read),
		gcs_s_gini_handle_str[MAX_INI_LINE_LENGTH],
		line,
		start,
		sectionid = INI_INVALID_SECTION_ID;
	gcs_s_gini_file_section_amount = 1;
	while(line < MAX_INI_LINES && fread(gcs_s_gini_handle,gcs_s_gini_handle_str)){
		gini_stripNewLine(gcs_s_gini_handle_str);
		for(start = 0;gcs_s_gini_handle_str[start] == ' ';start++){}
		switch(gcs_s_gini_handle_str[start]){
			case '[':{
				new split = strfind(gcs_s_gini_handle_str,"]",false,start);
				if(split == -1){
					gini_setToComment(gcs_s_gini_handle_str,sectionid);
				}else{
					if(gini_validSectionName(gcs_s_gini_handle_str,split)){
						gini_setToSection(gcs_s_gini_handle_str,sectionid);
					}else{
						gini_setToComment(gcs_s_gini_handle_str,sectionid);
					}
				}
			}
			case ';':{
				gini_setToComment(gcs_s_gini_handle_str,sectionid);
			}
			default:{
				new split = strfind(gcs_s_gini_handle_str,"=",false,start+1);
				if(split == -1){
					gini_setToComment(gcs_s_gini_handle_str,sectionid);
				}else{
					if(gini_validEntryName(gcs_s_gini_handle_str,split)){
						gini_setToEntry(gcs_s_gini_handle_str,split,sectionid);
					}else{
						gini_setToComment(gcs_s_gini_handle_str,sectionid);
					}
				}
			}
		}
		line++;
	}
	fclose(gcs_s_gini_handle);
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_close
Param(s):
	-
Return:
	close or not
Description:
	Close the opened-file
\*----------------------------------------------------------------------*/
stock bool:gini_close(){
	INI_DEBUG_output("[debug_gini]gini_close()");
	if(!gini_opened()){
		return false;
	}
	for(new i;i < MAX_INI_ENTRY;i++){
		gcs_s_gini_file_entry[i][E_gini_file_entry_sectionid] = INI_INVALID_SECTION_ID;
		gcs_s_gini_file_entry[i][E_gini_file_entry_str][0] = '\0';
		gcs_s_gini_file_entry[i][E_gini_file_entry_split] = -1;
		//gcs_s_gini_file_entry[i][E_gini_file_entry_pos] = 0;
	}
	for(new i;i < MAX_INI_SECTION;i++){
		gcs_s_gini_file_section[i][E_gini_file_section_str][0] = '\0';
		gcs_s_gini_file_section[i][E_gini_file_section_amount] = 0;
		gcs_s_gini_file_section[i][E_gini_file_section_pos_amount] = 0;
		for(new j;j < MAX_INI_SECTION_SON;j++){
			gcs_s_gini_file_section[i][E_gini_file_section_pos][j] = 0;
			gcs_s_gini_file_section[i][E_gini_file_section_pos_type][j] = gini_file_section_type_none;
		}
	}
	for(new i;i < MAX_INI_COMMENT;i++){
		gcs_s_gini_file_comment[i][E_gini_file_comment_sectionid] = 0;
		gcs_s_gini_file_comment[i][E_gini_file_comment_str][0] = '\0';
		//gcs_s_gini_file_comment[i][E_gini_file_comment_pos] = 0;
	}
	gcs_s_gini_file_entry_amount = 0;
	gcs_s_gini_file_section_amount = 0;
	gcs_s_gini_file_comment_amount = 0;
	gcs_s_gini_file[E_gini_file_name][0] = '\0';
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_save
Param(s):
	-
Return:
	save or not
Description:
	Save the opened-file
\*----------------------------------------------------------------------*/
stock bool:gini_save(){
	INI_DEBUG_output("[debug_gini]gini_save()");
	if(!fexist(gcs_s_gini_file[E_gini_file_name])){
		printf "File '%s' doesn't exist.",gcs_s_gini_file[E_gini_file_name]
		return false;
	}
	if(!gini_opened())return false;
	fremove(gcs_s_gini_file[E_gini_file_name]);
	new 
		File:gcs_s_gini_handle = fopen(gcs_s_gini_file[E_gini_file_name],io_append),
		gcs_s_gini_handle_str[MAX_INI_LINE_LENGTH];
	for(new i;i < gcs_s_gini_file_section_amount;i++){
		format(gcs_s_gini_handle_str,MAX_INI_LINE_LENGTH,"%s\r\n",gcs_s_gini_file_section[i][E_gini_file_section_str]);
		//printf("  %s",gcs_s_gini_handle_str);
		if(i != INI_INVALID_SECTION_ID) gini_fwrite(gcs_s_gini_handle,gcs_s_gini_handle_str);
		for(new j,l;j < gcs_s_gini_file_section[i][E_gini_file_section_pos_amount];j++){
			l = gcs_s_gini_file_section[i][E_gini_file_section_pos][j];
			switch(gcs_s_gini_file_section[i][E_gini_file_section_pos_type][j]){
				case gini_file_section_type_entry:{
					format(gcs_s_gini_handle_str,sizeof(gcs_s_gini_handle_str),"%s\r\n",gcs_s_gini_file_entry[l][E_gini_file_entry_str]);
				}
				case gini_file_section_type_comment:{
					format(gcs_s_gini_handle_str,sizeof(gcs_s_gini_handle_str),"%s\r\n",gcs_s_gini_file_comment[l][E_gini_file_comment_str]);
				}
			}
			//printf("    %s",gcs_s_gini_handle_str);
			gini_fwrite(gcs_s_gini_handle,gcs_s_gini_handle_str);
		}
	}
	fclose(gcs_s_gini_handle);
	gini_close();
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_setToSection
Param(s):
	section_value[] - the value to set to.
Return:
	sectionid
Description:
	Set value to build a section
\*----------------------------------------------------------------------*/
stock gini_setToSection(const section_value[],&sectionid){
	INI_DEBUG_output("[debug_gini]gini_setToSection(%s)",section_value);
	sectionid = gcs_s_gini_file_section_amount;
	gcs_s_gini_file_section_amount++;
	if(sectionid >= MAX_INI_SECTION){
		sectionid = INI_INVALID_SECTION_ID;
		return false;
	}
	gcs_s_gini_file_section[sectionid][E_gini_file_section_amount] = 0;
	format(gcs_s_gini_file_section[sectionid][E_gini_file_section_str],MAX_INI_SECTION_LENGTH,"%s",section_value);
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_setToComment
Param(s):
	comment_value[] - the value to set to.
	sectionid - the section to set to.
Return:
	0/1
Description:
	Set value to build a comment
\*----------------------------------------------------------------------*/
stock gini_setToComment(const comment_value[],const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_setToComment(%s,%d)",comment_value,sectionid);
	new
		pos = gcs_s_gini_file_comment_amount++;
	if(pos >= MAX_INI_COMMENT){
		return false;
	}
	new
		strpos;
	for(strpos = 0;comment_value[strpos] == ' ';strpos++){}
	if(comment_value[strpos] != ';'){
		format(gcs_s_gini_file_comment[pos][E_gini_file_comment_str],MAX_INI_COMMENT_LENGTH,";%s",comment_value);
	}else{
		format(gcs_s_gini_file_comment[pos][E_gini_file_comment_str],MAX_INI_COMMENT_LENGTH,"%s",comment_value);
	}
	gcs_s_gini_file_comment[pos][E_gini_file_comment_sectionid] = sectionid;
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos][gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]] = pos;
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_type][gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]] = gini_file_section_type_comment;
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]++;
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_setToEntry
Param(s):
	entry_value - the value to set to.
	sectionid - the section to set to.
Return:
	0/1
Description:
	Set value to bulid an entry,which based on section
\*----------------------------------------------------------------------*/
stock gini_setToEntry(const entry_value[],const entry_split,const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_setToEntry(%s,%d,%d)",entry_value,entry_split,sectionid);
	new
		pos = gcs_s_gini_file_entry_amount++;
	if(pos >= MAX_INI_ENTRY){
		return false;
	}
	format(gcs_s_gini_file_entry[pos][E_gini_file_entry_str],MAX_INI_ENTRY_LENGTH,"%s",entry_value);
	gcs_s_gini_file_entry[pos][E_gini_file_entry_split] = entry_split;
	gcs_s_gini_file_entry[pos][E_gini_file_entry_sectionid] = sectionid;	
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos][gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]] = pos;
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_type][gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]] = gini_file_section_type_entry;
	gcs_s_gini_file_section[sectionid][E_gini_file_section_pos_amount]++;	
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_getSectionNameFromID
Param(s):
	sectionid - the sectionid
	section_name - to store the name
	len - sizeof section_name
Return:
	0/1
Description:
	Get a section name from section identify.
\*----------------------------------------------------------------------*/
stock bool:gini_getSectionNameFromID(const sectionid,section_name[],const len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_getSectionNameFromID(%d,%s,%d)",sectionid,section_name,len);
	if(sectionid == INI_INVALID_SECTION_ID){
		return true;
	}else{
		gini_delChar(section_name,gcs_s_gini_file_section[sectionid][E_gini_file_section_str],' ',0,len);
		return true;
	}
}

/*----------------------------------------------------------------------*\
Name:
	gini_getSectionIDFromName
Param(s):
	section_name - the section name
	sectionid - to stroe the id
Return:
	0/1
Description:
	Get a section id from section name
\*----------------------------------------------------------------------*/
stock bool:gini_getSectionIDFromName(const section_name[],&sectionid,const len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_getSectionIDFromName(%s,%d,%d)",section_name,sectionid,len);
	if(!section_name[0]){
		sectionid = INI_INVALID_SECTION_ID;
		return true;
	}else{
		for(new i;i < gcs_s_gini_file_section_amount;i++){
			new
				tmpstr[MAX_INI_SECTION_LENGTH];
			gini_delChar(tmpstr,gcs_s_gini_file_section[i][E_gini_file_section_str],' ',0,len);
			//printf("%d,%s,%s,",i,tmpstr,section_name);
			if(!gcs_ini_strcmp(tmpstr,section_name)){
				sectionid = i;
				return true;
			}
		}
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_validSectionName
Param(s):
	section_name[] - the section name 
	end - the end of section name
Return:
	0/1
Description:
	Check if is valid section name
\*----------------------------------------------------------------------*/
stock gini_validSectionName(const section_name[],end){
	INI_DEBUG_output("[debug_gini]gini_validSectionName(%s,%d)",section_name,end);
	for(new i;section_name[i] && i < end;i++){
		if(
			!(
				(section_name[i] >= 'a' && section_name[i] <= 'z') ||
				(section_name[i] >= 'A' && section_name[i] <= 'Z') ||
				(section_name[i] >= '0' && section_name[i] <= '9') ||
				(section_name[i] == '_') || (section_name[i] == '[') || (section_name[i] == ']') || (section_name[i] == ' ')
			)
		){
			return false;
		}
	}
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_createSection
Param(s):
	sectionid - to store the sectionid
	section_name - the section name
Return:
	0/1
Description:
	Create a section
\*----------------------------------------------------------------------*/
stock bool:gini_createSection(&sectionid,const section_name[],len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_createSection(%d,%s)",sectionid,section_name);
	if(gini_getSectionIDFromName(section_name,sectionid,len)) return false;
	if(gini_setToSection(section_name,sectionid)){
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_removeSection
Param(s):
	sectionid - the sectionid to remove
	entry_remove - remove entry or not
Return:
	0/1
Description:
	Remove a section with removeing its entry/comment.
\*----------------------------------------------------------------------*/
stock bool:gini_removeSection(const sectionid,const bool:entry_remove = true){
	INI_DEBUG_output("[debug_gini]gini_removeSection(%d,%d)",sectionid,entry_remove);
	for(new i;i < gcs_s_gini_file_entry_amount;i++){
		if(gcs_s_gini_file_entry[i][E_gini_file_entry_sectionid] == sectionid){
			gcs_s_gini_file_entry[i][E_gini_file_entry_sectionid] = INI_INVALID_SECTION_ID;
			if(entry_remove){
				gcs_s_gini_file_entry[i][E_gini_file_entry_split] = -1;
				//gcs_s_gini_file_entry[i][E_gini_file_entry_pos] = 0;
				gcs_s_gini_file_entry[i][E_gini_file_entry_str][0] = '\0';
			}
		}
	}
	for(new i;i < gcs_s_gini_file_comment_amount;i++){
		if(gcs_s_gini_file_comment[i][E_gini_file_comment_sectionid] == sectionid){
			gcs_s_gini_file_comment[i][E_gini_file_comment_sectionid] = INI_INVALID_SECTION_ID;
			if(entry_remove){
				//gcs_s_gini_file_comment[i][E_gini_file_comment_pos] = 0;
				gcs_s_gini_file_comment[i][E_gini_file_comment_str][0] = '\0';
			}
		}
	}
	gcs_s_gini_file_section[sectionid][E_gini_file_section_str][0] = '\0';
	gcs_s_gini_file_section[sectionid][E_gini_file_section_amount] = 0;
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_renameSection
Param(s):
	sectionid - the section to rename
	section_name - new name
	len - sizeof section_name
Return:
	0/1
Description:
	TODO
\*----------------------------------------------------------------------*/
stock bool:gini_renameSection(const sectionid,const section_name[],const len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_renameSection(%d,%s,%d)",sectionid,section_name,len);
	#pragma unused sectionid,section_name,len
	//format(section_name,len,gcs_s_gini_file_section[sectionid][E_gini_file_section_str]);
	return true;
}


/*----------------------------------------------------------------------*\
Name:
	gini_sSection
Param(s):
	section_name - the section name to create
Return:
	sectionid
Description:
	Create a section,which uses for user.
\*----------------------------------------------------------------------*/
stock gini_sSection(const section_name[],len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_cSection(%s)",section_name);
	new
		sectionid;
	gini_createSection(sectionid,section_name,len);
	return sectionid;
}

/*----------------------------------------------------------------------*\
Name:
	gini_rSection
Param(s):
	section_name - the section name
Return:
	0/1
Description:
	Remove a section,which uses for user.
\*----------------------------------------------------------------------*/
stock bool:gini_rSection(const section_name[]/*,const bool:entry_remove = true*/,const len = sizeof(section_name)){
	INI_DEBUG_output("[debug_gini]gini_rSection(%s,%d)",section_name,len);
	new
		sectionid;
	if(gini_getSectionIDFromName(section_name,sectionid,len)){
		if(gini_removeSection(sectionid,true)){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_getEntryNameFromID
Param(s):
	entryid - the entry id to get
	entry_name[] - to store the entry name
	#sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	Get an entry name from an entry id
\*----------------------------------------------------------------------*/
stock bool:gini_getEntryNameFromID(const entryid,entry_name[],/*const sectionid = INI_INVALID_SECTION_ID,*/const len = sizeof(entry_name)){
	INI_DEBUG_output("[debug_gini]gini_getEntryNameFromID(%d,%s,%d)",entryid,entry_name,len);
	new
		tmpstr[MAX_INI_ENTRY_LENGTH];
	gini_delChar(tmpstr,entry_name,' ',0,gcs_s_gini_file_entry[entryid][E_gini_file_entry_split]);
	format(entry_name,len,tmpstr);
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_getEntryIDFromName
Param(s):
	entry_name[] - the entry name to get
	entryid - to store the entry id
	sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	Get an entry id from an entry name
\*----------------------------------------------------------------------*/
stock bool:gini_getEntryIDFromName(const entry_name[],&entryid,const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_getEntryIDFromName(%s,%d,%d)",entry_name,entryid,sectionid);
	for(new i;i < gcs_s_gini_file_entry_amount;i++){
		new
			tmpstr[MAX_INI_ENTRY_LENGTH];
		if(gcs_s_gini_file_entry[i][E_gini_file_entry_sectionid] == sectionid){
			gini_delChar(tmpstr,gcs_s_gini_file_entry[i][E_gini_file_entry_str],' ',0,gcs_s_gini_file_entry[i][E_gini_file_entry_split]);
			//printf("%d,%s,%s,",i,tmpstr,entry_name);
			if(!gcs_ini_strcmp(tmpstr,entry_name)){
				entryid = i;
				return true;
			}
		}
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_validEntryName
Param(s):
	entry_name[] - the entry name 
	end - the end of entry name
Return:
	0/1
Description:
	Check if is valid entry name
\*----------------------------------------------------------------------*/
stock gini_validEntryName(const entry_name[],end){
	INI_DEBUG_output("[debug_gini]gini_validEntryName(%s,%d)",entry_name,end);
	for(new i;entry_name[i] && i < end;i++){
		//printf "%c,%d",entry_name[i],entry_name[i]
		if(
			!(
				(entry_name[i] >= 'a' && entry_name[i] <= 'z') ||
				(entry_name[i] >= 'A' && entry_name[i] <= 'Z') ||
				(entry_name[i] >= '0' && entry_name[i] <= '9') ||
				(entry_name[i] == '_') || (entry_name[i] == ' ')
			)
		){
			return false;
		}
	}
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_createEntry
Param(s):
	entryid - to store the entry identify
	entry_name[] - the entry name to set
	entry_value[] - the entry value to set
	sectionid - the sectionid to set,defaultly set to invalid id
Return:
	0/1
Description:
	Create an entry
\*----------------------------------------------------------------------*/
stock bool:gini_createEntry(&entryid,const entry_name[],const entry_value[] = "",const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_createEntry(%d,%s,%s,%d)",entryid,entry_name,entry_value,sectionid);
	new
		tmpstr[MAX_INI_ENTRY_LENGTH];
	format(tmpstr,sizeof(tmpstr),"%s = %s",entry_name,entry_value);
	if(gini_setToEntry(tmpstr,strlen(entry_name)+2,sectionid)){
		entryid = gcs_s_gini_file_entry_amount-1;
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_removeEntry
Param(s):
	entryid - the entryid to remove
	sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	Remove an entry,which its value will set to comment
\*----------------------------------------------------------------------*/
stock bool:gini_removeEntry(const entryid,const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_removeEntry(%d,%d)",entryid,sectionid);
	if(gcs_s_gini_file_entry[entryid][E_gini_file_entry_sectionid] == sectionid){
		gcs_s_gini_file_entry[entryid][E_gini_file_entry_sectionid] = INI_INVALID_SECTION_ID;
		gcs_s_gini_file_entry[entryid][E_gini_file_entry_str][0] = '\0';
		gcs_s_gini_file_entry[entryid][E_gini_file_entry_split] = -1;
		//gcs_s_gini_file_entry[entryid][E_gini_file_entry_pos] = 0;
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_setEntryValue
Param(s):
	entryid - the entryid to set to
	entry_value[] - the value to set to
	sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	Set an entry with value
\*----------------------------------------------------------------------*/
stock bool:gini_setEntryValue(const entryid,const entry_value[],const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_setEntryValue(%d,%s,%d)",entryid,entry_value,sectionid);
	if(gcs_s_gini_file_entry[entryid][E_gini_file_entry_sectionid] == sectionid){
		gcs_s_gini_file_entry[entryid][E_gini_file_entry_str][gcs_s_gini_file_entry[entryid][E_gini_file_entry_split]+1] = ' ';
		new 
			i = gcs_s_gini_file_entry[entryid][E_gini_file_entry_split]+2,
			j;
		while(entry_value[j] && i < MAX_INI_ENTRY_LENGTH){
			gcs_s_gini_file_entry[entryid][E_gini_file_entry_str][i] = entry_value[j];
			i++;
			j++;
		}
		gcs_s_gini_file_entry[entryid][E_gini_file_entry_str][i] = '\0';
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_getEntryValue
Param(s):
	entryid - the entryid to get to
	entry_value[] - to store the value
	sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	Get an entry value to an array
\*----------------------------------------------------------------------*/
stock bool:gini_getEntryValue(const entryid,value[],const sectionid = INI_INVALID_SECTION_ID,const len = sizeof(value)){
	INI_DEBUG_output("[debug_gini]gini_getEntryValue(%d,%s,%d,%d)",entryid,value,sectionid,len);
	if(gcs_s_gini_file_entry[entryid][E_gini_file_entry_sectionid] == sectionid){
		format(value,len,gcs_s_gini_file_entry[entryid][E_gini_file_entry_str][gcs_s_gini_file_entry[entryid][E_gini_file_entry_split]+1]);
		gini_delChar(value,value,' ',0,len);
		#if INI_SHOWVALUE
			printf("[gini]value:%s",value);
		#endif
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_renameEntry
Param(s):
	entryid - the entryid to remove
	sectionid - the sectionid,defaultly set to invalid id
Return:
	0/1
Description:
	TODO
\*----------------------------------------------------------------------*/
stock bool:gini_renameEntry(const entryid,const sectionid = INI_INVALID_SECTION_ID){
	INI_DEBUG_output("[debug_gini]gini_renameEntry(%d,%d)",entryid,sectionid);
	#pragma unused entryid,sectionid
	return true;
}

/*----------------------------------------------------------------------*\
Name:
	gini_sEntry
Param(s):
	entry_name[] - the entry name
	entry_value[] - the value to set to
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	0/1
Description:
	Set an entry with value,which uses for user
\*----------------------------------------------------------------------*/
stock bool:gini_sEntry(const entry_name[],const entry_value[],const entry_section[] = "",const len = sizeof(entry_section)){
	//printf("[debug_gini]gini_sEntry(%s,%s,%s,%d)",entry_name,entry_value,entry_section,len);
	INI_DEBUG_output("[debug_gini]gini_sEntry(%s,%s,%s,%d)",entry_name,entry_value,entry_section,len);
	if(!gini_opened())return false;
	new
		sectionid,
		entryid;
	if(gini_getSectionIDFromName(entry_section,sectionid,len)){
		if(gini_getEntryIDFromName(entry_name,entryid,sectionid)){
			gini_setEntryValue(entryid,entry_value,sectionid);
		}else{
			gini_createEntry(entryid,entry_name,entry_value,sectionid);
		}
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_rEntry
Param(s):
	entry_name[] - the entry name
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	0/1
Description:
	Remove an entry,which uses for user
\*----------------------------------------------------------------------*/
stock bool:gini_rEntry(const entry_name[],const entry_section[] = "",const len = sizeof(entry_section)){
	printf("[debug_gini]gini_rEntry(%s,%s,%d)",entry_name,entry_section,len);
	INI_DEBUG_output("[debug_gini]gini_rEntry(%s,%s,%d)",entry_name,entry_section,len);
	if(!gini_opened())return false;
	new
		sectionid,
		entryid;
	if(gini_getSectionIDFromName(entry_section,sectionid,len)){
		if(gini_getEntryIDFromName(entry_name,entryid,sectionid)){
			gini_removeEntry(entryid,sectionid);
			return true;
		}
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	Float:gini_readf
Param(s):
	entry_name[] - the entry name
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	A float value
Description:
	Get a float value,which uses for user
\*----------------------------------------------------------------------*/
stock Float:gini_readf(const entry_name[],const entry_section[] = "",const len = sizeof(entry_section)){
	INI_DEBUG_output("[debug_gini]gini_readf(%s,%s,%d)",entry_name,entry_section,len);
	if(!gini_opened())return 0.0;
	new
		sectionid,
		entryid;
	gini_getSectionIDFromName(entry_section,sectionid,len);
	if(gini_getEntryIDFromName(entry_name,entryid,sectionid)){
		new
			entry_value[MAX_INI_ENTRY_LENGTH];
		gini_getEntryValue(entryid,entry_value,sectionid);
		return floatstr(entry_value);
	}
	return 0.0;
}

/*----------------------------------------------------------------------*\
Name:
	gini_readi
Param(s):
	entry_name[] - the entry name
	entry_setcion[] - the entry_section name,,defaultly set to invalid name
Return:
	Integer
Description:
	Get a int value,which uses for user
\*----------------------------------------------------------------------*/
stock gini_readi(const entry_name[],const entry_section[] = "",const len = sizeof(entry_section)){
	//printf("[debug_gini]gini_readi(%s,%s,%d)",entry_name,entry_section,len);
	INI_DEBUG_output("[debug_gini]gini_readi(%s,%s,%d)",entry_name,entry_section,len);
	if(!gini_opened())return 0;
	new
		sectionid,
		entryid;
	gini_getSectionIDFromName(entry_section,sectionid,len);
	if(gini_getEntryIDFromName(entry_name,entryid,sectionid)){
		new
			entry_value[MAX_INI_ENTRY_LENGTH];
		gini_getEntryValue(entryid,entry_value,sectionid);
		return strval(entry_value);
	}
	return 0;
}

/*----------------------------------------------------------------------*\
Name:
	gini_reads
Param(s):
	entry_name[] - the entry name
	entry_setcion[] - the entry_section name,,defaultly set to invalid name
Return:
	String
Description:
	Get a string,which uses for user
\*----------------------------------------------------------------------*/
stock gini_reads(const entry_name[],const entry_section[] = "",const len = sizeof(entry_section)){
	INI_DEBUG_output("[debug_gini]gini_reads(%s,%s,%d)",entry_name,entry_section,len);
	new
		sectionid,
		entryid,
		entry_value[MAX_INI_ENTRY_LENGTH];
	if(!gini_opened())return entry_value;
	gini_getSectionIDFromName(entry_section,sectionid,len);
	if(gini_getEntryIDFromName(entry_name,entryid,sectionid)){
		gini_getEntryValue(entryid,entry_value,sectionid);
	}
	return entry_value;
}

/*----------------------------------------------------------------------*\
Name:
	gini_writei
Param(s):
	entry_name[] - the entry name
	value - the value to write to
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	0/1
Description:
	Write int,which uses for user
\*----------------------------------------------------------------------*/
stock bool:gini_writei(const entry_name[],const value,const entry_section[] = "",const len = sizeof(entry_name)){
	INI_DEBUG_output("[debug_gini]gini_writei(%s,%d,%s,%d)",entry_name,value,entry_section,len);
	if(!gini_opened())return false;
	new
		entry_value[MAX_INI_ENTRY_LENGTH];
	format(entry_value, sizeof(entry_value), "%d", value);
	if(gini_sEntry(entry_name,entry_value,entry_section,len)){
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_writef
Param(s):
	entry_name[] - the entry name
	Float:value - the float value to write to
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	0/1
Description:
	Write float,which uses for user
\*----------------------------------------------------------------------*/
stock bool:gini_writef(const entry_name[],const Float:value,const entry_section[] = "",const len = sizeof(entry_name)){
	INI_DEBUG_output("[debug_gini]gini_writef(%s,%f,%s,%d)",entry_name,value,entry_section,len);
	if(!gini_opened())return false;
	new
		entry_value[MAX_INI_ENTRY_LENGTH];
	format(entry_value, sizeof(entry_value), "%f", value);
	if(gini_sEntry(entry_name,entry_value,entry_section,len)){
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------*\
Name:
	gini_writes
Param(s):
	entry_name[] - the entry name
	value[] - the string to write to
	entry_setcion[] - the entry_section name,defaultly set to invalid name
Return:
	0/1
Description:
	Write string,which uses for user
\*----------------------------------------------------------------------*/
stock bool:gini_writes(const entry_name[],const value[],const entry_section[] = "",const len = sizeof(entry_name)){
	INI_DEBUG_output("[debug_gini]gini_writes(%s,%s,%s,%d)",entry_name,value,entry_section,len);
	if(!gini_opened())return false;
	if(gini_sEntry(entry_name,value,entry_section,len)){
		return true;
	}
	return false;
}



/*----------------------------------------------------------------------*\
Name:
	gini_struction
Param(s):
	-
Return:
	-
Description:
	Struct gini system
\*----------------------------------------------------------------------*/
gini_struction(){
	INI_DEBUG_output("[debug_gini]gini_struction()");
	for(new i;i < MAX_INI_ENTRY;i++){
		gcs_s_gini_file_entry[i][E_gini_file_entry_sectionid] = INI_INVALID_SECTION_ID;
		gcs_s_gini_file_entry[i][E_gini_file_entry_split] = -1;
		gcs_s_gini_file_entry[i][E_gini_file_entry_str][0] = '\0';
		//gcs_s_gini_file_entry[i][E_gini_file_entry_pos] = 0;
	}
	gcs_s_gini_file_entry_amount = 0;
	for(new i;i < MAX_INI_COMMENT;i++){
		gcs_s_gini_file_comment[i][E_gini_file_comment_sectionid] = INI_INVALID_SECTION_ID;
		gcs_s_gini_file_comment[i][E_gini_file_comment_str][0] = '\0';
		//gcs_s_gini_file_comment[i][E_gini_file_comment_pos] = 0;
	}
	gcs_s_gini_file_comment_amount = 0;
	for(new i;i < MAX_INI_SECTION;i++){
		gcs_s_gini_file_section[i][E_gini_file_section_str][0] = '\0';
		gcs_s_gini_file_section[i][E_gini_file_section_amount] = 0;
		gcs_s_gini_file_section[i][E_gini_file_section_pos_amount] = 0;
		for(new j;j < MAX_INI_SECTION_SON;j++){
			gcs_s_gini_file_section[i][E_gini_file_section_pos][j] = 0;
			gcs_s_gini_file_section[i][E_gini_file_section_pos_type][j] = gini_file_section_type_none;
		}
	}
	gcs_s_gini_file[E_gini_file_name][0] = '\0';
}

stock gini_skimCache(){
	INI_DEBUG_output("[debug_gini]gini_skimCache()");
	print("[debug_gini]Skim cache");
	for(new i;i < gcs_s_gini_file_section_amount;i++){
		printf("  %s",gcs_s_gini_file_section[i][E_gini_file_section_str]);
		for(new j;j < gcs_s_gini_file_section[i][E_gini_file_section_pos_amount];j++){
			switch(gcs_s_gini_file_section[i][E_gini_file_section_pos_type][j]){
				case gini_file_section_type_entry:{
					printf("    %s",gcs_s_gini_file_entry[gcs_s_gini_file_section[i][E_gini_file_section_pos][j]][E_gini_file_entry_str]);
				}
				case gini_file_section_type_comment:{
					printf("    %s",gcs_s_gini_file_comment[gcs_s_gini_file_section[i][E_gini_file_section_pos][j]][E_gini_file_comment_str]);
				}
			}
		}
	}
	print("[debug_gini]Skim end");
}


/*----------------------------------------------------------------------*\
Name:
	gini_isSectionExist
Param(s):
	section_name - the section name
Return:
	0/1
Description:
	Check if a section is exist.
	For user.
Note:
	Coded by Shindo(ssh)
\*----------------------------------------------------------------------*/
stock gini_isEntryExist(const entry_name[],const section_name[] = ""){
	INI_DEBUG_output("[debug_gini]gini_isEntryExist(%s)",entry_name);
	if(!section_name[0]){
		return false;
	}else{
		new tmpval = INI_INVALID_SECTION_ID;
		if(section_name[0]) gini_getSectionIDFromName(section_name,tmpval,MAX_INI_SECTION_LENGTH);
		if(gini_getEntryIDFromName(entry_name,tmpval,tmpval)){
    	    return true;
		}
	}
	return false;
}


/*----------------------------------------------------------------------*\
Name:
	gini_isSectionExist
Param(s):
	section_name - the section name
Return:
	0/1
Description:
	Check if a section is exist.
	For user.
\*----------------------------------------------------------------------*/
stock gini_isSectionExist(const section_name[]){
	INI_DEBUG_output("[debug_gini]gini_isSectionExist(%s)",section_name);
	new 
		sectionid = INI_INVALID_SECTION_ID;
	if(!section_name[0]){
		return false;
	}else{
		if(gini_getSectionIDFromName(section_name,sectionid,MAX_INI_SECTION_LENGTH) && (sectionid != INI_INVALID_SECTION_ID)){
    	    return true;
		}
	}
	return false;
}

forward gini_writeiEx(entry_name[],value,entry_section[],len);
public gini_writeiEx(entry_name[],value,entry_section[],len){
	if(entry_name[0] == '\1')entry_name[0] = '\0';
	if(entry_section[0] == '\1')entry_section[0] = '\0';
	return gini_writei(entry_name,value,entry_section,len);
}


/*----------------------------------------------------------------------*\
Name:
	gini_readSpecial
Param(s):
	file[] - 
	format[] - 
	split[] - 
	{Float,_}:... - 
Return:
	-
Description:
	Struct gini system
\*----------------------------------------------------------------------*/
/*
stock gini_readSpecial(const file[],const format[],const split,{Float,_}:...){
	if(!fexist(file))return false;
	new 
		File:fhandle = fopen(file,io_read),
		fstring[512],
		split_amount,
		format_amount = strlen(format);
	while(fread(fhandle,fstring)){
		//check same split for format
		for(new i;fstring[i];i++)
			if(fstring[i] == split) 
				split_amount++;
		if(split_amount-1 != format_amount)
			return false;
		//
		//spilit
		for(new i;format[i];i++){
			switch(format[i]){
				case 's','S':{
					
				}
				case 'd','D','i','I':{
				
				}
				case 'f','F':{
				
				}
				
gini_rEntry(const entry_name[],const entry_section[] = "",const len = sizeof(entry_section))


*/





