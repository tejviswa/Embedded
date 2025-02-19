

int mstrstr(char str[],char sub[])
{
	int i,j,k,l,le,c=0;
	for(i=0;sub[i]!='\0';i++);
	le=i;
	
	for(i=0;str[i]!='\0';i++)
	{
		j=0;
		if(sub[j]==str[i])
		{
			c++;
			for(k=i+1,l=j+1;l<le;k++,l++)
			{
				if(sub[l]==str[k])
					c++;
			}
			
			}
		j++;
		}
	if(c==le)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}



