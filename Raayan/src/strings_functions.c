//string length function
int my_strlen(char s[])
{
	int i;
	for(i=0;s[i]!='\0';i++);
	return i;
}


//string compare function
int my_strcmp(char s1[],char d1[])
{
	int i;
	//for(i=0;s1[i]!='\0';i++);
	
	
	for(i=0;s1[i]==d1[i];i++)
	{
		if(d1[i] == '\0')
			return 0;
	}
	return s1[i]-d1[i];
}
		

//itoa function
	
void itoa(char s[],int x)
{
	int y,j,l,i=0;
	char ch;
	while(x)
	{
		y=x%10;
		s[i]=y+'0';
		x=x/10;
		i++;
	}
	s[i]='\0';
	
	for(i=0;s[i]!='\0';i++);
	l=i;
	for(i=0,j=l-1;j>0;i++,j--)
	{
		ch=s[i];
		s[i]=s[j];
		s[j]=ch;
	}

}

//case reverse function
void my_caserev(char s2[])
{
	int i;
	for(i=0;s2[i]!='\0';i++)
	{
		if(s2[i]>='A' && s2[i]<='Z')
		{
			s2[i]=s2[i]+32;
		}
		if(s2[i]<='a' && s2[i]>='z')
		{
			s2[i]=s2[i]-32;
		}
	}
}
	

//string reverse function
void my_strrev(char s[])
{
	int i,l,ch,j;
	for(i=0;s[i]!='\0';i++);
	l=i;
	for(i=0,j=l-1;j>0;i++,j--)
	{
		ch=s[i];
		s[i]=s[j];
		s[j]=ch;
	}
}
			

int main()
{
	int x=123,r,l;
	char s[50];
	char s1[50]="Tejo";
	char d1[50]="Teja";
	char s2[30]="Viswa";
	
	itoa(s,x);
	r=my_strcmp(s1,d1);
	my_caserev(s2);
	l=my_strlen(s2);
	my_strrev(d1);
}
	





			