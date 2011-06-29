/*
								The MIT License  
								
	Copyright (c) <2010> <yezizhu>  
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:  

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.  
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.  
	==================================
	版权(c) <2010> <yezizhu>  

	使用该许可证的软件被授予以下权限，免费，任何人可以得到这个软件及其相关文档的一个拷贝，
	并且经营该软件不受任何限制，包括无限制的使用、复制、修改、合并、出版、发行、发放从属证书、或者出售该软件的拷贝的权利。
	同时允许获得这些软件的用户享受这些权利，使其服从下面的条件：  
	
	以上的版权通知和权限通知应该包含在所有该软件的拷贝中或者是其他该软件的真实部分中。
	
	该软件按本来的样子提供，没有任何形式的担保，不管是明确地或者暗含的，包含这些但是不受商业性质的担保的限制。
	适合一个特定的用途并且不受侵犯。作者和版权持有人在任何场合对使用该软件涉及的任何要求、损害或者其他责任都不应负责。
	不管它是正在起作用还是只是合同形式、民事侵权或是其他方式，如由它引起，在其作用范围内、与该软件有联系、该软件的使用或者有这个软件引起的其他行为。  
	=====================================   
*/	


#if defined _gcs_sqladvanced_included
	#endinput
#endif
#define _gcs_sqladvanced_included
#pragma library gcs_sqladvanced


enum {
	sql_mode_none,
	sql_mode_new,
	sql_mode_cat
}
	
#define MAX_SQL_STR	(1024)
new stock  
	gcs_sql[MAX_SQL_STR],
	gcs_sql_main[MAX_SQL_STR];

/*
stock sql(const sqlstr[], mode = sql_mode_cat){
	if(mode == sql_mode_new){
		format(gcs_sql,sizeof(gcs_sql),sqlstr);
	}
	else if(mode == sql_mode_cat){
		strcat(gcs_sql,sqlstr);
	}
		
	new
		len = strlen(sqlstr);
	if(len >= sizeof(gcs_sql)){
		print(" Error: sql erroe code:001(sql query string is out of index)");
		//format(gcs_sql,sizeof(gcs_sql),"");
		return false;
	}
	sqlstr[len] = ' ';
	sqlstr[len] = '\0';
	return true;
}
*/


#define sql(%1,%2) \
	format(gcs_sql,sizeof(gcs_sql),(%1),%2);\
	strcat(gcs_sql_main,gcs_sql);gcs_sql_main[strlen(gcs_sql_main)+1]='\0';gcs_sql_main[strlen(gcs_sql_main)]='\n'

stock sql(const sqlstr[]){
	strcat(gcs_sql_main,sqlstr);
	gcs_sql_main[strlen(gcs_sql_main)+1]='\0';
	gcs_sql_main[strlen(gcs_sql_main)]='\n';
}

stock sql_clear(){
	//sql_outputquery();
	for(new i,j=sizeof(gcs_sql_main);i < j;i++){
		gcs_sql_main[i] = '\0';
	}
	//format(gcs_sql_main,sizeof(gcs_sql_main),"");
}

stock DBResult:sql_query(DB:db){
	new
		DBResult:dbr3 = db_query(db,gcs_sql_main);
	sql_outputquery();
	sql_clear();
	
	return dbr3;
}

stock sql_outputquery(){
	printf "\n%s",gcs_sql_main
}


/*
stock db_get_field_adv(DBResult:dbresult, field, result[], maxlength){
	new
		rdbr = db_get_field(dbresult,field,result,maxlength);
	printf("db value:%s",result);
	return  rdbr;
}
#define db_get_field(%1) db_get_field_adv(%1)

*/































